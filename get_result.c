/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_result.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 12:33:43 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/31 15:56:33 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester_header.h"

static t_result	*create_new_node(char *line)
{
	t_result	*temp;

	temp = malloc(sizeof(t_result));
	if (temp != NULL)
	{
		temp->line = line;
		temp->next = NULL;
	}
	return (temp);
}

void	get_result(t_result **result, int fd, char *(*f)(int))
{
	char		*line;
	t_result	*temp;

	line = f(fd);
	*result = create_new_node(line);
	temp = *result;
	while (true)
	{
		line = f(fd);
		if (line == NULL)
			break ;
		temp->next = create_new_node(line);
		temp = temp->next;
	}
}

static void	print_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\n')
		{
			ft_putstr_fd(BLUE, 1);
			write(1, "\\n", 2);
			ft_putstr_fd(RESET, 1);
		}
		else
			write(1, &(str[i]), 1);
	}
}

void	print_results(t_result *stdresult, t_result *userresult)
{
	t_result	*temp;
	int			i;

	temp = stdresult;
	i = 1;
	printf(YELLOW "Imagination:\n");
	printf("\n--------------------\n" RESET);
	while (stdresult != NULL)
	{
		printf("line [%d]:\t", i++);
		fflush(stdout);
		print_line(stdresult->line);
		write(1, "\n", 1);
		stdresult = stdresult->next;
	}
	printf(YELLOW "\n--------------------\n" RESET);
	i = 1;
	printf(GREEN "Reality:\n");
	printf("\n--------------------\n" RESET);
	while (userresult != NULL)
	{
		printf("line [%d]:\t", i++);
		fflush(stdout);
		if (strcmp(userresult->line, temp->line) != 0)
			ft_putstr_fd(RED, 1);
		print_line(userresult->line);
		write(1, "\n", 1);
		ft_putstr_fd(RESET, 1);
		userresult = userresult->next;
		temp = temp->next;
	}
	printf(GREEN "\n--------------------\n" RESET);
}

int	check_correct(t_result *stdresult, t_result *userresult)
{
	int	std_len = 0;
	int	user_len = 0;
	t_result	*std_temp = stdresult;
	t_result	*user_temp = userresult;

	while (std_temp != NULL)
	{
		std_len++;
		std_temp = std_temp->next;
	}
	while (user_temp != NULL)
	{
		user_len++;
		user_temp = user_temp->next;
	}
	if (std_len != user_len)
		return (0);
	while (stdresult != NULL)
	{
		if (strcmp(stdresult->line, userresult->line) != 0)
			return (0);
		stdresult = stdresult->next;
		userresult = userresult->next;
	}
	return (1);
}

void	free_results(t_result *stdresult, t_result *userresult)
{
	t_result	*temp;

	while (stdresult != NULL)
	{
		temp = stdresult->next;
		free(stdresult->line);
		free(stdresult);
		stdresult = temp;
	}
	while (userresult != NULL)
	{
		temp = userresult->next;
		free(userresult->line);
		free(userresult);
		userresult = temp;
	}
}
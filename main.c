/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:29:06 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/06 16:36:31 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester_header.h"

static void	init_status(int ac, char **av, t_status *status)
{

	status->tests_runned = 0;
	status->current_test = 0;
	status->tests_correct = 0;
	status->mand = 0;
	status->bonus = 0;
	if (ac == 1 || (ac == 2 && strcmp(av[1], "m") == 0))
		status->mand = 1;
	else if (ac == 2 && strcmp(av[1], "b") == 0)
		status->bonus = 1;
	else if (ac == 2 && strcmp(av[1], "a") == 0)
	{
		status->mand = 1;
		status->bonus = 1;
	}
	else
	{
		printf("Invalid flag\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_status	*status;
	int			runned;
	int			correct;

	if (ac > 2)
	{
		printf("Too many flags\n");
		exit(1);
	}
	status = malloc(sizeof(t_status));
	init_status(ac, av, status);
	run_tests(status);
	correct = status->tests_correct;
	runned = status->tests_runned;
	printf("\n%d tests got correct over %d tests\n", correct, runned);
	printf("Score: ");
	if (status->tests_correct * 100 / status->tests_runned >= 50)
		printf(GREEN);
	else
		printf(RED);
	printf("%d%%\n", status->tests_correct * 100 / status->tests_runned);
	ft_putstr_fd(RESET, 1);
	free(status);
}
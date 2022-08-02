/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:28:18 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/02 17:19:40 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HEADER_H
# define TESTER_HEADER_H

/*Built in headers*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <stdarg.h>

/*Colours*/
# define BOLD		"\x1b[1m"
# define RED		"\x1b[31m"
# define GREEN 		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

/*Constants*/
# define READ 0
# define WRITE 1
# define BUFFER 1000
# define LEAKS_ERROR 4242

typedef struct s_status {
	int		tests_runned;
	int		current_test;
	int		tests_correct;
	int		mand;
	int		bonus;
}	t_status;

typedef struct s_result {
	char	*line;
	struct s_result	*next;
}	t_result;

char	*get_next_line(int fd);
char	*gnl(int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);
void	handle_signals(int sig);
char	*get_file_content(int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	run_tests(t_status *status);
int		check_result(t_status *status, int exit_sig, int correct);
void	free_results(t_result *stdresult, t_result *userresult);
int		check_correct(t_result *stdresult, t_result *userresult);
void	print_results(t_result *stdresult, t_result *userresult);
void	get_result(t_result **result, int fd, char *(*f)(int));
void	get_bonus_result(t_result **result, int *fds, int files, char *(*f)(int));
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);


#endif
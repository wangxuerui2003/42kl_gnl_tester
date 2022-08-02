/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:02:50 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/02 18:02:38 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester_header.h"

void	bonus_test(t_status *status, int files, ...)
{
	int					do_test;
	int					timeout_checker;
	int					result_pipe[2];
	struct sigaction	sa;
	int					wstatus;
	t_result			*stdresult = NULL;
	t_result			*userresult = NULL;
	int					exitpid;
	int					exit_sig;
	int					correct;
	va_list				args;
	char				*(filenames[files]);
	int					fds[files];

	va_start(args, files);
	ft_putstr_fd("\n", 1);
	for (int i = 0; i < files; i++)
	{
		filenames[i] = va_arg(args, char *);
		ft_putstr_fd(filenames[i], 1);
		ft_putstr_fd(", ", 1);
	}
	va_end(args);
	ft_putstr_fd("\n", 1);
	status->current_test++;
	sa.sa_handler = &handle_signals;
	sa.sa_flags = SA_RESTART;
	pipe(result_pipe);
	do_test = fork();
	if (do_test == 0)
	{
		close(result_pipe[READ]);
		sigaction(SIGSEGV, &sa, NULL);
		sigaction(SIGABRT, &sa, NULL);
		for (int i = 0; i < files; i++)
			fds[i] = open(filenames[i], O_RDONLY);
		int err = open("user_err.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(err, STDERR_FILENO);
		get_bonus_result(&stdresult, fds, files, &gnl);
		for (int i = 0; i < files; i++)
			close(fds[i]);
		for (int i = 0; i < files; i++)
			fds[i] = open(filenames[i], O_RDONLY);
		get_bonus_result(&userresult, fds, files, &get_next_line);
		for (int i = 0; i < files; i++)
			close(fds[i]);
		if (check_correct(stdresult, userresult) == 0)
			print_results(stdresult, userresult);
		ft_putnbr_fd(check_correct(stdresult, userresult), result_pipe[WRITE]);
		close(result_pipe[WRITE]);
		free_results(stdresult, userresult);
		free(status);
		close(err);
		exit(0);
	}
	exit_sig = 0;
	timeout_checker = fork();
	if (timeout_checker == 0)
	{
		sleep(100);
		exit(0);
	}
	exitpid = wait(&wstatus);
	if (exitpid == do_test)
	{
		kill(timeout_checker, SIGKILL);
		wait(NULL);
		exit_sig = WEXITSTATUS(wstatus);
	}
	else if (exitpid == timeout_checker)
	{
		kill(do_test, SIGKILL);
		wait(&wstatus);
		exit_sig = SIGKILL;
	}
	if (exit_sig == 0)
	{
		int	err_fd = open("user_err.txt", O_RDONLY);
		char	*leaks_info = get_file_content(err_fd);
		if (ft_strnstr(leaks_info, "current: ", strlen(leaks_info)) != NULL
			&& ft_strnstr(leaks_info, "current: 0", strlen(leaks_info)) == NULL)
			exit_sig = LEAKS_ERROR;
		free(leaks_info);
		close(err_fd);
	}
	close(result_pipe[WRITE]);
	char	temp;
	read(result_pipe[READ], &temp, 1);
	correct = temp - 48;
	status->tests_correct += check_result(status, exit_sig, correct);
	status->tests_runned++;
	close(result_pipe[READ]);
}

void	basic_test(t_status *status, char *filename)
{
	int					do_test;
	int					timeout_checker;
	int					fd;
	int					fd2;
	int					result_pipe[2];
	struct sigaction	sa;
	int					wstatus;
	t_result			*stdresult = NULL;
	t_result			*userresult = NULL;
	int					exitpid;
	int					exit_sig;
	int					correct;

	printf("\n%s\n", filename);
	status->current_test++;
	sa.sa_handler = &handle_signals;
	sa.sa_flags = SA_RESTART;
	pipe(result_pipe);
	do_test = fork();
	if (do_test == 0)
	{
		close(result_pipe[READ]);
		sigaction(SIGSEGV, &sa, NULL);
		sigaction(SIGABRT, &sa, NULL);
		fd = open(filename, O_RDONLY);
		fd2 = open(filename, O_RDONLY);
		int err = open("user_err.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(err, STDERR_FILENO);
		get_result(&stdresult, fd, &gnl);
		get_result(&userresult, fd2, &get_next_line);
		if (check_correct(stdresult, userresult) == 0)
			print_results(stdresult, userresult);
		ft_putnbr_fd(check_correct(stdresult, userresult), result_pipe[WRITE]);
		close(fd);
		close(fd2);
		close(result_pipe[WRITE]);
		free_results(stdresult, userresult);
		free(status);
		close(err);
		exit(0);
	}
	exit_sig = 0;
	timeout_checker = fork();
	if (timeout_checker == 0)
	{
		sleep(1);
		exit(0);
	}
	exitpid = wait(&wstatus);
	if (exitpid == do_test)
	{
		kill(timeout_checker, SIGKILL);
		wait(NULL);
		exit_sig = WEXITSTATUS(wstatus);
	}
	else if (exitpid == timeout_checker)
	{
		kill(do_test, SIGKILL);
		wait(&wstatus);
		exit_sig = SIGKILL;
	}
	if (exit_sig == 0)
	{
		int	err_fd = open("user_err.txt", O_RDONLY);
		char	*leaks_info = get_file_content(err_fd);
		if (ft_strnstr(leaks_info, "current: ", strlen(leaks_info)) != NULL
			&& ft_strnstr(leaks_info, "current: 0", strlen(leaks_info)) == NULL)
			exit_sig = LEAKS_ERROR;
		free(leaks_info);
		close(err_fd);
	}
	close(result_pipe[WRITE]);
	char	temp;
	read(result_pipe[READ], &temp, 1);
	correct = temp - 48;
	status->tests_correct += check_result(status, exit_sig, correct);
	status->tests_runned++;
	close(result_pipe[READ]);
}

int	check_result(t_status *status, int exit_sig, int correct)
{
	(void)status;
	if (exit_sig != 0 && exit_sig != LEAKS_ERROR)
	{
		ft_putstr_fd(RED, 1);
		if (exit_sig == SIGSEGV)
			ft_putstr_fd("SEG_FAULT! " RESET, 1);
		else if (exit_sig == SIGKILL)
			ft_putstr_fd("TIMEOUT! (more than 1 second) " RESET, 1);
		else if (exit_sig == SIGABRT)
			ft_putstr_fd("SIGABRT! " RESET, 1);
		else
			ft_putstr_fd("Unknown Crash! " RESET, 1);
		return (0);
	}
	if (correct == 1)
	{
		ft_putstr_fd(GREEN "OK! " RESET, STDOUT_FILENO);
		if (exit_sig == LEAKS_ERROR)
		{
			ft_putstr_fd(RED "but LEAKS!" RESET, 1);
			return (0);
		}
		return (1);
	}
	ft_putstr_fd(RED "KO! " RESET, STDOUT_FILENO);
	if (exit_sig == LEAKS_ERROR)
	{
		ft_putstr_fd(RED "and LEAKS!" RESET, 1);
		sleep(1);
		return (0);
	}
	sleep(1);
	return (0);
}

void	run_tests(t_status *status)
{
	char	filename[17];
	char	filename2[17];
	char	filename3[17];
	int		i;
	printf(MAGENTA"MANDATORY\n"RESET);
	sleep(1);
	printf("Basic Tests: \n");

	basic_test(status, "nl_at_EOF/Arrow_S2.txt");
	basic_test(status, "nl_at_EOF/Harry_but_nothing.txt");
	basic_test(status, "nl_at_EOF/Harry_Potter.txt");
	basic_test(status, "nl_at_EOF/sean.txt");
	basic_test(status, "no_nl_at_EOF/Arrow_S2.txt");
	basic_test(status, "no_nl_at_EOF/Harry_but_nothing.txt");
	basic_test(status, "no_nl_at_EOF/Harry_Potter.txt");
	basic_test(status, "no_nl_at_EOF/sean.txt");

	sleep(1);
	printf("Random Tests: \n");
	i = 0;
	while (++i <= 500)
	{
		sprintf(filename, "%s%d", "random_tests/", i);
		basic_test(status, filename);
	}

	if (status->bonus == 0)
		return ;

	ft_putstr_fd(CYAN"\nBONUS\n"RESET, 1);
	bonus_test(status, 2, "nl_at_EOF/Arrow_S2.txt", "nl_at_EOF/Harry_but_nothing.txt");
	sleep(1);
	i = 0;
	while (++i <= 500)
	{
		sprintf(filename, "%s%d", "random_tests/", rand() % 500);
		sprintf(filename2, "%s%d", "random_tests/", rand() % 500);
		sprintf(filename3, "%s%d", "random_tests/", rand() % 500);
		bonus_test(status, 3, filename, filename2, filename3);
	}
}
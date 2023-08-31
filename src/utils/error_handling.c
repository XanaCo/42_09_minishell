/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/31 09:40:02 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	error_handling_custom_2(char *str, int error);
static void	error_handling_custom_3(char *str, int error);
static void	error_handling_custom_4(char *str, int error);

/*
A custom error handling for some messages that cannot be printed with errno 
		printf("ERROR = %d\n", g_error_value);
*/
void	error_handling_custom(char *str, int error)
{
	if (error == -1)
	{
		g_error_value = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (error == -2)
	{	
		g_error_value = 2;
		ft_putstr_fd("minishell: syntax error next to unexpected token\n", 2);
	}
	else if (error == -3)
	{
		g_error_value = 2;
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putchar_fd(str[0], 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	else
		error_handling_custom_2(str, error);
}

/*
Just the continuation of the error handling custom 1. 
(The Norm at 42 doesn't allow functions over 25 lines)
*/
static void	error_handling_custom_2(char *str, int error)
{
	if (error == -4)
	{
		g_error_value = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (error == -5)
	{
		g_error_value = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": too many arguments\n", 2);
	}
	else if (error == -6)
	{
		g_error_value = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("export / unset: not valid syntax name for variable: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else
		error_handling_custom_3(str, error);
}

/*
*/
static void	error_handling_custom_3(char *str, int error)
{
	if (error == -7)
	{
		g_error_value = 127;
		ft_putstr_fd("minishell: syntax error near unexpected token: \
`<<' or `>>'\n", 2);
	}
	if (error == -8)
	{
		g_error_value = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is a directory:\n", 2);
	}
	if (error == -9)
	{
		g_error_value = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	else
		error_handling_custom_4(str, error);
}

/*
*/
static void	error_handling_custom_4(char *str, int error)
{
	if (error == -10)
	{
		g_error_value = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

/*
*/
int	cd_error_msg(int error)
{
	if (error == 1)
		error_handling_custom("cd", -5);
	if (error == 2)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	if (error == 3)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	if (error == 4)
		ft_putstr_fd("minishell: No such file or directory\n", 2);
	return (1);
}

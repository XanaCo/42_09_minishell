/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 21:11:49 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Get_prompt sends back the cute colored prompt,
changing it depending on the global error value
*/
char	*get_prompt(void)
{
	char	*p;

	if (g_error_value)
		p = "\001\033[1;91m\002x mini\001\033[0m\033[0;93m\002shell : \001\033[0m\002";
	else
		p = "\001\033[1;93m\002~ mini\001\033[0m\033[0;93m\002shell : \001\033[0m\002";
	return (p);
}

/*
This function prints the minishel title in ASCII art :)
*/
void	print_title(void)
{
	printf("\033[0;93m");
	printf("\n");
	printf(" ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████");
	printf("  ██▓     ██▓\n");
	printf(" ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀");
	printf(" ▓██▒    ▓██▒    \n");
	printf(" ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███");
	printf("   ▒██░    ▒██░    \n");
	printf(" ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█");
	printf("  ▄ ▒██░    ▒██░    \n");
	printf(" ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████");
	printf("▒░██████▒░██████▒\n");
	printf(" ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ");
	printf("░░ ▒░▓  ░░ ▒░▓  ░\n");
	printf(" ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ");
	printf("░░ ░ ▒  ░░ ░ ▒  ░\n");
	printf(" ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░  ");
	printf("   ░ ░     ░ ░   \n");
	printf("        ░    ░           ░  ░        ░   ░  ░  ░   ░  ░");
	printf("    ░  ░    ░  ░\n");
	printf("\n");
	printf("\033[0m");
}

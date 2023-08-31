/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:48:38 by ancolmen          #+#    #+#             */
/*   Updated: 2023/04/25 18:29:10 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(void **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

// changed char to void in function param
// also created this shorter pointer version (to verify)
//
// void	ft_free_matrix(void **strs)
// {
// 	if (!strs)
// 		return ;
// 	while (*(strs))
// 		free(*(strs++));
// 	free(strs);
// }

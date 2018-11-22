/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:24:51 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 04:43:06 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>

int			ft_pchar(int nb)
{
	return (write(STDOUT_FILENO, &nb, 1));
}

void	delete_down(void)
{
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
}

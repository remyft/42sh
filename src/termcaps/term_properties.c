/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 03:54:40 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 20:30:39 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "libft.h"
#include "shell_term.h"

void		term_restore(struct termios save)
{
	if (tcsetattr(0, TCSANOW, &save) == -1)
	{
		ft_putendl("Fatal error: unable to restore the term attributes.");
		exit(2);
	}
}

void		define_new_term(struct termios *save)
{
	struct termios	termios;

	if (tcgetattr(0, save) != 0)
	{
		ft_putendl("Fatal error: unable to get term attributes.");
		exit(2);
	}
	ft_memcpy(&termios, save, sizeof(termios));
	termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSANOW, &termios)) == -1)
	{
		ft_putendl("Fatal error: unable to set the new term attributes.");
		exit(2);
	}
}

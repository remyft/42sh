/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:59:17 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/29 23:02:35 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "libft.h"
#include "shell_lib.h"
#include "dirent.h"

static void	deal_access(t_line *line, char *file)
{
	char	*tmp;
	char	*stmp;
	char	*ptr;

	stmp = sh_strrchr(line->curr->buff, ' ') + 1;
	if ((ptr = ft_strrchr(stmp, '/')) && ft_strchr(line->curr->buff, '~'))
	{
		tmp = replace_tilde(stmp, getenv("HOME"));
		stmp = ft_strndup(tmp, ft_strrchr(tmp, '/') - tmp + 1);
	}
	else if (ptr)
		stmp = ft_strndup(stmp, ptr - stmp);
	else
		stmp = ft_strdup("");
	stmp = ft_strjoinfree(stmp, file, 1);
	if (!access(stmp, X_OK))
		ft_putstr(RED);
	free(stmp);
}

void		deal_type(unsigned int type, t_line *line, char *file)
{
	static char			*col[] = {CYAN, YELLOW, MAGENTA, BLUE, ERROR};
	static unsigned int	ttab[] = {DT_DIR, DT_CHR, DT_LNK, DT_BLK, DT_UNKNOWN};
	int					i;

	i = -1;
	while (++i < (int)(sizeof(col) / sizeof(*col)))
		if (type == ttab[i])
			return (ft_putstr(col[i]));
	if (type == DT_REG)
		deal_access(line, file);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fieldsplit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:31:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/19 22:49:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

static char		check_quote(char c, char quote)
{
	if (quote == c)
		return (0);
	if (quote == 0)
		return (c);
	return (quote);
}

static char		*check_word(char *str, const char *ifs, t_ret *ret)
{
	char		quote;

	quote = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			quote = check_quote(*str, quote);
		else if (*str == '\\')
		{
			if (param_addchar(*str++, ret))
				return (NULL);
		}
		else if (quote == 0 && ft_strchr(ifs, *str))
			return (str);
		if (param_addchar(*str, ret))
			return (NULL);
		str++;
	}
	return (str);
}

static int		get_word(char *str, const char *ifs, t_ret **ret)
{
	size_t		i;

	i = 0;
	while (*str)
	{
		while (ft_strchr(ifs, *str))
			str++;
		if (!*str || !(str = check_word(str, ifs, *ret)) || !*str)
			break ;
		if (!((*ret)->next = ft_memalloc(sizeof(**ret))))
			return (ERR_MALLOC);
		*ret = (*ret)->next;
	}
	return ((str) ? ERR_NONE : ERR_MALLOC);
}

static void		ifs_whitespace(char *ifsws, const char *ifs)
{
	size_t		i;

	i = 0;
	ft_memset(ifsws, 0, 4);
	while (*ifs)
	{
		if (ft_strchr(IFS_SEPARATORS, *ifs) && !ft_strchr(ifsws, *ifs))
			ifsws[i] = *ifs;
		ifs++;
	}
}

int				expand_fieldsplit(t_ret **ret, const char *ifs)
{
	char		ifsws[4];
	char		*ptr;
	int			error;

	ifs_whitespace(ifsws, ifs);
	ptr = (*ret)->word;
	while (ft_strchr(ifsws, *ptr))
		ptr = ft_strcpy(ptr, ptr + 1);
	ptr = (*ret)->word + ft_strlen((*ret)->word) - 1;
	while (ft_strchr(ifsws, *ptr) && *(ptr - 1) != '\\')
		*ptr-- = '\0';
	ptr = (*ret)->word;
	ft_memset(*ret, 0, sizeof(char *) + sizeof(size_t) + sizeof(size_t));
	error = get_word(ptr, ifs, ret);
	free(ptr);
	return (error);
}

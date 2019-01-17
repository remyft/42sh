/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_null_assign.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 02:29:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/16 23:22:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "free_env.h"
#include "expansion_word.h"
#include "expansion_errors.h"
#include "expansion_action.h"
#include "expansion_lib.h"

static void		word_fill_str(char **dst, char *cpy, t_ret *word)
{
	ft_strcpy(*dst, cpy);
	ft_strcat(*dst, "=");
	if (word->substitute)
		ft_strcat(*dst, word->substitute);
	else if (word->word)
		ft_strcat(*dst, word->word);
}

static int		replace_env_value(t_ret *parameter, t_ret *word, t_exp *param)
{
	char		*name;
	char		**ret;
	char		*save;
	size_t		len;

	name = parameter->word + parameter->brace + parameter->hash + 1;
	if (!(ret = exp_getnenvaddr(name, param->e->public_env)))
		if (!(ret = exp_getnenvaddr(name, param->e->private_env)))
			if (!(ret = exp_newenv(&param->e->private_env)))
				return (ERR_MALLOC);
	save = *ret;
	len = ft_strlen(name) + 2;
	len += (word->substitute) ?
		ft_strlen(word->substitute) : ft_strlen(word->word);
	if (!(*ret = ft_memalloc(len)))
	{
		*ret = save;
		return (ERR_MALLOC);
	}
	free(save);
	word_fill_str(ret, name, word);
	return (ERR_NONE);
}

int				word_null_assign(t_ret *subs, t_ret *para, t_exp *param)
{
	if (para->substitute && para->substitute[0])
		return (ERR_NONE);
	if (replace_env_value(para, subs, param) != ERR_NONE)
		return (ERR_MALLOC);
	expand_free_t_ret(para, 0);
	ft_memcpy(para, subs, sizeof(*para));
	ft_memset(subs, 0, sizeof(*subs));
	return (ERR_NONE);
}

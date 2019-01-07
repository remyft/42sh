/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 00:07:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/07 19:54:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "quote_removal.h"

static void		remove_squote(char *str, char *quote, size_t *i)
{
	if (!*quote)
	{
		*quote = str[*i];
		ft_strcpy(str + *i, str + *i + 1);
	}
	else if (*quote == str[*i])
	{
		*quote = 0;
		ft_strcpy(str + *i, str + *i + 1);
	}
}

static void		remove_dquote(char *str, char *quote, size_t *i)
{
	if (!*quote)
	{
		*quote = str[*i];
		ft_strcpy(str + *i, str + *i + 1);
	}
	else if (*quote == str[*i])
	{
		*quote = 0;
		ft_strcpy(str + *i, str + *i + 1);
	}
}

static void		remove_back(char *str, char *quote, size_t *i)
{
	if (*quote == '\'')
		return ;
	ft_strcpy(str + *i, str + *i + 1);
	*i += 1;
}

void			quote_removal(t_ret *ret)
{
	static t_q_removal	removal[] = {
		{ '\'', remove_squote }, { '"', remove_dquote }, { '\\', remove_back },
	};
	size_t				i;
	char				quote;
	size_t				j;

	quote = 0;
	while (ret)
	{
		i = 0;
		while (ret && ret->word && ret->word[i])
		{
			j = 0;
			while (j < sizeof(removal) / sizeof(removal[0]))
			{
				if (removal[j].value == ret->word[i])
					removal[j].handler(ret->word, &quote, &i);
				j++;
			}
			i++;
		}
		ret = ret->next;
	}
}

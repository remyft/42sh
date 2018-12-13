/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 04:02:23 by gbourgeo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/12/13 15:16:08 by gbourgeo         ###   ########.fr       */
=======
/*   Updated: 2018/12/13 16:56:06 by rfontain         ###   ########.fr       */
>>>>>>> 4137f821b52167f44df66f9e33c3d98e0baeea9d
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static size_t	my_strlen(const char *dst)
{
	if (!dst)
		return (0);
	return (ft_strlen(dst));
}

static char		*my_strcpy(char *dst, const char *src)
{
	if (!dst)
		return (NULL);
	return (ft_strcpy(dst, src));
}

static char		*my_strnjoin(char *dst, const char *src, size_t n)
{
	char		*ret;

	if (n == 0)
		return (dst);
	if (!(ret = ft_memalloc(my_strlen(dst) + n + 1)))
		return (dst);
	if (dst)
		my_strcpy(ret, dst);
	ft_strncat(ret, src, n);
	if (dst)
		free(dst);
	return (ret);
}

static char		*my_strnchr(const char *s, int c, size_t len)
{
<<<<<<< HEAD
	size_t		i;
=======
	size_t        i;
>>>>>>> 4137f821b52167f44df66f9e33c3d98e0baeea9d

	i = 0;
	while (i < len)
	{
		if (s[i] == c)
<<<<<<< HEAD
			return (char *)((s + i));
=======
			return ((char*)(s + i));
>>>>>>> 4137f821b52167f44df66f9e33c3d98e0baeea9d
		i++;
	}
	return (NULL);
}
<<<<<<< HEAD

=======
>>>>>>> 4137f821b52167f44df66f9e33c3d98e0baeea9d
char			*expand_word(const char *buff, t_token *token)
{
	size_t		i;
	size_t		start;
	char		*ret;
	t_token		*sub;

	i = token->head;
	start = i;
	ret = NULL;
	sub = token->subs;
	while (i < token->tail)
	{
		if (buff[i] == '\''
				&& (!token->quote || token->quote & SINGLE_QUOTE))
		{
			if (!my_strnchr(buff + i + 1, '\'', token->tail - i) && !(token->quote & SINGLE_QUOTE))
			{
				i++;
				continue ;
			}
			ret = my_strnjoin(ret, buff + start, i - start);
			start = i + 1;
			if (!token->quote)
				token->quote |= SINGLE_QUOTE;
			else
				token->quote &= ~SINGLE_QUOTE;
		}
		else if (buff[i] == '"'
				&& (!token->quote || token->quote & DOUBLE_QUOTE))
		{
<<<<<<< HEAD
			if (!my_strnchr(buff + i, '"', token->tail - i))
				continue ;
=======
			if (!my_strnchr(buff + i + 1, '"', token->tail - i) && !(token->quote & DOUBLE_QUOTE))
			{
				i++;
				continue ;
			}
>>>>>>> 4137f821b52167f44df66f9e33c3d98e0baeea9d
			ret = my_strnjoin(ret, buff + start, i - start);
			start = i + 1;
			if (!token->quote)
				token->quote |= DOUBLE_QUOTE;
			else
				token->quote &= ~DOUBLE_QUOTE;
		}
		else if (buff[i] == '\\'
				&& (!token->quote || token->quote & DOUBLE_QUOTE))
		{
			ret = my_strnjoin(ret, buff + start, i - start);
			start = i + 1;
			i++;
		}
		else if (buff[i] == '$' && !(token->quote & SINGLE_QUOTE))
		{
			ret = my_strnjoin(ret, buff + start, i - start);
			if (sub)
			{
				ret = my_strnjoin(ret, buff + sub->head, sub->tail - sub->head);
				start = sub->tail;
				i = start - 1;
				sub = sub->next;
			}
		}
		i++;
	}
	ret = my_strnjoin(ret, buff + start, i - start);
	return (ret);
}

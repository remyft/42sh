/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:42:11 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/06 21:44:23 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"

void	export_print(char **exported, char **public_env)
{
	int		i;
	char	**sorted;
	int		len;
	char	*sub;

	i = 0;
	sorted = clone_2_arr(exported, public_env);
	export_sort(&sorted);
	while (sorted[i])
	{
		if ((len = var_name_len(sorted[i])) > 0)
		{
			sub = ft_strsub(sorted[i], 0, len + 1);
			ft_printf("declare -x %s", sub);
			free(sub);
		}
		else
			ft_printf("declare -x %s", sorted[i]);
		if (len > 0)
			ft_printf("\"%s\"\n", &(sorted[i])[len + 1]);
		(len == -1) ? ft_printf("\"\"\n") : ft_printf("\n");
		i++;
	}
	sh_freetab(&sorted);
}

void	export_sort(char ***sorted)
{
	int		sort;
	int		i;
	char	*tmp;
	int		count;

	count = count_strarr(*sorted) - 1;
	sort = 0;
	tmp = NULL;
	while (!sort)
	{
		i = 0;
		sort = 1;
		while (i < count)
		{
			if (ft_strcmp((*sorted)[i], (*sorted)[i + 1]) > 0)
			{
				sort = 0;
				tmp = (*sorted)[i];
				(*sorted)[i] = (*sorted)[i + 1];
				(*sorted)[i + 1] = tmp;
			}
			i++;
		}
	}
}

char	**clone_arr(char **arr)
{
	char	**clone;
	int		i;

	i = 0;
	clone = ft_memalloc(sizeof(char **) * (count_strarr(arr) + 2));
	while (arr[i])
	{
		clone[i] = ft_strdup(arr[i]);
		i++;
	}
	clone[i] = NULL;
	return (clone);
}

char	**clone_2_arr(char **arr1, char **arr2)
{
	int		i;
	int		j;
	char	**clone;

	i = 0;
	j = 0;
	clone = ft_memalloc(sizeof(char **) *
			(count_strarr(arr1) + count_strarr(arr2) + 2));
	while (arr1[i])
	{
		clone[j] = ft_strdup(arr1[i]);
		printf("arr1 clone[%d] = %s\n", j, clone[j]);
		i++;
		j++;
	}
	i = 0;
	while (arr2[i])
	{
		clone[j] = ft_strdup(arr2[i]);
		printf("arr2 clone[%d] = %s\n", j, clone[j]);
		i++;
		j++;
	}
	clone[j] = NULL;
	return (clone);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:16:17 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/25 22:55:53 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"
#include "shell_lib.h"


int		builtin_test(t_execute *exec, t_s_env *e)
{
	int ret;

	(void)e;
	ret = parse_test_input(exec->cmd, e);
	return (ret);
}

int		parse_test_input(char **cmd, t_s_env *e)
{
	int		size;

	(void)e;
	size = sh_tablen((const char **)cmd);
	if (size == 1)
		return (1);
	if (size == 2)
		return ((cmd[1][0] != '\0') ? 0 : 1);
	if (size == 5)
	{
		ft_dprintf(2, "42sh: test: too many arguments\n");
		return (2);
	}
	if (size == 3)
	{
		if (ft_strcmp(cmd[1], "!") == 0)
			return (cmd[2][0] == '\0' ? 0 : 1);
		return (test_two_arg(cmd[1], cmd[2]));
	}
	//if (cmd[1] && cmd[2] && cmd[3])
	//	return parse_test_three_arg(cmd[1], cmd[2], cmd[3])*
	return (0);	
}

int		test_two_arg(char *arg1, char *arg2)
{
	(void)arg2;
	if (arg1[0] != '-' || ft_strlen(arg1) != 2)
	{
		ft_dprintf(2, "42sh: test: %s: unary operator expected\n", arg1);
		return (2);
	}
	else
		return (test_two_arg_exec(arg1, arg2));
}

int		test_two_arg_exec(char *arg1, char *arg2)
{
	static t_operators   operators[] = {
	OPERATOR_B, OPERATOR_C, OPERATOR_D, OPERATOR_E, OPERATOR_F, OPERATOR_G,
	OPERATOR_LL, OPERATOR_P, OPERATOR_R, OPERATOR_SS, OPERATOR_S, OPERATOR_U,
	OPERATOR_W, OPERATOR_X, OPERATOR_Z,
	};
    size_t              i;

	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		if (!ft_strcmp(operators[i].name, arg1))
			return (operators[i].handler(arg2));
		i++;
	}
	ft_dprintf(2, "42sh: test: %s: unary operator expected\n", arg1);
	return (2);
}

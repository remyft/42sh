/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/26 23:35:15 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		cmp_strpart(char *src, char *str, int *beg)
{
	int i;

	i = 0;
	while (src[i] && src[i] == str[*beg] && src[i] != '=')
	{
		i++;
		*beg += 1;
	}
	if (src[i] == '=')
		if (!str[*beg] || !ft_isalnum(str[*beg]))
			return (i);
	return (0);
}

char	*test_var(char **env, char *cmd)
{
	int		beg;
	int		end;
	int		to_cp;
	int		i;
	char	*ret;

	beg = 0;
	while (cmd[beg] != '$')
		beg++;
	beg++;
	i = 0;
	while (env[i])
	{
		end = beg;
		if ((to_cp = cmp_strpart(env[i], cmd, &end)))
		{
			ret = ft_strnew(to_cp + 2);
			ret[0] = '$';
			ft_strncpy(ret + 1, env[i], to_cp);
			ret[to_cp + 1] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int		get_var(char **env, char **cmd)
{
	int		i;
	char	*tmp;
	char	*var;
	char	*rep;

	i = -1;
	while (cmd[++i])
		if (ft_occuc(cmd[i], '$'))
		{
			if (!(tmp = test_var(env, cmd[i])))
			{
				ft_putend(ft_strstr(cmd[i], "$"), " : Undefined variable.\n");
				return (0);
			}
			else
			{
				var = ft_strdup(cmd[i]);
				free(cmd[i]);
				cmd[i] = replace_str(var, tmp, (rep = get_env(env, &tmp[1])));
				free(tmp);
			}
		}
		else if (cmd[i][0] == '~')
		{
			tmp = get_env(env, "HOME");
			free(cmd[i]);
			cmd[i] = ft_strdup(tmp);
			free(tmp);
		}
	return (1);
}

static void sig_hdlr(int sig)
{
	(void)sig;
}

int		main(__unused int ac, __unused char **av, char **ep)
{
	char	*line;
	char	**env;
	int		i;
	char	**parse;
	char	**cmd;
	char	prompt[4097];
	char	tmp[10];
	struct termios	save;
	int		nb_read;
	char	buff[8193];
	int		index;
	t_hist	*curr;
	char	*term;
	char	buff_tmp[8194];
	int		j;
	t_tree	*bin;
	t_tree	*files;
	int		put;
	char	*path;
	char	*save_path;

	i = 0;
	env = collect_env(ep);
	save_path = get_env(env, "PATH");
	line = NULL;
	term = getenv("TERM");
	tgetent(NULL, term);
	curr = NULL;
	create_hist(&curr);
	curr = curr->begin;
	define_new_term(&save);
	nb_read = 0;
	signal(SIGINT, &sig_hdlr);
	signal(SIGQUIT, &sig_hdlr);
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	ft_bzero(buff_tmp, 8194);
	bin = create_tree(env);
	files = create_file_tree();
	while (1)
	{
		ft_putstr(RESET);
		ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
		ft_putstr(WHITE);
		ft_bzero(buff, 8193);
		if (ft_strcmp((path = get_env(env, "PATH")), save_path) != 0)
		{
			free_tree(bin);
			bin = create_tree(env);
		}
		if (path)
			free(path);
		i = 0;
		index = 0;
		tmp[0] = '\0';
		while (tmp[0] != 10 && tmp[0] != -1)
		{
			put = 0;
		//		j = -1;
		//		while (++j < nb_read)
		//			ft_putnbend(tmp[j], "  ");
			if (i + (nb_read = read(0, tmp, 10)) < 8192) /* Type and cmd+V */
		//	{
				i = get_typing(&index, buff, tmp, nb_read, buff_tmp);
				//ft_bzero(buff_tmp, 8194);
		//	}
			if (nb_read == 1 && tmp[0] == 4 && !buff[0]) /* ctrl+D*/
				ft_exit2(save, &(curr->begin));
			else if (nb_read == 1 && tmp[0] == 3) /* ctrl+C */
				tmp[0] = ft_cancel(index, i, buff_tmp, &curr);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 65) /* up arrow */
				i = up_arrow(&index, buff, buff_tmp, &curr);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 66) /* down key */
				i = down_arrow(&index, buff, buff_tmp, &curr);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 67) /* right key*/
				right_arrow(&index, i);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 68) /* left key */
				left_arrow(&index);
			else if (nb_read == 1 && tmp[0] == 127) /* delete left */
				i = del_left(&index, buff, buff_tmp, curr);
			else if (nb_read == 4 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 51 && tmp[3] == 126) /* delete right */
				del_right(index, &i, buff);
			else if (nb_read == 1 && tmp[0] == 12) /* ctrl+L */
				ft_clear(buff, prompt);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 72) /* home */
				index = go_home(index);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 70) /* end */
				index = go_end(index, i);
			else if (nb_read == 1 && tmp[0] == 23) /* ctrl+W */
				next_word(&index, i, buff);
			else if (nb_read == 1 && tmp[0] == 2) /* ctrl+B */
				prev_word(&index, i, buff);
			else if (nb_read == 1 && tmp[0] == 9)
			{
				if (!ft_occuc(buff, ' '))
				{
					tputs(tgetstr("sc", NULL), 1, ft_pchar);
					tputs(tgetstr("do", NULL), 1, ft_pchar);
					tputs(tgetstr("cr", NULL), 1, ft_pchar);
					tputs(tgetstr("cd", NULL), 1, ft_pchar);
					if (!buff_tmp[8193])
					{
						ft_strcpy(buff_tmp, buff);
						buff_tmp[8193] = 1;
					}
					else
						put = 1;
						put_complet(buff_tmp, bin, buff, &put);
					tputs(tgetstr("rc", NULL), 1, ft_pchar);
					tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3), 1, ft_pchar);
					j = -1;
					while (++j < i)
						tputs(tgetstr("dc", NULL), 1, ft_pchar);
					ft_putstr(buff);
					index = ft_strlen(buff);
					i = index;
				}
				else
				{
					tputs(tgetstr("sc", NULL), 1, ft_pchar);
					tputs(tgetstr("do", NULL), 1, ft_pchar);
					tputs(tgetstr("cr", NULL), 1, ft_pchar);
					tputs(tgetstr("cd", NULL), 1, ft_pchar);
					if (!buff_tmp[8193])
					{
						ft_strcpy(buff_tmp, buff);
						buff_tmp[8193] = 1;
					}
					else
						put = 1;
						put_complet(buff_tmp, files, buff, &put);
					tputs(tgetstr("rc", NULL), 1, ft_pchar);
					tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3), 1, ft_pchar);
					j = -1;
					while (++j < i)
						tputs(tgetstr("dc", NULL), 1, ft_pchar);
					ft_putstr(buff);
					index = ft_strlen(buff);
					i = index;
				}
			}
		}
		ft_putchar('\n');
		if (buff[0] && tmp[0] != -1)
		{
			deal_commande(index, buff, buff_tmp, &curr);
		parse = NULL;
		parse = ft_strsplit(buff, ';');
		i = -1;
		while (parse && parse[++i])
		{
			cmd = ft_strsplit_ws(parse[i]);
			if (ft_strcmp(cmd[0], "cd") == 0)
			{
				free_tree(files);
				files = create_file_tree();
			}
			if (!(get_var(env, cmd)))
				continue ;
			deal_cmd(cmd, &env, &save);
			free_tab(&cmd);
		}
		if (parse)
			free_tab(&parse);
		}
	}
	return (0);
}

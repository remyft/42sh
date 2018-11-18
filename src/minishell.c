/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/18 20:26:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

#include "minishell.h"
#include "token.h"

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
	if (!env)
		return (0);
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

void	put_prompt(void)
{
	char	prompt[4097];

	ft_putstr(RESET);
	ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
	ft_putstr(WHITE);
}

int		inprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (ft_isprint(str[i]))
			return(1);
	return (0);
}

int		main(__unused int ac, __unused char **av, char **ep)
{
	char	*line;
	char	**env;
	int		i;
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
	t_tree	*tmp_files;
	int		put;
	char	*path;
	char	*save_path;
	t_st	*e_cmpl;
	DIR		*dir;
	char	*stmp;

	i = 0;
	e_cmpl = ft_memalloc(sizeof(t_st));
	env = collect_env(ep);
	save_path = get_env(env, "PATH");
	line = NULL;
	term = get_env(env, "TERM");
	tgetent(NULL, term);
	curr = NULL;
	create_hist(&curr, env);
	if (curr)
		curr = curr->begin;
	define_new_term(&save);
	nb_read = 0;
	signal(SIGINT, &sig_hdlr);
	signal(SIGQUIT, &sig_hdlr);
	tputs(tgetstr("cl", NULL), 1, &ft_pchar);
	ft_bzero(buff_tmp, 8194);
	bin = create_tree(env);
	files = create_file_tree(".");
	tmp_files = NULL;
	dir = NULL;
	while (1)
	{
		put_prompt();
		ft_bzero(buff, 8193);
		path = get_env(env, "PATH");
		if (path && ft_strcmp((path = get_env(env, "PATH")), save_path) != 0)
		{
			free_tree(bin);
			bin = create_tree(env);
		}
		if (path)
			free(path);
		i = 0;
		index = 0;
		tmp[0] = '\0';
		while ((tmp[0] != 10 && tmp[0] != -1) || *e_cmpl & COMPLETION)
		{
			put = 0;
			//			j = -1;
			//			while (++j < nb_read)
			//				ft_putnbend(tmp[j], "  ");
			if (i + (nb_read = read(0, tmp, 10)) < 8192) /* Type and cmd+V */
				//	{
				i = get_typing(&index, buff, tmp, nb_read, buff_tmp);
			//ft_bzero(buff_tmp, 8194);
			//	}
			if (tmp[0] == '/')
			{
				if (tmp_files)
					free_tree(tmp_files);
				tmp_files = NULL;
			}
			else if (nb_read == 1 && tmp[0] != 9)
			{
				if (files)
					reset_put(files);
				if (bin)
					reset_put(bin);
			}
			if (nb_read == 1 && tmp[0] == 4 && !buff[0]) /* ctrl+D*/
			{
				free_tree(files);
				ft_exit2(save, &curr);//&(curr->begin));
			}
			else if (nb_read == 1 && tmp[0] == 3) /* ctrl+C */
			{
				if (*e_cmpl & COMPLETION)
				{
					tputs(tgetstr("cr", NULL), 1, &ft_pchar);
					tputs(tgetstr("cd", NULL), 1, &ft_pchar);
					put_prompt();
					ft_bzero(buff, i);
					ft_strcpy(buff, buff_tmp);
					ft_bzero(buff_tmp, 8194);
					ft_putstr(buff);
					index = ft_strlen(buff);
					i = index;
					reset_put(files);
					reset_put(bin);
				}
				else
				{
					tmp[0] = ft_cancel(index, i, buff_tmp, &curr);
					if (tmp_files)
						free_tree(tmp_files);
					tmp_files = NULL;
				}
				*e_cmpl &= ~COMPLETION;
			}
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 65) /* up arrow */
				i = up_arrow(&index, buff, buff_tmp, &curr);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 66) /* down key */
				i = down_arrow(&index, buff, buff_tmp, &curr);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 67) /* right key*/
				right_arrow(&index, i);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 68) /* left key */
				left_arrow(&index);
			else if (nb_read == 1 && tmp[0] == 127) /* delete left */
			{
				if (*e_cmpl & COMPLETION)
				{
					tputs(tgetstr("sc", NULL), 1, &ft_pchar);
					tputs(tgetstr("do", NULL), 1, &ft_pchar);
					tputs(tgetstr("cr", NULL), 1, &ft_pchar);
					tputs(tgetstr("cd", NULL), 1, &ft_pchar);
					tputs(tgetstr("rc", NULL), 1, &ft_pchar);
					*e_cmpl &= ~COMPLETION;
					ft_bzero(buff_tmp, 8194);
				}
				else
					i = del_left(&index, buff, buff_tmp, curr);
			}
			else if (nb_read == 4 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 51 && tmp[3] == 126) /* delete right */
			{
				if (*e_cmpl & COMPLETION)
				{
					tmp[0] = 10;
					nb_read = 1;
				}
				else
					del_right(index, &i, buff);
			}
			else if (nb_read == 1 && tmp[0] == 12) /* ctrl+L */
				ft_clear(buff);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 72) /* home */
				index = go_home(index);
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 70) /* end */
				index = go_end(index, i);
			else if (nb_read == 1 && tmp[0] == 23) /* ctrl+W */
				next_word(&index, i, buff);
			else if (nb_read == 1 && tmp[0] == 2) /* ctrl+B */
				prev_word(&index, i, buff);
			else if (inprint(buff) && nb_read == 1 && tmp[0] == 9)
			{
				*e_cmpl |= COMPLETION;
				if (!ft_strchr(buff, ' '))
				{
					tputs(tgetstr("sc", NULL), 1, &ft_pchar);
					tputs(tgetstr("do", NULL), 1, &ft_pchar);
					tputs(tgetstr("cr", NULL), 1, &ft_pchar);
					tputs(tgetstr("cd", NULL), 1, &ft_pchar);
					if (!buff_tmp[8193])
					{
						ft_strcpy(buff_tmp, buff);
						buff_tmp[8193] = 1;
					}
					else
						put = 1;
					if (put_complet2(buff_tmp, bin, buff, &put))
						tmp[0] = 10;
					tputs(tgetstr("rc", NULL), 1, &ft_pchar);
					tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3), 1, &ft_pchar);
					j = -1;
					while (++j < i)
						tputs(tgetstr("dc", NULL), 1, &ft_pchar);
					ft_putstr(buff);
					index = ft_strlen(buff);
					i = index;
				}
				else if (!ft_strchr(ft_strrchr(buff, ' '), '/'))
				{
					tputs(tgetstr("sc", NULL), 1, &ft_pchar);
					tputs(tgetstr("do", NULL), 1, &ft_pchar);
					tputs(tgetstr("cr", NULL), 1, &ft_pchar);
					tputs(tgetstr("cd", NULL), 1, &ft_pchar);
					if (!buff_tmp[8193])
					{
						ft_strcpy(buff_tmp, buff);
						buff_tmp[8193] = 1;
					}
					else
						put = 1;
					if ((put = put_complet2(buff_tmp, files, buff, &put)) == 1)
						tmp[0] = 10;
					else if (put == -1)
					{
						*e_cmpl &= ~COMPLETION;
						tmp[0] = 0;
					}
					tputs(tgetstr("rc", NULL), 1, &ft_pchar);
					tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3), 1, &ft_pchar);
					j = -1;
					while (++j < i)
						tputs(tgetstr("dc", NULL), 1, &ft_pchar);
					ft_putstr(buff);
					index = ft_strlen(buff);
					i = index;
				}
				else
				{
					if (!tmp_files)
					{
						stmp = ft_strrchr(buff, ' ') + 1;
						stmp = ft_strndup(stmp, ft_strrchr(stmp, '/') - stmp);
						tmp_files = create_file_tree(stmp);
						free(stmp);
					}
					if (tmp_files)
					{
						tputs(tgetstr("sc", NULL), 1, &ft_pchar);
						tputs(tgetstr("do", NULL), 1, &ft_pchar);
						tputs(tgetstr("cr", NULL), 1, &ft_pchar);
						tputs(tgetstr("cd", NULL), 1, &ft_pchar);
						if (!buff_tmp[8193])
						{
							ft_strcpy(buff_tmp, buff);
							buff_tmp[8193] = 1;
						}
						else
							put = 1;
						if ((put = put_complet(buff_tmp, tmp_files, buff, &put)) == 1)
							tmp[0] = 10;
						else if (put == -1)
						{
							*e_cmpl &= ~COMPLETION;
							tmp[0] = 0;
						}
						tputs(tgetstr("rc", NULL), 1, &ft_pchar);
						tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3), 1, &ft_pchar);
						j = -1;
						while (++j < i)
							tputs(tgetstr("dc", NULL), 1, &ft_pchar);
						ft_putstr(buff);
						index = ft_strlen(buff);
						i = index;
					}
				}
			}
			if (*e_cmpl & COMPLETION && nb_read == 1 && tmp[0] == 10)
			{
				tputs(tgetstr("sc", NULL), 1, &ft_pchar);
				tputs(tgetstr("do", NULL), 1, &ft_pchar);
				tputs(tgetstr("cr", NULL), 1, &ft_pchar);
				tputs(tgetstr("cd", NULL), 1, &ft_pchar);
				tputs(tgetstr("rc", NULL), 1, &ft_pchar);
				*e_cmpl &= ~COMPLETION;
				tmp[0] = 0;
				if (ft_strrchr(buff, ' ') && (dir = opendir(ft_strrchr(buff, ' ') + 1)))
				{
					if (tmp_files)
						free_tree(tmp_files);
					tmp_files = NULL;
					buff[i++] = '/';
					buff[i] = '\0';
					index = i;
					ft_putchar('/');
				}
				else
				{
					buff[i++] = ' ';
					buff[i] = '\0';
					index = i;
					ft_putchar(' ');
				}
				if (dir)
					closedir(dir);
				ft_bzero(buff_tmp, 8194);
			}
		}
		ft_putchar('\n');
		if (buff[0] && tmp[0] != -1)
		{
			deal_commande(index, buff, buff_tmp, &curr, env);
			t_token	*tokens = get_tokens(buff);
			for(t_token*ptr=tokens;ptr;ptr=ptr->next)
				printf("-------------------------------------------\n"
				"rights: %d\n"
				"command: %s\n", ptr->rights, ptr->line);
			get_commands(tokens);
			// parse = NULL;
			// parse = ft_strsplit(buff, ';');
			// i = -1;
			// while (parse && parse[++i])
			// {
			// 	cmd = ft_strsplit_ws(parse[i]);
			// 	if (!(get_var(env, cmd)))
			// 		continue ;
			// 	deal_cmd(cmd, &env, &save);
			// 	if (files)
			// 		free_tree(files);
			// 	files = create_file_tree(getcwd(prompt, 4097));
			// 	if (tmp_files)
			// 	{
			// 		free_tree(tmp_files);
			// 		tmp_files = NULL;
			// 	}
			// 	free_tab(&cmd);
			// }
			// if (parse)
			// 	free_tab(&parse);
		}
	}
	return (0);
}

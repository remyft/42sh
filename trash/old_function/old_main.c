int		main(__unused int ac, __unused char **av, char **ep)
{
	t_line	*line;
	char	**env;
	int		i;
	char	**parse;
	char	**cmd;
	int		nb_read;
	char	prompt[4097];

	i = 0;
	env = collect_env(ep);
	line = init_line(env);
	nb_read = 0;
	while (1)
	{
		put_prompt(line->prompt);
		ft_bzero(line->buff, 8193);
		check_path(line, env);
		line->len = 0;
		line->index = 0;
		line->tmp[0] = '\0';
		while ((line->tmp[0] != 10 && line->tmp[0] != -1) || *(line->e_cmpl) & COMPLETION)
		{
			ft_bzero(line->tmp, 10);
			if (line->len + (nb_read = read(0, line->tmp, 10)) < 8192)  Type and cmd+V 
				line->len = get_typing(&(line->index), line->buff, line->tmp, nb_read, line->buff_tmp);
			if (is_change)
				deal_winch(line);
			line->tmp[nb_read] = '\0';
			if (line->tmp[0] == '/')
				line->tree[2] = free_tree(line->tree[2]);
			else if (line->tmp[0] != 9)
				deal_reset(line->tree[0], line->tree[1], NULL);
			deal_key(line);
			if (*(line->e_cmpl) & COMPLETION && line->tmp[0] == 10)
				set_complet(line);
		}
		ft_putendl("");
		if (line->buff[0] && line->tmp[0] != -1 && line->buff[0] != 10)
		{
			*(line->e_cmpl) &= ~COMPLETION;
			save_history(line->index, line->buff, line->buff_tmp, &(line->curr), env);
			line->buff[line->len] = '\n';
			parse = NULL;
			parse = ft_strsplit(line->buff, ';');
			i = -1;
			while (parse && parse[++i])
			{
				if (!(cmd = ft_strsplit_ws(parse[i])))
					break ;
				if (!(get_var(env, cmd)))
					continue ;
				deal_cmd(cmd, &env, &(line->save));
				if (line->tree[1])
					free_tree(line->tree[1]);
				line->tree[1] = create_file_tree(getcwd(prompt, 4097));
				if (line->tree[2])
				{
					free_tree(line->tree[2]);
					line->tree[2] = NULL;
				}
				free_tab(&cmd);
			}
			if (parse)
				free_tab(&parse);
		}
	}
	return (0);
}*/

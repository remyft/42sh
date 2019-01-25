char	*replace_str(char *path, char *src, char *replace)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	if (!ft_strstr(path, src))
		return (NULL);
	i = 0;
	j = 0;
	ft_find(path, src, &i, &j);
	if (!(str = malloc(sizeof(char) * (ft_strlen(path) - ft_strlen(src)
						+ ft_strlen(replace) + 1))))
		return (NULL);
	k = -1;
	while (++k < i)
		str[k] = path[k];
	str[k] = '\0';
	l = -1;
	while (replace[++l])
		str[k + l] = replace[l];
	k--;
	while (path[++k + j])
		str[k + l] = path[k + j];
	str[k + l] = '\0';
	return (str);
}

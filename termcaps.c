#include <termios.h>
#include <term.h>
#include "../libft/libft.h"


char        *ft_tgetstr(char *t)
{
	char            *tmp;

	if ((tmp = tgetstr(t, NULL)) == NULL)
	{
		ft_putstr_fd(t, 2);
		ft_putendl_fd(" not available", 2);
	}
	return (tmp);
}

int			ft_pchar(int nb)
{
	return (write(STDOUT_FILENO, &nb, 1));
}

void		ft_term_restore(struct termios save)
{
	if (tcsetattr(0, TCSANOW, &save) == -1)
	{
		ft_putendl("Fatal error: unable to restore the term attributes.");
		exit(2);
	}
}

void		ft_define_new_term_cap(struct termios *save)
{
	struct termios	termios;

	if (tcgetattr(0, save) != 0)
	{
		ft_putendl("Fatal error: unable to get term attributes.");
		exit(2);
	}
	if (tcgetattr(0, &termios) != 0)
	{
		ft_putendl("Fatal error: unable to the term attributes.");
		exit(2);
	}
	termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSANOW, &termios)) == -1)
	{
		ft_putendl("Fatal error: unable to set the new term attributes.");
		exit(2);
	}
}

static void sig_hdlr(int sig)
{
	ft_putstr("Sig : ");
	ft_putnbr(sig);
	ft_putchar('\n');
}

int		main(void)
{
	char	tmp[10];
	struct termios	save;
	int		nb_read;
	int		i;
	char	buff[8193];
	int		index;
	char	*cm_cap;
	char	*term;
	int		ret;
	int		cp;
	int		nb_col;
	int		j;
	char	tchar;
	char	cbis;

	term = getenv("TERM");
	ret = tgetent(NULL, term);
	ft_define_new_term_cap(&save);
	nb_read = 0;
	signal(SIGINT, &sig_hdlr);
	signal(SIGQUIT, &sig_hdlr);
	i = 0;
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	while (1)
	{
		ft_putstr("$> ");
		ft_bzero(buff, i);
		i = 0;
		index = 0;
		tmp[0] = '\0';
		while (tmp[0] != 10 && tmp[0] != -1)
		{
		//	j = -1;
		//	while (++j < nb_read)
		//		ft_putnbend(tmp[j], "  ");
			ret = tgetent(NULL, term);
			nb_col = tgetnum("co");
			if (i + (nb_read = read(0, tmp, 10)) < 8192)
			{
				cp = 0;
				while (cp < nb_read && ft_isprint(tmp[cp]))
				{
					tchar = buff[index + 1];
					if (index != i)
						buff[index + 1] = buff[index];
					buff[index++] = tmp[cp];
					i++;
					j = 1;
					if (index != i)
					{
						while (index + j < i)
						{
							cbis = buff[index + j];
							buff[index + j] = tchar;
							tchar = cbis;
							j++;
						}
					}
					ft_putchar(tmp[cp++]);
					if (index != i)
					{
						tputs(tgetstr("sc", NULL), 1, ft_pchar);
						ft_putstr(&buff[index]);
						tputs(tgetstr("rc", NULL), 1, ft_pchar);
					}
				}
			}
			if (nb_read == 1 && tmp[0] == 4 && !buff[0])
			{
				ft_term_restore(save);
				ft_putchar('\n');
				exit(0);
			}
			else if (nb_read == 1 && tmp[0] == 3)
			{
				i = i % nb_col < nb_col ? i + (nb_col - i % nb_col) : i;
				while ((index = index + nb_col) < i)
					ft_putchar('\n');
				tmp[0] = -1;
			}
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 68)
			{
				index = index > 0 ? index - 1 : 0;
				if (index && (index + 3) % nb_col == nb_col - 1)
					tputs(tgetstr("up", NULL), 1, ft_pchar);
				tputs(tgoto(tgetstr("ch", NULL), 0, (index + 3) % nb_col), 1, ft_pchar);
			}
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 67)
			{
				index = index < i ? index + 1 : i;
				if (index && (index + 3) % nb_col == 0)
					tputs(tgetstr("do", NULL), 1, ft_pchar);
				tputs(tgoto(tgetstr("ch", NULL), 0, (index + 3) % nb_col), 1, ft_pchar);
			}
			else if (nb_read == 1 && tmp[0] == 127)
			{
				j = 0;
				if (index && (index + 2) % nb_col == nb_col - 1)
					tputs(tgetstr("up", NULL), 1, ft_pchar);
				if (index != 0)
				{
					index = index > 0 ? index - 1 : 0;
					while (index + j < i)
					{
						buff[index + j] = buff[index + j + 1];
						j++;
					}
					buff[i] = '\0';
					i = i > 0 ? i - 1 : 0;
					tputs(tgoto(tgetstr("ch", NULL), 0, (index + 3) % nb_col), 1, ft_pchar);
					tputs(tgetstr("dc", NULL), 1, ft_pchar);
				}
				if ((index + 3) % nb_col == nb_col - 1)
				{
					tputs(tgetstr("sc", NULL), 1, ft_pchar);
					ft_putchar(' ');
					tputs(tgetstr("rc", NULL), 1, ft_pchar);
				}
				if (i + 3 > nb_col - 1)
				{
					j = index / nb_col;
					ret = i / nb_col;
					
					tputs(tgetstr("sc", NULL), 1, ft_pchar);
					tputs(tgetstr("cr", NULL), 1, ft_pchar);
					tputs(tgetstr("dl", NULL), 1, ft_pchar);
					tputs(tgetstr("rc", NULL), 1, ft_pchar);
					while (j++ < ret)
					{
						tputs(tgetstr("sc", NULL), 1, ft_pchar);
						tputs(tgetstr("do", NULL), 1, ft_pchar);
						tputs(tgetstr("cr", NULL), 1, ft_pchar);
						tputs(tgetstr("dl", NULL), 1, ft_pchar);
						tputs(tgetstr("rc", NULL), 1, ft_pchar);
					}
					tputs(tgetstr("sc", NULL), 1, ft_pchar);
					index < i ? ft_putstr(&buff[index]) : ft_putstr("");
					tputs(tgetstr("rc", NULL), 1, ft_pchar);
				}
			}
			else if (nb_read == 1 && tmp[0] == 12)
			{
				tputs(tgetstr("cl", NULL), 1, ft_pchar);
				ft_putstr("$> ");
				ft_putstr(buff);
			}
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 72)
			{
				j = index / nb_col;
				while (j--)
					tputs(tgetstr("up", NULL), 1, ft_pchar);
				tputs(tgoto(tgetstr("ch", NULL), 0, 3), 1, ft_pchar);
				index = 0;
			}
			else if (nb_read == 3 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 70)
			{
				j = index / nb_col - 1;
				ret = i / nb_col;
				while (++j < ret)
					tputs(tgetstr("do", NULL), 1, ft_pchar);
				tputs(tgoto(tgetstr("ch", NULL), 0, (i + 3) % nb_col), 1, ft_pchar);
				index = i;
			}
			else if (nb_read == 4 && tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 51 && tmp[3] == 126)
			{
				j = -1;
				while (index + ++j < i)
					buff[index + j] = buff[index + j + 1];
				j = index / nb_col;
				ret = i / nb_col;
				while (j++ < ret)
				{
					tputs(tgetstr("sc", NULL), 1, ft_pchar);
					tputs(tgetstr("do", NULL), 1, ft_pchar);
					tputs(tgetstr("cr", NULL), 1, ft_pchar);
					tputs(tgetstr("dl", NULL), 1, ft_pchar);
					tputs(tgetstr("rc", NULL), 1, ft_pchar);
				}
				tputs(tgetstr("sc", NULL), 1, ft_pchar);
				index < i ? ft_putstr(&buff[index]) : ft_putstr("");
				tputs(tgetstr("rc", NULL), 1, ft_pchar);
				i = i > index ? i - 1 : index;
			}
			else if (nb_read == 1 && tmp[0] == 23)
			{
				while (buff[index] != ' ' && index < i)
				{
					if (i > nb_col)
						if (index % nb_col == 0 && index < i)
							tputs(tgetstr("do", NULL), 1, ft_pchar);
					index++;
				}
				if (index < i)
					index++;
				tputs(tgoto(tgetstr("ch", NULL), 0, (index + 3) % nb_col), 1, ft_pchar);
			}
		}
		ft_putchar('\n');
		if (buff[0] && tmp[0] != -1)
		{
			buff[i] = '\0';
			ft_putendl(buff);
		}
		/*nb_read = read(0, tmp, 10);
		  i = -1;
		  while (++i < nb_read)
		  {
		  ft_putnbr(tmp[i]);
		  ft_putchar('\n');
		  }
		  if (tmp[0] == 'c') {
		  ft_term_restore(save);
		  pid_t  pid = fork();
		  if (pid == 0)
		  {
		  char *cmd[] = { "/sbin/ping", "google.fr", NULL };
		  execve(cmd[0], cmd, NULL);
		  exit(1);
		  } else if (pid > 0) {
		  int status;
		  ft_putendl("waiting...");
		  waitpid(pid, &status, 0);
		  ft_putstr("ret=");
		  ft_putnbr(status);
		  ft_putchar('\n');
		  }
		  ft_define_new_term_cap(&save);
		  }
		  if (tmp[0] == 'q')
		  break;*/
	}
	ft_term_restore(save);
	return (0);
}

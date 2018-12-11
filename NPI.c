#include "libft/include/libft.h"

typedef struct	s_pile
{
	char			op;
	int				val;
	struct s_pile	*next;
	struct s_pile	*prev;
}				t_pile;

int		is_op(char op)
{
	if (op == '(' || op == '*' || op == '+')
		return (1);
	return (0);
}

void	feed_pile(t_pile **pile, char *token)
{
//	if ((*pile) && token == (*pile)->op)
//		return ;
	if (*pile)
	{
		(*pile)->next = (t_pile *)ft_memalloc(sizeof(t_pile));
		(*pile)->next->prev = (*pile);
		if (ft_isdigit(*token))
			(*pile)->next->val = ft_atoi(token);
		else
			(*pile)->next->op = *token;
		(*pile) = (*pile)->next;
	}
	else
	{
		(*pile) = ft_memalloc(sizeof(t_pile));
		if (ft_isdigit(*token))
			(*pile)->val = ft_atoi(token);
		else
			(*pile)->op = *token;
	}
}

void	ft_depile(t_pile **pile, t_pile **out)
{
	t_pile *save;

	while ((*pile))
	{
		if ((*pile)->op == '*' || (*pile)->op == '+')
		{
			(*out)->next = ft_memalloc(sizeof(t_pile));
			(*out)->next->prev = (*out);
			(*out)->next->op = (*pile)->op;
			(*out) = (*out)->next;
			save = (*pile);
			(*pile) = (*pile)->prev;
			if (*pile)
				(*pile)->next = NULL;
			free(save);
		}
		else if ((*pile)->op == '(')
		{
			save = (*pile);
			(*pile) = (*pile)->prev;
			free(save);
			if (*pile)
				(*pile)->next = NULL;
			break;
		}
	}
}

int		get_calc(int a, int b, char op)
{
	if (op == '*')
		return (a * b);
	else if (op == '+')
		return (a + b);
	return (0);
}

/*int		resolve_npi(t_pile *out)
{
	int tmp;

	while (!is_op(out->next->op))
		out = out->next;
	tmp = get_calc(out->prev->prev->val, out->prev->val, out->op);
}*/

int		NPI(char *expr)
{
	int		i;
	t_pile	*pile;
	t_pile	*out;

	i = 0;
	pile = NULL;
	out = NULL;
	while (expr[i])
	{
		if (expr[i] == ' ')
			i++;
		else if (is_op(expr[i]) == 1)
			feed_pile(&pile, &expr[i++]);
		else if (expr[i] == ')')
		{
			ft_depile(&pile, &out);
			i++;
		}
		else
		{
			feed_pile(&out, &expr[i]);
			while (ft_isdigit(expr[i]))
				i++;
		}
	}
	if (pile)
		ft_depile(&pile, &out);
	while (out->prev)
		out = out->prev;
	while (out)
	{
		if (out->op)
			printf("%c ", out->op);
		else
			printf("%d ", out->val);
		out = out->next;
	}
	ft_putchar('\n');
	return (1);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		NPI(av[1]);
	return (0);
}

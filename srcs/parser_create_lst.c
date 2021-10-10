/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:08:53 by cquiana           #+#    #+#             */
/*   Updated: 2021/01/22 00:22:12 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cmd_parse(char *line, int *i)
{
	if (line[(*i)] == '|')
		return (2);
	else if (line[(*i)] == '>' && ((line[(*i) + 1]) && line[(*i) + 1] != '>'))
		return (3);
	else if (line[(*i)] == '<')
		return (4);
	else if (line[(*i)] == '>' && ((line[(*i) + 1]) && line[(*i) + 1] == '>'))
	{
		(*i)++;
		return (5);
	}
	else
		return (1);
}

void		ft_add_back(t_args **lst, t_args *elem)
{
	t_args	*tmp;

	if (!(*lst))
		*lst = elem;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
}

t_args		*ft_init_arg(t_args *new, char **arr)
{
	int j;

	j = 0;
	if (!(new = (t_args *)malloc(sizeof(t_args))))
		ft_error("malloc error", 2);
	new->cmd = NULL;
	if (!(new->cmd = (char **)malloc(sizeof(char*) * (array_len(arr) + 1))))
		ft_error("malloc error", 2);
	while (arr[j] != NULL)
	{
		new->cmd[j] = ft_strdup(arr[j]);
		j++;
	}
	new->cmd[j] = NULL;
	new->exec_path = NULL;
	new->simbol_last = 0;
	return (new);
}

t_args		*ft_crt_new(char **array, char *line, int *i, t_data *data)
{
	t_args	*new;

	if (!array)
		return (NULL);
	new = ft_init_arg(new, array);
	new->simbol = cmd_parse(line, i);
	if ((ft_is_builtin(new->cmd[0])) == 0)
		new->exec_path = NULL;
	else if (!(ft_strchr("./", new->cmd[0][0])))
		parse_exec_path(data, new);
	else
		new->exec_path = ft_strdup(new->cmd[0]);
	new->next = NULL;
	ft_free_double_array(array);
	return (new);
}

void		ft_free_pars_sruc(t_pars *p)
{
	p->arg = NULL;
	p->arr = NULL;
	p->c = 0;
	p->i = 0;
}

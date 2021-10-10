/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <cquiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:29:57 by cjani             #+#    #+#             */
/*   Updated: 2021/01/21 13:28:29 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		minishell_execve(t_args *tab, t_data *data)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid < 0)
		perror(NULL);
	else if (pid == 0)
	{
		ret = execve(tab->exec_path, tab->cmd, data->envp);
		if (ret == -1)
		{
			ft_putstr_fd("Command not found\n", 2);
			g_status = 127;
			minishell_tabs_free(tab, data);
		}
		exit(g_status);
	}
	else
	{
		wait(&pid);
		g_status = WEXITSTATUS(pid);
	}
	return (0);
}

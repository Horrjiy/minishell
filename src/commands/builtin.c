/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:29:00 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/19 16:18:40 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Checks if the command is a self-made command

static bool	ft_builtin_helper(char *name, t_list *stream)
{
	if (ft_strncmp(name, "echo", 5) == 0)
	{
		TOKEN->error = ft_exe_echo(stream);
		return (true);
	}
	else if (ft_strncmp(name, "pwd", 4) == 0)
	{
		TOKEN->error = ft_exe_pwd(stream);
		return (true);
	}
	else if (ft_strncmp(name, "exit", 5) == 0)
	{
		TOKEN->error = ft_exe_exit(stream);
		return (true);
	}
	return (false);
}

bool	ft_builtin_cmd(char *name, t_list *stream, char ***copy_env)
{
	if (ft_strncmp(name, "cd", 3) == 0)
	{
		TOKEN->error = ft_exe_cd(stream, copy_env);
		return (true);
	}
	else if (ft_strncmp(name, "export", 8) == 0)
	{
		TOKEN->error = ft_exe_export(stream, copy_env);
		return (true);
	}
	else if (ft_strncmp(name, "unset", 6) == 0)
	{
		TOKEN->error = ft_exe_unset(stream, copy_env);
		return (true);
	}
	else if (ft_strncmp(name, "env", 4) == 0)
	{
		TOKEN->error = ft_exe_env(stream, *copy_env);
		return (true);
	}
	if (ft_builtin_helper(name, stream) == true)
		return (true);
	return (false);
}

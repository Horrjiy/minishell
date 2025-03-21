/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:19 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/21 16:46:50 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_valid_arg(char *str)
{
	int	i;

	if (ft_isdigit(str[0]) == 1)
	{
		write(2, "Error: export: \'", 16);
		write(2, str, ft_strlen(str));
		write(2, "\' not a valid identifier!\n", 26);
		return (false);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		if (env_char(str[i]) == false)
		{
			write(2, "Error: export: \'", 16);
			write(2, str, ft_strlen(str));
			write(2, "\' not a valid identifier!\n", 26);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	ft_write_envvar(char *str, int fd_out)
{
	bool	equal_sign;
	int		i;

	write(fd_out, "declare -x ", 11);
	i = 0;
	equal_sign = false;
	while (str[i])
	{
		write(fd_out, &str[i], 1);
		if (str[i] == '=')
		{
			if (equal_sign == false)
				write(fd_out, "\"", 1);
			equal_sign = true;
		}
		i++;
	}
	if (equal_sign == true)
		write(fd_out, "\"", 1);
	write(fd_out, "\n", 1);
}

static int	ft_export_empty(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_strarrdup_sort(*copy_env);
	if (!temp)
		return (ft_error_cmd("Malloc failed.", "export"), 12);
	while (temp[i])
	{
		if (ft_str_same("LINES=", temp[i], 6) == false
			&& ft_str_same("COLUMNS=", temp[i], 8) == false)
		{
			ft_write_envvar(temp[i], TOKEN->fd_out);
		}
		i++;
	}
	free_strarr(temp);
	return(0);
}

static char	**ft_env_change(char *arg, char *name, char ***copy_env)
{
	char	**temp;

	if (name == NULL)
		temp = ft_add_envvar(arg, *copy_env);
	else
		temp = ft_update_envvar(arg, name, *copy_env);
	if (!(temp))
		return (NULL);
	free_strarr(*copy_env);
	return (temp);
}

// Executes export
int	ft_exe_export(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;
	char	**env_name;

	if (!TOKEN->arg[1])
		return (ft_export_empty(stream, copy_env));
	i = 0;
	while (TOKEN->arg[i + 1])
	{
		if (ft_valid_arg(TOKEN->arg[i + 1]) == true)
		{
			env_name = ft_split(TOKEN->arg[i + 1], '=');
			if (!env_name)
				return (ft_error_cmd("Malloc failed.", "export"), 12);
			if (ft_env_exists(env_name[0], *copy_env) == false)
				temp = ft_env_change(TOKEN->arg[i + 1], NULL, copy_env);
			else
				temp = ft_env_change(TOKEN->arg[i + 1], env_name[0], copy_env);
			free_strarr(env_name);
			if (!temp)
				return (ft_error_cmd("Malloc failed.", "export"), 12);
			*copy_env = temp;
		}
		i++;
	}
	return(0);
}

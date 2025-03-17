/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:57:46 by joklein           #+#    #+#             */
/*   Updated: 2025/03/17 12:09:30 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_char(char input)
{
	if (input >= 'a' && input <= 'z')
		return (1);
	if (input >= 'A' && input <= 'Z')
		return (1);
	if (input >= '0' && input <= '9')
		return (1);
	if (input == '_')
		return (1);
	return (0);
}

int	if_heredoc(int i, char *input)
{
	if (i >= 2)
	{
		while (i > 1 && input[i] != '<' && !wh_space(input[i]))
			i--;
		while (i > 1 && input[i] != '<' && wh_space(input[i]))
			i--;
		if (input[i] == '<' && input[i - 1] == '<')
			return (1);
	}
	return (0);
}

int	skip_until_char(int i, char *input, char cha)
{
	i++;
	while (input[i] && input[i] != cha)
		i++;
	if (input[i] == '\0')
		i--;
	return (i);
}

int	check_env(int i, char *input, char **copy_env)
{
	int		i_temp;
	int		u;
	char	*str;

	i_temp = i;
	while (input[i + 1] && env_char(input[i + 1]))
		i++;
	str = creat_str(i, i_temp, input);
	if (!str)
		return (free(input), 1);
	u = find_envp(str, copy_env);
	if (!copy_env[u])
		if ((input[i + 1] && wh_space(input[i + 1])) || input[i+1] == '\0')
		{
			ft_printf("%s: ambiguous redirect\n", str);
			return (free(str), 1);
		}
	return (free(str), 0);
}

int	if_redir_empty_file(int i, char *input, char **copy_env)
{
	int	i_temp;

	i_temp = i;
	
	if (i >= 1)
	{
		while (i > 0 && input[i] != '>' && !wh_space(input[i]))
			i--;
		while (i > 0 && input[i] != '>' && wh_space(input[i]))
			i--;
		if (input[i] == '>')
		{
			if (check_env(i_temp, input, copy_env))
				return (1);
		}
	}
	return (0);
}

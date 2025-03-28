/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash_dot_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:54:26 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 14:07:44 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_slash_syntax(char **arg, t_token *stream, char ***copy_env)
{
	if (strchr(arg[0], '/') == NULL)
		return (false);
	return (true);
	// nicht fertig
	(void)stream;
	(void)copy_env;
}

bool	ft_dot_syntax(char **arg, t_token *stream, char ***copy_env)
{
	if (arg[0][0] != '.')
		return (false);
	if (arg[0][1] == '\0')
	{
		write(2, "Error: builtin command '.' ", 27);
		write(2, "does not have to be handled!\n", 29);
		return (token_err(stream, 127), true);
	}
	if (arg[0][1] == '.' && arg[0][2] == '\0')
		return (token_err(stream, 127), ft_error(CMD_NF, arg[0]), true);
	(void)copy_env;
	return (false);
}

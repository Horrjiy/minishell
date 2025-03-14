/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:23 by joklein           #+#    #+#             */
/*   Updated: 2025/03/13 13:06:44 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_in(char *input, int i, t_list *stream)
{
	int		i_temp;
	char	*str;

	i_temp = i;
	while (input[i] && !wh_space(input[i]) && !spec_char_wo_dol(input[i]))
	{
		if (input[i] == '\'')
			i = skip_until_char(i, input, '\'');
		if (input[i] == '\"')
			i = skip_until_char(i, input, '\"');
		i++;
	}
	str = str_quote_less(&input[i_temp], i - i_temp);
	if (!str)
		return (-1);
	if (TOKEN->in_file)
		free(TOKEN->in_file);
	TOKEN->in_file = str;
	TOKEN->fd_in = 3;
	return (i);
}

int	redirect_in(char *input, int i, t_list *stream, char **copy_env)
{
	i++;
	if (input[i] == '<')
	{
		i++;
		while (wh_space(input[i]))
			i++;
		i = heredoc(i, input, stream, copy_env);
	}
	else
	{
		while (wh_space(input[i]))
			i++;
		i = file_in(input, i, stream);
	}
	if (input[i] == '\0')
		i--;
	return (i);
}

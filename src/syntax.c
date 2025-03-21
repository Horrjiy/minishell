/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:20:06 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/20 15:46:06 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntax(char *input)
{
	int		i;
	char	*syn_str;

	i = 0;
	syn_str = NULL;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		i++;
	}
	if (syn_str != NULL)
		{
			ft_printf("syntax error near unexpected token `%s'", syn_str);
			free(input);
			return(1);
		}
	return (0);
}

// Syntax check Heredoc
// bei input >>
// str = str_quote_less(&input[i_temp], i - i_temp);
// if (!str)
// 	return (free(input), -1);
// if (str[0] == '\0')
// 	return (free(str), free(input), write(1, "syntax error\n", 13), -1);


// if (input[i] == '>')
// {
// 	i++;
// 	while (input[i] && wh_space(input[i]))
// 		i++;
// 	if (input[i] == '>')
// 		syn_char = input[i];
// 	return (syn_char);
// }
// if (input[i])
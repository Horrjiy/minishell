/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/19 16:02:40 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_value(int num)
{
	static int	return_num = 0;
	int			return_num_temp;

	return_num_temp = return_num;
	return_num = num;
	return (return_num_temp);
}

char	*get_input()
{
	char	*line;
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline("\033[0;34mminishell> \033[0m");
	else
	{
		line = get_next_line(STDIN_FILENO);
		input = ft_strtrim(line, "\n");
		free(line);
	}
	return (input);
}

int	main(void)
{
	char	**copy_env;
	char	*input;

	setup_signals();
	copy_env = ft_strarrdup(environ);
	if (!copy_env)
		return (ft_errmal("Error: minishell: "), 1);
	while (1)
	{
		input = get_input();
		if (!input && isatty(STDIN_FILENO))
			return (free_strarr(copy_env), rl_clear_history(), \
			write(1,"exit\n", 5), 0);
		else if (!input)
			return (free_strarr(copy_env), rl_clear_history(), 1);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (check_syntax(input) == 1)
			continue ;
		return_value(start_process(input, copy_env));
	}
}

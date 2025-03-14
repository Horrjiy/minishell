/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:29:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/13 12:48:33 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_strstr(char **sstr)
{
	int	i;

	i = 0;
	while (sstr[i])
		free(sstr[i++]);
	if(sstr)
		free(sstr);
}

void	free_content(t_list *stream)
{
	if (TOKEN->arg)
		free_strstr(TOKEN->arg);
	if (TOKEN->in_file)
		free(TOKEN->in_file);
	if (TOKEN->out_file)
		free(TOKEN->out_file);
	if (TOKEN->fd_out != STDOUT_FILENO)
		close(TOKEN->fd_out);
	if (TOKEN->hd_file)
	{
		unlink(TOKEN->hd_file);
		free(TOKEN->hd_file);
	}
}

void	free_stream(t_list *stream)
{
	t_list	*stream_next;

	while (stream->next)
	{
		stream_next = stream->next;
		free_content(stream);
		free(stream->cont);
		free(stream);
		stream = stream_next;
	}
	free_content(stream);
	free(stream->cont);
	free(stream);
}

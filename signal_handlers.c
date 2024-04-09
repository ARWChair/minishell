/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:02:28 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/16 16:36:56 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/*	signal handler for SIG_INT (interrrupt)	*/
void	siginthandler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*	sets up/updates all signal handlers	*/
void	signal_setup(int mode)
{
	if (mode == INTERACTIVE)
	{
		signal(SIGINT, siginthandler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, siginthandler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SLEEP)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

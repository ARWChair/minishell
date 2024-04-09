/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:55:39 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/16 17:50:03 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

/*	formats dir for "get_arrow" function	*/
static char	*dir_trim(char *cwd)
{
	int	i;

	i = 0;
	while (cwd[i])
		i++;
	while (ft_strncmp(&cwd[i], "/", 1) != 0)
		i--;
	i++;
	return (&cwd[i]);
}

/*	looks up and formats current dir for prompt	*/
static char	*get_arrow(char *prompt, char *home)
{
	char	cwd[256];

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	if (ft_strncmp(cwd, home, sizeof(cwd)) == 0)
	{
		prompt = ft_strdup("~ > ");
		if (!prompt)
			return (NULL);
	}
	else if (ft_strncmp(cwd, "/", sizeof(cwd)) == 0)
	{
		prompt = ft_strdup("/ > ");
		if (!prompt)
			return (NULL);
	}
	else
	{
		prompt = ft_strjoin(dir_trim(cwd), " > ");
		if (!prompt)
			return (NULL);
	}
	return (prompt);
}

/*	displays the prompt	*/
static char	*prompt_creator(void)
{
	char	*prompt;
	char	*input;
	char	*home;

	prompt = NULL;
	home = getenv("HOME");
	if (!home)
		return (NULL);
	prompt = get_arrow(prompt, home);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (!input)
		return (NULL);
	return (input);
}

/*	saves env in list	*/
static void	env_create(t_mini *mini, char **envp)
{
	int	i;

	mini->env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0 && envp[i][6] < 57)
			envp[i][6]++;
		env_add_back(&mini->env, envp[i++]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		return (-1);
	mini->env = NULL;
	env_create(mini, &*envp);
	while (argv && argc)
	{
		signal_setup(INTERACTIVE);
		input = prompt_creator();
		if (input == NULL)
			break ;
		if (input[0])
		{
			add_history(input);
			if (cmd_split_master(input, &*mini) != 0)
				break ;
		}
		free(input);
	}
	free_and_clear(0, mini->env, &input);
	free(mini);
	return (g_exit_status);
}

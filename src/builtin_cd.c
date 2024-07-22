/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:25:38 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 18:01:21 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_cd(char *path)
{
	ft_putstr_fd("cd: ", 2);
	perror(path);
	error_status(256 * 1);
	free(path);
	return (true);
}

bool	do_cd(t_token *token, t_env **env, char *path)
{
	if (token->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		error_status(256 * 1);
		return (false);
	}
	if (!ft_strncmp(token->str, "-", 1) && ft_strlen(token->str) == 1)
	{
		path = get_env_value("OLDPWD", *env);
		ft_putendl_fd(path, 1);
	}
	else if (!ft_strncmp(token->str, "~", 1) && ft_strlen(token->str) == 1)
		path = get_env_value("HOME", *env);
	else
		path = ft_strdup(token->str);
	if (chdir(path) == -1)
	{
		return (error_cd(path));
	}
	error_status(0);
	free(path);
	return (true);
}

bool	builtin_cd(t_token *token, t_env **env)
{
	char	*path;

	path = NULL;
	if (!token->next)
	{
		path = get_env_value("HOME", *env);
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			free(path);
			return (true);
		}
		if (path[0] == '\0')
		{
			free(path);
			return (true);
		}
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			perror(path);
			error_status(256 * 1);
			return (false);
		}
		return (true);
	}
	token = token->next;
	return (do_cd(token, env, path));
}

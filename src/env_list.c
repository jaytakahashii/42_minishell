/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:55 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/20 15:52:03 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_back(t_env *new, t_env **env)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!env || !*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*new_variable(char *env_line)
{
	t_env	*env;
	char	*key;
	char	*value;

	env = malloc(sizeof(t_env));
	if (!env)
		ft_error("malloc", "env", strerror(errno), EXIT_FAILURE);
	key = get_key_from_str(env_line);
	value = get_value_from_str(env_line);
	env->key = key;
	env->value = value;
	env->is_export = false;
	env->next = NULL;
	return (env);
}

t_env	*new_export_env(char *env_line)
{
	t_env	*env;
	char	*key;
	char	*value;

	env = malloc(sizeof(t_env));
	if (!env)
		ft_error("malloc", "env", strerror(errno), EXIT_FAILURE);
	key = get_key_from_str(env_line);
	if (!key)
		return (NULL);
	value = get_value_from_str(env_line);
	env->key = key;
	env->value = value;
	env->is_export = true;
	env->next = NULL;
	return (env);
}

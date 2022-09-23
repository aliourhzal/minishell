/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elix <elix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 05:26:45 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/20 19:55:45 by elix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			new = NULL;
		}
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
			new = NULL;
		}
	}
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

t_env	*ft_lstnew(char *id, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->id = ft_strdup(id);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
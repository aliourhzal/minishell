#include "minishell.h"

void	add_env(t_env **lst, t_env *new)
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
			last = last_env(*lst);
			last->next = new;
			new->prev = last;
			new = NULL;
		}
	}
}

t_env	*last_env(t_env *lst)
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

t_env	*new_env(char *id, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->id = ft_strdup(id);
	new->value = ft_strdup(value);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	del_env(t_env *lst, char *id)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp && ft_strcmp(tmp->id, id))
		tmp = tmp->next;
	if (!tmp)
		return (0);
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	free(tmp->id);
	free(tmp->value);
	free(tmp);
	return (1);
}

t_env	*search_env(t_env *envp, char *id)
{
	t_env *head;

	head = envp;
	while(head && ft_strcmp(id, head->id))
		head = head->next;
	return(head);
}
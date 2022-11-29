/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:46:13 by pnoutere          #+#    #+#             */
/*   Updated: 2021/12/02 14:40:11 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_content(void *content, size_t size)
{
	(void) size;
	if (content != NULL)
		free(content);
}

static t_list	*null_returner(t_list *node)
{
	ft_lstdel(&node, &free_content);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;
	t_list	*cpy;

	cpy = lst;
	if (!lst || !f)
		return (NULL);
	new = f(lst);
	if (!new)
		return (null_returner(cpy));
	start = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = f(lst);
		if (!new->next)
			return (null_returner(cpy));
		new = new->next;
	}
	return (start);
}

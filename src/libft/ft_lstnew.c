/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:35:36 by pnoutere          #+#    #+#             */
/*   Updated: 2021/11/29 13:17:50 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh;
	char	*write;

	fresh = NULL;
	write = (char *)content;
	fresh = (t_list *)malloc(sizeof(t_list));
	if (!fresh)
		return (NULL);
	fresh->next = NULL;
	if (content == NULL)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
		fresh->next = NULL;
	}
	else
	{
		fresh->content = (char *)malloc(sizeof(char) * content_size);
		fresh->content_size = content_size;
		ft_memcpy(fresh->content, content, content_size);
	}
	return (fresh);
}

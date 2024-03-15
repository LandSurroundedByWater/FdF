/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:03:08 by tsaari            #+#    #+#             */
/*   Updated: 2023/11/21 12:17:11 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_free(t_list **lst, void (*del)(void *), void *fres)
{
	if (fres)
		(del)(fres);
	ft_lstclear(lst, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;
	void	*fres;

	if (!lst || !f || !del)
		return (0);
	ret = 0;
	while (lst)
	{
		fres = f(lst -> content);
		if (!fres)
			return (ft_free(&ret, del, fres));
		new = ft_lstnew(fres);
		if (!new)
			return (ft_free(&ret, del, fres));
		ft_lstadd_back(&ret, new);
		lst = lst -> next;
	}
	return (ret);
}

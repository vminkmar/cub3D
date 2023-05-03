#include "cub3d.h"

void	ft_lstadd_back_tex(t_tex_list **lst, t_tex_list *new)
{	
	t_tex_list	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{	
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstadd_back_map(t_map_list **lst, t_map_list *new)
{	
	t_map_list	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{	
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

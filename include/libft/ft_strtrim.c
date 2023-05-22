/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:10:13 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/22 15:31:11 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	b;
	char	*a;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	while (*s1 != '\0' && *set != '\0')
	{
		if (!ft_strchr(set, *s1))
			break ;
		s1++;
	}
	if (*s1 == '\0')
		return (ft_strdup(""));
	b = ft_strlen(s1);
	b--;
	while (b > 0)
	{
		if (!ft_strchr(set, s1[b]))
			break ;
		b--;
	}
	a = ft_substr(s1, 0, b + 1);
	return ((char *)a);
}

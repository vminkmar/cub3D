/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:40:25 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/03 20:38:59 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*stupid_shit( char *s1, char *s2)
{
	size_t	c;
	size_t	d;
	char	*a;

	c = ft_strlen(s1);
	d = ft_strlen(s2);
	a = malloc((c + d) * sizeof(char) + 1);
	if (a == NULL)
		return (NULL);
	return (a);
}

char	*sl_strjoin(char *s1, char *s2)
{
	char	*a;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (0);
	a = stupid_shit(s1, s2);
	while (s1[i] != '\0')
	{
		a[i] = s1[i];
		i ++;
	}
	while (s2[j] != '\0')
	{
		a[i] = s2[j];
		i++;
		j++;
	}
	a[i] = '\0';
	free(s1);
	return (a);
}

int	ft_strcmp(char *first, char *second)
{
	int	counter_first;
	int	counter_second;

	counter_first = 0;
	while(first[counter_first] != '\0')
	{
		counter_second = 0;
		while(second[counter_second] != '\0')
		{	
			if(first[counter_first] != second[counter_second])
				return (1);
			counter_second++;
		}
		counter_first ++;
	}
	return (0);
}

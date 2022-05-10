/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:23:02 by kkaczoro          #+#    #+#             */
/*   Updated: 2022/05/10 15:33:42 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdio.h>

char	*ft_sign(const char *s, char *old_str, int i_conv);
char	*ft_field(const char *s, char *old_str, int i_conv);
char	*ft_zero(const char *s, char *old_str, int i_conv, int field);

char	*ft_flag(const char *s, char *old_str, int i_conv)
{
	old_str = ft_dot(s, old_str, i_conv);
	if (old_str == NULL)
		return (NULL);
	old_str = ft_hash(s, old_str, s[i_conv]);
	if (old_str == NULL)
		return (NULL);
	old_str = ft_sign(s, old_str, i_conv);//control sign AFTER making MFV work
	if (old_str == NULL)
		return (NULL);
	old_str = ft_field(s, old_str, i_conv);
	if (old_str == NULL)
		return (NULL);
	return (old_str);
}

int	ft_isflag(const char *s, char flag, char conv)
{
	while (*s != conv)
	{
		if (*s == flag)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_sign(const char *s, char *old_str, int i_conv)
{
	int		plus;
	int		space;
	int		len_old;
	char	*new_str;

	space = ft_isflag(s, ' ', s[i_conv]);
	plus = ft_isflag(s, '+', s[i_conv]);
	len_old = ft_strlen(old_str);
	if ((s[i_conv] != 'i' && s[i_conv] != 'd') || old_str[0] == '-'
		|| (!space && !plus))
		return (old_str);
	new_str = (char *)malloc(sizeof(char) * len_old + 2);
	if (new_str == NULL)
		return (NULL);
	new_str[0] = ' ';
	if (plus)
		new_str[0] = '+';
	(void)ft_strlcpy(new_str + 1, old_str, len_old + 1);
	free(old_str);
	return (new_str);
}

char	*ft_field(const char *s, char *old_str, int i_conv)
{
	int		field;
	int		len_old;
	char	*new_str;

	new_str = (char *)s;
	while (*s == '-' || *s == '0' || *s == '#' || *s == ' ' || *s == '+')
		s++;
	field = ft_atoi(s);
	len_old = (int)ft_strlen(old_str);
	if (!field || field <= len_old)
		return (old_str);
	if (ft_isflag(s, '0', s[i_conv]) && !ft_isflag(s, '-', s[i_conv]))
		new_str = ft_zero(new_str, old_str, i_conv, field);//OTHER CASES MUST FREE old_str INSIDE RESPECTIVE FUNCTIONS or INSIDE respective scopes
	return (new_str);
}

char	*ft_zero(const char *s, char *old_str, int i_conv, int field)
{
	char	*s2;
	char	*str_field;
	char	*new_str;

	if ((s[i_conv] == 'd' || s[i_conv] == 'i') && old_str[0] == '-')
		field--;
	str_field = ft_itoa(field);
	if (str_field == NULL)
		return (NULL);
	s2 = ft_strjoin(ft_strjoin(ft_strjoin(".", str_field), "d"), s);
	if (s2 == NULL)
	{
		free(str_field);
		return (NULL);
	}
	new_str = ft_dot((const char *)s2, old_str, 1 + (int)ft_strlen(str_field));
	free(str_field);
	free(s2);
	return (new_str);
}

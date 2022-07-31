/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:28:25 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/31 11:07:49 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester_header.h"

char	*get_file_content(int fd)
{
	char	*content;
	int		byteread;

	content = malloc((BUFFER + 1) * sizeof(char));
	byteread = read(fd, content, BUFFER);
	content[byteread] = '\0';
	return (content);
}

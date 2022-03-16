/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:19:56 by alex              #+#    #+#             */
/*   Updated: 2022/03/16 17:41:35 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define INVALID_DATA	-3
# define BAD_MEMALLOC	1
# define INIT_ERROR		-2

void	inp_error(void);
void	error(int code, char *text);

#endif
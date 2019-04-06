/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 04:08:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/06 18:53:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_ERROR_H
# define TOKEN_ERROR_H

enum
{
	ERR_NONE = 0,
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_ALIAS
};

#endif

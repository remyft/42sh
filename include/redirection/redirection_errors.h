/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_errors.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:14:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/16 20:08:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_ERRORS_H
# define REDIRECTION_ERRORS_H

enum
{
	ERR_FREE_ALL = -1,
	ERR_NONE,
	ERR_MALLOC,
	ERR_AMBIGUOUS,
	ERR_BAD_FD,
};

# define MALLOC_STR		"not enought memory"
# define AMBIGOUS_STR	"ambiguous redirect"
# define BAD_FD_STR		"Bad file descriptor"

#endif

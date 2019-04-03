/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_terminated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:18:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/03 17:45:30 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "job_control.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>


/*static void	ended(int jobs)
{
	(void)jobs;
	printf("Ended\n");
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siglist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:21:48 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/12 17:42:43 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGLIST_H
# define SIGLIST_H

# include <signal.h>

# define SGHUP		"hangup"
# define SINT		"interrupt"	
# define SQUIT		"quit"
# define SILL		"illegal instruction"
# define STRAP		"BPT trace/trap"
# define SABRT		"ABORT instruction"
# define SEMT		"EMT instruction"
# define SFPE		"Floating point exception"
# define SKILL		"Killed"
# define SBUS		"Bus error"
# define SSEGV		"Segmentation fault"
# define SSYS		"Bad system call"
# define SPIPE		"Broken pipe"
# define SALRM		"Alarm clock"
# define STERM		"Terminated"
# define SURG		"Urgent IO condition"
# define SSTOP		"Stopped (signal)"
# define STSTP		"Stopped"
# define SCONT		"Continue"
# define SCHLD		"Child death or stop"
# define STTIN		"Stopped (tty input)"
# define STTOU		"Stopped (tty output)"
# define SIO		"I/O ready"
# define SXCPU		"CPU limit"
# define SXFSZ		"File limit"
# define SVTALRM	"Alarm (virtual)"
# define SPROF		"Alarm (profile)"
# define SWINCH		"Window changed"
# define SLOST		"Record lock"
# define SUSR1		"User signal 1"
# define SUSR2		"User signal 2"

#endif

#include "job_control.h"
#include "siglist.h"
#include <stdio.h>


char	*process_translate_status(int status)
{
	if (status == 0)
		return (NULL);
	if (status == STATUS_FINISHED)
		return (STR_TERMINATED);
	if (status == STATUS_RUNNING)
		return (STR_RUNNING);
	if (status == STATUS_SUSPENDED)
		return (STR_SUSPENDED);
	if (status == STATUS_STOPPED)
		return (STR_STOPPED);
	return (STR_RUNNING);
}

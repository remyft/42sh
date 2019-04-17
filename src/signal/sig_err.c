#include "siglist.h"

char	*sig_err_translate(int sig)
{
	static char		*tab[] = {
		0, SGHUP, SINT, SQUIT, SILL, STRAP, SABRT, SEMT, SFPE, SKILL,
		SBUS, SSEGV, SSYS, SPIPE, SALRM, STERM, SURG, SSTOP, STSTP, SCONT,
		SCHLD, STTIN, STTOU, SIO, SXCPU, SXFSZ, SVTALRM, SPROF, SWINCH, SLOST,
		SUSR1, SUSR2,
	};
	return (tab[sig]);
}

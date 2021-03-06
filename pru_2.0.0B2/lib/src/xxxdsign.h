/* xxxdsign.h -- common _[FL]Dsign functionality */
#include "xmath.h"
_STD_BEGIN

int FNAME(Dsign)(FTYPE x)
	{	/* test floating-point sign bit */
	return (FISNEG(x));
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */

/* xxexpm1.h -- common expm1[fl] functionality */
#include "xmath.h"
_STD_BEGIN

	/* coefficients */

 #if   FBITS <= 26
  #define DPOLY(x)	((c[0] * x + c[1]) * x + c[2])
  #define NPOLY(x)	(((s[0] * x + s[1]) * x + s[2]) * x + s[3])

static const FTYPE s[] = {	/* 3/2, ln(1/2) <= x <= ln(3/2) */
	FLIT( 0.0024490478),
	FLIT( 0.0305274668),
	FLIT( 0.1538026623),
	FLIT( 0.9483177732),
	};

static const FTYPE c[] = {
	FLIT( 0.0326527809),
	FLIT(-0.3203561199),
	FLIT( 0.9483177697),
	};

 #elif FBITS <= 57
  #define DPOLY(x)	(((((c[0] * x + c[1]) * x + c[2]) * x + c[3]) * x \
	+ c[4]) * x + c[5])
  #define NPOLY(x)	(((((s[0] * x + s[1]) * x + s[2]) * x + s[3]) * x \
	+ s[4]) * x + s[5])

static const FTYPE s[] = {	/* 5/5, ln(1/2) <= x <= ln(3/2) */
	FLIT( 0.00000259766943573417),
	FLIT( 0.00011305370687423613),
	FLIT( 0.00109066792970778349),
	FLIT( 0.02784564909329514297),
	FLIT( 0.03926190614812718186),
	FLIT( 0.92389869353018596046),
	};

static const FTYPE c[] = {
	FLIT(-0.00001757061517257875),
	FLIT( 0.00060499786991627820),
	FLIT(-0.00956033110459000699),
	FLIT( 0.08520625381341306649),
	FLIT(-0.42268744061696587854),
	FLIT( 0.92389869353018596365),
	};

 #elif FBITS <= 70
  #define DPOLY(x)	FNAME(Poly)(x, c, sizeof (c) / sizeof (c[0]) - 1)
  #define NPOLY(x)	FNAME(Poly)(x, s, sizeof (s) / sizeof (s[0]) - 1)

static const FTYPE s[] = {	/* 6/6, ln(1/2) <= x <= ln(3/2) */
	FLIT( 0.0000000996601140025436411),
	FLIT( 0.0000041839973209071404972),
	FLIT( 0.0001582999600184100984757),
	FLIT( 0.0010038471175422549009921),
	FLIT( 0.0294536522061038977858451),
	FLIT( 0.0331247665984150491876615),
	FLIT( 0.9222478957464352023288259),
	};

static const FTYPE c[] = {
	FLIT( 0.0000007890901021948765579),
	FLIT(-0.0000373186765020580194525),
	FLIT( 0.0008299475632192266768626),
	FLIT(-0.0109625817689751052137663),
	FLIT( 0.0897452602190993066969116),
	FLIT(-0.4279991812748025519900121),
	FLIT( 0.9222478957464352023289281),
	};

 #elif FBITS <= 119
  #define DPOLY(x)	FNAME(Poly)(x, c, sizeof (c) / sizeof (c[0]) - 1)
  #define NPOLY(x)	FNAME(Poly)(x, s, sizeof (s) / sizeof (s[0]) - 1)

static const FTYPE s[] = {	/* 10/9, ln(1/2) <= x <= ln(3/2) */
	FLIT( 0.00000000000012818986408092252751292),
	FLIT( 0.00000000001428952550658840506533140),
	FLIT( 0.00000000081054904211965426801590232),
	FLIT( 0.00000002714396809227941884766202224),
	FLIT( 0.00000084453934960624439085565907441),
	FLIT( 0.00001204895789600869991707659157132),
	FLIT( 0.00028907662550871354051081358967353),
	FLIT( 0.00156490179731940575184302059459486),
	FLIT( 0.03355056573820619356610826301215112),
	FLIT( 0.04463642672013964051925117381701811),
	FLIT( 0.92399118484136404074231397293134908),
	};

static const FTYPE c[] = {
	FLIT(-0.00000000001606114383057081132311608),
	FLIT( 0.00000000171630993030070248482117283),
	FLIT(-0.00000008844828836869586081039206729),
	FLIT( 0.00000286703527325077118671607946564),
	FLIT(-0.00006407590885970264729481622917105),
	FLIT( 0.00101918511497541007184511135875053),
	FLIT(-0.01149067884510538765460684642671914),
	FLIT( 0.08823161778158337670167550718125457),
	FLIT(-0.41735916570054237985190581264865644),
	FLIT( 0.92399118484136404074231397293134908),
	};

 #else /* FBITS */
  #error expm1 has insufficient precision
 #endif /* FBITS */

static const FTYPE lnhalf = FLIT(-0.69314718055994530941723212145817658);
static const FTYPE lnone_half = FLIT(0.40546510810816438197801311546434915);

FTYPE (FFUN(expm1))(FTYPE x)
	{	/* compute exp(x)-1 */
	switch (FNAME(Dtest)(&x))
		{	/* test for special codes */
	case _NANCODE:
	case 0:
		return (x);
	case _INFCODE:
		return (FISNEG(x) ? FLIT(-1.0) : x);
	default:	/* -INF or finite */
		if (lnhalf < x && x < lnone_half)
			return (x * NPOLY(x) / DPOLY(x));
		else
			return (FFUN(exp)(x) - FLIT(1.0));
		}
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */

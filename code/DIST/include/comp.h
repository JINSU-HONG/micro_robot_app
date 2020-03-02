#ifndef	_CUSTOMIZED_COMP
#define	_CUSTOMIZED_COMP

// Floating-point Constants
#define	PI			((double)3.1415926535897932384626433832795)
#define	PI2			((double)6.283185307179586476925286766559)
#define	PI_THIRD	((double)1.0471975511965977461542144610932)
#define INV_2PI		((double)0.15915494309189533576888376337251)
#define INV_PI		((double)0.31830988618379067153776752674503)
#define	SQRT2		((double)1.4142135623730950488016887242097)
#define	SQRT3		((double)1.7320508075688772935274463415059)
#define	SQRT3HALF   ((double)0.86602540378443864676372317075294)
#define	SQRT3THIRD  ((double)0.57735026918962576450914878050196)
#define	INV_SQRT2	((double)0.70710678118654752440084436210485)
#define	INV_SQRT3	((double)0.57735026918962576450914878050196)
#define	INV_3		((double)0.33333333333333333333333333333333)
#define	INV_2_3		((double)0.66666666666666666666666666666667)
#define Rm2Rpm		((double)9.5492965855137201461330258023509)
#define Rpm2Rm		((double)0.10471975511965977461542144610932)

// Macro Functions
#define LIMIT(x,s,l)			(((x)>(l))?(l):((x)<(s))?((s)):(x))
#define	MAX(a, b)				((a)>(b) ? (a) : (b))
#define	MIN(a, b)				((a)>(b) ? (b) : (a))
#define	BOUND_PI(x)             ((x>0)?((x)-2.*PI*(int)((x+PI)/(2.*PI))):((x)-2.*PI*(int)((x-PI)/(2.*PI))))
#define	ABS(x)					((x>0)?(x):(-x))
#define	SIGN(x)					((x<0)? -1. : 1. )

#endif

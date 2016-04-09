#include "Indice2D.h"
#include "cudaTools.h"
#include <Device.h>

#include "MandelbrotMath.h"

#include "IndiceTools_GPU.h"
#include "DomaineMath_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrTabPixels, uint w, uint h, uint t, DomaineMath domaineMath);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ static void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrTabPixels, uint w, uint h, uint t, DomaineMath domaineMath)
    {
    MandelbrotMath mandelbrotMath = MandelbrotMath(t);

    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();
    int s = TID;
    int pixelI;	// in [0,h[
    int pixelJ; // in [0,w[

    const int WH = w * h;

    // TODO pattern entrelacement

    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); 	// update (pixelI, pixelJ)

	workPixel(&ptrTabPixels[s], pixelI, pixelJ, domaineMath, &mandelbrotMath);

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * i in [0,h[
 * j in [0,w[
 *
 * code commun a:
 * 	- entrelacementOMP
 * 	- forAutoOMP
 */

__device__
void workPixel(uchar4* ptrColorIJ, int i, int j,const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath)
    {
    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2

    double x;
    double y;
    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    // float t=variateurAnimation.get();

    ptrMandelbrotMath->colorXY(ptrColorIJ, x, y); // in [01]
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


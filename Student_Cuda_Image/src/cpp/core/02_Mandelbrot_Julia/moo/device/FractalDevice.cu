#include "Indice2D.h"
#include "cudaTools.h"
#include <Device.h>

#include "MandelbrotMath.h"
#include "FractalMath.h"
#include "JuliaMath.h"

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

__global__ void julia(uchar4* ptrTabPixels, uint w, uint h, uint t, float c1, float c2, DomaineMath domaineMath);

 /*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ static void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, FractalMath* ptrMandelbrotMath);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__device__ void fractal(uchar4* ptrTabPixels, uint w, uint h, uint t, DomaineMath &domaineMath, FractalMath* m)
    {

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

	workPixel(&ptrTabPixels[s], pixelI, pixelJ, domaineMath, m);

	s += NB_THREAD;
	}
    }


__global__ void mandelbrot(uchar4* ptrTabPixels, uint w, uint h, uint t, DomaineMath domaineMath)
    {
    //MandelbrotMath mandelbrotMath = MandelbrotMath(t);
    FractalMath *m = new MandelbrotMath(t);

    fractal(ptrTabPixels, w, h, t, domaineMath, m);

    delete m;
    }


__global__ void julia(uchar4* ptrTabPixels, uint w, uint h, uint t, float c1, float c2, DomaineMath domaineMath)
    {
    FractalMath *m = new JuliaMath(t, c1, c2);

    fractal(ptrTabPixels, w, h, t, domaineMath, m);

    delete m;
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
void workPixel(uchar4* ptrColorIJ, int i, int j,const DomaineMath& domaineMath, FractalMath* ptrMandelbrotMath)
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


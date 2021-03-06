#include "Indice2D.h"
#include "cudaTools.h"

#include <stdio.h>
#include <reductiontool.h>



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void piDevice(float* ptrDevPi, int nbSlice);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reduceIntraThread(float* ptrDevTabSM, int nbSlice);
static __device__ float aireRectangle(int sliceNumber, int nombreSlice);
static __device__ float f(float x);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void piDevice(float* ptrDevPi, int nbSlice)
    {
    extern __shared__ float tabSM[]; // lu par tout les thread mais fait une fois
    reduceIntraThread(tabSM, nbSlice);

    __syncthreads();
    ReductionTool<float>::reduce(tabSM , ptrDevPi);
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reduceIntraThread(float* ptrDevTabSM, int nbSlice)
    {
    float sumThread = 0;
    const int NB_THREAD=Indice2D::nbThread();
    const int TID=Indice2D::tid();
    const int TID_BLOC=Indice2D::tidLocalBlock();

    int s = TID;

    while(s < nbSlice)
	{
	sumThread += aireRectangle(s, nbSlice);

	s+= NB_THREAD;
	}

    ptrDevTabSM[TID_BLOC] = sumThread / nbSlice;
    }

__device__ float aireRectangle(int sliceNumber, int nombreSlice)
    {
    const float x = (1.0f / (float) nombreSlice) * (float) sliceNumber;
    return f(x);
    }

__device__ float f(float x)
    {
    return 4.0f/ (1.0f + x * x);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


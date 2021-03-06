#include "Indice2D.h"
#include "cudaTools.h"
#include <curand_kernel.h>

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void monteCarlo(float M, int nbFlechettes);
__global__ void setup_kernel_rand(curandState* tabDevGenerator, int deviceID);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(int* tabSM, curandState* ptrTabDevGeneratorGM, int nbFlechettes);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__
void monteCarlo(curandState* ptrTabDevGeneratorGM, int* ptrDevN0, int nbFlechettes)
    {
    extern __shared__ int tabSM[];
    reductionIntraThread(tabSM, ptrTabDevGeneratorGM, nbFlechettes);
    __syncthreads();
    ReductionTools::reducitonIntraBloc(tabSM);
    ReductionTools::reducitonInterBloc(tabSM, ptrDevN0);

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
__global__
void setup_kernel_rand(curandState* tabDevGenerator, int deviceId)
    {
    const int TID = Indice1D::tid();
    //Customisation du generator: Proposition (au lecteur de faire mieux)
    // Contrainte : Doit etre différent d'un GPU à l'autre
    int deltaSeed = deviceId * INT_MAX / 10000;
    int deltaSequence = deviceId * 100;
    int deltaOffset = deviceId * 100;
    int seed = 1234 + deltaSeed;
    int sequenceNumber = TID + deltaSequence;
    int offset = deltaOffset;
    curand_init(seed, sequenceNumber, offset, &tabDevGenerator[tid]);
    }

__device__
void reductionIntraThread(int* tabSM, curandState* ptrTabDevGeneratorGM, int nbFlechettes)
    {
    const int NB_THREAD = Indice2D::nbThread();
    const int TID_LOCAL = Indice2D::tidLocal();
    const int TID = Indice2D::tid();

    // Debug
    if (TID == 0)
	{
	printf("Coucou from device tid%d", TID); //required   Device::synchronize(); after the call of kernel
	}

    // pattern entrelacement

    int s = TID;
    while (s < nbFlechettes)
	{
	tabSM[s] = ptrTabDevGeneratorGM[s];
	s += NB_THREAD;
	}
    //ptrDevN0[TID_LOCAL] =
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


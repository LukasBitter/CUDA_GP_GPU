#include <iostream>

#include "Device.h"
#include "MonteCarlo.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void monteCarlo(float M, int nbFlechettes);
extern __global__ void setup_kernel_rand(curandState* tabDevGenerator,Device::getDeviceId() )

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

MonteCarlo::MonteCarlo(float M, int nbFlechettes) :
	M(M), nbFlechettes(nbFlechettes)
    {

    // Grid
	{
	this->dg = dim3(16, 2, 1); // disons, a optimiser selon le gpu
	this->db = dim3(32, 4, 1); // puissance de 2

	Device::gridHeuristic(dg, db);
	}

    // nb de blocks * nb de threads
    this->sizeOctetTabGenerator = dg.x * dg.y * db.z * db.x * db.y * db.z * sizeof(curandState);
    this->sizeOctetN0 = sizeof(int); // octet
    this->sizeSM = db.x * db.y * db.z * sizeof(int);

    // MM
	{
	// MM (malloc Device)
	    {
	    HANDLE_ERROR(cudaMalloc(&ptrDevN0, sizeOctetN0));
	    HANDLE_ERROR(cudaMalloc(&ptrTabDevGeneratorGM, sizeOctetTabGenerator));
	    }

	// MM (memset Device)
	    {
	    HANDLE_ERROR(cudaMemset(ptrTabDevGeneratorGM, 0, sizeOctetN0));
	    }

	// MM (copy Host->Device)
	    {
	    // rien
	    }

	Device::lastCudaError("MonteCarlo MM (end allocation)"); // temp debug
	}
	setup_kernel_rand(tabDevGenerator,Device::getDeviceId());

    }

MonteCarlo::~MonteCarlo(void)
    {
    //MM (device free)
	{
	HANDLE_ERROR(cudaFree(ptrDevN0));
	HANDLE_ERROR(cudaFree(ptrTabDevGeneratorGM));

	Device::lastCudaError("MonteCarlo MM (end deallocation)"); // temp debug
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

public float getPi()
    {
    return this->pi;
    }

void MonteCarlo::run()
    {

    Device::lastCudaError("monteCarlo (before)"); // temp debug
    monteCarlo<<<dg,db, sizeSM>>>(ptrTabDevGeneratorGM, ptrDevN0, nbFlechettes); // assynchrone
    Device::lastCudaError("monteCarlo (after)"); // temp debug

    Device::synchronize(); // Temp, only for printf in  GPU

    // MM (Device -> Host)
	{
	HANDLE_ERROR(cudaMemcpy(&n0, ptrDevN0, sizeOctetN0, cudaMemcpyDeviceToHost)); // barriere synchronisation implicite
	}
	pi = (N0 / nbFlechettes ) * M // TODO à verifier
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#include "PI.h"

#include <iostream>

#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void slice(float* ptrDevPi, int nbSlice);


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

PI::PI(int nbSlice) :
	nbSlice(nbSlice)
    {
    this->sizeOctetPI = sizeof(float);

    // MM
	{
	// MM (malloc Device)
	    {
	    HANDLE_ERROR(cudaMalloc(&ptrDevPi, sizeOctetPI));
	    }

	// MM (memset Device)
	    {
	    HANDLE_ERROR(cudaMemset(ptrDevPi, 0, sizeOctetPI));
	    }

	// MM (copy Host->Device)
	    {
	    // rien
	    }

	Device::lastCudaError("PI MM (end allocation)"); // temp debug
	}

    // Grid
	{
	this->dg = dim3(16, 2, 1); // disons, a optimiser selon le gpu
	this->db = dim3(32, 4, 1); // Contrainte: produti des 3 donne une puissance de 2

	Device::gridHeuristic(dg, db);
	}

	this->sizeOctetSM = db.x * db.y * db.z * sizeof(float);
	// assert : doit être puissance de 2 (faisable avec opérteur binaire)
    }

PI::~PI(void)
    {
    //MM (device free)
	{
	HANDLE_ERROR(cudaFree(ptrDevPi));

	Device::lastCudaError("PI MM (end deallocation)"); // temp debug
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void PI::run()
    {
    Device::lastCudaError("pi (before)"); // temp debug
    slice<<<dg,db>>>(ptrDevPi, nbSlice); // assynchrone
    Device::lastCudaError("pi (after)"); // temp debug

    //Device::synchronize(); // Temp, only for printf in  GPU

    // MM (Device -> Host)
	{
	// copie de droite à gauche pour les 2 premières variables
	HANDLE_ERROR(cudaMemcpy(&piRes, ptrDevPi, sizeOctetSM, cudaMemcpyDeviceToHost)); // barriere synchronisation implicite
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
#ifndef SRC_CPP_CORE_03_SLICE_MOO_HOST_SLICE_H_
#define SRC_CPP_CORE_03_SLICE_MOO_HOST_SLICE_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

#include "cudaTools.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Slice
    {
    public:
	Slice(int n);

	virtual ~Slice();

	void run();

	float result();

    private:
	// Inputs
	int nbSlice;
	// Tools
	dim3 dg;
	dim3 db;
	int sizeOctetGM;
	int sizeOctetSM;
	float* ptrDevGM;

	// Output
	float piRes;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

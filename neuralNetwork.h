/*******************************************************************
* Basic Feed Forward Neural Network Class
* ------------------------------------------------------------------
* Bobby Anguelov - takinginitiative.wordpress.com (2008)
* MSN & email: banguelov@cs.up.ac.za
********************************************************************/

#ifndef NNetwork
#define NNetwork

#include "dataReader.h"

class neuralNetworkTrainer;

class neuralNetwork
{
	//class members
	//--------------------------------------------------------------------------------------------
private:

	//number of neurons
	int nInput, nHidden, nOutput;
	
	//neurons
	double* inputNeurons;
	double* hiddenNeurons;
	double* outputNeurons;

	//weights
	double** wInputHidden;
	double** wHiddenOutput;
		
	//Friends
	//--------------------------------------------------------------------------------------------
    friend class neuralNetworkTrainer;
	
	//public methods
	//--------------------------------------------------------------------------------------------

public:

	//constructor & destructor
	neuralNetwork(int numInput, int numHidden, int numOutput);
	~neuralNetwork();

	//weight operations
    bool loadWeights(const char* inputFilename);
    bool saveWeights(const char* outputFilename);
	int* feedForwardPattern( double* pattern );
	double getSetAccuracy( std::vector<dataEntry*>& set );
	double getSetMSE( std::vector<dataEntry*>& set );
    double getOutputValue(int neuronNr);
    void feedForward( double* pattern );
	//private methods
	//--------------------------------------------------------------------------------------------

private: 

	void initializeWeights();
	inline double activationFunction( double x );
    int clampOutput( double x );
	
};

#endif

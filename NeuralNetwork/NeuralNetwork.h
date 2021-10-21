#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include "NeuralNetworkTools.h"




/**
 *
 * Définition de notre structure de réseau de neuronnes
 *
 *
 *
 *
 *
 *
 *
 *
*/

/**
 *
 * Definition of our neural network structure
 *
 *
 *
 *
 *
 *
 *
 *
*/

struct NeuralNetwork{

    int nbInput;
    int nbHidden1;
    int nbHidden2;
    int nbOutput;


    double wanted[52];

    double WeightIH1[28*28][28];
    double WeightH1H2[28][28];
    double WeightH2O[28][52];


    double BiasH1[28];
    double BiasH2[28];
    double BiasOutput[52];

    double neuralValueInput[28*28];
    double neuralValueH1[28];
    double neuralValueH2[28];
    double neuralValueOutput[52];

    double deltaWeightIH1[28*28][28];
    double deltaWeightH1H2[28][28];
    double deltaWeightH2O[28][52];

    double deltaNeuralValueH1[28];
    double deltaNeuralValueH2[28];
    double deltaNeuralValueOutput[52];

    double MaxError;
    double Error;
    double alpha;
    double beta;

};

struct NeuralNetwork* initializeNetwork();
void feedForward(struct  NeuralNetwork *rn);
char ocr(char *filename);
void beginTraining();
void continueTraining(int current);

#endif
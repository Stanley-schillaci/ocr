#ifndef NEURALNETWORKPRINTVALUE_H
#define NEURALNETWORKPRINTVALUE_H

#include "NeuralNetwork.h"

void printNeuralValueInput(struct  NeuralNetwork *rs);
void printNeuralValueH1(struct  NeuralNetwork *rs);
void printNeuralValueH2(struct  NeuralNetwork *rs);
void printNeuralValueOutput(struct  NeuralNetwork *rs);

void printWeightIH1(struct  NeuralNetwork *rs);
void printWeightH1H2(struct  NeuralNetwork *rs);
void printWeightH2O(struct  NeuralNetwork *rs);

void printBiasH1(struct  NeuralNetwork *rs);
void printBiasH2(struct  NeuralNetwork *rs);
void printBiasOutput(struct  NeuralNetwork *rs);

void printDeltaNeuralValueH1(struct  NeuralNetwork *rs);
void printDeltaNeuralValueH2(struct  NeuralNetwork *rs);
void printDeltaNeuralValueOutput(struct  NeuralNetwork *rs);

void printDeltaWeightIH1(struct  NeuralNetwork *rs);
void printDeltaWeightH1H2(struct  NeuralNetwork *rs);
void printDeltaWeightH2O(struct  NeuralNetwork *rs);

void printWanted(struct  NeuralNetwork *rs);
void printError(struct  NeuralNetwork *rs);
void printMaxError(struct  NeuralNetwork *rs);

#endif
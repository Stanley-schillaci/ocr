#ifndef NEURALNETWORKTOOLS_H
#define NEURALNETWORKTOOLS_H



#include "NeuralNetwork.h"

double sigmoid(double x);

double sigmoidPrime(double x);

double randomNN();

double *wanted(char c);
double **wantedMat();
int posWanted(double *wanted);

int letterN(int i);

double *matImageFromFile(char *filename);

double **matLetters();

void saveData(struct NeuralNetwork *rn);

int maxOutput(struct  NeuralNetwork *rn);
char letterPosChar(int n);
int letterPosInt(char c);

void test(struct  NeuralNetwork *rn, char *filename, char want);
int testLetter(struct  NeuralNetwork *rn, char c);
double testAllLetters(struct NeuralNetwork *rn,int arg);

char ocr(char *filename);

#endif
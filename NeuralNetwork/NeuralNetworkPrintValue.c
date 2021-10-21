#include <stdio.h>

#include "NeuralNetwork.h"


/**
 * Dans ce fichier il y a une fonction de print
 * Pour chaque élements qui compose notre structure de réseau de neuronnes
 * De cette manière, on peut suivre l'évolution des valeurs de notre réseau
 * afin de réaliser des debugs
 *
 * Je ne détaille pas les fonctions car c'est à peu près toutes les mêmes
 *
 * Elles prennent en paramètres --> une structure de reseau de neuronnes (qui se trouvent dans notre NeuralNetwork.h)
 *
 * Pour appeler une fonction il faut d'abord initialiser un réseau :
 *         Par ex  --> struct NeuralNetwork *rn = InitializeNetwork();
 *         Ensuite --> PrintOutputH1(rn);
 **/

/**
 * In this file there is a print function
 * For each element that makes up our neural network structure
 * In this way, we can follow the evolution of the values of our network
 * in order to carry out debugs
 *
 * I do not detail the functions because they are almost all the same
 *
 * They take in parameters -> a network structure of neurons (which can be found in our NeuralNetwork.h)
 *
 * To call a function you must first initialize a network:
 * For example -> struct NeuralNetwork * rn = InitializeNetwork ();
 * Then -> PrintOutputH1 (rn);
**/

//Print notre matrice image d'entrée
//Print our input image matrix
void printNeuralValueInput(struct  NeuralNetwork *rn){
    printf("\nPrint Mat Image : \n");
    for(int i = 0; i < rn -> nbInput;i++){
        printf("ImageMat[%i] = %f\n",i, rn -> neuralValueInput[i]);
    }
}

//Print la valeur contenu dans chaque neuronnes du Hidden Layer 1
//Print the value contained in each neuron of Hidden Layer 1
void printNeuralHiddenH1(struct  NeuralNetwork *rn){
    printf("\nPrint Output H1 : \n");
    for(int i = 0; i < rn -> nbHidden1;i++){
        printf("OutputH1[%i] = %f\n",i, rn -> neuralValueH1[i]);
    }
}


//Print la valeur contenu dans chaque neuronnes du Hidden Layer 2
//Print the value contained in each neuron of Hidden Layer 2
void printNeuralHiddenH2(struct  NeuralNetwork *rn){
    printf("\nPrint Output H2 : \n");
    for(int i = 0; i < rn -> nbHidden2;i++){
        printf("OutputH2[%i] = %f\n",i, rn -> deltaNeuralValueH2[i]);
    }
}

//Print la valeur contenu dans chaque neuronnes du Output Layer
//Print the value contained in each neuron of the Output Layer
void printNeuralValueOutput(struct  NeuralNetwork *rn){
    printf("\nPrint Output O : \n");
    for(int i = 0; i < rn -> nbOutput;i++){
        printf("OutputO[%i] = %f\n",i, rn -> neuralValueOutput[i]);
    }
}




//Print les poids entre les Input Layers et l'Hidden Layer 1
//Print the weights between the Input Layers and the Hidden Layer 1
void printWeightIH1(struct  NeuralNetwork *rn){
    printf("\nPrint Weight Input -> H1 : \n");
    for(int i = 0; i < rn -> nbInput;i++){
        for(int j = 0; j < rn -> nbHidden1; j++){
            printf("WeightIH1[%i][%i] = %f\n",i,j, rn -> WeightIH1[i][j]);
        }
    }
}

//Print les poids entre l'Hidden Layer 1 et l'Hidden Layer 2
//Print the weights between Hidden Layer 1 and Hidden Layer 2
void printWeightH1H2(struct  NeuralNetwork *rn){
    printf("\nPrint Weight H1 -> H2 : \n");
    for(int i = 0; i < rn -> nbHidden1;i++){
        for(int j = 0; j < rn -> nbHidden2; j++){
            printf("WeightH1H2[%i][%i] = %f\n",i,j, rn -> WeightH1H2[i][j]);
        }
    }
}
//Print les poids entre l'Hidden Layer 2 et l'Output Layer
//Print the weights between Hidden Layer 2 and Output Layer
void printWeightH2O(struct  NeuralNetwork *rn){
    printf("\nPrint Weight H2 -> Ouput : \n");
    for(int i = 0; i < rn -> nbHidden2;i++){
        for(int j = 0; j < rn -> nbOutput; j++){
            printf("WeightH2O[%i][%i] = %f\n",i,j, rn -> WeightH2O[i][j]);
        }
    }
}



//Print les bias de chaque neuronne du Hidden Layer 1
//Print the bias of each neuron of Hidden Layer 1
void printBiasH1(struct  NeuralNetwork *rn){
    printf("\nPrint Bias H1 : \n");
    for(int i = 0; i < rn -> nbHidden1;i++){
        printf("BH1[%i] = %f\n",i, rn -> BiasH1[i]);
    }
}

//Print les bias de chaque neuronne du Hidden Layer 2
//Print the bias of each neuron of Hidden Layer 2
void printBiasH2(struct  NeuralNetwork *rn){
    printf("\nPrint Bias H2 : \n");
    for(int i = 0; i < rn -> nbHidden2;i++){
        printf("BH2[%i] = %f\n",i, rn -> BiasH2[i]);
    }
}

//Print les bias de chaque neuronne du Output Layer
//Print the bias of each neuron of the Output Layer
void printBiasOutput(struct  NeuralNetwork *rn){
    printf("\nPrint Bias Output : \n");
    for(int i = 0; i < rn -> nbOutput;i++){
        printf("BO[%i] = %f\n",i, rn -> BiasOutput[i]);
    }
}


//Print les Delta de chaque neuronnes du Hidden Layer 1
//Print the Delta of each neuron of Hidden Layer 1
void printDeltaNeuralValueH1(struct  NeuralNetwork *rn){
    printf("\nPrint Delta Output H1 : \n");
    for(int i = 0; i < rn -> nbHidden1;i++){
        printf("dOutputH1[%i] = %f\n",i, rn -> deltaNeuralValueH1[i]);
    }
}

//Print les Delta de chaque neuronnes du Hidden Layer 2
//Print the Delta of each neuron of Hidden Layer 2
void printDeltaNeuralValueH2(struct  NeuralNetwork *rn){
    printf("\nPrint Delta Output H2 : \n");
    for(int i = 0; i < rn -> nbHidden2;i++){
        printf("dOutputH2[%i] = %f\n",i, rn -> deltaNeuralValueH2[i]);
    }
}

//Print les Delta de chaque neuronnes du Output Layer
//Print the Delta of each neuron of the Output Layer
void printDeltaNeuralValueOutput(struct  NeuralNetwork *rn){
    printf("\nPrint Delta Output O : \n");
    for(int i = 0; i < rn -> nbOutput;i++){
        printf("dOutputO[%i] = %f\n",i, rn -> deltaNeuralValueOutput[i]);
    }
}


//Print les Delta de chaque poids entre l'input layer et l'hidden layer 1
//Print the Delta of each weight between the input layer and the hidden layer 1
void printDeltaWeightIH1(struct  NeuralNetwork *rn){
    printf("\nPrint Delta Weight Input -> H1 : \n");
    for(int i = 0; i < rn -> nbInput;i++){
        for(int j = 0; j < rn -> nbHidden1; j++){
            printf("dWeightIH1[%i][%i] = %f\n",i,j, rn -> deltaWeightIH1[i][j]);
        }
    }
}

//Print les Delta de chaque poids entre l'hidden layer 1 et l'hidden layer 2
//Print the Delta of each weight between the hidden layer 1 and the hidden layer 2
void printDeltaWeightH1H2(struct  NeuralNetwork *rn){
    printf("\nPrint Delta Weight H1 -> H2 : \n");
    for(int i = 0; i < rn -> nbHidden1;i++){
        for(int j = 0; j < rn -> nbHidden2; j++){
            printf("dWeightH1H2[%i][%i] = %f\n",i,j, rn -> deltaWeightH1H2[i][j]);
        }
    }
}

//Print les Delta de chaque poids entre l'hidden layer 2 et l'output layer
//Print the Delta of each weight between the hidden layer 2 and the output layer
void printDeltaWeightH2O(struct  NeuralNetwork *rn){
    printf("\nPrint Delta Weight H2 -> Ouput : \n");
    for(int i = 0; i < rn -> nbHidden2;i++){
        for(int j = 0; j < rn -> nbOutput; j++){
            printf("dWeightH2O[%i][%i] = %f\n",i,j, rn -> deltaWeightH2O[i][j]);
        }
    }
}

//Print la matrice (output) résultat attendu pour un caractères données
// Print the matrix (output) expected result for a given character
void printWanted(struct  NeuralNetwork *rn){
    printf("\nPrint Wanted : \n");
    for(int i = 0; i < rn -> nbOutput;i++){
        printf("Wanted[%i] = %f\n",i, rn -> wanted[i]);
    }
}


//Print double

void printError(struct NeuralNetwork *rn){
    printf("\n Print Error : %f\n",rn -> Error);
}

void printMaxError(struct NeuralNetwork *rn){
    printf("\n Print MaxError : %f\n",rn -> MaxError);
}





#include <stdio.h>
#include "NeuralNetworkTools.h"
#include "NeuralNetworkPrintValue.h"

#include "NeuralNetwork.h"

#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"

/**
 *
 * Ce fichier contient tout les fonctions "importante" du réseau de neuronnes
 *
*/

/**
  *
  * This file contains all the "important" functions of the neural network
  *
*/


/**
 *
 * La fonction initializeNetwork() nous permet de crée une nouvelle base pour le réseau de neuronne
 *
 * On peut configurer le reseau avec
 *              le nombre de neuronne en input (cela correspond à la dimension de notre image d'entrée) --> on a choisi 28*28
 *              le nombre de neuronne en hidden layer 1 --> on a choisi 28
 *              le nombre de neuronne en hidden layer 2 --> on a choisi 28
 *              le nombre de neuronne en output layer --> on a 52 réponses possible (minuscule + majuscule)
 *              la valeur alpha --> coefficient de multiplication de l'erreur --> plus ce chiffre est grand moins le réseau sera précis dans l'apprentisage
 *              la valeur beta --> coefficient de multipliction du Delta des poids
 *
 * On initialise l'erreur à 0.0
 *
 * On initialise ensuite grâce à des boucles de parcour, tout les poids et bias de manière aléatoires,
 *          ainsi que les delta des Poids et le delta De l'output à 0
 *
 *
 * la fonction retourne le réseau
 *
 *
 *
*/

/**
 *
 * The initializeNetwork () function allows us to create a new base for the neural network
 *
 * You can configure the network with
 * the number of neuron in input (this corresponds to the dimension of our input image) -> we chose 28 * 28
 * the number of neurons in hidden layer 1 -> we chose 28
 * the number of neurons in hidden layer 2 -> we chose 28
 * the number of neurons in output layer -> we have 52 possible responses (lower case + upper case)
 * the alpha value -> coefficient of multiplication of the error -> the greater this figure, the less precise the network will be in the learning process
 * the beta value -> multipliction coefficient of the Delta of the weights
 *
 * We initialize the error to 0.0
 *
 * We then initialize through loops of course, all weights and bias in a random way,
 * as well as the delta of the Weights and the delta of the output at 0
 *
 *
 * the function returns the network
 *
 *
 *
*/

struct NeuralNetwork* initializeNetwork(){
    struct NeuralNetwork *rn = NULL;
    rn = malloc(sizeof(struct NeuralNetwork));
    rn -> nbInput = 28*28;
    rn -> nbHidden1 = 28;
    rn -> nbHidden2 = 28;
    rn -> nbOutput = 52;
    rn -> Error = 0.0;
    rn -> alpha = 0.15;
    rn -> beta = 0.15;

    //Définition des poids (et delta) entre les Input et les Hidden Layer 1
    //Definition of the weights (and delta) between the Inputs and the Hidden Layer 1
    for (int i = 0; i < rn -> nbInput; i++){
        for(int j = 0; j < rn -> nbHidden1; j++){
            rn -> WeightIH1[i][j] = randomNN();
            rn -> deltaWeightIH1[i][j] = 0.0;
        }
    }

    //Définition des poids entre les Hidden Layer 1 et les Hidden Layer 2
    //Definition of weights between Hidden Layer 1 and Hidden Layer 2
    for (int i = 0; i < rn -> nbHidden1; i++){
        for(int j = 0; j < rn -> nbHidden2; j++){
            rn -> WeightH1H2[i][j] = randomNN();
            rn -> deltaWeightH1H2[i][j] = 0.0;
        }
        rn -> BiasH1[i] = randomNN();
    }

    //Définition des poids entre les Hidden Layer 2 et les Output Layer
    //Definition of the weights between the Hidden Layer 2 and the Output Layer
    for (int i = 0; i < rn -> nbHidden2; i++){
        for(int j = 0; j < rn -> nbOutput; j++){
            rn -> WeightH2O[i][j] = randomNN();
            rn -> deltaWeightH2O[i][j] = 0.0;
        }
        rn -> BiasH2[i] = randomNN();
    }

    for(int i = 0; i < rn -> nbOutput; i++){
        rn -> BiasOutput[i] = randomNN();
        rn -> deltaNeuralValueOutput[i] = 0.0;
    }

    return rn;

}



/**
 *  arg : NeuralNetwork *rn --> notre réseau
 *
 *  cette fonction parcout le réseau de cette manière :
 *
 *      input layer --> hidden layer 1 --> hidden layer 2 --> output layer
 *
 *  on propage dans le réseau les valeurs se trouvant dans notre input layers.
 *  en effet les valeurs des neuronnes en hidden layer 1, puis 2 et en output layers.
 *
 *  La valeur se trouvant dans un neuronne (peut importe sa couche sauf pour ceux du input layer)
 *
 *  correspond donc aux valeurs de chaque neuronnes le précedent auxquels il est rellié multiplié par le poids qui relie chaque neuronne + un bias, le tout dans une fonction sigmoid
 *
 *  on a donc sigmoid(nb(neuronne*poids) + biais)
 *
 *
 *
 *
*/

/**
  * arg: NeuralNetwork * rn -> our network
  *
  * this function traverses the network in this way:
  *
  * input layer -> hidden layer 1 -> hidden layer 2 -> output layer
  *
  * we propagate in the network the values found in our input layers.
  * indeed the values of the neurons in hidden layer 1, then 2 and in output layers.
  *
  * The value located in a neuron (regardless of its layer except for those of the input layer)
  *
  * therefore corresponds to the values of each neuron the previous one to which it is real multiplied by the weight which connects each neuron + a bias, all in a sigmoid function
  *
  * we therefore have sigmoid (nb (neuron * weight) + bias)
  *
  *
  *
  *
*/


void feedForward(struct  NeuralNetwork *rn){

    double total, weight, neuralValue, bias;

    //Calculate Output pour Hidden Layer 1 (from input)
    //Calculate Output for Hidden Layer 1 (from input)
    for(int i = 0; i < rn -> nbHidden1; i++){
        total = 0.0;
        for(int j = 0; j < rn -> nbInput; j++){
            weight = rn -> WeightIH1[j][i];
            neuralValue = rn -> neuralValueInput[j];

            total += weight * neuralValue;
        }
        bias = rn -> BiasH1[i];
        rn -> neuralValueH1[i] = sigmoid(total + bias);
    }

    //Calculate Output pour Hidden Layer 2 (from Hidden Layer 1)
    //Calculate Output for Hidden Layer 2 (from Hidden Layer 1)
    for(int i = 0; i < rn -> nbHidden2; i++){
        total = 0.0;
        for(int j = 0; j < rn -> nbHidden1; j++){
            weight = rn -> WeightH1H2[j][i];
            neuralValue = rn -> neuralValueH1[j];

            total += weight * neuralValue;
        }
        bias = rn -> BiasH2[i];
        rn -> neuralValueH2[i] = sigmoid(total + bias);
    }

    //Calculate Output pour Output Layer (from Hidden Layer 2)
    //Calculate Output for Output Layer (from Hidden Layer 2)
    for (int i = 0; i < rn -> nbOutput; i++) {
        total = 0.0;
        for(int j = 0; j < rn -> nbHidden2;j++){
            weight = rn -> WeightH2O[j][i];
            neuralValue = rn -> neuralValueH2[j];

            total += weight * neuralValue;
        }
        bias = rn -> BiasOutput[i];
        rn -> neuralValueOutput[i] = sigmoid(total + bias);
    }
}


/**
 *  arg : NeuralNetwork *rn --> notre réseau
 *
 *  cette fonction parcout le réseau de cette manière :
 *
 *      output layer --> hidden layer 2 --> hidden layer 1 --> input layer
 *
 *      tout d'abord on calcule l'erreur grâce à notre matrice de résultat voulu (fonction wanted)
 *      on trouve donc une valeur delta (delta pour difference) pour chaque neuronnes de l'output layer
 *
 *      ensuite on effectue donc la méthode de la descente gradiante en effectuant la dérivé.
 *
 *      ensuite on mutltiplie le poids (reliant au neuronne précédent) par le delta du neuronne pour trouver le delta du neuronne précédent
 *      on effectue cette action pour propager entre chaque couche
 *
 *
 *
*/

/**
  * arg: NeuralNetwork * rn -> our network
  *
  * this function traverses the network in this way:
  *
  * output layer -> hidden layer 2 -> hidden layer 1 -> input layer
  *
  * first of all we calculate the error thanks to our desired result matrix (wanted function)
  * we therefore find a delta value (delta for difference) for each neuron of the output layer
  *
  * then the gradual descent method is carried out by performing the derivative.
  *
  * then we multiply the weight (connecting to the previous neuron) by the delta of the neuron to find the delta of the previous neuron
  * we perform this action to propagate between each layer
  *
  *
  *
*/

static void backPropagation(struct  NeuralNetwork *rn){

    double neuralValue, prime, wanted, err,  sum, weight, delta;

    //Calculate Cost function for output neurons
    for (int i = 0; i < rn -> nbOutput; i++) {
        neuralValue = rn -> neuralValueOutput[i];
        prime = sigmoidPrime(neuralValue);
        wanted = rn -> wanted[i];
        err = (wanted - neuralValue) * prime;

        rn -> deltaNeuralValueOutput[i] = err;
    }

    //Calculate Cost function for hidden neurons 2
    for (int i = 0; i < rn -> nbHidden2; i++) {
        sum = 0.0;
        for(int j = 0; j < rn -> nbOutput; j++){
            weight = rn -> WeightH2O[i][j];
            delta = rn -> deltaNeuralValueOutput[j];

            sum += weight * delta;
        }
        neuralValue = rn -> neuralValueH2[i];
        prime = sigmoidPrime(neuralValue);
        rn -> deltaNeuralValueH2[i] = sum * prime;
    }

    //Calculate Cost function for hidden neurons 1
    for (int i = 0; i < rn -> nbHidden1; i++) {
        sum = 0.0;
        for(int j = 0; j < rn -> nbHidden2; j++){
            weight = rn -> WeightH1H2[i][j];
            delta = rn -> deltaNeuralValueH2[j];

            sum += weight * delta;
        }
        neuralValue = rn -> neuralValueH1[i];
        prime = sigmoidPrime(neuralValue);
        rn -> deltaNeuralValueH1[i] = sum * prime;
    }

}

/**
 *  arg : NeuralNetwork *rn --> notre réseau
 *
 *  cette fonction parcout le réseau de cette manière :
 *
 *      input layer --> hidden layer 1 --> hidden layer 2 --> output layer
 *
 *  le but sera de faire évoluer les poids entre chaque neuronnes
 *
 *  pour chaque poids on récupére la valeur de son neuronnes de départ et le delta de la valeur de son neuronne d'arrivé
 *
 *  le nouveau poids sera égal au neuronne d'entré + delta du neuronnes d'arrivés fois une constante + le delta du poids fois une constante
 *  le delta du poids sera égal au neuronne d'entré + delta du neuronnes d'arrivés fois une constante
 *
 *
 *
 *
*/

/**
  * arg: NeuralNetwork * rn -> our network
  *
  * this function traverses the network in this way:
  *
  * input layer -> hidden layer 1 -> hidden layer 2 -> output layer
  *
  * the goal will be to change the weights between each neuron
  *
  * for each weight we recover the value of its starting neuron and the delta of the value of its arrival neuron
  *
  * the new weight will be equal to the input neuron + delta of the arrived neurons times a constant + the delta of the weight times a constant
  * the delta of the weight will be equal to the entered neuron + delta of the arrived neurons times a constant
  *
  *
  *
  *
*/

static void updateWeights(struct NeuralNetwork *rn){
    double alpha, beta,error, neuralValue, dWeight;
    alpha = rn -> alpha;
    beta = rn -> beta;


    //Weight between Input and Hidden Layers 1
    for(int i = 0; i < rn -> nbHidden1; i++){
        for (int j = 0; j < rn -> nbInput; j++) {
            neuralValue = rn -> neuralValueInput[j];
            error = rn -> deltaNeuralValueH1[i];
            dWeight = rn -> deltaWeightIH1[j][i];

            rn -> WeightIH1[j][i] += alpha * error * neuralValue + beta *dWeight;
            rn -> deltaWeightIH1[j][i] = alpha * error * neuralValue;
        }
    }

    //Weight between Hidden Layers 1 et Hidden Layer 2
    for(int i = 0; i < rn -> nbHidden2; i++){
        for (int j = 0; j < rn -> nbHidden1; j++) {
            neuralValue = rn -> neuralValueH1[j];
            error = rn -> deltaNeuralValueH2[i];
            dWeight = rn -> deltaWeightH1H2[j][i];

            rn -> WeightH1H2[j][i] += alpha * error * neuralValue + beta * dWeight;
            rn -> deltaWeightH1H2[j][i] = alpha * error * neuralValue;
        }
    }

    //Weight between Hidden Layers 2 et Output Layer
    for(int i = 0; i < rn -> nbOutput; i++){
        for (int j = 0; j < rn -> nbHidden2; j++) {
            neuralValue = rn ->neuralValueH2[j];
            error = rn -> deltaNeuralValueOutput[i];
            dWeight = rn -> deltaWeightH2O[j][i];

            rn -> WeightH2O[j][i] += alpha * error * neuralValue + beta * dWeight;
            rn -> deltaWeightH2O[j][i] = alpha * error * neuralValue;
        }
    }

}

/**
 *  arg : NeuralNetwork *rn --> notre réseau
 *
 *  cette fonction parcout le réseau de cette manière :
 *
 *      input layer --> hidden layer 1 --> hidden layer 2 --> output layer
 *
 *  le but sera de faire évoluer les biais de chaque neuronnes
 *
 *  la valeur de chaque bias évolue du delta de son neuronnes multiplé par une constante
 *
 *
 *
 *
*/

/**
  * arg: NeuralNetwork * rn -> our network
  *
  * this function traverses the network in this way:
  *
  * input layer -> hidden layer 1 -> hidden layer 2 -> output layer
  *
  * the goal will be to change the biases of each neuron
  *
  * the value of each bias evolves from the delta of its neurons multiplied by a constant
  *
  *
  *
  *
*/

static void updateBiases(struct NeuralNetwork *rn){
    double alpha, delta, dBias;
    alpha = rn -> alpha;

    //Update Bias H1
    for(int i =0; i < rn -> nbHidden1;i++){
        delta = rn -> deltaNeuralValueH1[i];
        dBias = alpha * delta;

        rn -> BiasH1[i] += dBias;
    }

    //Update Bias H2
    for(int i =0; i < rn -> nbHidden2;i++){
        delta = rn -> deltaNeuralValueH2[i];
        dBias = alpha * delta;

        rn -> BiasH2[i] += dBias;
    }

    //Update Bias Output
    for(int i =0; i < rn -> nbOutput;i++){
        delta = rn -> deltaNeuralValueOutput[i];
        dBias = alpha * delta;

        rn -> BiasOutput[i] += dBias;
    }
}


/**
 *  arg : NeuralNetwork *rn --> notre réseau
 *        double *input --> la matrice d'entrée
 *        double *want --> la matrice de sortie voulu
 *
 *  On défini les valeurs de chaque neuronnes d'entrée et de la matrice wanted
 *
 *  puis on appel dans l'ordre
 *
 *  feed forward --> backpropagation --> updateWeight --> updateBiases
 *
 *  c'est la fonction coeur du réseau celle qui le fait évoluer
 *
 *
 *
*/

/**
  * arg: NeuralNetwork * rn -> our network
  * double * input -> the input matrix
  * double * want -> the desired output matrix
  *
  * We define the values of each input neuron and the wanted matrix
  *
  * then we call in order
  *
  * feed forward -> backpropagation -> updateWeight -> updateBiases
  *
  * it is the core function of the network that makes it evolve
  *
  *
  *
*/

void neuralNetwork(struct NeuralNetwork *rn, double *input, double *want){


    for (int i = 0; i < rn -> nbOutput; i++)
    {
        rn -> wanted[i] = want[i];
    }
    for(int j = 0; j < rn -> nbInput; j++)
    {
        rn -> neuralValueInput[j] = input[j];
    }

    feedForward(rn);
    backPropagation(rn);
    updateWeights(rn);
    updateBiases(rn);
}


/**
 *  Cette fonction permet d'initialiser un réseau grâce au résultat sauvergarder dans des fichiers
 *    elle est similaire à la première fonction de ce fichier (InitialiseNetwork) mais au lieu d'initialiser de manière
 *    random on initialise avec des valeurs connus
*/

/**
  * This function is used to initialize a network thanks to the result save in files
  * it is similar to the first function of this file (InitialiseNetwork) but instead of initializing in a
  * random on initialize with known values
*/

struct NeuralNetwork* initValue(){

    struct NeuralNetwork *rn = malloc(sizeof(struct NeuralNetwork));
    rn -> nbInput = 28*28;
    rn -> nbHidden1 = 28;
    rn -> nbHidden2 = 28;
    rn -> nbOutput = 52;
    rn -> Error = 0.0;
    rn -> alpha = 0.15;
    rn -> beta = 0.15;

    int sizeMax = 15;
    char *line = calloc(15, sizeof(char));


    FILE* biasO = fopen("NeuralNetwork/SaveNN/BiasOutput.txt", "r");
    for (int i = 0; i < rn -> nbOutput; i++){
        fgets(line, sizeMax, biasO);
        strtok(line, "\n");
        rn -> BiasOutput[i] = atof(line);
    }
    fclose(biasO);


    FILE* biasH1 = fopen("NeuralNetwork/SaveNN/BiasH1.txt", "r");
    for (int i = 0; i < rn -> nbHidden1; i++){
        fgets(line, sizeMax, biasH1);
        strtok(line, "\n");
        rn -> BiasH1[i] = atof(line);
    }
    fclose(biasH1);

    FILE* biasH2 = fopen("NeuralNetwork/SaveNN/BiasH2.txt", "r");
    for (int i = 0; i < rn -> nbHidden2; i++){
        fgets(line, sizeMax, biasH2);
        strtok(line, "\n");
        rn -> BiasH2[i] = atof(line);
    }
    fclose(biasH2);

    //WeightIH1
    FILE* weightIH1= fopen("NeuralNetwork/SaveNN/WeightIH1.txt", "r");
    for(int i = 0; i < rn -> nbInput; i++){
        for(int j = 0; j < rn -> nbHidden1; j++){
            fgets(line, sizeMax, weightIH1);
            strtok(line, "\n");
            rn -> WeightIH1[i][j] = atof(line);
        }
    }
    fclose(weightIH1);


    FILE* weightH1H2= fopen("NeuralNetwork/SaveNN/WeightH1H2.txt", "r");
    for(int i = 0; i < rn -> nbHidden1; i++){
        for(int j = 0; j < rn -> nbHidden2; j++){
            fgets(line, sizeMax, weightH1H2);
            strtok(line, "\n");
            rn -> WeightH1H2[i][j] = atof(line);
        }
    }
    fclose(weightH1H2);


    FILE* weightH2O= fopen("NeuralNetwork/SaveNN/WeightH2O.txt", "r");
    for(int i = 0; i < rn -> nbHidden1; i++){
        for(int j = 0; j < rn -> nbOutput; j++){
            fgets(line, sizeMax, weightH2O);
            strtok(line, "\n");
            rn -> WeightH2O[i][j] = atof(line);
        }
    }
    fclose(weightH2O);

    return rn;

}


/**
 *  arg : NeuralNetwork *rn --> notre réseau
 *
 *  tout les x itérations on appelle cette fonction,
 *  elle enregistre les valeurs du réseau et elle appelle la fonction qui test toutes les lettres
 *
*/

/**
  * arg: NeuralNetwork * rn -> our network
  *
  * every x iterations we call this function,
  * it saves the values of the network and it calls the function which tests all the letters
  *
*/

void state(struct NeuralNetwork *rn){


    printf(WHT "\nSerie de Test : \n\n");
    printf( "Sucess : %f%%\n\n",testAllLetters(rn,1));
}



/**
 *  arg : NeuralNetwork *rn --> notre réseau
 *        int current -> le numéro de l'itération d'où l'on commence le training
 *
 *  Cette fonction permet d'entrainer notre réseau
 *
 *  elle appelle la fonction neuralNetwork en boucle
 *  elle appelle également la fonction state pour les auvergardes et les prints
 *
 *  pour un nouvelle entrainement  --> on met int current à 0
 *          si on veut continuer un entrainement avec un réseau déjà entrainer --> on met int currant à la valeur de la dernière sauvergarde de notre réseau
 *
*/

/**
  * arg: NeuralNetwork * rn -> our network
  * int current -> the number of the iteration from which we start the training
  *
  * This function allows to train our network
  *
  * it calls the neuralNetwork function in loop
  * it also calls the state function for the auvergardes and the prints
  *
  * for a new training -> we set int current to 0
  * if we want to continue training with a network already trained -> we set current to the value of the last backup of our network
  *
*/

void training(struct NeuralNetwork *rn, int current){

    int nbmin = 4*26;
    int nbmaj = 5*26;

    int nbmindiv = nbmin/26;
    int nbmajdiv = nbmaj/26;

    int nbIteration = 1000000;
    int nbLetters = nbmin + nbmaj; //234

    int pos = 0;
    int printState = 1000;

    double **letters = matLetters();


    double **wantedMa = wantedMat();

    for (int i = current; i < nbIteration;i++) {
        if(i %10 == 0 ) printf(MAG "Iteration : %i\n",i);

        if(i != 0 && i % printState == 0){
            state(rn);
        }

        if(i != 0 && i % 10000 == 0){
            saveData(rn);
        }

        for (int j = 0; j < nbLetters; ++j){


            if(j < nbmin){
                pos = j/nbmindiv;
            }
            else{
                pos = (j - nbmin)/nbmajdiv + 26;
            }


            neuralNetwork(rn, letters[j],wantedMa[pos]);
        }

    }


    saveData(rn);

}


/**
 *  commence un nouvelle entrainement en initialisant un nouveau réseau
 *
*/

/**
  * start a new training by initializing a new network
  *
*/

void beginTraining(){


    struct NeuralNetwork *rn = initializeNetwork();

    remove("NeuralNetwork/SaveNN/Sucess.txt");

    training(rn, 0);

}


/**
 *  continue l'entrainement depuis la valeur choisi,
 *          en initialisant un réseau avec les valeurs présentes dans SaveNN
 *
*/

/**
  * continue training from the chosen value,
  * by initializing a network with the values present in SaveNN
  *
*/

void continueTraining(int current){

    struct NeuralNetwork *rn = initValue();
    training(rn, current);

}


/**
 *
 *
 * Function use in the main file
 * arg --> filename --> chemin du fichier
 *
 *    --> return letter found by the neural Network
 */

char ocr(char *filename){

    struct NeuralNetwork *rn = initValue();


    double *input = matImageFromFile(filename);



    for(int j = 0; j < rn -> nbInput; j++)
    {
        rn -> neuralValueInput[j] = input[j];
    }



    feedForward(rn);

    char res = letterPosChar(maxOutput(rn));

    for(int k = 0; k < 28*28; k++){
        if(k == 420) printf("\t --> %c",res);
        if(k % 28 == 0) printf("\n");
        printf("%i",(int)rn -> neuralValueInput[k]);
    }

    printf("\n");
    return res;
}



//int main() {



  //  printf("\t%c\n",ocr("BD/majs/A/A2.txt"));

    /**
     * Pour commencer un nouvelle entrainement faire :
     *          beginTraining();
     *
     * WARNING : cette action remplacera les fichiers de sauvergardes déjà présent
     *
     *
     */



    /**
     * Pour continuer un entrainement faire :
     *
     *          continueTraining(int i):
     *
     *
     *          int i --> correspond à la dernière itération sauvergarder par votre dernier entrainement sur ce reseau
     *
     *          --> cad la dernière itération revenu au 1000ème d'avant
     *
     *          Ex --> 68 743 --> 68 000 (int de la dernière sauvegarde)
     *
     *          Cette valeur est en réalité objective mais elle permet de savoir a peu près où vous en êtes
     *          (si vous écrivez une estimation ex 50 000 au lieu de 60 000 ca ne changera pas fondamentalement)
     *
     * WARNING : cette action remplacera les fichiers de sauvergardes déjà présent
     *
     *
     */

    /**
     *     Pour tester un reseau
     *
     *     Etape 1) Verifier que les sauvergardes se trouvent bien dans OCR/SaveNN
     *
     *     Etape 2)
     *
     *          struct NeuralNetwork *rn = initValue();
     *
     *          testAllLetters(rn,0);
     *
     */



//    beginTraining();

    //continueTraining(529000);



    /*
    struct NeuralNetwork *rn = initValue();

    testAllLetters(rn, 1);

    */
//}

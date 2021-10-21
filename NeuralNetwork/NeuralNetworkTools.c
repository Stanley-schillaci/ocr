#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "NeuralNetwork.h"
#include "NeuralNetworkPrintValue.h"

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KBLU  "\x1B[34m"
#define RESET "\x1B[0m"
#define CYN   "\x1B[36m"
#define MAG   "\x1B[35m"


/**
 * Ce fichier contient tout les programmes "outils" pour le réseau de neuronne
 *
*/

/**
  * This file contains all the "tool" programs for the neural network
  *
*/





/** sigmoid
 *
 * Args : x (double)  --> Valeur sur R
 * Return : double --> Valeur entre [0;1]
 * Purpose : Simplifier nos calculs en ramenant tout en 0 et 1
*/

/** sigmoid
  *
  * Args: x (double) -> Value on R
  * Return: double -> Value between [0; 1]
  * Purpose: Simplify our calculations by reducing everything to 0 and 1
*/

double sigmoid(double x){
    return(1.0 / (1.0 + exp(-x)));
}

/** sigmoidPrime
 *
 * Args : x (double)  --> a signmoid function --> valeur entre [0;1]
 * Return : double --> La dérivé de sigmoid donc la pente de la courbe
 * Purpose : Lors de la backpropagation il nous faut savoir si notre fonction de cout à un point précis est croissante
 *           ou bien décroissante afin de trouver un minimum local
 *           Pour cela on utilisera la dérivé de sigmoid (car au préalable notre fonction de cout sera une fonction
 *           sigmoid)
 *           De cette manière on sait si la pente est croissante ou décroissante.
*/

/** sigmoidPrime
  *
  * Args: x (double) -> a signmoid function -> value between [0; 1]
  * Return: double -> The derivative of sigmoid therefore the slope of the curve
  * Purpose: During backpropagation we need to know if our cost function at a specific point is increasing
  * or decreasing in order to find a local minimum
  * For this we will use the derivative of sigmoid (because beforehand our cost function will be a function
  * sigmoid)
  * In this way we know whether the slope is increasing or decreasing.
*/

double sigmoidPrime(double x){
    return x * (1.0 - x);
}


/** random
 *
 * Args : aucun
 * Return : double --> entre -1 et 1
 * Purpose : Lors de la création d'une nouvelle base de réseau de neuronne, on initialise, les poids et les bias.
 *
*/

/** random
  *
  * Args: none
  * Return: double -> between -1 and 1
  * Purpose: When creating a new neural network base, we initialize, weights and biases.
  *
*/

double randomNN(){
    static int first = -1;
    if((first = (first<0)))
        srand(time(NULL)+getpid());

    return ((double)rand()) / ((double)RAND_MAX / 2) -1;
}

/** wanted
 *
 * Args : c (char) entre 'a' et 'z' ou 'A' et 'Z'
 * Return : *double -> array contenant 51 fois la valeur 0 et une fois la valeur 1
 * Purpose : Lors de notre backpropagation on a besoin de calculer l'erreur de notre programme,
 *           pour cela on lui dit qu'elle était l'ouput attendu grâce à cette fonction.
 *
*/

/** wanted
  *
  * Args: c (char) between 'a' and 'z' or 'A' and 'Z'
  * Return: * double -> array containing 51 times the value 0 and once the value 1
  * Purpose: During our backpropagation we need to calculate the error of our program,
  * for that we tell him that it was the expected ouput thanks to this function.
  *
*/

double *wanted(char c){
    double *goal = calloc(52, sizeof(double));

    //minuscule
    if(c >= 97 && c <= 122){
        goal[c - 97]= 1.0;

    }
    //majuscule
    else if(c >= 65 && c <= 90){
        goal[c - 39] = 1.0;
    }
    else{
        printf("%c",c);
        printf("Caractère not supported\n");
        exit(1);
    }

    return goal;
}



/** wantedMat
 *
 * Args : aucun
 * Return : **double -> array d'array de double --> contenant les 52 arrays que peut renvoyer la fonction wanted (voir au dessus)
 * Purpose : Au lieu d'appeler la fonction wanted a chaque itération, on crée dès le début de l'entrainement une matrice contenant toute les réponses possibles
 *           afin de ne pas crée de nouvelle array à chaque itération (cela nous à causer des gros problèmes de mémoire dans les premières versions du programme)
 *
*/

/** wantedMat
  *
  * Args: none
  * Return: ** double -> array of array of double -> containing the 52 arrays that the wanted function can return (see above)
  * Purpose: Instead of calling the wanted function at each iteration, we create at the start of the training a matrix containing all the possible responses
  * so as not to create a new array with each iteration (this caused us big memory problems in the first versions of the program)
  *
*/

double **wantedMat(){
    double **wantReturn = malloc(sizeof(double) * 52);
    char min = 'a';
    char maj = 'A';

    for (int i = 0; i < 26; ++i) {
        wantReturn[i] = wanted(min);
        min +=1;
    }

    for (int j = 26; j < 52; ++j) {
        wantReturn[j] = wanted(maj);
        maj +=1;
    }

    return wantReturn;
}

/** wantedMat
 *
 * Args : *double
 * Return : int pos --> position de la valeur 1 dans la matrice wanted (voir fonction au dessus)
 * Purpose : Trouver le 1 dans une matrice de wanted (surtout utilisé pour faire des test)
 *
*/

/** wantedMat
  *
  * Args: * double
  * Return: int pos -> position of value 1 in the wanted matrix (see function above)
  * Purpose: Find the 1 in a wanted matrix (mostly used for testing)
  *
*/

int posWanted(double *wanted) {
    int pos = -1;
    for (int i = 0; i < 52; i++) {
        if(wanted[i] == 1.0){
            pos = i;
        }
    }

    return pos;
}

/** letter
 *
 * Args : int i --
 * Return : la lettre qu'on l'on veut tester
 * Purpose : Dans notre programme de training dans (NeuralNetwork.c) à chaque itération on appelle notre programme avec un certain nombre de lettre,
 *           suivant le nombre de lettre minuscule et majuscule mis dans la base de données on peut savoir qu'elle itération dans l'itération (double boucle for) correspond à quelle lettre
*/

/** letter
  *
  * Args: int i -
  * Return: the letter we want to test
  * Purpose: In our training program in (NeuralNetwork.c) at each iteration we call our program with a certain number of letters,
  * depending on the number of lowercase and uppercase letters put in the database, we can know which iteration in the iteration (double for loop) corresponds to which letter
*/

int letterN(int i){

    char min = 'a';
    char maj = 'A';
    int nbmin = 4*26; //104
    int nbmaj = 5*26; //130

    int div = nbmin/26;
    int divmaj = nbmaj/26;

    if(i < nbmin){
        return min += i / div;
    }
    else{
        return maj += (i - nbmin) / divmaj;
    }


}


/** matImageFromFile
 *
 * Args : char --> chemin d'un fichier
 * Return : retourner une matrice de 0 et de 1
 * Purpose : après avoir binarisé un caractère et l'avoir sauvergardé d'un fichier, on peut obtenir une matrice de ce fichier grâce à cette fonction.
 *
*/

/** matImageFromFile
  *
  * Args: char -> path of a file
  * Return: return a matrix of 0 and 1
  * Purpose: after having binarized a character and having saved it from a file, we can obtain a matrix of this file thanks to this function.
  *
*/

double *matImageFromFile(char *filename)
{
    double *matImage = malloc(sizeof(double) * 28 * 28);
    FILE *fptr = fopen(filename,"r");

    if(fptr == NULL) {
        printf("%s : File is NULL \n",filename);
    }

    for(int i = 0; i <= 28; i++)
    {
        for(int j = 0; j <= 28; j++)
        {
            int bin = fgetc(fptr);
            if(bin == 49){
                matImage[i*28 + j] = 1;
            }
            else if(bin == 48){
                matImage[i*28 + j] = 0;
            }
        }
    }
    fclose(fptr);
    return matImage;
}


/** matLetters
 *
 * Args : aucun
 * Return : **double --> array d'array de matImageFromFile
 * Purpose : Au lieu d'appeller matImageFromFIle à chaque itération, on l'appelle une seule fois à l'initialisation du training pour chaque caractères dans notre base de données
 *
*/

/** matLetters
  *
  * Args: none
  * Return: ** double -> array array of matImageFromFile
  * Purpose: Instead of calling matImageFromFIle at each iteration, we call it once when training is initialized for each character in our database
  *
*/

double **matLetters(){

    double **MatLettersR = malloc(sizeof(double *) * 52);
    char path[31] = "NeuralNetwork/BD/m00s/0/00.txt";

    char count = '0';
    char min = 'a';
    char maj = 'A';

    int nbmin = 4*26;
    int nbmaj = 5*26;

    int nbmindiv = nbmin/26;
    int nbmajdiv = nbmaj/26;

    for (int i = 0; i < nbmin + nbmaj; ++i) {
        if(i < nbmin){

            path[18] = 'i';
            path[19] = 'n';

            if(count < ('0' + nbmindiv) ){
                path[22] = min;
                path[24] = min;
                path[25] = count;
            }
            else{
                count = '0';
                min += 1 ;
                path[22] = min;
                path[24] = min;
                path[25] = count;
            }
        }
        else{
            if(i == nbmin) count = '0';

            path[18] = 'a';
            path[19] = 'j';

            if(count < ('0' + nbmajdiv) ){
                path[22] = maj;
                path[24] = maj;
                path[25] = count;
            }
            else{
                count = '0';
                maj += 1 ;
                path[22] = maj;
                path[24] = maj;
                path[25] = count;
            }
        }
        count += 1;

        double *mat = matImageFromFile(path);

        MatLettersR[i] = mat;

    }
    return MatLettersR;
}

/** maxOutput
 *
 * Args : struct NeuralNetwork
 * Return : retourner la position du neuronne de la couche des outputs layer le plus activé
 * Purpose : Notre réseau nous renvoi après chaque feedForward ses résulats,
 *           le neuronnes le plus activé correspond à celui qui à le plus de chance d'être le bon selon le réseau
 *
*/

/** maxOutput
  *
  * Args: struct NeuralNetwork
  * Return: return the position of the most activated output layer neuron
  * Purpose: Our network refers us after each feedForward its results,
  * the most activated neurons correspond to the one that has the most chance of being the right one according to the network
  *
*/

int maxOutput(struct  NeuralNetwork *rn){
    double max = 0.0;
    int pos = 0;
    for (int i = 0; i < rn -> nbOutput; i++) {
        if(rn -> neuralValueOutput[i] > max){
            max = rn -> neuralValueOutput[i];
            pos = i;
        }
    }
    return pos;
}

/** letterPosChar
 *
 * Args : int n --> position récupérer dans la fonction maxOutput
 * Return : char
 * Purpose : après avoir récupéré l'index du neuronne d'output le plus activé (grâce a maxOutput)
 *           on traduit l'index du neuronne, par le caractères correspondant (voir le fichier wanted.txt --> fichier uniquement à titre indicatif)
 *
*/

/** letterPosChar
  *
  * Args: int n -> position retrieve in the maxOutput function
  * Return: char
  * Purpose: after having retrieved the index of the most activated output neuron (thanks to maxOutput)
  * we translate the index of the neuron, by the corresponding characters (see the file wanted.txt -> file only for information)
  *
*/

char letterPosChar(int n){
    if (n < 26){
        return 'a' + n;
    }
    else{
        return 'A' + n - 26;
    }
}


/** letterPosInt
 *
 * Args : char c;
 * Return : int
 * Purpose : c'est l'inverse de la fonction letterPosChar --> elle est utilisé uniquement pour faire des tests.
 *
*/

/** letterPosInt
  *
  * Args: char c;
  * Return: int
  * Purpose: this is the reverse of the letterPosChar function -> it is only used for testing.
  *
*/

int letterPosInt(char c){
    if(c >= 97 && c <= 122){
        return c - 'a';

    }
    else if(c >= 65 && c <= 90){
        return c - 'A' + 26;
    }
    else{
        return -1;
    }
}

/** test
 *
 * Args : Struct NeuralNetwork --> notre réseau
 *        char *filename --> le chemin du fichier de lettre binarisé à tester
 *        char want --> la bonne réponse
 * Return : int -> 1 ou 0 --> équivalent d'un booléen
 * Purpose : on test notre réseau sur une lettre
 *
*/

/** test
  *
  * Args: Struct NeuralNetwork -> our network
  * char * filename -> the path of the binarized letter file to test
  * char want -> the correct answer
  * Return: int -> 1 or 0 -> equivalent of a boolean
  * Purpose: we test our network on a letter
  *
*/

int test(struct  NeuralNetwork *rn, char *filename, char want){

    double *input = matImageFromFile(filename);

    for(int j = 0; j < rn -> nbInput; j++)
    {
        rn -> neuralValueInput[j] = input[j];
    }

    feedForward(rn);
    char res = letterPosChar(maxOutput(rn));


    if(want == res){
        return 1;
    }
    else{
        return 0;
    }





}

/** testLetter
 *
 * Args : Struct NeuralNetwork --> notre réseau
 *        char c --> caractères à tester
 * Return : int -> nombre de bonne réponses
 * Purpose : on test notre réseau sur l'ensemble des versions d'un caractères présent dans notre base de données.
 *
*/

/** testLetter
  *
  * Args: Struct NeuralNetwork -> our network
  * char c -> characters to test
  * Return: int -> number of correct answers
  * Purpose: we test our network on all the versions of a character present in our database.
  *
*/

int testLetter(struct  NeuralNetwork *rn, char c){

    int count = 0;
    char nb = '0';

    int nbmindiv = 4;
    int nbmajdiv = 5;

    if(c >= 97 && c <= 122){
        char path[31] = "NeuralNetwork/BD/mins/0/00.txt";
        path[22] = c;
        path[24] = c;

        for (int i = 0; i < nbmindiv; i++) {
            path[25] = nb;
            count += test(rn, path,c);
            nb +=1;
        }

    }
    else if(c >= 65 && c <= 90){
        char path[31] = "NeuralNetwork/BD/majs/0/00.txt";
        path[22] = c;
        path[24] = c;

        for (int i = 0; i < nbmajdiv; i++) {
            path[25] = nb;
            count += test(rn, path,c);
            nb +=1;
        }
    }

    return count;
}


/** testLetter
 *
 * Args : Struct NeuralNetwork --> notre réseau
 *        int arg --> n'affiche pas de print si arg == 0
 * Return : double --> pourcentage de réussite
 * Purpose : on test notre réseau sur l'ensemble des versions de chaques caractères de notre base de données
 *           et on renvoi un joli print
*/

/** testLetter
  *
  * Args: Struct NeuralNetwork -> our network
  * int arg -> does not display print if arg == 0
  * Return: double -> percentage of success
  * Purpose: we test our network on all the versions of each character in our database
  * and we send back a nice print
*/

double testAllLetters(struct NeuralNetwork *rn,int arg){
    int globalCount = 0;
    int globalCountMin = 0;
    int globalCountMaj = 0;
    int charcountMin = 0;
    int charcountMaj = 0;
    char min = 'a';
    char maj = 'A';

    for (int i = 0; i < 26; ++i) {
        charcountMin += testLetter(rn,min);
        charcountMaj += testLetter(rn,maj);

        if(arg != 0){
            if(charcountMin < 3){
                printf(KRED "char : %c ---> %i/4 -> %i%%",min,charcountMin,(charcountMin*25));
            }
            else if(charcountMin == 4){
                printf(KGRN "char : %c ---> %i/4 -> %i%%",min,charcountMin,(charcountMin*25));
            }else{
                printf(KBLU "char : %c ---> %i/4 -> %i%%",min,charcountMin,(charcountMin*25));
            }

            printf("\t\t\t");


            if (charcountMaj < 4) {
                printf(KRED "char : %c ---> %i/5 -> %i%%\n", maj, charcountMaj, (charcountMaj * 20));
            } else if (charcountMaj == 5) {
                printf(KGRN "char : %c ---> %i/5 -> %i%%\n", maj, charcountMaj, (charcountMaj * 20));
            } else {
                printf(KBLU "char : %c ---> %i/5 -> %i%%\n", maj, charcountMaj, (charcountMaj* 20));
            }
        }


        globalCountMin += charcountMin;
        globalCountMaj += charcountMaj;






        min +=1;
        maj += 1;

        charcountMin = 0;
        charcountMaj = 0;
    }


    globalCount = globalCountMin + globalCountMaj;

    double percentage = 0.0;
    for (int i = 0; i < globalCount; i++) {
        percentage += 0.42735043;
    }

    if(arg != 0) {

        if (globalCountMin < 78) {
            printf(KRED "\nTotal Minuscule result %i/104", globalCountMin);
        } else if (globalCountMin > 100) {
            printf(KGRN "\nTotal Minuscule result %i/104", globalCountMin);
        } else {
            printf(KBLU "\nTotal Minuscule result %i/104", globalCountMin);
        }

        printf("\t\t\t");

        if (globalCountMaj < 104) {
            printf(KRED "Total Majuscule result %i/130\n", globalCountMaj);
        } else if (globalCountMaj > 126) {
            printf(KGRN "Total Majuscule result %i/130\n", globalCountMaj);
        } else {
            printf(KBLU "Total Majuscule result %i/130\n", globalCountMaj);
        }




        if (percentage < 75.0) {
            printf(KRED "\nTotal result %i/234 --> %f%%\n\n", globalCount, percentage);
        } else if (percentage > 95.0) {
            printf(KGRN "\nTotal result %i/234 --> %f%%\n\n", globalCount, percentage);
        } else {
            printf(KBLU "\nTotal result %i/234 --> %f%%\n\n", globalCount, percentage);
        }
        printf(RESET "");
    }

    return percentage;
}


/** saveData
 *
 * Args : Struct NeuralNetwork --> notre réseau
 * Return : void
 * Purpose : écrit dans le dossier "SaveNN" les valeurs de chaques poids et chaque bias.
 *           de cet manière après un entrainement on peut réutilliser un réseau qu'on a sauvergarder
 *           il y à aussi un fichier "Sucess" qui permet de suivre l'évolution du pourcentage au fil des entrainements
 *
*/

/** saveData
  *
  * Args: Struct NeuralNetwork -> our network
  * Return: void
  * Purpose: write in the "SaveNN" folder the values of each weight and each bias.
  * in this way after training we can reuse a network that we have saved
  * there is also a "Sucess" file which allows you to follow the evolution of the percentage over the training sessions
  *
*/

void saveData(struct NeuralNetwork *rn){
    FILE *fptr;

    fptr = fopen("NeuralNetwork/SaveNN/BiasOutput.txt","w");
    for (int i = 0; i < rn -> nbOutput; i++) {
        fprintf(fptr, "%f\n", rn -> BiasOutput[i]);
    }
    fclose(fptr);

    fptr = fopen("NeuralNetwork/SaveNN/BiasH1.txt","w");
    for (int i = 0; i < rn -> nbHidden1; i++) {
        fprintf(fptr, "%f\n", rn -> BiasH1[i]);
    }
    fclose(fptr);

    fptr = fopen("NeuralNetwork/SaveNN/BiasH2.txt","w");
    for (int i = 0; i < rn -> nbHidden2; i++) {
        fprintf(fptr, "%f\n", rn -> BiasH2[i]);
    }
    fclose(fptr);

    fptr = fopen("NeuralNetwork/SaveNN/WeightIH1.txt","w");
    for (int i = 0; i < rn -> nbInput; i++) {
        for(int j = 0; j < rn -> nbHidden1; j++){
            fprintf(fptr, "%f\n", rn -> WeightIH1[i][j]);
        }
    }
    fclose(fptr);

    fptr = fopen("NeuralNetwork/SaveNN/WeightH1H2.txt","w");
    for (int i = 0; i < rn -> nbHidden1; i++) {
        for(int j = 0; j < rn -> nbHidden2; j++){
            fprintf(fptr, "%f\n", rn -> WeightH1H2[i][j]);
        }
    }
    fclose(fptr);

    fptr = fopen("NeuralNetwork/SaveNN/WeightH2O.txt","w");
    for (int i = 0; i < rn -> nbHidden2; i++) {
        for(int j = 0; j < rn -> nbOutput; j++){
            fprintf(fptr, "%f\n", rn -> WeightH2O[i][j]);
        }
    }
    fclose(fptr);

    fptr = fopen("NeuralNetwork/SaveNN/Sucess.txt","a");
    fprintf(fptr, "%f%%\n", testAllLetters(rn,0));
    fclose(fptr);

    printf(CYN "[saveData] Done\n");
}


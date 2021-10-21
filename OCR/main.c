# include "main.h"


#define WHT   "\x1B[37m"
#define KGRN  "\x1B[32m"
#define KBLU  "\x1B[34m"
#define CYN   "\x1B[36m"
#define MAG   "\x1B[35m"


void help(){
    printf(KGRN "\nWelcome to the OCR projet of the JSML Team\n\n ");
    printf("Please use the commands : \n ");
    printf(CYN "\t ./main digitalProcess 'path' --> to applique a preprocess to a picture\n\n");
    printf(KBLU "\t ./main segmentation 'path' --> to use segmentation on a picture\n\n");
    printf(MAG "\t ./main neuralNetwork 'path' --> to predict a char --> Warning you must use 28*28 picture binarize\n ");
    printf("\t ./main neuralNetwork beginTraining --> to start a new training --> Warning it will erase actual Value for our network\n ");
    printf("\t ./main neuralNetwork continueTraining int --> to continue a training --> int is the last iteration you make (you can put any value)\n ");
    printf("\n\t  Une base de données contenu des caractères en .txt se trouve dans le dossier NeuralNetwork/BD/...\n");
    printf(WHT "\n");
}


int main(int argc, char *argv[]){

    if(argc > 1){
        if(strcmp(argv[1], "help") == 0){
            help();
        }else if(strcmp(argv[1], "digitalProcess") == 0) {
            digitalProcess(argv[2]);
        }else if(strcmp(argv[1], "segmentation") == 0) {
            segmentation(argv[2]);
        }else if(strcmp(argv[1], "neuralNetwork") == 0){
            if(strcmp(argv[2], "beginTraining") == 0){
                beginTraining();
            }
            if(strcmp(argv[2], "continueTraining") == 0){
                unsigned long param = strtoul(argv[3], NULL, 10);
                continueTraining(param);
            }
            else{
               ocr(argv[2]);
            }
        }
    }else{
        help();
    }
}
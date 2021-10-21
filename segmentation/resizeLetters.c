#include "headers/resizeLetters.h"
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

//function that copy the array src to the array dst
void arrCp(int * src, int * dst, int len){
	for(int i=0;i<len;i++)
    {
	    dst[i] = src[i];
    }
}

void printL(Letter * l)//function which permitted to see the array we use
{
    printf("\n\n");
    for(int y = 0; y < l->height; y++)
    {
        for(int x = 0; x < l->width; x++)
        {
            printf("%d ", l->array[y*l->width+x]);
        }

        printf("\n");
    }
}

//Erased the useless line
void cropH(Letter * l){
	printf("cropH\n");
	int w = l->width;
	int h = l->height;
	
	int ny = 0;

	//Check if the line is empty
	for(int y = 0; y < h; y++)
	{
		int em = 0;
		int x  = 0;
		while( x < w && !em)
		{
			if (l->array[y*w+x] == 1)
            {
			    em = 1;
            }
			x+=1;
		}
		//if the line is a white line we increments our ny variable to see the number of line that is useless
		if(em)
		{
			for(int i=0; i < w; i++)
            {
			    l->array[ny*w+i] = l->array[y*w+i];
            }
			ny++;
		}
	}
	//Update the new heigth without the useless line
	l->height -= (l->height - ny);
}

//Erased uselless columns of the array
void cropW(Letter * l){
	printf("cropW\n");
	int w = l->width;
	int h = l->height;
	
	int newW = 0;

    //Check if a useless character is at the end of each line and if there is one we increments newW
	for(int x = 0; x < w; x++)
	{

		int em = 0;
		int y = 0;
		while( y < h && !em)
		{
			if (l->array[y*w+x] == 1)
			{
				em = 1;
				newW++;
			}
			y++;
		}
	}
	if(newW != w) // If we found a useless column newW will be different of w
	{
		int *ar = (int*) malloc(sizeof(int)*h*newW);
		for(int i=0; i <newW*h; i++) // create a new array of value 2 with dimension h and newW
        {
		    ar[i] = 2;
        }

		int nx = 0;
		for(int x = 0; x < w; x++)
		{
			int em = 0;
            int y=0;
			while( y < h && !em)//Check where there is a black character
			{
				if (l->array[y*w+x] == 1)
                {
				    em = 1;
                }
				y++;
			}

			if(em)// if there is one copy the value the whole line in ar
			{
				for(int z=0; z < h; z++)
                {
				    ar[nx + z * newW] = l->array[x + z * w];
                }
				nx++;
			}

		}
		l->width = newW;
		arrCp(ar,l->array,l->width*l->height);// the copy will just redimension l
		free(ar);
	}
}

//Place the character in a 28*28 array top-left corner
void corner(Letter * l){
	printf("corner\n");
	int newS = 28;

	int *ar = (int*) malloc(sizeof(int)*newS*newS);//Create an array of 0 with dimension 28*28
	for(int i=0; i <newS*newS; i++)
    {
	    ar[i] = 0;
    }

	//Copy the value of each coordinate of l in ar
	for(int y = 0; y < l->height; y++)
	{
		for(int x = 0; x < l->width; x++)
        {
		    ar[y*newS+x] = l->array[y*l->width+x];
        }
	}
	l->height = newS;
	l->width  = newS;

	l->array = malloc(sizeof(int)*l->width*l->height);//create a new array with de new dimension
	arrCp(ar,l->array,l->width*l->height);//copy the value in l
	free(ar);
}


void addWhiteLine(Letter * l){//add a new line of 0
	printf("addWhiteLine\n");
	l->height++;
	
	for(int x=0; x < l->width; x++)
		l->array[(l->height-1)*l->width+x] = 0;
}

void addWhiteCollumn(Letter * l){ //add a new column
	printf("addWhiteC\n");
	int *ar = (int*) malloc(sizeof(int)*(l->width+1)*l->height);//Create an array of 0 of the dimension of heigth and width+1
	for(int i=0; i <(l->width+1)*l->height; i++)
    {
	    ar[i] = 0;
    }
		
	for(int y = 0; y < l->height; y++)//copy the value of l in ar
	{
		for(int x = 0; x < l->width; x++)
        {
		    ar[y*(l->width+1)+x] = l->array[y*l->width+x];
        }
	}
	
	l->width++;
	
	l->array =malloc(sizeof(int)*l->width*l->height);//recreate the l array with new dimension
	arrCp(ar,l->array,l->width*l->height);//copy the value of ar in l
	free(ar);
}

//Make the letter as big as possible
void scaleUp(Letter * l){
	printf("scaleUP\n");
	
	if(l->height%2 != 0)//if height is impair we add a line
    {
	    addWhiteLine(l);
    }
		
	if(l->width%2 != 0)//if width is impair we add a column
    {
	    addWhiteCollumn(l);
    }

	int h = l->height;
	int w = l->width;
	int newH = h*2;
	int newW = w*2;

	int *ar = (int*) malloc(sizeof(int)*newH*newW);//create an array of value 0 and dimension 2*height and 2*width
	for(int i=0; i <newW*newH; i++)
    {
	    ar[i] = 0;
    }
	//For scale up one pixel will become 4 pixel
	int i=0;
    int j;
	for(int y=0; y<h; y++)
	{
        j = 0;
		for(int x=0; x<w; x++)
		{
			int px = l->array[y*w+x];// we get a pixel
			ar[(i)*newW+(j)] = px;//we multiplicate in ar
			ar[(i)*newW+(j+1)] = px;
			ar[(i+1)*newW+(j)] = px;
			ar[(i+1)*newW+(j+1)] = px;
			j+=2;
		}
		i+=2;
	}

	l->height = newH;// we set the new dimension of the array
	l->width = newW;

    arrCp(ar,l->array,l->width*l->height);
	//free(ar);  //I do not know why we do not have to free the memory in this case
}


//Reduce the size of a letter
void reduce(Letter * l){
	//Loop offer the array with x+2 and y+2;
	printf("reduce\n");
	
	if(l->height%2 != 0)
    {
	    addWhiteLine(l);
    }
		
	if(l->width%2 != 0)
	{
		addWhiteCollumn(l);
	}


	int h = l->height;
	int w = l->width;
	int newH = h/2;
	int newW = w/2;

    //create a new array of 0 with dimension heigth/2 and width/2
    int *ar = (int*) malloc(sizeof(int)*newH*newW);
	for(int i=0; i <newW*newH; i++)
    {
	    ar[i] = 0;
    }

    int i =0;
	int j;
	for(int y=0; y<h-2; y+=2)
	{
	    j = 0;
		for(int x=0; x<w-2; x+=2)
		{
		    //av is the average of 4 pixels that are beside
			int av = l->array[(y+1)*w+x]+l->array[(y+1)*w+x+1];
			av += l->array[y*w+x]+l->array[y*w+x+1];
			av = av/4;

			if(av<0.5){//We needs to have the average to have the value of each coordinate in ar
			    av=0;
			}
			else{
			    av=1;
			}
			ar[i*newW+j] = av;
			j++;
		}
		i++;
	}

	l->height = newH;
	l->width = newW;

	arrCp(ar,l->array,l->width*l->height);
	free(ar);
}

//Do the resizing process
void resize(Letter * l){
	printf("resize\n");
	//cut the useless border
	cropH(l);
	cropW(l);

	//if it is too big we have to reduce the array
	while(l->width > 28  ||  l->height > 28){
		reduce(l);
		cropH(l);
		cropW(l);
	}

    // if it is to small we have to increase the size of the array
	while(MAX(l->height,l->width) <= 28/2){
		scaleUp(l);
		if(MAX(l->height,l->width) != 28)
        {
		    cropH(l);
            cropW(l);
        }

	}
}



void process(Letter ** letterList){
	for(long unsigned int i =0; i < sizeof(letterList)/sizeof(Letter);i++)
		resize(letterList[i]);
}
/*
void main_resize(){
	Letter *l =(struct Letter*) malloc(sizeof(Letter));

	int *arr;
	l->array=(int*)malloc(sizeof(int)*29*30);

	l->height = 7;
	l->width = 6;

	arr=(int[]){1,1,1,1,1,0,
				1,0,0,0,0,0,
				1,1,0,0,0,0,
				1,0,0,0,0,0,
				1,1,1,1,1,0,
				0,0,0,0,0,0,
				0,0,0,0,0,0};

    //you have to choose between those two test if you want to test
	l->height = 29;
	l->width = 30;

	arr=(int[]){1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


	for(int i=0;i<7*6;i++)
		l->array[i]=arr[i];

	printL(l);

	resize(l);
	printL(l);


	//addWhiteCollumn(l);
    //printL(l);

	//addWhiteLine(l);
	//printL(l);

	//scaleUp(l);
	//printL(l);

	//cropH(l);
	//printL(l);

	//cropW(l);
	//printL(l);

	//reduce(l);
	//printL(l);

	free(l);
}
*/

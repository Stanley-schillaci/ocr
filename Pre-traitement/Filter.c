#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pixel_operations.h"

/*
int **data;
int hist[255];
double sigma[255],sort[255];

double otsu(int min,int max,int ht,int wth)
{
	//printf("\n Function call ");
  int i,j;
	double mean=0.0,wt_bg,sum=0.0,mean_bg,var=0.0,var_bg;
	double varience,sq,diff;
	
		for(i=min;i<=max;i++)
		{
			//wt = wt + hist[i];
			mean=mean+i*hist[i];
			sum = sum+hist[i];
		}
		if(sum!=0.0)
		{
		//printf("\nMean=%f Sum=%f",mean,sum);
		wt_bg = sum/(ht*wth);
		//printf("\nWeight = %f",wt_bg);
		mean_bg = mean/sum;		
		//printf("\nmean = %f",mean_bg);
		for(j=min;j<=max;j++)
		{
			diff = j-mean_bg;
			sq= pow(diff,2);
			var =var + (sq*hist[j]);
		}
		//printf("\n%f", var);
		var_bg=var/sum;
		varience = wt_bg * pow(var_bg,2);
		return (varience);
		}
		else
			return(0.0);
}

int histogram_otsu(SDL_Surface* l)
{

	int i,j,k,t,count,final_threshold;
	float threshold;
	double var_bg;
	double var_fg;
	double thes,temp;
	int wth= l->w;
	int ht= l->h;
	
	for(k=0;k<=255;k++)
	{
		count = 0;
		
		for(i=0;i<ht;i++)
		{
			for(j=0;j<wth;j++)
			{
				if(data[i][j]==k)
				{
					count++;
					hist[k]=count;
				}
			}
		}
	}
	
	
	//calling OTSU
	for(t=0;t<254;t++)
	{
		//printf("\nLower boundary 0, higher boundary %d",t);
		var_bg = otsu(0,t,ht,wth);
		//printf("\nLower boundary %d, higher boundary 255",t);
		var_fg = otsu(t+1, 255,ht,wth);
		
		//printf("\n The variance background =%f varience forgraound=%f",var_bg,var_fg);	
		sigma[t] = var_bg + var_fg;	
		sort[t]= sigma[t];	
		
	}
	
	
	for (i=1;i<254;i++)
		{
		//printf("%f ",sigma[i]);
			for(j=1;j<254-i;j++)
			{
					
				if(sigma[i]<sigma[j])
				{
					temp = sigma[i];
					sigma[i]=sigma[j];
					sigma[j]=temp;
				}
			}
		}
		printf("\n");		
	thes = sigma[2];
	//printf("Threshold :%f",thes);
	for(i=1;i<=255;i++)
	{
		if(sort[i] == thes)
			threshold = i;
	}
	final_threshold = (int)threshold;
	//printf("\nThe Threshold is %d\n",final_threshold);
	return (final_threshold);
	
	//binary_conversion(final_threshold,ht,wth,255);

}
*/

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

/*Grey touch, set every pixel to a grey color*/
void grayscale(SDL_Surface* l)
{
  int width = l->w;
  int height = l->h;
  for (int i=0; i<width; i++)
    {
      for (int j=0; j<height; j++)
	{
	   Uint32 pixel = get_pixel(l, i, j);
           Uint8 r, g, b;
           SDL_GetRGB(pixel, l->format, &r, &g, &b);
           Uint8 average=0.3*r + 0.59*g + 0.11*b;
           r=g=b=average;
           pixel = SDL_MapRGB(l->format, r, g, b);
           put_pixel(l, i, j, pixel);
	}
    }
}

/*Self-explanatory, depending on the given input, pixel will be either black or white*/
void blackNwhite(SDL_Surface* image_surface, float thresold)
{
    int width = image_surface->w;
    int height = image_surface->h;
    for (int i=0; i < width; i++)
    {
        for (int j=0; j<height; j++)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            Uint8 r;
            SDL_GetRGB(pixel, image_surface->format, &r, &r, &r);
            if (r > thresold)
	      r=255;
	    else
	      r=0;
            pixel = SDL_MapRGB(image_surface->format, r, r, r);
            put_pixel(image_surface, i, j, pixel);
        }
    }
}

/* Creates small matrixes of pixels  and multiply them by their average value to filter the image, makes sure that the search is never going out of bounds
*/

Uint32 CheckCorners(SDL_Surface* l, int x, int y, int lim)
{
  int average= 0;
  /*Defines the limits of the picture*/
  int left_border= SDL_max(x-lim, 0);
  int top_border=SDL_max(y-lim, 0);
  int right_border=SDL_min(x+lim, l->w-1);
  int bottom_border=SDL_min(y+lim, l->h-1);
  int total = ((right_border-left_border)*(bottom_border-top_border));
  /*Gets the avergae value*/
  for (int i=left_border; i<right_border; i++)
    {
      for (int j=top_border; j<bottom_border; j++)
	{
	  Uint32 pixy= get_pixel(l, i, j);
	  Uint8 r,g,b;
	  SDL_GetRGB(pixy, l->format, &r, &g, &b);
	  average += r;
	}
    }
  return (average/total);
}
  
/*Median filter, removes noises and other parasites*/
void filter(SDL_Surface* l, int lim)
{
  int x = l -> w;
  int y = l -> h;
  for (int i=0; i<x; i++)
    {
      for (int j=0; j<y-lim; j++)
	{
	  Uint32 pixel= get_pixel(l, x, y);
	  Uint8 r, g, b;
	  SDL_GetRGB(pixel, l->format, &r, &g, &b);
	  Uint32 average = CheckCorners(l, i, j, lim);
	  Uint32 pixy= SDL_MapRGB(l->format, average, average, average);
	  put_pixel(l, i, j, pixy);
	}
    }
}

SDL_Surface* SDL_RotationCentral(SDL_Surface* origin, float angle)
{
 int i;
 int j;
 int mx, my;
 int bx, by;
 float angle_radian;

/* To get the radian value of your angle*/
 angle_radian = -angle * M_PI / 180.0;

 SDL_Surface* copy= SDL_ConvertSurface(origin, origin->format, SDL_SWSURFACE);

/* To make the reading easier*/
 mx = origin->w/2;
 my = origin->h/2;

 for(j=0;j<origin->h;j++)
  for(i=0;i<origin->w;i++)
  {
/* Gets the pixel that will fit at the (i, j) position of the final surface*/

/* Inversed matrix to get the appropriate pixel from the initial surface */
   bx = (int) (cos(angle_radian) * (i-mx) + sin(angle_radian) * (j-my)) + mx;
   by = (int) (-sin(angle_radian) * (i-mx) + cos(angle_radian) * (j-my)) + my;
   /* Check to not exceed limits*/
   if (bx>=0 && bx< origin->w && by>=0 && by< origin->h)
   {
     Uint32 pixy = get_pixel(origin, bx, by);
     put_pixel(copy, i, j, pixy);
   }
  }
 return copy;
}

void SDL_FreeSurface(SDL_Surface *surface);




void digitalProcess(char *filename)
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    float angle=0;
    float thresold=0;

    init_sdl();
    /* Displays the initial picture*/
    image_surface = load_image(filename);
    screen_surface = display_image(image_surface);
    wait_for_keypressed();
    /*Grey touch*/
    grayscale(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    /*Filter*/
    filter(image_surface, 2);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    /*Rotates the picture, requires a new window to better match the dimensiosn of the new picture*/
    printf ("Choose an angle then press enter:"); 
    scanf("%e", &angle);
    SDL_Surface* rotated_image= SDL_RotationCentral(image_surface, angle);
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    SDL_Surface* new_surface = display_image(rotated_image);
    wait_for_keypressed();
    /*Black and white*/
    printf ("Choose a thresold value then press enter:"); 
    scanf("%e", &thresold);
    blackNwhite(rotated_image, thresold);
    update_surface(new_surface, rotated_image);
    wait_for_keypressed();
    SDL_FreeSurface(rotated_image);
    SDL_FreeSurface(new_surface);

}





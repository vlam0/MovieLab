/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"
#include "Image.h"
#include "ImageList.h"

/* Clip Function */
int clip(int x);

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
     MOVIE *movie;
     movie = malloc(sizeof(MOVIE));
     movie->Frames = CreateImageList();
     return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
     assert(movie);    
     DeleteImageList(movie->Frames);
     free(movie);
     movie = NULL;
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
     assert(movie);

     IENTRY *entry;

     entry = movie->Frames->First;
     
     int x = 0;
     int i = 0, w = 0, h = 0;
     int c, d, e;
     
     /* Loops through the frames of the movie */
     for (i = 0; i < MovieLength(movie); i++)
     {
	 entry->RGBImage = CreateImage(MovieWidth(movie), MovieHeight(movie));

         /* Seting new values to a new RGB image */
         for (w = 0; w < MovieWidth(movie); w++)
         {
	      for (h = 0; h < MovieHeight(movie); h++)
     	      {
		  c = GetPixelY(entry->YUVImage, w, h) - 16;
  		  d = GetPixelU(entry->YUVImage, w, h) - 128;
		  e = GetPixelV(entry->YUVImage, w, h) - 128;

                  x = clip((298 * c + 409 * e + 128) >> 8);
		  SetPixelR(entry->RGBImage, w, h, x);

		  x = clip((298 * c - 100 * d - 208 * e + 128) >> 8);
		  SetPixelG(entry->RGBImage, w, h, x);

                  x = clip((298 * c + 516 * d + 128) >> 8);
		  SetPixelB(entry->RGBImage, w, h, x);
	      }
         }
	 
	 DeleteYUVImage(entry->YUVImage);
	 entry->YUVImage = NULL;
         entry = entry->Next;
     }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
     assert(movie);

     IENTRY *entry;

     entry = movie->Frames->First;
     
     int x = 0;
     int i = 0, w = 0, h = 0;
     int r, g, b;

     /* Loops through the frames of the movie */
     for (i = 0; i < MovieLength(movie) ; i++)
     {
         entry->YUVImage = CreateYUVImage(MovieWidth(movie), MovieHeight(movie));

         /* Setting new values to a new YUVimage */
         for (w = 0; w < MovieWidth(movie); w++)
         {
              for (h = 0; h < MovieHeight(movie); h++)
              {
                  r = GetPixelR(entry->RGBImage, w, h);
                  g = GetPixelG(entry->RGBImage, w, h);
                  b = GetPixelB(entry->RGBImage, w, h);
	
                  x = clip(((66 * r + 129 * g + 25 * b + 128) >> 8) + 16);
		  SetPixelY(entry->YUVImage, w, h, x);

                  x = clip(((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128);
		  SetPixelU(entry->YUVImage, w, h, x);

                  x = clip(((112 * r - 94 * g - 18 * b + 128) >> 8) + 128);
                  SetPixelV(entry->YUVImage, w, h, x);
              }
         }
         
         DeleteImage(entry->RGBImage);
	 entry->RGBImage = NULL;
	 entry = entry->Next;
     }
}

int MovieLength(const MOVIE *movie)
{
    return movie->Frames->length;
}

int MovieHeight(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
    {
        return movie->Frames->First->RGBImage->H;
    }//if

    else if(movie->Frames->First->YUVImage)
    {
        return movie->Frames->First->YUVImage->H;
    }//if else

    else
    return 0;
}

int MovieWidth(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
    {
         return movie->Frames->First->RGBImage->W;
    }//if

    else if(movie->Frames->First->YUVImage)
    {
          return movie->Frames->First->YUVImage->W;
    }//if else

    else
    return 0;
}

int clip(int x)
{
     return ((x < 0) ? 0 : ((x > 255) ? 255 : x));
}
/* EOF */

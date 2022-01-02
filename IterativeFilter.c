/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "IterativeFilter.h"
#include "Image.h"
#include "Movie.h"

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, int start, int end, int change)
{
    assert(image);
    MOVIE *movie = CreateMovie();
    IMAGE *RGBimage = CopyImage(image);
    
    int i = 0;
    
    /* Increasing Percentage */
    if (start < end)
    {
	 change = ((change < 0) ? -change : change);
	 for (i = start; i <= end; i += change)
	 {    
	      AppendRGBImage(movie->Frames, filter(CopyImage(RGBimage), i));
	 }
    }	
	
    /* Decreasing Percentage */
    else
    {
	 change = ((change > 0) ? -change : change);
	 for (i = start; i >=end; i += change)
         {
	      AppendRGBImage(movie->Frames, filter(CopyImage(RGBimage), i));
         }
    }
      
    DeleteImage(RGBimage);
    
    return movie;   
}

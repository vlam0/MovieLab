/*********************************************************************/
/* 02/27/20 Bo Tsai      updated for EECS22 assignment Winter2020    */
/* Author: Tim Schmidt Date: 11/09/2017                              */
/*                                                                   */
/* DIPs.c: source file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Image.h"
#include "Constants.h"
#include "FileIO.h"
#include <math.h>

/* Black and White function */
IMAGE *BlackNWhite(IMAGE *image, int percent)
{
    assert(image);
    int x, y, gray;
    float p = percent / 100.0;
    int offsetR, offsetG, offsetB;
    int newR, newG, newB;
    
    for (x = 0; x < image->W; x++)
    {
        for(y = 0; y < image->H; y++)
        {
	    /* get grayscale color */
            gray = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
	    
	    /* find difference from grayscale */    	
	    offsetR = gray - GetPixelR(image, x, y);
	    offsetG = gray - GetPixelG(image, x, y);
	    offsetB = gray - GetPixelB(image, x, y);
    
	    /* add difference multiplied by percentage */
	    newR = GetPixelR(image, x, y) + (offsetR * p);
	    newG = GetPixelG(image, x, y) + (offsetG * p);
	    newB = GetPixelB(image, x, y) + (offsetB * p);

            newR = ((newR < 0) ? 0 : ((newR > 255) ? 255 : newR));
	    newG = ((newG < 0) ? 0 : ((newG > 255) ? 255 : newG));
	    newB = ((newB < 0) ? 0 : ((newB > 255) ? 255 : newB));

	    /* Sets new color change to image */
            SetPixelR(image, x, y, newR);
            SetPixelG(image, x, y, newG);
            SetPixelB(image, x, y, newB);
        }
    }

    return image;
}

/* Hue function */
IMAGE *HueRotate(IMAGE *image, int percent)
{
    double degree = (percent / 100.0) * 360.0;
    double a, b, r;
    double d = degree * PI / 180.0;
    double tmpr, tmpg, tmpb;

    /* alpha, beta, rho equations */
    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (int x = 0; x < image->W; x++)
    {   
	for (int y = 0; y < image->H; y++)
        {
            tmpr = GetPixelR(image, x, y) * a + GetPixelG(image, x, y) * b + GetPixelB(image, x, y) * r;
            tmpg = GetPixelR(image, x, y) * r + GetPixelG(image, x, y) * a + GetPixelB(image, x, y) * b;
            tmpb = GetPixelR(image, x, y) * b + GetPixelG(image, x, y) * r + GetPixelB(image, x, y) * a;

            SetPixelR(image, x, y, (tmpr > MAX_PIXEL)?MAX_PIXEL:(tmpr < 0)?0:tmpr);
            SetPixelG(image, x, y, (tmpg > MAX_PIXEL)?MAX_PIXEL:(tmpg < 0)?0:tmpg);
            SetPixelB(image, x, y, (tmpb > MAX_PIXEL)?MAX_PIXEL:(tmpb < 0)?0:tmpb);
        }
    }
    return image;
}

/* EOF */

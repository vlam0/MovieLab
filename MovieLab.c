/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2020                   */
/*                                                                   */
/* Author: Bo Tsai                                                   */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

/* Menu Error Image */
void PrintImageMenu(char *ProgramName)
{
    fprintf(stderr, "\n-------------%s------------\n"
		   "Image options: \n"
		   "\t-i <file.ppm>: import image\n"
		   "\t-o <file.yuv>: export movie\n"
		   "\t-start <startVal>: set start parameter\n"
		   "\t-end <endVal>: set end parameter\n"
		   "\t-step <stepVal>: set step parameter\n"
		   "\t-hue: use hue filter\n"
		   "\t-bw: use black and white filter\n",
		   ProgramName);
}

/* Menu Error Movie */
void PrintMovieMenu(char *ProgramName)
{
    fprintf(stderr, "\n-------------%s-------------\n"
                   "Movie options: \n"
                   "\t-m <file.yuv>: import movie\n"
                   "\t-o <file.yuv>: export movie\n"
                   "\t-f <frameNum>: number of frames in the input movie\n"
                   "\t-s <WxH>: size of a movie frame\n"
                   "\t-reverse: use reverse filter\n",
                   ProgramName);
}

int main(int argc, char *argv[])
{
    IMAGE *input = NULL;
    MOVIE *movieinput = NULL, *movieoutput = NULL;
    iterableFilter filter_func = NULL;
    char *program = NULL;
    char *inputMovie = NULL, *exportMovie = NULL, *inputImage = NULL;
    char *checkI, *checkO, *checkM;
    char *resolution, *width = NULL, *height = NULL;
    char *frame = NULL;
    int start = -1, end = -1, step;
    int importFlag = 0;
    int frameNum = 0, W = 0, H = 0;
    int reverseFlag = 0;
    int correct = 1;
    int i = 0;

    // loop through each argument for the main function
    for(int n = 0; n < argc; n++)
    {
	/* Obtains program name */
	program = strtok(argv[0], "./");

        // If the user wants to import an image
        if(!strcmp(argv[n], "-i"))
        {
            /* Check if output file correct format */
            if (n != argc - 1)
            {
                checkI = strstr(argv[n+1], ".ppm");

                if (checkI)
                {
                     input = LoadImage(argv[++n]);
		     inputImage = argv[n];
                }
            }
            // Let the program know an image has succesfully been imported
            importFlag = 1;
        }

        // If the user wants to import a movie
        else if(!strcmp(argv[n], "-m"))
        {    
            /* Check if movie input file correct format */
            if (n != argc - 1)
            {
                checkM = strstr(argv[n+1], ".yuv");

                if (checkM)
                {
                     inputMovie = argv[++n];
                }
            }                                                                                                                                       
            // Let the program know a movie has succesfully been imported
            importFlag = 2;
        }
        
	/* Frame number */
	else if(!strcmp(argv[n], "-f"))
        {
	    if (n != argc - 1)
            {
                frame = argv[n+1];
                sscanf(frame, "%d", &frameNum);
            }
	}

        /* Resolution */
	else if(!strcmp(argv[n], "-s"))
        {
	    /* Separates string for resolution */
            if (n != argc - 1)
            {
		resolution = strtok(argv[n+1], "x");
		width = resolution;
	
		while (resolution != NULL)
		{
		     height = resolution;
		     resolution = strtok(NULL, " ");	     
		}
		sscanf(width, "%d", &W);
		sscanf(height, "%d",&H);
            }
        }

	/* Output file */
	else if(!strcmp(argv[n], "-o"))
        {   
	    /* Check if output file correct format */
	    if (n != argc - 1)
	    {
		checkO = strstr(argv[n+1], ".yuv");
		
		if (checkO)
		{
		     exportMovie = argv[++n];
		}       
	    }
        }
	
	/* Start option */
	else if(!strcmp(argv[n], "-start"))
        {
            if (n != argc - 1)
            {
                start = atoi(argv[n+1]);
            }
        }

	/* End option */
	else if(!strcmp(argv[n], "-end"))
        {
            if (n != argc - 1)
            {
                end = atoi(argv[n+1]);
            }
        }
	
	/* Step option */
	else if(!strcmp(argv[n], "-step"))
        {
            if (n != argc - 1)
            {
                step = atoi(argv[n+1]);
            }
        }

	/* Filters */
	else if(!strcmp(argv[n], "-hue"))
	{
	    filter_func = &HueRotate;
	}
	else if(!strcmp(argv[n], "-bw"))
	{
	    filter_func = &BlackNWhite;
	}
	else if(!strcmp(argv[n], "-reverse"))
	{
	    reverseFlag = 1;	
	}

    }

    // Load the default image if no argument was specified
    if(!importFlag)
    {
        printf("\nNo -i nor -m for input file to read\n");
        return 0;
    }

    /* Image Option */
    else if(importFlag == 1)
    {
	/* Error Menu display */
        if (!exportMovie || start < 0 || end < 0 || !step || !inputImage || !filter_func)
	{
	    PrintImageMenu(program);
	    correct = 0;
	}
	/* Error Messages */
	if (!inputImage)
	    printf("\n\tPlease provide the name of the image you want to import\n");
	if (!exportMovie)
	    printf("\n\tPlease provide the name of the output file\n");
	if (start < 0)
	    printf("\n\tPlease provide the start parameter\n");
	if (end < 0)
	    printf("\n\tPlease provide the end parameter\n");
	if (!step)	
	    printf("\n\tPlease provide the step parameter\n");
        if (!filter_func)
	    printf("\n\tPlease provide filter\n\n");
	if (!input && inputImage)
	{
            printf("\n\tThe image file %s could not be read\n\n", inputImage);
	    return 0;
	}
	if (!exportMovie || start < 0 || end < 0 || !step || !inputImage || !filter_func)
        {
            DeleteImage(input);
	    input = 0;
        }

	if (correct == 1)
	{
	    movieoutput = doIterativeFilter(input, filter_func, start, end, step);
	    if (!movieoutput)
	    {
		movieoutput = NULL;
	    }
	    else
	    {   
		RGB2YUVMovie(movieoutput);

		SaveMovie(exportMovie, movieoutput);
		DeleteImage(input);
		DeleteMovie(movieoutput);
	    }
	}
	return 0;   
    }

    else if(importFlag == 2)
    {
        if (!exportMovie || !frameNum || !W || !H || !inputMovie)
	{
	    PrintMovieMenu(program);
	    correct = 0;
        }
	/* Error Messages */
	if (!inputMovie)	
	    printf("\n\tPlease provide the name of the movie you want to import\n");
	if (!exportMovie)
            printf("\n\tPlease provide the name of the output file\n");
	if (!frameNum)
	    printf("\n\tMissing arguement for the number of frames!\n");
	if (!W || !H)
	    printf("\n\tMissing arguement for the resolution of the frame!\n\n");

	if (correct == 1)
	{
	    movieinput = LoadMovie(inputMovie, frameNum, W, H);
	    
	    if (!movieinput)
	    {
		printf("\n\tThe movie file %s could not be read\n\n", inputMovie);
		return 0;
	    }	   
	    else
            {
		IENTRY *entry, *next;
		entry = movieinput->Frames->First;
	        movieoutput = CreateMovie();
		YUVIMAGE *YUVimage = NULL;

	        frameNum = (frameNum > MovieLength(movieinput) ? MovieLength(movieinput) : frameNum);
                for (i = 1; i <= frameNum; i++)
                { 
	            next = entry->Next;
		    YUVimage = CopyYUVImage(entry->YUVImage);
                    AppendYUVImage(movieoutput->Frames, YUVimage);
		    YUVimage = NULL;
		    entry = next;
                }
                
		if (reverseFlag)
		{
		    ReverseImageList(movieoutput->Frames);
		    printf("Operation Reverse is done!\n");
		}
 		
                SaveMovie(exportMovie, movieoutput);
                
                DeleteMovie(movieoutput);
            }
          
            DeleteMovie(movieinput);
	}
	return 0;
    }
    return 0;
}

/* EOF */

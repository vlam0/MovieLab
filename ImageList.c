/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"
#include "Image.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
     IENTRY *entry;
     entry = malloc(sizeof(IENTRY));

     if (!entry)
     {
          perror("Out of memory! Abort...");
          exit(10);
     }

     /* Sets all properties to NULL */
     entry->List = NULL;
     entry->Next = NULL;
     entry->Prev = NULL;
     entry->RGBImage = NULL;
     entry->YUVImage = NULL;

     return entry;
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{    
     assert(entry);
 
     if (entry->RGBImage)
     {
	 DeleteImage(entry->RGBImage);
     }

     if (entry->YUVImage)
     {
	 DeleteYUVImage(entry->YUVImage);
     }
  
     free(entry);
     entry = NULL;
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
     ILIST *list;
     list = malloc(sizeof(ILIST));
     
     if (!list)
     {
         perror("Out of memory! Aborting...");
         exit(10);
     }

     list->length = 0;
     list->First = NULL;
     list->Last = NULL;

     return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
     IENTRY *entry, *next;

     assert(list);

     entry = list->First;

     while (entry)
     {
	 next = entry->Next;
         DeleteImageEntry(entry);
         entry = next;
         list->length--;   
     }

     free(list);
     list = NULL;
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
     IENTRY *entry;

     assert(list);
     assert(RGBimage);

     entry = CreateImageEntry();
     entry->List = list;

     if (list->Last)
     {
         entry->Next = NULL;
         entry->Prev = list->Last;
         list->Last->Next = entry;
         entry->RGBImage = RGBimage;
         list->Last = entry;
     }
     
     /* Empty List */
     else
     {
	 entry->Next = NULL;
         entry->Prev = NULL;
         entry->RGBImage = RGBimage;
         list->First = entry;
	 list->Last = entry;
     }
    
     list->length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
     IENTRY *entry;

     assert(list);
     assert(YUVimage);

     entry = CreateImageEntry();
     entry->List = list;

     if (list->Last)
     {
         entry->Next = NULL;
         entry->Prev = list->Last;
	 list->Last->Next = entry;
         entry->YUVImage = YUVimage;
	 list->Last = entry;
     }

     /* Empty List */
     else
     {
         entry->Next = NULL;
         entry->Prev = NULL;
         entry->YUVImage = YUVimage;
         list->First = entry;
	 list->Last = entry;
     }
    
     list->length++;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
     IENTRY *entry = NULL, *next = NULL, *prev = NULL;
     IENTRY *temp = NULL;
     entry = list->First;
 
     temp = list->First;
     list->First = list->Last;
     list->Last = temp;

     while (entry)
     {
	 next = entry->Next;   
         entry->Next = prev;
         prev = entry;
         entry->Prev = next;
         entry = next; 	  
     }
}

/* Copy YUV Image */
YUVIMAGE *CopyYUVImage(YUVIMAGE *image)
{
        YUVIMAGE *ret = CreateYUVImage(image->W, image->H);

        for(unsigned int i = 0; i < image->W; i++)
        {
                for(unsigned int j = 0; j < image->H; j++)
                {
                        SetPixelY(ret, i, j, GetPixelY(image, i, j));
                        SetPixelU(ret, i, j, GetPixelU(image, i, j));
                        SetPixelV(ret, i, j, GetPixelV(image, i, j));
                }
        }

        return ret;
}






















/* EOF */

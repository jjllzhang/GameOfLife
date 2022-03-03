/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    char format[3];
    int width, height, max;
    fscanf(fp, "%s", format);
    if(format[0] != 'P' || format[1] != '3') {
        printf("Error: Not a P3 file\n");
        return NULL;
    }
    fscanf(fp, "%d %d %d", &width, &height, &max);
    Image *img = (Image*) malloc(sizeof(Image));
    img->width = width;
    img->height = height;
    if(img->width <= 0 || img->height <= 0 || max != 255) {
        printf("Error: Invalid image size\n");
        return NULL;
    }
    img->image = (Color **) malloc(sizeof(Color*) * totalPixels);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            img->image[i][j] = (Color*) malloc(sizeof(Color));
            fscanf(fp, "%d %d %d", &img->image[i][j]->R, &img->image[i][j]->G, &img->image[i][j]->B);
        }
    }
    fclose(fp);
    return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    printf("P3\n");
    printf("%d %d\n", image->width, image->height);
    printf("255\n");
    for(int i = 0; i < image->width; i++) {
        for(int j = 0; j < image->height; j++) {
            printf("%d %d %d\n", image->image[i][j]->R, image->image[i][j]->G, image->image[i][j]->B);
        }
    }
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
    for(int i = 0; i < image->width; i++) {
        for(int j = 0; j < image->height; j++) {
            free(image->image[i][j]);
        }
    }
    free(image->image);
    free(image);
}
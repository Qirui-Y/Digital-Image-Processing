//
//  DIP_MyHeaderFile.h
//  hw_1_prob_1_a1
//
//  Created by Abinaya Manimaran on 1/19/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#ifndef DIP_MyHeaderFile_h
#define DIP_MyHeaderFile_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// Define all the functions written below ------
void fileRead(char *fileName, unsigned char *imageFromFile, long int imageLen );
unsigned char ** allocMemory2D(unsigned char ** image2D, int row, int col);
unsigned char *** allocMemory3D(unsigned char *** image3D, int row, int col, int bytesPerPixel);
unsigned char ** image1Dto2D(unsigned char ** image2D, unsigned char *image1D, int row, int col);
unsigned char *** image1Dto3D(unsigned char *** image3D, unsigned char *image1D, int row, int col, int bytesPerPixel);
void image2Dto1D(unsigned char ** image2D, unsigned char *image1D, int row, int col);
void image3Dto1D(unsigned char *** image3D, unsigned char *image1D, int row, int col, int bytesPerPixel);
unsigned char ** seperateChannels(unsigned char *** image3D, unsigned char **image2DChannel, int row, int col, int channelNumber);
unsigned char *** combineChannels(unsigned char *** image3D, unsigned char ** image2DChannel1, unsigned char ** image2DChannel2, unsigned char **image2DChannel3, int row, int col, int bytesPerPixel);
void fileWrite(char *fileName, unsigned char *imageToFile, long int imageLen );
void fileWriteHist(char* fileName, unsigned int histData[256]);
void freeMemory2D(unsigned char ** image2D, int row, int col);
void freeMemory3D(unsigned char *** image3D, int row, int col, int bytesPerPixel);
unsigned int * histogram2DImage(unsigned char ** image2D, unsigned int *histCalculated, int row, int col);
unsigned int * histogram2DImageLongDouble(long double ** image2D, unsigned int *histCalculated, int row, int col);
long double ** convert1DtoMatrix(long double ** matrix, long double *array, int ROW, int COL);
long double *** allocMemory3DLongDouble(long double *** image3D, int ROW, int COL, int BYTESPERPIXEL);
long double ** allocMemory2DLongDouble(long double ** image2D, int ROW, int COL);
long double ** image1Dto2DLongDouble(long double ** image2D, unsigned char *image1D, int row, int col);
long double *** image1Dto3DLongDouble(long double *** image3D, unsigned char *image1D, int row, int col, int bytesPerPixel);
long double* image2Dto1DLongDouble(long double ** image2D, long double * image1D, int row, int col);


// Read Raw file and store it in 1D array --------
void fileRead(char *fileName, unsigned char *imageFromFile, long int imageLen ) {
    FILE *file;
    if (!(file=fopen(fileName,"rb"))) {
        cout << "Cannot open file: " << fileName << endl;
        exit(1);
    }
    fread(imageFromFile, sizeof(unsigned char), imageLen, file);
    fclose(file);
}

// Allocate memory for 2D array and initialize to zero --------

unsigned char ** allocMemory2D(unsigned char ** image2D, int row, int col){
    image2D = new unsigned char *[row]();
    long int temp_count = 0;
    for(int i=0; i < row; i++) {
        image2D[i] = new unsigned char [col]();
        for(int j=0; j < col; j++) {
            image2D[i][j] = 0;
            temp_count = temp_count + 1;
        }
    }
    return image2D;
}

// Allocate memory for 3D array and initialize to zero --------
unsigned char *** allocMemory3D(unsigned char *** image3D, int row, int col, int bytesPerPixel){
    long int temp_count = 0;
    image3D = new unsigned char **[row]();
    for(int i=0; i < row; i++) {
        image3D[i] = new unsigned char *[col]();
        for(int j=0; j < col; j++) {
            image3D[i][j] = new unsigned char [bytesPerPixel]();
            for(int k=0; k < bytesPerPixel; k++) {
                image3D[i][j][k] = 0;
                temp_count = temp_count + 1;
            }
        }
    }
    return image3D;
}

// Convert 1D array to 2D array --------
unsigned char ** image1Dto2D(unsigned char ** image2D, unsigned char *image1D, int row, int col) {
    image2D = new unsigned char *[row]();
    long int temp_count = 0;
    for(int i=0; i < row; i++) {
        image2D[i] = new unsigned char [col]();
        for(int j=0; j < col; j++) {
            image2D[i][j] = image1D[temp_count];
            temp_count = temp_count + 1;
        }
    }
    return image2D;
}

// Convert 1D array to 3D array --------
unsigned char *** image1Dto3D(unsigned char *** image3D, unsigned char *image1D, int row, int col, int bytesPerPixel) {
    long int temp_count = 0;
    image3D = new unsigned char **[row]();
    for(int i=0; i < row; i++) {
        image3D[i] = new unsigned char *[col]();
        for(int j=0; j < col; j++) {
            image3D[i][j] = new unsigned char [bytesPerPixel]();
            for(int k=0; k < bytesPerPixel; k++) {
                image3D[i][j][k] = image1D[temp_count];
                temp_count = temp_count + 1;
            }
        }
    }
    return image3D;
}

// Convert 2D array to 1D array --------
void image2Dto1D(unsigned char ** image2D, unsigned char * image1D, int row, int col) {
    long int temp_count = 0;
    for(int i=0; i < row; i++) {
        for(int j=0; j < col; j++) {
            image1D[temp_count] = image2D[i][j];
            temp_count = temp_count + 1;
        }
    }
}

// Convert 3D array to 1D array --------
void image3Dto1D(unsigned char *** image3D, unsigned char *image1D, int row, int col, int bytesPerPixel) {
    long int temp_count = 0;
    for(int i=0; i < row; i++) {
        for(int j=0; j < col; j++) {
            for(int k=0; k < bytesPerPixel; k++) {
                image1D[temp_count] = image3D[i][j][k];
                temp_count = temp_count + 1;
            }
        }
    }
}

// Seperate channels from 3D image --------
unsigned char ** seperateChannels(unsigned char *** image3D, unsigned char **image2DChannel, int row, int col, int channelNumber) {
    image2DChannel = new unsigned char *[row]();
    for(int i=0; i < row; i++){
        image2DChannel[i] = new unsigned char [col]();
        for(int j=0; j < col; j++) {
            image2DChannel[i][j] = image3D[i][j][channelNumber];
        }
    }
    return image2DChannel;
}

// Combine channels to form 3D image --------
unsigned char *** combineChannels(unsigned char *** image3D, unsigned char ** image2DChannel1, unsigned char ** image2DChannel2, unsigned char **image2DChannel3, int row, int col, int bytesPerPixel) {
    image3D = new unsigned char **[row]();
    for(int i=0; i < row; i++) {
        image3D[i] = new unsigned char *[col]();
        for(int j=0; j < col; j++) {
            image3D[i][j] = new unsigned char [bytesPerPixel]();
            image3D[i][j][0] = image2DChannel1[i][j];
            image3D[i][j][1] = image2DChannel2[i][j];
            image3D[i][j][2] = image2DChannel3[i][j];
        }
    }
    return image3D;
}


// Write 1D array to a raw file --------
void fileWrite(char *fileName, unsigned char *imageToFile, long int imageLen ) {
    FILE *file;
    if (!(file=fopen(fileName,"wb"))) {
        cout << "Cannot open file: " << fileName << endl;
        exit(1);
    }
    fwrite(imageToFile, sizeof(unsigned char), imageLen, file);
    fclose(file);
}

void fileWriteHist(char* fileName, unsigned int histData[256]) {
    FILE *file;
    file = fopen(fileName, "w");
    if (file != NULL)
    {
        for (int i = 0; i < 256;  i++)
        {
            fprintf(file, "%d\t%u\n", i, histData[i]);
        }
        fclose(file);
        //cout << "File " << fileName << " written successfully !!!" << endl;
    }
    else
    {
        cout << "Cannot open file " << fileName << endl;
    }
}

// Deallocate memory from 2D array --------
void freeMemory2D(unsigned char ** image2D, int row, int col) {
    for (int i=0; i<row; i++) {
        delete[] image2D[i];
    }
    delete[] image2D;
}

// Deallocate memory from 3D array
void freeMemory3D(unsigned char *** image3D, int row, int col, int bytesPerPixel) {
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            delete[] image3D[i][j];
        }
        delete[] image3D[i];
    }
    delete[] image3D;
}

// Histogram given a 2D image
unsigned int * histogram2DImage(unsigned char ** image2D, unsigned int *histCalculated, int row, int col) {
    int indexToIncrement;
    for(int i=0; i < row; i++) {
        for(int j=0; j < col; j++) {
            indexToIncrement = image2D[i][j];
            histCalculated[indexToIncrement] = histCalculated[indexToIncrement] + 1;
        }
    }
    return histCalculated;
}
unsigned int * histogram2DImageLongDouble(long double ** image2D, unsigned int *histCalculated, int row, int col) {
    int indexToIncrement;
    for(int i=0; i < row; i++) {
        for(int j=0; j < col; j++) {
            indexToIncrement = (int) image2D[i][j];
            histCalculated[indexToIncrement] = histCalculated[indexToIncrement] + 1;
        }
    }
    return histCalculated;
}

unsigned char ** convert1DtoMatrix(unsigned char ** matrix, unsigned char *array, int ROW, int COL) {
    unsigned int tempCount = 0;
    matrix = new unsigned char *[ROW]();
    for(int i=0; i < ROW; i++){
        matrix[i] = new unsigned char [COL]();
        for(int j=0; j < COL; j++){
            matrix[i][j] = array[tempCount];
            tempCount ++;
        }
    }
    return matrix;
}
long double ** convert1DtoMatrixLongDouble(long double ** matrix, long double *array, int ROW, int COL) {
    unsigned int tempCount = 0;
    matrix = new long double *[ROW]();
    for(int i=0; i < ROW; i++){
        matrix[i] = new long double [COL]();
        for(int j=0; j < COL; j++){
            matrix[i][j] = array[tempCount];
            tempCount ++;
        }
    }
    return matrix;
}

long double *** allocMemory3DLongDouble(long double *** image3D, int ROW, int COL, int BYTESPERPIXEL) {
    image3D = new long double **[ROW]();
    for(int i=0; i < ROW; i++) {
        image3D[i] = new long double *[COL]();
        for(int j=0; j < COL; j++) {
            image3D[i][j] = new long double [BYTESPERPIXEL]();
            for(int k=0; k < BYTESPERPIXEL; k++) {
                image3D[i][j][k] = 0;
            }
        }
    }
    return image3D;
}

long double ** allocMemory2DLongDouble(long double ** image2D, int ROW, int COL) {
    image2D = new long double *[ROW]();
    for(int i=0; i < ROW; i++) {
        image2D[i] = new long double [COL]();
        for(int j=0; j < COL; j++) {
            image2D[i][j] = 0;
        }
    }
    return image2D;
}

// Deallocate memory from 2D array - Long Double
void freeMemory2DLongDouble(long double ** image2D, int row, int col) {
    for (int i=0; i<row; i++) {
        delete[] image2D[i];
    }
    delete[] image2D;
}

// Deallocate memory from 3D array - Long Double
void freeMemory3DLongDouble(long double *** image3D, int row, int col, int bytesPerPixel) {
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            delete[] image3D[i][j];
        }
        delete[] image3D[i];
    }
    delete[] image3D;
}

// Convert 1D array to 2D array Long Double --------
long double ** image1Dto2DLongDouble(long double ** image2D, unsigned char *image1D, int row, int col) {
    image2D = new long double *[row]();
    long int temp_count = 0;
    for(int i=0; i < row; i++) {
        image2D[i] = new long double [col]();
        for(int j=0; j < col; j++) {
            image2D[i][j] = (long double) image1D[temp_count];
            temp_count = temp_count + 1;
        }
    }
    return image2D;
}

// Convert 1D array to 3D array --------
long double *** image1Dto3DLongDouble(long double *** image3D, unsigned char *image1D, int row, int col, int bytesPerPixel) {
    long int temp_count = 0;
    image3D = new long double **[row]();
    for(int i=0; i < row; i++) {
        image3D[i] = new long double *[col]();
        for(int j=0; j < col; j++) {
            image3D[i][j] = new long double [bytesPerPixel]();
            for(int k=0; k < bytesPerPixel; k++) {
                image3D[i][j][k] = (long double) image1D[temp_count];
                temp_count = temp_count + 1;
            }
        }
    }
    return image3D;
}

//Convert 2D array to 1D array Long Double
long double* image2Dto1DLongDouble(long double ** image2D, long double * image1D, int row, int col) {
    long int temp_count = 0;
    for(int i=0; i < row; i++) {
        for(int j=0; j < col; j++) {
            image1D[temp_count] = image2D[i][j];
            temp_count = temp_count + 1;
        }
    }
    return image1D;
}

#endif /* DIP_MyHeaderFile_h */

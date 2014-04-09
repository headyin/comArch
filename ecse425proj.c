#include "ecse425proj.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Specify the data layout format */
const DLayout dlayout = ColMaj;

void randInitialize(int sz, double *vPtr)
{
    int i;
    for (i = 0; i < sz; i++)
        vPtr[i] = drand48();
}

void displayVec(int sz, const double *vPtr)
{
    if(dlayout == RowMaj || dlayout == ColMaj )
    {
        int i;
        printf("[");
        for (i = 0; i < sz; i++)
        {
            printf("%e",vPtr[i]);
            if(i < sz-1)
                printf(",");
            else
                printf("]");
        }
    }
}

void displayMat(int rows, int cols, const double *vPtr)
{
    if(dlayout == RowMaj)
    {
        int i;
        printf("[\n");
        for (i = 0; i < rows; i++) {
            displayVec(cols, &vPtr[i*rows]);
            printf("\n");
        }
        printf("]\n");
    }
    else
    {
        int i,j;
        printf("[\n");
        for (i = 0; i < rows; i++)
        {
            printf("[");
            for (j = 0; j < cols; j++)
            {
                printf("%e", (vPtr + cols * j)[i]);
                if (j < cols - 1)
                    printf(",");
                else
                    printf("]");
            }
            printf("\n");
        }
        printf("]\n");
    }
}

void matVecMult_rowMaj(int N, const double *matA, const double *vecB, double *vecC)
{
    int i, j;
    for (i =0; i < N; i++)
    {
        vecC[i] = 0;
        for (j = 0; j < N; j++)
        {
            vecC[i] += (matA+i*N)[j] * vecB[j];
        }
    }
}



void matMult(int N, const double *matA, const double *matB, double *matC)
{
    if(dlayout == RowMaj)
    {
        // Code in your naive implementation here
        double* vecB = (double*)malloc(sizeof(double)*N);
        double* result = (double*)malloc(sizeof(double)*N);
        int i = 0;
        int j = 0;
        int k = 0;
        while (i < N){
            j = 0;
            while (j < N){	
                vecB[j] = (matB+j*N)[i];
                j++;
            }
            matVecMult(N, matA, vecB, result);
            k = 0;
            while (k < N)
            {
                (matC+k*N)[i] = result[k];
                k++;
            }
            i++;
        }
    }
    else
    {
        double* vecB = (double*)malloc(sizeof(double)*N);
        double* result = (double*)malloc(sizeof(double)*N);
        int i = 0;
        int j = 0;
        int k = 0;
        while (i < N){
            j = 0;
            while (j < N){
                vecB[j] = (matA+j*N)[i];
                j++;
            }
            matVecMult_rowMaj(N, matB, vecB, result);
            k = 0;
            while (k < N)
            {
                (matC+k*N)[i] = result[k];
                k++;
            }
            i++;
        }

    }
}


void matVecMult(int N, const double *matA, const double *vecB, double *vecC)
{

    if(dlayout == RowMaj)
    {
        // Code in your naive implementation here
        int i, j;
        for (i =0; i < N; i++)
        {
            vecC[i] = 0;
            for (j = 0; j < N; j++)
            {
                vecC[i] += (matA+i*N)[j] * vecB[j];
            }
        }
    }
    else
    {
        int i,j;
        for (i =0; i < N; i++)
        {
            vecC[i] = 0;
            for (j = 0; j < N; j++)
            {
                vecC[i] += (matA+j*N)[i] * vecB[j];
            }
        }

    }
}

double compareVecs(int N, const double *src, const double *ref)
{
    double ds = 0., ss = 0.;
    int i;
    for(i = 0; i < N; i++)
    {
        ds += (src[i] - ref[i]) * (src[i] - ref[i]);
        ss += ref[i] * ref[i];
    }
    ss = ds/ss;
    printf("Error SQUARED is: %e\n",ss);
    return ss;
}

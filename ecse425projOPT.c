#include "ecse425projOPT.h"
#include "ecse425proj.h"

#include <string.h>
#include <stdlib.h>

#define BLOCK_ELEMENTS 8 //echa block can have 8 doubles

void matVecMult_part(int L, int N, int M, const double *matA, const double *vecB, double *vecC)
{
    int i, j;
    for (i =0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            vecC[i] += (matA+i*L)[j] * vecB[j];
        }
    }
}


void matVecMult_opt(int N, const double *matA, const double *vecB, double *vecC) 
{
    // Code in your optimized implementation here
    int i, j;
    for (i =0; i < N; i++)
    {
        vecC[i] = 0;
        for (j = 0; j < N; j++)
        {
            vecC[i] += (matA+i*N)[j] * vecB[j];
        }
    }
/*
    int row = 0, column;
    memset(vecC, 0, sizeof(double) * N);
    while (row + BLOCK_ELEMENTS < N)
    {
        column = 0;
        while (column + BLOCK_ELEMENTS < N)
        {
            matVecMult_part(N, BLOCK_ELEMENTS, BLOCK_ELEMENTS, matA + row * N + column, vecB + column, vecC + row);
            column += BLOCK_ELEMENTS;
        }
        matVecMult_part(N, BLOCK_ELEMENTS, N - column, matA + row * N + column, vecB + column, vecC + row);
        row += BLOCK_ELEMENTS;
    }
    column = 0;
    while (column + BLOCK_ELEMENTS < N)
    {
        matVecMult_part(N, N - row, BLOCK_ELEMENTS, matA + row * N + column, vecB + column, vecC + row);
        column += BLOCK_ELEMENTS;
    }
    matVecMult_part(N, N - row, N - column, matA + row * N + column, vecB + column, vecC + row);
*/
}

void matMult_opt(int N, const double *matA, const double *matB, double *matC) 
{
    // Code in your optimized implementation here
    int i,j,k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                (matC + i*N)[k] += (matA + i*N)[j] *(matB + j*N)[k];
            }
        }
    }
}

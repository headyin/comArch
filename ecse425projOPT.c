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

}

void matMult_part8(int L, const double *matA, const double *matB, double *matC)
{ 
    int i,j,k;
    for (i = 0; i < BLOCK_ELEMENTS; i++)
    {
        for (j = 0; j < BLOCK_ELEMENTS; j++)
        {
            for (k = 0; k < BLOCK_ELEMENTS; k++)
            {
                (matC + i*L)[k] += (matA + i*L)[j] *(matB + j*L)[k];
            }
        }
    }
}

void matMult_part(int L, int N, int M, int P, const double *matA, const double *matB, double *matC) 
{
    if ((N == M) && (N == P) && (N == BLOCK_ELEMENTS))
    {
        matMult_part8(L, matA, matB, matC);
        return;
    }
    int i,j,k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            for (k = 0; k < P; k++)
            {
                (matC + i*L)[k] += (matA + i*L)[j] *(matB + j*L)[k];
            }
        }
    }
}


void matMult_opt(int N, const double *matA, const double *matB, double *matC) 
{
    // Code in your optimized implementation here
    int rowA = 0, columnA, columnB, dRowA, dColumnA, dColumnB; //columnA is equal to rowB
    memset(matC, 0, sizeof(double) * N * N);
    while (rowA < N)
    {
        dRowA = (BLOCK_ELEMENTS < N - rowA) ? BLOCK_ELEMENTS : N - rowA;
        columnA = 0;
        while (columnA < N)
        {
            dColumnA = (BLOCK_ELEMENTS < N - columnA) ? BLOCK_ELEMENTS : N - columnA;
            columnB = 0;
            while (columnB < N)
            {
                dColumnB = (BLOCK_ELEMENTS < N - columnB) ? BLOCK_ELEMENTS : N - columnB;
                matMult_part(N, dRowA, dColumnA, dColumnB, matA + rowA * N + columnA, matB + columnA * N + columnB, matC + rowA * N + columnB);
                columnB += BLOCK_ELEMENTS;
            }            
            columnA += BLOCK_ELEMENTS;
        }
        rowA += BLOCK_ELEMENTS;
    }
}

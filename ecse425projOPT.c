#include "ecse425projOPT.h"
#include "ecse425proj.h"

#include <string.h>
#include <stdlib.h>

#define BLOCK_ELEMENTS 8 //echa block can have 8 doubles

void matVecMult_part88(const double *matA, const double *vecB, double *vecC)
{
//    int j;
//    for (j = 0; j < BLOCK_ELEMENTS; j++)
//    {
//        (*vecC) += (matA)[j] * vecB[j];
//    }
    double temp = matA[0] * vecB[0];
    temp += matA[1] * vecB[1];
    temp += matA[2] * vecB[2];
    temp += matA[3] * vecB[3];
    temp += matA[4] * vecB[4];
    temp += matA[5] * vecB[5];
    temp += matA[6] * vecB[6];
    temp += matA[7] * vecB[7];
    *vecC += temp;

//    *vecC += (matA[0] * vecB[0] + matA[1] * vecB[1] + matA[2] * vecB[2] + matA[3] * vecB[3]
//            + matA[4] * vecB[4] + matA[5] * vecB[5] + matA[6] * vecB[6] + matA[7] * vecB[7]);
}


void matVecMult_part(int M, const double *matA, const double *vecB, double *vecC)
{
    int j;
    for (j = 0; j < M; j++)
    {
        (*vecC) += (matA)[j] * vecB[j];
    }
}



void matVecMult_opt(int N, const double *matA, const double *vecB, double *vecC) 
{
    // Code in your optimized implementation here
    int row, column;
    memset(vecC, 0, sizeof(double) * N);
    for (row = 0; row < N; row++)
    {
        column = 0;
        while (column + BLOCK_ELEMENTS < N)
        {
            matVecMult_part88(matA + row * N + column, vecB + column, vecC + row);
            column += BLOCK_ELEMENTS;
        }
        matVecMult_part(N - column, matA + row * N + column, vecB + column, vecC + row);
    }
}

__attribute__((optimize("unroll-loops")))
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

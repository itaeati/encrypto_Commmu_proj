#pragma once

#include "Librarys.h"

void mul_Matrix(int* keyMatrix, int keyMatrix_sideSize, char* strArray);
int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void cal_inverseDeterminant(int* keyMatrix, int* result_InverseMatrix, int keyMatrix_sideSize);
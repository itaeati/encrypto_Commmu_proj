#pragma once

#include "Librarys.h"

void mul_Matrix(int* leftMatrix, int leftMatrix_sideSize, int* rightMatrix, int rightMatrix_size, int* resultMatrix);
int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void cal_inverseMaxtrix(int* keyMatrix, int* result_InverseMatrix, int keyMatrix_sideSize);
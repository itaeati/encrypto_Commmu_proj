#pragma once

void cleanUp_func(void);
int* make_keyMatrix(int* keyMatrix_sideSize);
void input_to_strArray(void);
void matrixMoudulation(int* targetMatrix, int matrixSize);
void peddingMatrix(int* numMatrix, int leftMatrix_sideSize, int rightMatrix_size);
void numtoString(int* targetMatrix, char* resultMatrix);

#ifdef DEBUG
void printMatrix(int* Matrix, int Matrix_maxRow, int Matrix_maxCol);
void printAddr(void* ptr, char* Name); 
void printStatus(void);
void printLoopNum(void);
#endif 

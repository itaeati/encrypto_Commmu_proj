#include "code.h"

void encodingFunc(int keyMatrix_sideSize, int* keyMatrix)
{
	paddingMatrix(numMatrix, keyMatrix_sideSize, g_maxIdx);

	mul_Matrix(keyMatrix, keyMatrix_sideSize, numMatrix, g_maxIdx, deliverMatrix);

	matrixMoudulation(deliverMatrix, g_maxIdx + g_paddingSize);

}

void decodingFunc(int keyMatrix_sideSize, int* deliverMatrix, int* keyMatrix)
{

	int* result_InverseMatrix = NULL;

	result_InverseMatrix = (int*)malloc(keyMatrix_sideSize * keyMatrix_sideSize * sizeof(int));
	
	if (result_InverseMatrix == NULL)
	{
		errNum = 7;
		goto exit_decodingFunc;
	}

	memset(result_InverseMatrix, 0, (keyMatrix_sideSize * keyMatrix_sideSize * sizeof(int)));

	cal_inverseMaxtrix(keyMatrix, result_InverseMatrix, keyMatrix_sideSize);

	matrixMoudulation(result_InverseMatrix, keyMatrix_sideSize * keyMatrix_sideSize);

	mul_Matrix(result_InverseMatrix, keyMatrix_sideSize, deliverMatrix, g_maxIdx + g_paddingSize, numMatrix);

	matrixMoudulation(numMatrix, g_maxIdx + g_paddingSize);

	numtoString(numMatrix, result_strArray);


exit_decodingFunc:
	free(result_InverseMatrix);
}


#include "Matrix.h"
#include "globalVar.h"

#define FINDING_MODULAR_INVERSE(dN, n) (dN*n)%ALPABET_SIZE

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);

char result_strArray[STR_SIZE];		// ��ȣȭ ���� ��� �迭

int find_modularInverse(void) // ����ã��
{
	int num = 0; // ������ �׳� �Ǵ°Ÿ� 1���ص� ��ⷯ������ ��.

	while (1)
	{
		if (FINDING_MODULAR_INVERSE(g_detNum, ++num) == 1) // �ּ� ������ ��ȯ
			break;
	}

	return num;
}

void mul_Scalar(int* inverseMatrix, int keyMatrix_Size)
{
	int modularInverse = find_modularInverse();

	for (int i = 0; i < keyMatrix_Size; i++)
		inverseMatrix[i] *= modularInverse; 
}

void transpose_Matrix(int* Matrix, int matrix_sideSize)
{
	int srcPOS = 0;
	int desPOS = 0;
	for (int row = 0; row < matrix_sideSize; row++) // ����� �밢���� �������θ� �����ϸ� ��
	{
		for (int col = row + 1; col < matrix_sideSize; col++)
		{
			srcPOS = row * matrix_sideSize + col;
			desPOS = col * matrix_sideSize + row;

			// srcPOS�� desPOS�� ���ٸ� ������ ���� ���� 0�̵�. ���� �޶���ϸ� �� (xor�� ������)
			Matrix[srcPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // src = src ^ des 
			Matrix[desPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // des = src = (src ^ des) ^ des
			Matrix[srcPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // src = des = (src ^ des) ^ src(=desPOS)
		}
	}
}

void cal_inverseMaxtrix(int* keyMatrix, int* result_InverseMatrix, int keyMatrix_sideSize) // ó������ ��������, ������� ���� �迭, (int)sqrt(maxIdx+peddedNum) ���� 
// ȣ���ڿ��� errNum�� Ȯ���ϸ� ���� break
{
	/*--------------------------------*/
	// 1. �ʿ��� ������ �̸� ���� 
	/*--------------------------------*/

	int** subMatrixs = NULL;					// ù��° ����ĵ��� �����ϴ� �����͹迭
	int keyMatrix_Size = (int)pow(keyMatrix_sideSize, 2);

	int nextMatrix_sideSize = keyMatrix_sideSize - 1;		// ��Ľ��� ���� +1 �ϼ���, ����� ũ�Ⱑ -1
	int nextMatrix_Size = (int)pow(nextMatrix_sideSize, 2);
	int signNum = 0;
	

	/*--------------------------------*/
	// 2. ũ�⸸ŭ �����Ҵ� 
	/*--------------------------------*/

	subMatrixs = (int**)malloc(keyMatrix_Size * sizeof(int));
	if (subMatrixs == NULL)
	{
		errNum = 5;
		goto cal_inverseDeterminant_exit1;
	}

	memset(subMatrixs, NULL, keyMatrix_Size);	

	/*--------------------------------*/
	// 3. ������ ���ȭ
	/*--------------------------------*/

	for (int i = 0; i < keyMatrix_Size; i++)
	{
		subMatrixs[i] = (int*)malloc(nextMatrix_Size * sizeof(int)); 

		if ( subMatrixs[i] == NULL)
		{
			errNum = 6;
			goto cal_inverseDeterminant_exit2;
		}

		copyIdx(subMatrixs[i], keyMatrix, i, keyMatrix_sideSize); // Ű��Ŀ����� ������� subMatrixs�� �ε��� ��Ŀ� �����ϴ� �۾�
		
		signNum = i / keyMatrix_sideSize + i % keyMatrix_sideSize;

		result_InverseMatrix[i] = (int)pow(-1, signNum) * cal_Determinant(subMatrixs[i], nextMatrix_sideSize); // �ش� ����Ľ� ���ؼ�, ����� ����� ����Ŀ� �ֱ�
	} 

	if (errNum == 3) //��ĽĿ��� �Ҵ� ���� ����ó��
	{
		goto cal_inverseDeterminant_exit2;
	}

	/*--------------------------------*/
	// 4. �������ȭ + ���� ��Į�� ����
	/*--------------------------------*/

	transpose_Matrix(result_InverseMatrix, keyMatrix_sideSize);
	mul_Scalar(result_InverseMatrix, keyMatrix_sideSize);
	
	/*--------------------------------*/
	// 5.. ����
	/*--------------------------------*/

cal_inverseDeterminant_exit2:
	for (int i = 0; i < keyMatrix_Size; i++)
		free(subMatrixs[i]);

	free(subMatrixs);

cal_inverseDeterminant_exit1:
	return;
}
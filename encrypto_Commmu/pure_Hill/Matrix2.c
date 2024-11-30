#include "Matrix.h"
#include "globalVar.h"

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);

char result_strArray[STR_SIZE];	// ��ȣȭ ���� ��� �迭

inline int FINDING_MODULAR_INVERSE(int detNum, int moduloNum) 
{
	int temp = (detNum * moduloNum) % ALPABET_SIZE; // �⺻ ����

	if (temp < 0) 
		temp += ALPABET_SIZE;            
	// ������ 26������� �����غ���, ������� ����ó���� �Ǿ�������. -> �ֳ��ϸ� �����������̴ϱ� �������� Ȯ���ϸ��
	// �׷��� ������ ������ -25���, �����̱⶧���� +26�� ���־����. -> +1 (���� wrapping ó��)
	// �ϴ� ��ⷯ ���� 1�� �Ǹ� �ϼ���

	return temp;
}

int find_modularInverse(void) // ����ã��   (���� ����)
{
	int num = 0; // ������ �׳� �Ǵ°Ÿ� 1���ص� ��ⷯ������ ��.

	while (1)
	{
		if (FINDING_MODULAR_INVERSE(g_detNum, ++num) == 1) // �ּ� ������ ��ȯ (�������� ���� ó�� �ʿ�...)
			break;
		else if (num == sqrt(INT_MAX)) // ã�� �� ����
		{
			errNum = 8;
			num = 0;
			break;
		}
	}
#if defined(DEBUG)
	printf("inverseModulation_number : %d\n", num);
#endif

	return num;
}

void mul_Scalar(int* inverseMatrix, int keyMatrix_sideSize)
{
	int modularInverse = find_modularInverse();

	if (modularInverse == 0)
	{
		printf("your KeyMatrix is not disjoint!!!\n"); // Ű��Ľ��� 26�� ���μҿ��߸� ��ⷯ ������ ��갡��
		return 0;
	}
		

	for (int i = 0; i < keyMatrix_sideSize* keyMatrix_sideSize; i++)
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
	
	int temp1 = 0, temp2 = 0; // ����ſ�

	/*--------------------------------*/
	// 2. ũ�⸸ŭ �����Ҵ� 
	/*--------------------------------*/

	subMatrixs = (int**)malloc(keyMatrix_Size * sizeof(int*));
	if (subMatrixs == NULL)
	{
		errNum = 5;
		goto cal_inverseDeterminant_exit1;
	}

	memset(subMatrixs, 0, keyMatrix_Size * sizeof(int*));

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

		temp1 = (int)pow(-1, signNum);
		temp2 = cal_Determinant(subMatrixs[i], nextMatrix_sideSize); // �ش� ����Ľ� ���ؼ�, ����� ����� ����Ŀ� �ֱ�

		result_InverseMatrix[i] = temp1 * temp2;
	} 

	if (errNum == 3) //��ĽĿ��� �Ҵ� ���� ����ó��
	{
		goto cal_inverseDeterminant_exit2;
	}

#ifdef DEBUG
	printf("after just inversing matrix..\n");
	printMatrix(result_InverseMatrix, keyMatrix_sideSize, keyMatrix_sideSize);
#endif

	/*--------------------------------*/
	// 4. �������ȭ + ���� ��Į�� ����
	/*--------------------------------*/


	transpose_Matrix(result_InverseMatrix, keyMatrix_sideSize); 
#ifdef DEBUG
	printf("after transposing..\n");
	printMatrix(result_InverseMatrix, keyMatrix_sideSize, keyMatrix_sideSize);
#endif


	mul_Scalar(result_InverseMatrix, keyMatrix_sideSize);
#ifdef DEBUG
	printf("after multplying scalar..\n");
	printMatrix(result_InverseMatrix, keyMatrix_sideSize, keyMatrix_sideSize);
#endif
	
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
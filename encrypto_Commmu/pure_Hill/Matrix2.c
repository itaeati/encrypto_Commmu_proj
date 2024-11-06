#include "Matrix.h"
#include "globalVar.h"

#define FINDING_MODULAR_INVERSE(dN, n) (dN*n)%ALPABET_SIZE

char result_strArray[STR_SIZE];		// ��ȣȭ ���� ��� �迭


int find_modularInverse(void) // ����ã��
{
	int num = 0; // ������ �׳� �Ǵ°Ÿ� 1���ص� ��ⷯ������ ��.

	while (1)
	{
		if (FINDING_MODULAR_INVERSE(detNum, ++num) == 1) // �ּ� ������ ��ȯ
			break;
	}

	return num;
}

void mul_Scalar(int* inverseArr, int keySize)
{
	int modularInverse = find_modularInverse();

	for (int i = 0; i < maxIdx; i++)
		inverseArr[i] *= modularInverse;
}

int cal_inverseDeterminant(int* keyArr, int* inverseArr,int keySize) // ó������ ��������, (int)sqrt(maxIdx+peddedNum) ����
{
	// 1. �������� ���ؼ�, ����Ľ��� �ɰ��ְ�, ����Ľ��� ����Ž��

	int** inverseArrays = NULL;			// ù��° ����ĵ��� �����ϴ� �����͹迭
	int modularInverse = 1;
	int next_tempSize = keySize - 1;	// ��Ľ��� ���� +1 �ϼ���, ����� ũ�Ⱑ -1
	int matrixSize = (int)pow(keySize, 2);

	/*--------------------------------*/
	// 1. �������ؼ�, ��Ŀ� ��Į���
	/*--------------------------------*/
	

	/*--------------------------------*/
	// 2. ũ�⸸ŭ �����Ҵ� -> ������ caller���� ������ڸ���!!!
	/*--------------------------------*/

	inverseArrays = (int**)malloc(matrixSize * sizeof(int*));
	if (inverseArrays == NULL)
	{
		errNum = 5;
		goto cal_inverseDeterminant_exit;
	}

	memset(inverseArrays, 0, matrixSize);
	

	/*--------------------------------*/
	// 3. ����Ľ� ���� + ����� �ϼ�
	/*--------------------------------*/

	// ù��°�� �Ҵ��� �迭 ����� ���� �Ҵ����� + �� ����

	// if(�����ڵ尡 0�Ͻ�)
	// {
	//	// ������
	//	// transpose �Լ�
	//	// mul_Scalar(inverseArr, keySize);
	// }
	//	
	

	for (int i = 0; i < keySize; i++)
		free(inverseArrays[i]);

	free(inverseArrays);

cal_inverseDeterminant_exit:
	return inverseArrays;
}
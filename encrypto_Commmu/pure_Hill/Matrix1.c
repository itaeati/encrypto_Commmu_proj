#include "Matrix.h"

char input_strArray[STR_SIZE];		// ���� ��� �迭
int deliverMatrix[STR_SIZE];	// �� * key��� ����� ��� �迭
int maxIdx = 0;					// ���� ũ��
int numMatrix[STR_SIZE];			// ���� �����ϴ� ���ڷ� ��ȯ�� ���� �����ϴ� �迭
int detNum = 1;					// ��Ľİ�
int peddedSize = 0;				// �е�������

bool deleteKey_flag = false;	// Ȥ�ø𸣴� �˻�
int errNum = 0;					// ����üũ

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);
int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void keyElement_input(int* keyMatrix, int keyMatrix_sideSize);

int* make_keyMatrix(int* keyMatrix_sideSize) // key ũ�⸦ �Է¹ް�, key ����� ����� �Լ�
{
	/*--------------------------*/
	// 1. Ű ��� ������ �Է¹ޱ�
	/*--------------------------*/

	int* keyMatrix = NULL;
	printf("Ű�� ���� ũ�⸦ �Է��ϼ���:");

	scanf("%d", keyMatrix_sideSize);

	printf("\n");

	if (!(*keyMatrix_sideSize > 0))
	{
		goto make_keyMatrix_exit;
	}

	/*--------------------------*/
	// 2. Ű��� �Ҵ�
	/*--------------------------*/

	keyMatrix = (int*)malloc((int)pow(*keyMatrix_sideSize, 2) * sizeof(int));

	if (keyMatrix == NULL)
	{
		errNum = 1;
		goto make_keyMatrix_exit;
	}

	deleteKey_flag = true; // ������ �� �������� �����!

	/*--------------------------*/
	// 3. Ű��Ŀ� �Է�
	/*--------------------------*/

	keyElement_input(keyMatrix, *keyMatrix_sideSize);

make_keyMatrix_exit:
	return keyMatrix;
}

void keyElement_input(int* keyMatrix, int keyMatrix_sideSize) // key ��Ŀ� ���� ���ִ� �Լ�
{
	bool isZero_flag = true;
	int keyMatrix_size = keyMatrix_sideSize * keyMatrix_sideSize;

	while (isZero_flag)
	{
		for (int i = 0; i < keyMatrix_size; i++)
		{
			printf("Ű�� �Է��ϼ��� [%d][%d] : ", i / keyMatrix_sideSize, i % keyMatrix_sideSize);
			scanf("%d", &keyMatrix[i]);
			// ������ ����
		}

		if ((detNum = cal_Determinant(keyMatrix, keyMatrix_sideSize)) == 0)
		{
			printf("��Ľ��� 0�Դϴ�! �ٽ��Է��ϼ���!\n");
			isZero_flag = true;
		}
		else
			isZero_flag = false;
	}
	
	return;
}

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize) // key ����� ��Ľ��� 0������ �˻��ϴ� �Լ�
{
	// 0. �迭�� �Ѻ�ũ���� �迭�� ���� ������ �迭 ����

	int keyMatrix_Size = (int)pow(keyMatrix_sideSize, 2);
	int result = 0;				// default ������ 0�� ��ȯ�� caller���� ������ �߻��ϰ� ����ó��!!

	int** subMatrixs = (int**)malloc(keyMatrix_Size * sizeof(int*)); // ����Ľ��� ������ �迭
	int nextMatrix_sideSize = keyMatrix_sideSize - 1;	// ��Ľ��� ���� +1 �ϼ���, ����� ũ�Ⱑ -1
	int nextMatrix_Size = nextMatrix_sideSize * nextMatrix_sideSize;

	if (errNum || subMatrixs == NULL)
	{
		errNum = 2;
		goto cal_Determinant_exit1;
	}

	memset(subMatrixs, 0, keyMatrix_Size);

	if (keyMatrix_sideSize == 2)
	{
		result = keyMatrix[0] * keyMatrix[3] - keyMatrix[1] * keyMatrix[2]; // 2X2 ��Ľ� ������ڸ��� ��ȯ
	}
	else // ����Ž���˰���
	{
		// 1. ����Ľ��� ���� �迭 ����
		for (int i = 0; i < keyMatrix_sideSize; i++)
		{
			subMatrixs[i] = (int*)malloc(nextMatrix_Size * sizeof(int));
			if (errNum || subMatrixs == NULL)
			{
				errNum = 3;
				goto cal_Determinant_exit2;
			}

			// 2. �ش� �ε����� ��� ���� ������ ������ �ε��� ����
			copyIdx(subMatrixs[i], keyMatrix, i, keyMatrix_sideSize);

			// 3. ������� ����
			result += (int)pow(-1, i) * keyMatrix[i] * cal_Determinant(subMatrixs[i], nextMatrix_sideSize);
		}

		// 4. �Ҵ�迭 ����
		for (int i = 0; i < keyMatrix_sideSize; i++)
			free(subMatrixs[i]);
	}
cal_Determinant_exit2:

	if (errNum == 3) // ����Ľ� �Ҵ� ���н�, �Ҵ�� �迭�� ���� ����
	{
		for (int i = 0; i < keyMatrix_Size; i++)
			if (subMatrixs[i] != NULL) free(subMatrixs[i]);
			else break; // �Ҵ��� ���������� �Ǳ� ����
	}

	free(subMatrixs);

cal_Determinant_exit1:
	return result;
}

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize)
{
	// 2.1 ���� ��� �� ���ϱ�
	int srcStd_row = srcStd_idx / srcMatrix_sideSize;
	int srcStd_col = srcStd_idx % srcMatrix_sideSize;
	int destIdx = 0;

	for (int row = 0; row < srcMatrix_sideSize; row++)
	{
		for (int col = 0; col < srcMatrix_sideSize; col++)
		{
			// 2.2 ���� ��� �� ���� ī��
			if (col == srcStd_col || row == srcStd_row)
				continue;

			destMatrix[destIdx++] = srcMatrix[row * srcMatrix_sideSize + col];
		}
	}
}

void input_to_strArray(void)
{
	int padTime = strlen(strArray) - (maxIdx % strlen(strArray)); // keySize ������� �󸶸�ŭ ���������� �����ϴ� ����
	// ������ ����
	bool loopFlag = true;

	do
	{
		/*--------------------------*/
		// 1. strArray �ʱ�ȭ
		/*--------------------------*/

		memset(input_strArray, 0, STR_SIZE); // �迭 �ʱ�ȭ

		/*--------------------------*/
		// 2. string �Է¹ޱ�
		/*--------------------------*/

		printf("���� �Է��ϼ��� (qqq�Է½� ����) : ");

		fgets(input_strArray, STR_SIZE, stdin); //���� strArray�迭�� ���ڿ��� �Է��� �޴´�. (499���� ���� + null)

		if (strcmp(input_strArray, "qqq") || strcmp(input_strArray, "QQQ")) // �������� �˻�
		{
			errNum = 4; // ����ڰ� ��������
			break;
		}

		/*--------------------------*/
		// 3. �������� �˻� + ����ȭ �ϴ� �ݺ���
		/*--------------------------*/

		for (int i = 0; i < strlen(input_strArray); i++) // 
		{
			if ('A' <= input_strArray[i] || input_strArray[i] <= 'Z')
			{
				numMatrix[i] = (int)input_strArray[i] - 'A';
				loopFlag = false;
				maxIdx++;
			}
			else if ('a' <= input_strArray[i] || input_strArray[i] <= 'z')
			{
				numMatrix[i] = (int)input_strArray[i] - ('a' - 'A');
				loopFlag = false;
				maxIdx++;
			}
			else
			{
				printf("invaild charater : %c(%d)\n", input_strArray[i], i);
				printf("try input again\n");

				maxIdx = 0;
				loopFlag = true;
				break;
			}
		}
		if (maxIdx % strlen(strArray) != 0) //strArray�� key����� ���� ���̿� ���� �ʴٸ� ����
		{
			for (int i = 0; i < padTime; i++) //strArray�� key����� ���� ���̿� ���� �ʴٸ� ���� ������ ����
			{
				numArray[maxIdx + i] = '@'; // �߰��Ǵ� ���� 27��° ������ ���� �ִ´�. (27��° ���ڴ� '@'�� �����Ѵ�.)
			}
		}
	} while (loopFlag);

	//�� ������ �е��ϴ� ���� �Լ��� ����

	return;
}


void mul_Matrix(int* keyMatrix, int keyMatrix_sideSize,char* strArray) // ���� ��İ��� ���ִ� �Լ�

{

	int sum = 0;
	int quotient = 0;

	/*------------------------*/
	// 1. �����е�
	/*------------------------*/
	

	/*------------------------*/
	// 2. ���ڸ��� -> ���ϱ�
	/*------------------------*/

	quotient = strlen(numArray) / keySize;

	/*------------------------*/
	// 3. ��ŭ �ݺ��ؼ� ��İ� -> �������
	/*------------------------*/

	for (int i = 0; i < quotient; i++) // key��İ� key�� ����� �� ������ŭ�� �� ���
	{
		for (int j = 0; j < keySize; j++) // ���� �ε���

		{
			for (int k = 0; k < keySize; k++) // ���� �ε���

			{
				sum += keyArray[j * keySize + k] * numArray[i * keySize + k]; //keyArray�� strArray�� ��İ��� �����Ѵ�.
			}

			deliverArray[i * keySize + j] = sum; // ��� ��Ŀ� ��� ���� ������� �ִ´�.
		}
	}




}
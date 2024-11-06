#include "Matrix.h"

char strArray[STR_SIZE];		// ���� ��� �迭
int deliverArray[STR_SIZE];		// �� * key��� ����� ��� �迭
int maxIdx = 0;					// ���� ũ��
int numArray[STR_SIZE];			// ���� �����ϴ� ���ڷ� ��ȯ�� ���� �����ϴ� �迭
int detNum = 1;					// ��Ľİ�
int peddedSize = 0;				// �е�������

bool deleteKey_flag = false;	// Ȥ�ø𸣴� �˻�
int errNum = 0;					// ����üũ

void copyIdx(int* destArr, int* srcArr, int srcStd_idx, int srcSize);
int cal_Determinant(int* keyArray, int keySize);
void keyElement_input(int* keyArray, int keySize);

int* make_keyArray(int* keySize) // key ũ�⸦ �Է¹ް�, key ����� ����� �Լ�
{
	/*--------------------------*/
	// 1. Ű ��� ������ �Է¹ޱ�
	/*--------------------------*/

	int* keyArray = NULL;
	printf("Ű�� ���� ũ�⸦ �Է��ϼ���:");

	scanf("%d", keySize);

	printf("\n");

	if (!(*keySize > 0))
	{
		goto make_keyArray_exit;
	}

	/*--------------------------*/
	// 2. Ű��� �Ҵ�
	/*--------------------------*/

	keyArray = (int*)malloc((int)pow(*keySize, 2) * sizeof(int));

	if (keyArray == NULL)
	{
		errNum = 1;
		goto make_keyArray_exit;
	}

	deleteKey_flag = true; // ������ �� �������� �����!

	/*--------------------------*/
	// 3. Ű��Ŀ� �Է�
	/*--------------------------*/

	keyElement_input(keyArray, *keySize);

make_keyArray_exit:
	return keyArray;
}

void keyElement_input(int* keyArray, int keySize) // key ��Ŀ� ���� ���ִ� �Լ�
{
	bool isZero_flag = true;

	while (isZero_flag)
	{
		for (int i = 0; i < keySize * keySize; i++)
		{
			printf("Ű�� �Է��ϼ��� [%d][%d] : ", i / keySize, i % keySize);
			scanf("%d", &keyArray[i]);
			// ������ ����
		}

		if ((detNum = cal_Determinant(keyArray, keySize)) == 0)
		{
			printf("��Ľ��� 0�Դϴ�! �ٽ��Է��ϼ���!\n");
			isZero_flag = true;
		}
		else
			isZero_flag = false;
	}
	
	return;
}

int cal_Determinant(int* keyArray, int keySize) // key ����� ��Ľ��� 0������ �˻��ϴ� �Լ�
{
	// 0. �迭�� �Ѻ�ũ���� �迭�� ���� ������ �迭 ����

	int tempArr_size = (int)pow(keySize, keySize);
	int result = 0;				// default ������ 0�� ��ȯ�� caller���� ������ �߻��ϰ� ����ó��!!

	int** tempArr = (int**)malloc(tempArr_size * sizeof(int*)); // ����Ľ��� ������ �迭
	if (errNum || tempArr == NULL)
	{
		errNum = 2;
		goto cal_Determinant_exit1;
	}

	memset(tempArr, 0, tempArr_size);

	int tempSize = keySize - 1;	// ��Ľ��� ���� +1 �ϼ���, ����� ũ�Ⱑ -1


	if (keySize == 2)
	{
		result = keyArray[0] * keyArray[3] - keyArray[1] * keyArray[2]; // 2X2 ��Ľ� ������ڸ��� ��ȯ
	}
	else // ����Ž���˰���
	{
		// 1. ����Ľ��� ���� �迭 ����
		for (int i = 0; i < keySize; i++)
		{
			tempArr[i] = (int*)malloc((int)pow(tempSize, 2) * sizeof(int));
			if (errNum || tempArr == NULL)
			{
				errNum = 3;
				goto cal_Determinant_exit2;
			}

			// 2. �ش� �ε����� ��� ���� ������ ������ �ε��� ����
			copyIdx(tempArr[i], keyArray, i, keySize);

			// 3. ������� ����
			result += (int)pow(-1, i) * keyArray[i] * cal_Determinant(tempArr[i], tempSize);
		}

		// 4. �Ҵ�迭 ����
		for (int i = 0; i < keySize; i++)
			free(tempArr[i]);
	}
cal_Determinant_exit2:

	if (errNum == 3) // ����Ľ� �Ҵ� ���н�, �Ҵ�� �迭�� ���� ����
	{
		for (int i = 0; i < tempArr_size; i++)
			if (tempArr[i] != NULL) free(tempArr[i]);
			else break; // �Ҵ��� ���������� �Ǳ� ����
	}

	free(tempArr);

cal_Determinant_exit1:
	return result;
}

void copyIdx(int* destArr, int* srcArr, int srcStd_idx, int srcSize)
{
	// 2.1 ���� ��� �� ���ϱ�
	int srcStd_row = srcStd_idx / srcSize;
	int srcStd_col = srcStd_idx % srcSize;
	int destIdx = 0;

	for (int row = 0; row < srcSize; row++)
	{
		for (int col = 0; col < srcSize; col++)
		{
			// 2.2 ���� ��� �� ���� ī��
			if (col == srcStd_col || row == srcStd_row)
				continue;

			destArr[destIdx++] = srcArr[row * srcSize + col];
		}
	}
}

void input_strArray(void)
{
	// ������ ����
	bool loopFlag = true;

	do
	{
		/*--------------------------*/
		// 1. strArray �ʱ�ȭ
		/*--------------------------*/

		memset(strArray, 0, STR_SIZE); // �迭 �ʱ�ȭ

		/*--------------------------*/
		// 2. string �Է¹ޱ�
		/*--------------------------*/

		printf("���� �Է��ϼ��� (qqq�Է½� ����) : ");

		fgets(strArray, STR_SIZE, stdin); //���� strArray�迭�� ���ڿ��� �Է��� �޴´�. (499���� ���� + null)

		if (strcmp(strArray, "qqq") || strcmp(strArray, "QQQ")) // �������� �˻�
		{
			errNum = 4; // ����ڰ� ��������
			break;
		}

		/*--------------------------*/
		// 3. �������� �˻� + ����ȭ �ϴ� �ݺ���
		/*--------------------------*/

		for (int i = 0; i < strlen(strArray); i++) // 
		{
			if ('A' <= strArray[i] || strArray[i] <= 'Z')
			{
				numArray[i] = (int)strArray[i] - 'A';
				loopFlag = false;
			}
			else if ('a' <= strArray[i] || strArray[i] <= 'z')
			{
				numArray[i] = (int)strArray[i] - ('a' - 'A');
				loopFlag = false;
			}
			else
			{
				printf("invaild charater : %c(%d)\n", strArray[i], i);
				printf("try input again\n");

				loopFlag = true;
				break;
			}
		}
	} while (loopFlag);
}

void mul_Matrix(int* keyArray, int keySize,char* strArray) // ���� ��İ��� ���ִ� �Լ�
{
	/*------------------------*/
	// 1. �����е�
	/*------------------------*/

	/*------------------------*/
	// 2. ���ڸ��� -> ���ϱ�
	/*------------------------*/

	/*------------------------*/
	// 3. ��ŭ �ݺ��ؼ� ��İ� -> �������
	/*------------------------*/
}
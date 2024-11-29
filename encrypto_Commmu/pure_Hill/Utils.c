#include "Librarys.h"
#include "Utils.h"
#include "Matrix.h"
#include "globalVar.h"

void keyElement_input(int* keyMatrix, int keyMatrix_sideSize);
int findCoprime(int leftNum, int rightNum);
void clearBuffer();
void deleteEnterkey();

void cleanUp_func(void)
{
	g_detNum = 1;
	g_maxIdx = 0;
	g_peddedSize = 0;
	g_deleteKey_flag = false;

#ifdef DEBUG
	memset(input_strArray, 0, STR_SIZE * sizeof(char));
	printf("input_strArray reset\t");
	memset(result_strArray, 0, STR_SIZE * sizeof(char));
	printf("result_strArray reset\t");
	memset(deliverMatrix, 0, STR_SIZE * sizeof(int));
	printf("deliverMatrix reset\t");
	memset(numMatrix, 0, STR_SIZE * sizeof(int));
	printf("numMatrix reset\t");
#else
	memset(input_strArray, 0, STR_SIZE * sizeof(char));
	memset(result_strArray, 0, STR_SIZE * sizeof(char));
	memset(deliverMatrix, 0, STR_SIZE * sizeof(int));
	memset(numMatrix, 0, STR_SIZE * sizeof(int));
#endif // DEBUG

	
}

int* make_keyMatrix(int* keyMatrix_sideSize) // key ũ�⸦ �Է¹ް�, key ����� ����� �Լ�
{
	/*--------------------------*/
	// 1. Ű ��� ������ �Է¹ޱ�
	/*--------------------------*/

	int* keyMatrix = NULL;
	printf("Please enter the number of rows for the key:");

	scanf("%d", keyMatrix_sideSize);
	
	clearBuffer();

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

	g_deleteKey_flag = true; // ������ �� �������� �����!

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
	int GCD = 1; // �ִ����� (���������� ���μҰ� �Ǿ�� �ϱ⿡ 1�̵ɰ�)

	while (isZero_flag)
	{
		GCD = 1;

		for (int i = 0; i < keyMatrix_size; i++)
		{
			printf("Please enter the key [%d][%d] : ", i / keyMatrix_sideSize, i % keyMatrix_sideSize);
			scanf("%d", &keyMatrix[i]);
			// ������ ����
		}

		if ((g_detNum = cal_Determinant(keyMatrix, keyMatrix_sideSize)) == 0)
		{
			printf("The determinant is zero! Please enter again!\n");
			isZero_flag = true;
		}
		else
		{
			GCD = findCoprime(abs(g_detNum), ALPABET_SIZE); 
			// ��Ľİ��� ������ ���ü��� �ֱ⿡, �ּҰ������ ����� �ȳ��� ���� ���� (ex : 0) -> ������ ���밪���� Ȯ��
			if (GCD != 1)// ���ĺ�ũ��� ��Ľİ��� ���μ����� Ȯ��
			{
				printf("Your keyMatrix determinant_Num(%d) is not coprime with ALPABET_SIZE(%d)\n", g_detNum, ALPABET_SIZE);
				printf("The Greatest_Common_Divisor between detNum and ALPABET_SIZE = [%d]\n", GCD);
				printf("Please restart inputing keyMatrix process!!\n\n");
				isZero_flag = true;
			}
			else
			{
				printf("The Greatest_Common_Divisor between detNum and ALPABET_SIZE = [% d]\n", GCD);
				printf("You can use your KeyMatrix!!\n");
				isZero_flag = false;
			}
		}
	}
	clearBuffer();
	return;
}

void input_to_strArray(void)
{
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

		printf("Please enter the plaintext (type 'qqq' to exit) : ");

		fgets(input_strArray,STR_SIZE, stdin); //���� strArray�迭�� ���ڿ��� �Է��� �޴´�. (499���� ���� + null) (fgets�� ����Ϸ��� ���۸� ������Ѵ�.)

		deleteEnterkey();

		if (!strcmp(input_strArray, "qqq") || !strcmp(input_strArray, "QQQ")) // �������� �˻�
		{
			errNum = 4; // ����ڰ� ��������
			break;
		}

		/*--------------------------*/
		// 3. �������� �˻� + ����ȭ �ϴ� �ݺ���
		/*--------------------------*/

		for (int i = 0; i < strlen(input_strArray); i++)
		{
			if ('A' <= input_strArray[i] && input_strArray[i] <= 'Z')
			{
				numMatrix[i] = input_strArray[i] - 'A';
				loopFlag = false;
			}
			else if ('a' <= input_strArray[i] && input_strArray[i] <= 'z')
			{
				numMatrix[i] = input_strArray[i] - 'a';
				loopFlag = false;
			}
			else
			{
				printf("invaild charater : %c(%d)\n", input_strArray[i], i);
				printf("try input again\n");

				loopFlag = true;
				break;
			}
		}
	} while (loopFlag);
	clearBuffer();

	g_maxIdx = strlen(input_strArray);
}

void matrixMoudulation(int* targetMatrix, int matrixSize)
{
	if (errNum)
		return;

	for (int i = 0; i < matrixSize; i++)
	{
		targetMatrix[i] = (targetMatrix[i] % ALPABET_SIZE + ALPABET_SIZE) % ALPABET_SIZE; //������ ��츦 ��� ��ⷯ ���� �� 27 ���ϰ� �ٽ� ����
	}

#if defined(DEBUG)

	printf("\nYour Text has been modulated by (Hill cipher)\n");
	for (int i = 0; i < matrixSize; i++)
	{
		printf("%c ", (char)targetMatrix[i] + 'A');
	}
	printf("\n");
#endif
}

void peddingMatrix(int* numMatrix, int leftMatrix_sideSize, int rightMatrix_size)
{
	if (rightMatrix_size % leftMatrix_sideSize)
	{
		g_peddedSize = leftMatrix_sideSize - (rightMatrix_size % leftMatrix_sideSize);

		if (g_peddedSize != 0) //strArray�� key����� ���� ������ ����� �ƴ϶�� �е�����
		{
			for (int i = 0; i < g_peddedSize; i++)
			{
				numMatrix[rightMatrix_size + i] = 26; // �߰��Ǵ� ���� 27��° ������ ���� ����. (27��° ���ڴ� '@')
			}
		}
	}
}

void numtoString(int* targetMatrix, char* result_strArray)
{
	if (errNum)
		return;

	for (int i = 0; i < g_maxIdx ; i++)
	{
		result_strArray[i] = targetMatrix[i] + 'A'; // 26�� �ƴ� ��� 'A'��ŭ ���Ѵ�.
	}
	printf("decoding result = [%s]", result_strArray);
}

void clearBuffer()
{
	
	while (getchar() != '\n' && getchar() != EOF) {}

}

void deleteEnterkey()
{
	input_strArray[strlen(input_strArray) - 1] = NULL;
}

int findCoprime(int leftNum, int rightNum)// ��Ŭ���� �˰������� ���μ����� Ȯ��
{
	int cofactor = 0, gcd = 0;

	for (cofactor = 1; cofactor <= leftNum && cofactor <= rightNum; cofactor++)
	{
		if (leftNum % cofactor == 0 && rightNum % cofactor == 0)
			gcd = cofactor;
	}

	return gcd;
}

#ifdef DEBUG

void printMatrix(int * Matrix, int Matrix_maxRow, int Matrix_maxCol)
{
	for (int i = 0; i < Matrix_maxRow; i++)
	{
		for (int j = 0; j < Matrix_maxCol; j++)
		{
			printf("%d\t", Matrix[i * Matrix_maxRow + j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printAddr(void* ptr, char* Name) // ������ ����Ű�� �ּҰ��� ���
{
	printf("[%s]'s pointing Address : %X",Name,ptr); // ������ �ƴ϶� void * �� �޾Ƶ� �������
}

void printStatus(void)
{
	printf("stringLength : %d\n", g_maxIdx); // ���������� ���¸� ��ȯ
	printf("peddedLength : %d\n", g_peddedSize);
	printf("determinantValue : %d\n\n", g_detNum);
}

void printLoopNum(void)
{
	static int loopNum = 0;

	printf("\nNum of loop : %d\n", loopNum++);
}
#endif 

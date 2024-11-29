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

int* make_keyMatrix(int* keyMatrix_sideSize) // key 크기를 입력받고, key 행렬을 만드는 함수
{
	/*--------------------------*/
	// 1. 키 행렬 사이즈 입력받기
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
	// 2. 키행렬 할당
	/*--------------------------*/

	keyMatrix = (int*)malloc((int)pow(*keyMatrix_sideSize, 2) * sizeof(int));

	if (keyMatrix == NULL)
	{
		errNum = 1;
		goto make_keyMatrix_exit;
	}

	g_deleteKey_flag = true; // 루프를 다 돌기전에 지울것!

	/*--------------------------*/
	// 3. 키행렬에 입력
	/*--------------------------*/

	keyElement_input(keyMatrix, *keyMatrix_sideSize);

make_keyMatrix_exit:
	return keyMatrix;
}

void keyElement_input(int* keyMatrix, int keyMatrix_sideSize) // key 행렬에 값을 써주는 함수
{
	bool isZero_flag = true;
	int keyMatrix_size = keyMatrix_sideSize * keyMatrix_sideSize;
	int GCD = 1; // 최대공약수 (정상적으론 서로소가 되어야 하기에 1이될것)

	while (isZero_flag)
	{
		GCD = 1;

		for (int i = 0; i < keyMatrix_size; i++)
		{
			printf("Please enter the key [%d][%d] : ", i / keyMatrix_sideSize, i % keyMatrix_sideSize);
			scanf("%d", &keyMatrix[i]);
			// 류현수 구현
		}

		if ((g_detNum = cal_Determinant(keyMatrix, keyMatrix_sideSize)) == 0)
		{
			printf("The determinant is zero! Please enter again!\n");
			isZero_flag = true;
		}
		else
		{
			GCD = findCoprime(abs(g_detNum), ALPABET_SIZE); 
			// 행렬식값은 음수가 나올수도 있기에, 최소공약수가 제대로 안나올 수도 있음 (ex : 0) -> 본질은 절대값으로 확인
			if (GCD != 1)// 알파벳크기와 행렬식값이 서로소인지 확인
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
	// 류현수 구현
	bool loopFlag = true;

	do
	{
		/*--------------------------*/
		// 1. strArray 초기화
		/*--------------------------*/

		memset(input_strArray, 0, STR_SIZE); // 배열 초기화

		/*--------------------------*/
		// 2. string 입력받기
		/*--------------------------*/

		printf("Please enter the plaintext (type 'qqq' to exit) : ");

		fgets(input_strArray,STR_SIZE, stdin); //평문을 strArray배열에 문자열로 입력을 받는다. (499개의 문자 + null) (fgets를 사용하려면 버퍼를 비워야한다.)

		deleteEnterkey();

		if (!strcmp(input_strArray, "qqq") || !strcmp(input_strArray, "QQQ")) // 종료조건 검사
		{
			errNum = 4; // 사용자가 직접종료
			break;
		}

		/*--------------------------*/
		// 3. 한자한자 검사 + 정수화 하는 반복문
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
		targetMatrix[i] = (targetMatrix[i] % ALPABET_SIZE + ALPABET_SIZE) % ALPABET_SIZE; //음수일 경우를 대비 모듈러 연산 후 27 더하고 다시 연산
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

		if (g_peddedSize != 0) //strArray가 key행렬의 행의 길이의 배수가 아니라면 패딩시작
		{
			for (int i = 0; i < g_peddedSize; i++)
			{
				numMatrix[rightMatrix_size + i] = 26; // 추가되는 값은 27번째 문자의 값을 대입. (27번째 문자는 '@')
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
		result_strArray[i] = targetMatrix[i] + 'A'; // 26이 아닐 경우 'A'만큼 더한다.
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

int findCoprime(int leftNum, int rightNum)// 유클리드 알고리즘으로 서로소인지 확인
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

void printAddr(void* ptr, char* Name) // 변수가 가리키는 주소값을 출력
{
	printf("[%s]'s pointing Address : %X",Name,ptr); // 접근이 아니라서 void * 로 받아도 상관없음
}

void printStatus(void)
{
	printf("stringLength : %d\n", g_maxIdx); // 전역변수의 상태를 반환
	printf("peddedLength : %d\n", g_peddedSize);
	printf("determinantValue : %d\n\n", g_detNum);
}

void printLoopNum(void)
{
	static int loopNum = 0;

	printf("\nNum of loop : %d\n", loopNum++);
}
#endif 

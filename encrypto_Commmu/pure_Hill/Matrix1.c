#include "Matrix.h"

char input_strArray[STR_SIZE];		// 평문을 담는 배열
int deliverMatrix[STR_SIZE];	// 평문 * key행렬 결과를 담는 배열
int maxIdx = 0;					// 평문의 크기
int numMatrix[STR_SIZE];			// 평문을 대응하는 숫자로 변환한 값을 저장하는 배열
int detNum = 1;					// 행렬식값
int peddedSize = 0;				// 패딩사이즈

bool deleteKey_flag = false;	// 혹시모르는 검사
int errNum = 0;					// 에러체크

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);
int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void keyElement_input(int* keyMatrix, int keyMatrix_sideSize);

int* make_keyMatrix(int* keyMatrix_sideSize) // key 크기를 입력받고, key 행렬을 만드는 함수
{
	/*--------------------------*/
	// 1. 키 행렬 사이즈 입력받기
	/*--------------------------*/

	int* keyMatrix = NULL;
	printf("키의 행의 크기를 입력하세요:");

	scanf("%d", keyMatrix_sideSize);

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

	deleteKey_flag = true; // 루프를 다 돌기전에 지울것!

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

	while (isZero_flag)
	{
		for (int i = 0; i < keyMatrix_size; i++)
		{
			printf("키를 입력하세요 [%d][%d] : ", i / keyMatrix_sideSize, i % keyMatrix_sideSize);
			scanf("%d", &keyMatrix[i]);
			// 류현수 구현
		}

		if ((detNum = cal_Determinant(keyMatrix, keyMatrix_sideSize)) == 0)
		{
			printf("행렬식이 0입니다! 다시입력하세요!\n");
			isZero_flag = true;
		}
		else
			isZero_flag = false;
	}
	
	return;
}

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize) // key 행렬의 행렬식이 0인지를 검사하는 함수
{
	// 0. 배열의 한변크기의 배열을 담을 포인터 배열 선언

	int keyMatrix_Size = (int)pow(keyMatrix_sideSize, 2);
	int result = 0;				// default 값으로 0을 반환시 caller에서 오류가 발생하게 예외처리!!

	int** subMatrixs = (int**)malloc(keyMatrix_Size * sizeof(int*)); // 소행렬식을 저장할 배열
	int nextMatrix_sideSize = keyMatrix_sideSize - 1;	// 행렬식은 깊이 +1 일수록, 행렬의 크기가 -1
	int nextMatrix_Size = nextMatrix_sideSize * nextMatrix_sideSize;

	if (errNum || subMatrixs == NULL)
	{
		errNum = 2;
		goto cal_Determinant_exit1;
	}

	memset(subMatrixs, 0, keyMatrix_Size);

	if (keyMatrix_sideSize == 2)
	{
		result = keyMatrix[0] * keyMatrix[3] - keyMatrix[1] * keyMatrix[2]; // 2X2 행렬식 계산하자마자 반환
	}
	else // 깊이탐색알고리즘
	{
		// 1. 소행렬식을 위한 배열 선언
		for (int i = 0; i < keyMatrix_sideSize; i++)
		{
			subMatrixs[i] = (int*)malloc(nextMatrix_Size * sizeof(int));
			if (errNum || subMatrixs == NULL)
			{
				errNum = 3;
				goto cal_Determinant_exit2;
			}

			// 2. 해당 인덱스의 행과 열을 제외한 나머지 인덱스 대입
			copyIdx(subMatrixs[i], keyMatrix, i, keyMatrix_sideSize);

			// 3. 결과값에 대입
			result += (int)pow(-1, i) * keyMatrix[i] * cal_Determinant(subMatrixs[i], nextMatrix_sideSize);
		}

		// 4. 할당배열 해제
		for (int i = 0; i < keyMatrix_sideSize; i++)
			free(subMatrixs[i]);
	}
cal_Determinant_exit2:

	if (errNum == 3) // 소행렬식 할당 실패시, 할당된 배열들 전부 해제
	{
		for (int i = 0; i < keyMatrix_Size; i++)
			if (subMatrixs[i] != NULL) free(subMatrixs[i]);
			else break; // 할당은 순차적으로 되기 때문
	}

	free(subMatrixs);

cal_Determinant_exit1:
	return result;
}

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize)
{
	// 2.1 기준 행과 열 구하기
	int srcStd_row = srcStd_idx / srcMatrix_sideSize;
	int srcStd_col = srcStd_idx % srcMatrix_sideSize;
	int destIdx = 0;

	for (int row = 0; row < srcMatrix_sideSize; row++)
	{
		for (int col = 0; col < srcMatrix_sideSize; col++)
		{
			// 2.2 기준 행과 열 빼고 카피
			if (col == srcStd_col || row == srcStd_row)
				continue;

			destMatrix[destIdx++] = srcMatrix[row * srcMatrix_sideSize + col];
		}
	}
}

void input_to_strArray(void)
{
	int padTime = strlen(strArray) - (maxIdx % strlen(strArray)); // keySize 배수에서 얼마만큼 차이인지를 저장하는 변수
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

		printf("평문을 입력하세요 (qqq입력시 종료) : ");

		fgets(input_strArray, STR_SIZE, stdin); //평문을 strArray배열에 문자열로 입력을 받는다. (499개의 문자 + null)

		if (strcmp(input_strArray, "qqq") || strcmp(input_strArray, "QQQ")) // 종료조건 검사
		{
			errNum = 4; // 사용자가 직접종료
			break;
		}

		/*--------------------------*/
		// 3. 한자한자 검사 + 정수화 하는 반복문
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
		if (maxIdx % strlen(strArray) != 0) //strArray가 key행렬의 행의 길이와 같지 않다면 시행
		{
			for (int i = 0; i < padTime; i++) //strArray가 key행렬의 행의 길이와 같지 않다면 맞을 때까지 시행
			{
				numArray[maxIdx + i] = '@'; // 추가되는 값은 27번째 문자의 값을 넣는다. (27번째 문자는 '@'에 대응한다.)
			}
		}
	} while (loopFlag);

	//이 다음에 패딩하는 것을 함수로 구현

	return;
}


void mul_Matrix(int* keyMatrix, int keyMatrix_sideSize,char* strArray) // 둘의 행렬곱만 해주는 함수

{

	int sum = 0;
	int quotient = 0;

	/*------------------------*/
	// 1. 문자패딩
	/*------------------------*/
	

	/*------------------------*/
	// 2. 평문자르기 -> 몫구하기
	/*------------------------*/

	quotient = strlen(numArray) / keySize;

	/*------------------------*/
	// 3. 몫만큼 반복해서 행렬곱 -> 결과저장
	/*------------------------*/

	for (int i = 0; i < quotient; i++) // key행렬과 key의 행렬의 행 개수만큼의 평문 행렬
	{
		for (int j = 0; j < keySize; j++) // 행의 인덱스

		{
			for (int k = 0; k < keySize; k++) // 열의 인덱스

			{
				sum += keyArray[j * keySize + k] * numArray[i * keySize + k]; //keyArray와 strArray의 행렬곱을 시행한다.
			}

			deliverArray[i * keySize + j] = sum; // 결과 행렬에 행렬 곱의 결과들을 넣는다.
		}
	}




}
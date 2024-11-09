#include "Matrix.h"

char strArray[STR_SIZE];		// 평문을 담는 배열
int deliverArray[STR_SIZE];		// 평문 * key행렬 결과를 담는 배열
int maxIdx = 0;					// 평문의 크기
int numArray[STR_SIZE];			// 평문을 대응하는 숫자로 변환한 값을 저장하는 배열
int detNum = 1;					// 행렬식값
int peddedSize = 0;				// 패딩사이즈

bool deleteKey_flag = false;	// 혹시모르는 검사
int errNum = 0;					// 에러체크

void copyIdx(int* destArr, int* srcArr, int srcStd_idx, int srcSize);
int cal_Determinant(int* keyArray, int keySize);
void keyElement_input(int* keyArray, int keySize);

int* make_keyArray(int* keySize) // key 크기를 입력받고, key 행렬을 만드는 함수
{
	/*--------------------------*/
	// 1. 키 행렬 사이즈 입력받기
	/*--------------------------*/

	int* keyArray = NULL;
	printf("키의 행의 크기를 입력하세요:");

	scanf("%d", keySize);

	printf("\n");

	if (!(*keySize > 0))
	{
		goto make_keyArray_exit;
	}

	/*--------------------------*/
	// 2. 키행렬 할당
	/*--------------------------*/

	keyArray = (int*)malloc((int)pow(*keySize, 2) * sizeof(int));

	if (keyArray == NULL)
	{
		errNum = 1;
		goto make_keyArray_exit;
	}

	deleteKey_flag = true; // 루프를 다 돌기전에 지울것!

	/*--------------------------*/
	// 3. 키행렬에 입력
	/*--------------------------*/

	keyElement_input(keyArray, *keySize);

make_keyArray_exit:
	return keyArray;
}

void keyElement_input(int* keyArray, int keySize) // key 행렬에 값을 써주는 함수
{
	bool isZero_flag = true;

	while (isZero_flag)
	{
		for (int i = 0; i < keySize * keySize; i++)
		{
			printf("키를 입력하세요 [%d][%d] : ", i / keySize, i % keySize);
			scanf("%d", &keyArray[i]);
			// 류현수 구현
		}

		if ((detNum = cal_Determinant(keyArray, keySize)) == 0)
		{
			printf("행렬식이 0입니다! 다시입력하세요!\n");
			isZero_flag = true;
		}
		else
			isZero_flag = false;
	}
	
	return;
}

int cal_Determinant(int* keyArray, int keySize) // key 행렬의 행렬식이 0인지를 검사하는 함수
{
	// 0. 배열의 한변크기의 배열을 담을 포인터 배열 선언

	int tempArr_size = (int)pow(keySize, keySize);
	int result = 0;				// default 값으로 0을 반환시 caller에서 오류가 발생하게 예외처리!!

	int** tempArr = (int**)malloc(tempArr_size * sizeof(int*)); // 소행렬식을 저장할 배열
	if (errNum || tempArr == NULL)
	{
		errNum = 2;
		goto cal_Determinant_exit1;
	}

	memset(tempArr, 0, tempArr_size);

	int tempSize = keySize - 1;	// 행렬식은 깊이 +1 일수록, 행렬의 크기가 -1


	if (keySize == 2)
	{
		result = keyArray[0] * keyArray[3] - keyArray[1] * keyArray[2]; // 2X2 행렬식 계산하자마자 반환
	}
	else // 깊이탐색알고리즘
	{
		// 1. 소행렬식을 위한 배열 선언
		for (int i = 0; i < keySize; i++)
		{
			tempArr[i] = (int*)malloc((int)pow(tempSize, 2) * sizeof(int));
			if (errNum || tempArr == NULL)
			{
				errNum = 3;
				goto cal_Determinant_exit2;
			}

			// 2. 해당 인덱스의 행과 열을 제외한 나머지 인덱스 대입
			copyIdx(tempArr[i], keyArray, i, keySize);

			// 3. 결과값에 대입
			result += (int)pow(-1, i) * keyArray[i] * cal_Determinant(tempArr[i], tempSize);
		}

		// 4. 할당배열 해제
		for (int i = 0; i < keySize; i++)
			free(tempArr[i]);
	}
cal_Determinant_exit2:

	if (errNum == 3) // 소행렬식 할당 실패시, 할당된 배열들 전부 해제
	{
		for (int i = 0; i < tempArr_size; i++)
			if (tempArr[i] != NULL) free(tempArr[i]);
			else break; // 할당은 순차적으로 되기 때문
	}

	free(tempArr);

cal_Determinant_exit1:
	return result;
}

void copyIdx(int* destArr, int* srcArr, int srcStd_idx, int srcSize)
{
	// 2.1 기준 행과 열 구하기
	int srcStd_row = srcStd_idx / srcSize;
	int srcStd_col = srcStd_idx % srcSize;
	int destIdx = 0;

	for (int row = 0; row < srcSize; row++)
	{
		for (int col = 0; col < srcSize; col++)
		{
			// 2.2 기준 행과 열 빼고 카피
			if (col == srcStd_col || row == srcStd_row)
				continue;

			destArr[destIdx++] = srcArr[row * srcSize + col];
		}
	}
}

void input_strArray(void)
{
	int padTime = strlen(strArray) - (maxIdx % strlen(strArray)); // keySize 배수에서 얼마만큼 차이인지를 저장하는 변수
	// 류현수 구현
	bool loopFlag = true;

	do
	{
		/*--------------------------*/
		// 1. strArray 초기화
		/*--------------------------*/

		memset(strArray, 0, STR_SIZE); // 배열 초기화

		/*--------------------------*/
		// 2. string 입력받기
		/*--------------------------*/

		printf("평문을 입력하세요 (qqq입력시 종료) : ");

		fgets(strArray, STR_SIZE, stdin); //평문을 strArray배열에 문자열로 입력을 받는다. (499개의 문자 + null)

		if (strcmp(strArray, "qqq") || strcmp(strArray, "QQQ")) // 종료조건 검사
		{
			errNum = 4; // 사용자가 직접종료
			break;
		}

		/*--------------------------*/
		// 3. 한자한자 검사 + 정수화 하는 반복문
		/*--------------------------*/

		for (int i = 0; i < strlen(strArray); i++) // 
		{
			if ('A' <= strArray[i] || strArray[i] <= 'Z')
			{
				numArray[i] = (int)strArray[i] - 'A';
				loopFlag = false;
				maxIdx++;
			}
			else if ('a' <= strArray[i] || strArray[i] <= 'z')
			{
				numArray[i] = (int)strArray[i] - ('a' - 'A');
				loopFlag = false;
				maxIdx++;
			}
			else
			{
				printf("invaild charater : %c(%d)\n", strArray[i], i);
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

void mul_Matrix(int* keyArray, int keySize, int* numArray) // 둘의 행렬곱만 해주는 함수
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
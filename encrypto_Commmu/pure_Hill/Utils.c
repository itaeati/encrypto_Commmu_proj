#include "Librarys.h"
#include "Utils.h"
#include "Matrix.h"
#include "globalVar.h"

void keyElement_input(int* keyMatrix, int keyMatrix_sideSize);

void cleanUp_func(void)
{
	g_detNum = 1;
	g_maxIdx = 0;
	g_peddedSize = 0;
	g_deleteKey_flag = false;

	memset(input_strArray, 0, STR_SIZE * sizeof(char));
	memset(result_strArray, 0, STR_SIZE * sizeof(char));
	memset(deliverMatrix, 0, STR_SIZE * sizeof(int));
	memset(numMatrix, 0, STR_SIZE * sizeof(int));
}

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

	while (isZero_flag)
	{
		for (int i = 0; i < keyMatrix_size; i++)
		{
			printf("키를 입력하세요 [%d][%d] : ", i / keyMatrix_sideSize, i % keyMatrix_sideSize);
			scanf("%d", &keyMatrix[i]);
			// 류현수 구현
		}

		if ((g_detNum = cal_Determinant(keyMatrix, keyMatrix_sideSize)) == 0)
		{
			printf("행렬식이 0입니다! 다시입력하세요!\n");
			isZero_flag = true;
		}
		else
			isZero_flag = false;
	}

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
			}
			else if ('a' <= input_strArray[i] || input_strArray[i] <= 'z')
			{
				numMatrix[i] = (int)input_strArray[i] - ('a' - 'A');
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
}
#include "Librarys.h"
#include "Utils.h"
#include "Matrix.h"
#include "globalVar.h"

void keyElement_input(int* keyMatrix, int keyMatrix_sideSize);
void clearBuffer();
void deleteEnterkey();

void cleanUp_func(void)
{
	g_detNum = 1;
	g_maxIdx = 0;
	g_paddingSize = 0;
	g_deleteKey_flag = false;

	memset(input_strArray, 0, STR_SIZE * sizeof(char));
	printf("input_strArray reset\t");
	memset(result_strArray, 0, STR_SIZE * sizeof(char));
	printf("result_strArray reset\t");
	memset(deliverMatrix, 0, STR_SIZE * sizeof(int));
	printf("deliverMatrix reset\t");
	memset(numMatrix, 0, STR_SIZE * sizeof(int));
	printf("numMatrix reset\t");
}

int* make_keyMatrix(int* keyMatrix_sideSize) // key 크기를 입력받고, key 행렬을 만드는 함수
{
	/*--------------------------*/
	// 1. input key Matrix size
	/*--------------------------*/

	int* keyMatrix = NULL;
	printf("input key_side_Size:");

	scanf("%d", keyMatrix_sideSize);
	
	clearBuffer();

	printf("\n");

	if (!(*keyMatrix_sideSize > 0))
	{
		goto make_keyMatrix_exit;
	}

	/*--------------------------*/
	// 2. assign keyMatrix
	/*--------------------------*/

	keyMatrix = (int*)malloc((int)pow(*keyMatrix_sideSize, 2) * sizeof(int));

	if (keyMatrix == NULL)
	{
		errNum = 1;
		goto make_keyMatrix_exit;
	}

	g_deleteKey_flag = true; // Delete Before loop's done!

	/*--------------------------*/
	// 3. input keyMatrix componant
	/*--------------------------*/

	keyElement_input(keyMatrix, *keyMatrix_sideSize);

make_keyMatrix_exit:
	return keyMatrix;
}

void keyElement_input(int* keyMatrix, int keyMatrix_sideSize) // keyMatrix componant input function
{
	bool isZero_flag = true;
	int keyMatrix_size = keyMatrix_sideSize * keyMatrix_sideSize;

	while (isZero_flag)
	{
		for (int i = 0; i < keyMatrix_size; i++)
		{
			printf("input key [%d][%d] : ", i / keyMatrix_sideSize, i % keyMatrix_sideSize);
			scanf("%d", &keyMatrix[i]);
			
		}

		if ((g_detNum = cal_Determinant(keyMatrix, keyMatrix_sideSize)) == 0)
		{
			printf("determinant is 0! please try again!\n");
			isZero_flag = true;
		}
		else
			isZero_flag = false;
	}
	clearBuffer();
	return;
}

void input_to_strArray(void)
{
	bool loopFlag = true;

	do
	{
		/*--------------------------*/
		// 1. strArray initialization
		/*--------------------------*/

		memset(input_strArray, 0, STR_SIZE); // Array initializtion

		/*--------------------------*/
		// 2. string input
		/*--------------------------*/

		printf("input plaintext (if(input == qqq) end) : ");

		fgets(input_strArray,STR_SIZE, stdin); //"Receive plaintext as a string and store it in the strArray array. (499's text + null) (if use the fgets(), clear the buffer.)

		deleteEnterkey();

		if (!strcmp(input_strArray, "qqq") || !strcmp(input_strArray, "QQQ")) // termination condition check
		{
			errNum = 4; // user-initiated termination
			break;
		}

		/*--------------------------*/
		// 3. A loop that checks each character and converts it to an integer
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

	for (int i = 0; i < matrixSize; i++)
	{
		targetMatrix[i] = ((targetMatrix[i] % ALPABET_SIZE) + ALPABET_SIZE) % ALPABET_SIZE; // modulus operation with negative numbers

		printf("%c ", (char)targetMatrix[i] + 'A');
	}

	
}

void paddingMatrix(int* numMatrix, int leftMatrix_sideSize, int rightMatrix_size)
{
	if (rightMatrix_size % leftMatrix_sideSize)
	{
		g_paddingSize = leftMatrix_sideSize - (rightMatrix_size % leftMatrix_sideSize);

		if (g_paddingSize != 0) //"If strArray is not a multiple of the row length of the key matrix, start padding.
		{
			for (int i = 0; i < g_paddingSize; i++)
			{
				numMatrix[rightMatrix_size + i] = 26; //padding value is 26
			}
		}
	}
}

void numtoString(int* targetMatrix, char* result_strArray)
{
	for (int i = 0; i < g_maxIdx + g_paddingSize; i++)
	{
		if (targetMatrix[i] == 26)  // if padding value is 26, value is 'A'
		{
			result_strArray[i] = 'A';
		}

		result_strArray[i] = targetMatrix[i] + 'A'; // if padding value is not 26, add 'A'
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
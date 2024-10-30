#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* make_keyArray(int* key_size)
{
	/*--------------------------*/
	// 1. 키 행렬 사이즈 입력받기
	/*--------------------------*/

	int* keyArray = NULL;
	printf("키의 크기를 입력하세요:");
	scanf("%d", key_size);
	printf("\n");

	if (!(key_size > 0))
	{
		goto make_keyArray_exit;
	}

	/*--------------------------*/
	// 2. 키행렬 할당
	/*--------------------------*/
	
	keyArray = (int*)malloc((int)pow(*key_size, 2) * sizeof(int));

	if (keyArray == NULL)
	{
		goto make_keyArray_exit;
	}

	// 혹시몰라 더 써질지?

make_keyArray_exit:
	return keyArray;
}

void keyElement_input(int* keyArray, int key_size)
{
	
}

void main(void)
{
	int key_size = 0;
	int* keyArr = make_keyArray(&key_size);

	if (keyArr == NULL)
	{
		goto main_exit;
	}

	keyElement_input(keyArr, key_size);

main_exit:
	return;
}
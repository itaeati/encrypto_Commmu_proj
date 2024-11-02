#include "Librarys.h" // 명시를 위해서
#include "Matrix.h"

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
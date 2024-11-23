#pragma once

#include "globalVar.h"
#include "Librarys.h"
#include "Utils.h"
#include "Matrix.h"

void encodingFunc(int keysize, int* keyMatrix);
void decodingFunc(int keysize, int* deliverMatrix, int* keyMatrix);
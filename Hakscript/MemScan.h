#pragma once
#include <Windows.h>


struct ScanData;

class MemScanner
{

	uintptr_t SearchPattern(uintptr_t base, uintptr_t size, ScanData* data);//uses Boyer Moore Horspool alg

};

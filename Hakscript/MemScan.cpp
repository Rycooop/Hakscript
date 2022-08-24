#include "MemScan.h"


/*
	Sample usage:
	ScanData toScan { (char*)"\xF3\x41\x0F\x11\x6D\x50\xF3\x41\x0F\x10\x45\x50\xF3\x0F\x5A\xC0", (char*)"xxxxxxxxxxxxxxxx", PAGE_EXECUTE_READWRITE};
*/

struct ScanData
{
public:
	char* pattern;
	char* mask;
	size_t patternLen;
	DWORD protect = 0x0;//this is for telling what memory pages to scan
	BYTE bad_match_table[0xFF];


	ScanData(char* Pattern, char* Mask, DWORD Protect = 0)
	{
		pattern = Pattern;
		patternLen = strlen(pattern);
		mask = Mask;
		protect = Protect;

		memset(bad_match_table, patternLen, 0xFF);

		for (BYTE i = 0; i < patternLen - 1; i++)   //create a bad match table (necessary for Boyer Moore optimizations)
		{
			BYTE value = patternLen - i - 1;
			bad_match_table[(unsigned char)pattern[i]] = value;
		}
	}
};


/*
* Base: Address to start searching at
* Size: Length of data to search
* Data: ScanData struct to search for
* 
* Returns 0 if nothing found
*/
uintptr_t MemScanner::SearchPattern(uintptr_t base, uintptr_t size, ScanData* data)//uses Boyer Moore Horspool alg
{
	int last = data->patternLen - 1;//index of last element


	//search page
	uintptr_t i = base;
	while (i + data->patternLen < base + size)
	{

		bool found = true;

		uintptr_t loc = 0;

		for (int x = last; x > -1; x--)//iterate over pattern right to left
		{
			loc = i + x;
			try
			{
				if (data->pattern[x] != *(char*)(loc) && data->mask[x] != '?')
				{
					found = false;
					break;
				}
			}
			catch (...)//jic
			{
				found = false;
				break;
			}
		}

		if (found && (uintptr_t)(loc) != (uintptr_t)(data->pattern))
			return i;


		i += data->bad_match_table[*(unsigned char*)(loc)];
	}
	return 0x0;
}

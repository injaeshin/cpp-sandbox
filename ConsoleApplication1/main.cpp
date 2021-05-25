#include "Windows.h"

#include <iostream>

#include "MiniDump.h"

int main()
{
    MiniDump::Init();

	int a = 0;
	int b = 10;

	std::cout << b / a;

    return 0;
}

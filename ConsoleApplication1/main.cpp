#include "Windows.h"

#include <iostream>

#include "MiniDump.h"

int main()
{
    MiniDump::Init();


    int z = 0;
    int a = 10;

    std::cout << a / z;

    return 0;
}

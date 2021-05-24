#include "Windows.h"
#include "MiniDump.h"

int main()
{
    MiniDump::Init();

    int z = 0;
    int a = 10;
    int b = a / 1;


    int c = b / z;

    return 0;
}

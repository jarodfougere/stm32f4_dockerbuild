#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__UNIX__)
#define CMAKE_GENERATOR "Unix Makefiles"
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#else
#define CMAKE_GENERATOR "MinGW Makefiles" 
#error system does not have __UNIX__, _WIN32, WIN32, _WIN64, OR WIN64 DEFINED.
#endif 


static const char *toolchains[] = 
{
    "GNU",
};


int main(int argc, char* argv[])
{   
    int ret = system("cmake -E remove -f Pipeline/CMakeCache.txt; cmake -S CMake -B Pipeline -G %s;cmake --build Pipeline -D PROCESSOR_MPN:string=stm32f411xe", CMAKE_GENERATOR);

    return 0;
}
#include "../Headers/tree_output.h"

int CheckSize_t( size_t number )
{
    if( number < 1000000 )
        return 1;
    else
        return -1;
}


char* GetFilePath( char* filepath, const char* filename )
{
    printf("getting filepath\n");
    const char* directory = "/home/vyacheslav/BinaryTree/";
    sprintf(filepath, "%s%s", directory, filename);

    return filepath;
}



char* SkipSpaces(char* ptr)
{
    int i = 0;
    while( *(ptr + i) == ' ')
    {
        i++;
    }
    return ptr + i;
}

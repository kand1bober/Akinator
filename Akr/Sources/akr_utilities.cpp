#include "../Headers/akr_utilities.h"


char* SkipSpaces(char* ptr)
{
    int i = 0;
    while( *(ptr + i) == ' ')
    {
        i++;
    }
    return ptr + i;
}


char* SkipUntilSpace( char* ptr )
{
    int i  = 0;
    while( *(ptr + i) != ' ' )
    {
        i++;
    }
    return ptr + i;
}

void RotateArray( int* array, int size )
{
    int tmp = 0;
    for(int i = 0; i < size / 2; i++ )
    {
        tmp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = tmp;
    }
}
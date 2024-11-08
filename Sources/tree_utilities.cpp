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
    const char* directory = "/home/vyacheslav/Akinator/";
    sprintf(filepath, "%s%s", directory, filename);

    return filepath;
}


void BufferResize( struct Writing_buffer* buffer )
{
    if ( buffer->ip + 10 >= buffer->capacity )
    {
        buffer->buffer = (char*)realloc( buffer->buffer, buffer->capacity * 2 );
        buffer->capacity *= 2;
    }
}

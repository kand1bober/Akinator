#include <stdlib.h>

#ifndef UTILITIES_LIST_HEADER
#define UTILITIES_LIST_HEADER

char* GetFilePath( char* filepath, const char* filename );
int CheckSize_t( size_t number );
void BufferResize( struct Writing_buffer* buffer );

#endif
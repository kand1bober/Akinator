#include "tree_functions.h"

#ifndef AKINATOR_OUTPUT_HEADER
#define AKINATOR_OUTPUT_HEADER

const char output_image_name[30] = "AkinatorGraph.svg";
const char output_graph_name[30] = "AkinatorGraph.dot";
const char output_html_name[30] = "AkinatorGraph.html";

const size_t START_OUTPUT_FILE_SIZE = 10;
const char default_pointer_color[20] = "#0000CD";
const char pointer_left_color[20] = "#FF0000";
const char pointer_right__color[20] = "#00FF00";

const char fillcolor[20] = "#FFFACD";
const char bgcolor[20] = "#FFD7DC";

struct Writing_buffer
{
    size_t ip;
    char* buffer;
    size_t size;
    size_t capacity;
};

struct File_graph
{
    FILE* stream;
    size_t stream_size;

    Writing_buffer output_buffer;
};

enum Errors Output( struct File_graph* file, struct Node_t* graph );
enum Errors StartOutput( struct File_graph* file );
enum Errors FinishOutput( struct File_graph* file );
enum Errors Print( struct File_graph* file, struct Node_t* node );
void WriteEdge( struct File_graph* file, struct Node_t* node );

#endif

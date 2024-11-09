#include "tree_functions.h"

#ifndef AKINATOR_OUTPUT_HEADER
#define AKINATOR_OUTPUT_HEADER

const char output_image_name[30] = "TreeGraph.svg";
const char output_graph_name[30] = "TreeGraph.dot";
const char output_html_name[30] = "TreeGraph.html";

const size_t START_OUTPUT_FILE_SIZE = 10;
const char default_pointer_color[20] = "#0000CD";
const char pointer_left_color[20] = "#FF0000";
const char pointer_right__color[20] = "#00FF00";

const char fillcolor[20] = "#FFFACD";
const char bgcolor[20] = "#FFD7DC";

struct File_graph
{
    FILE* stream;
    size_t stream_size;
};

enum Errors Output( struct File_graph* file, struct Tree* tree );
enum Errors StartOutput( struct File_graph* file );
enum Errors FinishOutput( struct File_graph* file );
enum Errors Print( struct File_graph* file, struct Tree* tree );
void WriteEdge( struct File_graph* file, struct Node_t* node );

#endif

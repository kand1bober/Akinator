#include "tree_functions.h"

#ifndef AKINATOR_OUTPUT_HEADER
#define AKINATOR_OUTPUT_HEADER

const char output_image_name[30] = "TreeGraph.svg";
const char output_graph_name[30] = "TreeGraph.dot";
const char output_html_name[30] = "TreeGraph.html";

const size_t START_OUTPUT_FILE_SIZE = 10;
const char default_pointer_color[20] = "#FFE9C7";
const char pointer_left_color[20] = "#9ACD32"; 
const char pointer_right_color[20] = "#FF2B00";

const char fillcolor[20] = "#FFA9B8";
const char bgcolor[20] = "#8B4513";
const char fontcolor[20] = "#FFE9C7";

const char fontname[30] = "Verdana";
const char graph_header[30] = "Binary tree";


struct File_graph
{
    FILE* stream;
    size_t stream_size;
};

enum TreeErrors Output( struct File_graph* file, struct Tree* tree );
enum TreeErrors StartOutput( struct File_graph* file );
enum TreeErrors FinishOutput( struct File_graph* file );
enum TreeErrors Print( struct File_graph* file, struct Tree* tree );
void WriteEdge( struct File_graph* file, struct Node_t* node );

#endif

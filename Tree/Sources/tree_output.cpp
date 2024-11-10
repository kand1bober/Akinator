#include "../Headers/tree_functions.h"
#include "../Headers/tree_output.h"

enum TreeErrors Output( struct File_graph* file, struct Tree* tree )
{
    StartOutput( file );

    Print( file, tree );

    FinishOutput( file );

    return GOOD_OUTPUT;
}


enum TreeErrors StartOutput( struct File_graph* file )
{
    char code_filepath[200] = {};
    char html_filepath[200] = {};
    char image_filepath[200] = {};
    GetFilePath( image_filepath, output_image_name );
    GetFilePath( code_filepath, output_graph_name );
    GetFilePath( html_filepath, output_html_name );

    printf("Name of output file with code: %s\n", code_filepath); 

    //============================== GRAPH FILE ====================================
    file->stream = fopen(code_filepath, "w");
    fprintf(file->stream, "digraph G\n{\nlabel=\"%s\";\nlabelloc=\"t\";\nfontsize=30\nfontname=\"%s\";\nfontcolor=\"%s\"\n"
    "splines=polyline\nrankdir=TB;size=\"200,300\";bgcolor=\"%s\";\n", graph_header, fontname, fontcolor, bgcolor);
    //==============================================================================

    
    //============================== HTML FIlE =====================================
    FILE* html_stream = fopen( html_filepath, "w" );
    fprintf(html_stream, "<img src=\"%s\"  alt=\"MyGraph\" width=\"1300px\" height=\"900px\">", image_filepath);
    fclose( html_stream );
    //==============================================================================

    return GOOD_START_OUTPUT;
}


enum TreeErrors FinishOutput( struct File_graph* file )
{
    fprintf(file->stream, "\n}\n");
    char cmd[256] = {};
    snprintf(cmd, sizeof(cmd), "dot -Tsvg %s > %s", output_graph_name, output_image_name);
    ON_DEBUG( printf(SINIY "command for graphviz: " YELLOW "%s\n" DELETE_COLOR, cmd); )

    fclose(file->stream);

    system( cmd );

    return GOOD_FINISH_OUTPUT;
}


enum TreeErrors Print( struct File_graph* file, struct Tree* tree )
{   
    WriteEdge( file, tree->root );

    // fprintf(file->stream, "node_%d -> node_d [color = \"%s\", arrowsize = 1] ;\n", ,default_pointer_color);
        
    return GOOD_PRINT;
}

void WriteEdge( struct File_graph* file, struct Node_t* node )
{
    struct Node_t* left = node->left;
    struct Node_t* right = node->right;

    fprintf(file->stream, " node_%p [shape=record,style=\"rounded,filled\",fillcolor=\"%s\",color=\"%s\",label=\" { { <curr%p> curr: %p } | { <parent%p> parent: %p } | { <data%p> data: %0.2lf} | { { <left%p> L: %p } | { <right%p> R: %p } } } \" ]; ",
                            node, fillcolor, default_pointer_color, node, node, node, node->parent, node, node->data, node, left, node, right );

    if( node->left )
    {
        fprintf(file->stream, " node_%p [shape=record,style=\"rounded,filled\",fillcolor=\"%s\",color=\"%s\",label=\" { { <curr%p> curr: %p } { <parent%p> parent: %p } | | { <data%p> data: %0.2lf} | { { <left%p> L: %p } | { <right%p> R: %p } } } \" ];",
        left, fillcolor, default_pointer_color, left, left, left, left->parent, left, left->data, left, left->left, left, left->right);

        fprintf(file->stream, "node_%p -> node_%p [color = \"%s\", arrowsize = 1] ;\n", node, left, pointer_left_color );    
        WriteEdge( file, node->left );
    }

    if( node->right )
    {
        fprintf(file->stream, " node_%p [shape=record,style=\"rounded,filled\",fillcolor=\"%s\",color=\"%s\",label=\" { { <curr%p> curr: %p } { <parent%p> parent: %p } | | { <data%p> data: %0.2lf} | { { <left%p> L: %p } | { <right%p> R: %p } } } \" ];",
        right, fillcolor, default_pointer_color, right, right, right, right->parent, right, right->data, right, right->left, right, right->right );

        fprintf(file->stream, "node_%p -> node_%p [color = \"%s\", arrowsize = 1] ;\n", node, right, pointer_right_color );    
        WriteEdge( file, node->right );
    }

    return;
}

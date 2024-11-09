#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "tree_configuration.h"
#include "tree_macros.h"
#include "tree_decoration.h"
#include "tree_utilities.h"

#ifndef AKINATOR_FUNCTIONS_HEADER
#define AKINATOR_FUNCTIONS_HEADER

typedef double TreeElem;
const uint64_t POISON = 0xBADBABA;


enum Errors
{
    GOOD_TREE,
    BAD_TREE,

    GOOD_PRINT,
    BAD_PRINT,

    GOOD_OUTPUT,
    BAD_OUTPUT,

    GOOD_START_OUTPUT,
    BAD_START_OUTPUT,

    GOOD_FINISH_OUTPUT,
    BAD_FINISH_OUTPUT,

    GOOD_CTOR,
    BAD_CTOR,

    GOOD_DTOR,
    BAD_DTOR,

    GOOD_CREATE,
    BAD_CREATE,

    GOOD_INSERT,
    BAD_INSERT,

    GOOD_EXTRACT,
    BAD_EXTRACT,

    GOOD_DELETE,
    BAD_DELETE,

    GOOD_FIND,
    BAD_FIND,
};

struct Node_t
{   
    TreeElem data;
    Node_t* left;
    Node_t* right;
    Node_t* parent;
};

struct Tree 
{
    Node_t* root;
    Errors status;
};

enum Errors TreeCtor( struct Tree* tree );
enum Errors TreeDtor( struct Tree* tree );
void FreeTree( struct Node_t* node);
enum Errors CreateNode( TreeElem data, struct Node_t* new_node );
enum Errors ExtractNode( struct Tree* tree, struct Node_t* node );
enum Errors NodeInsert( struct Tree* tree, struct Node_t* left, struct Node_t* right, struct Node_t* node );
enum Errors Find( struct Tree* tree, TreeElem to_find, struct Node_t* answer);
void FindNode( struct Node_t* node_search, TreeElem to_find, struct Node_t* answer );


#endif

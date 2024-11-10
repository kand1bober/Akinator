#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "tree_configuration.h"
#include "tree_macros.h"
#include "tree_decoration.h"
#include "tree_utilities.h"

#ifndef AKINATOR_FUNCTIONS_HEADER
#define AKINATOR_FUNCTIONS_HEADER

typedef double TreeElem;
const uint64_t POISON = 0xBADBABA;


enum TreeErrors
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

enum Direction
{
    LEFT = 1,
    RIGHT = 2,
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
    TreeErrors status;
};

//------------------OPERATIONS WITH TREE---------------------------
enum TreeErrors TreeCtor( struct Tree* tree );
enum TreeErrors TreeDtor( struct Tree* tree );
void FreeTree( struct Node_t* node);


//------------------OPERATIONS WITH NODES--------------------------
enum TreeErrors CreateNode( TreeElem data, struct Node_t** new_node );
enum TreeErrors Find( struct Tree* tree, TreeElem to_find, struct Node_t** answer);
enum TreeErrors ExtractNode( struct Node_t* node );
enum TreeErrors NodeInsert( struct Node_t* left, struct Node_t* right, struct Node_t* node );
enum TreeErrors InsertLeave( struct Node_t* parent, enum Direction branch, struct Node_t* to_connect );
enum TreeErrors NodeDelete( struct Node_t* node );
//----------------------------RECURSIVE FUNCTIONS--------------------------------------
void FindNode( struct Node_t* node_search, TreeElem to_find, struct Node_t** answer );
void FindEmpty( struct Node_t* node, struct Node_t** answer );

#endif

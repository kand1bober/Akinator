#include <stdio.h>
#include <stdlib.h>

#include "tree_configuration.h"
#include "tree_macros.h"
#include "tree_decoration.h"
#include "tree_utilities.h"

#ifndef AKINATOR_FUNCTIONS_HEADER
#define AKINATOR_FUNCTIONS_HEADER


typedef double TreeElem;

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

    GOOD_INSERT,
    BAD_INSERT,

    GOOD_EXTRACT,
    BAD_EXTRACT,

    GOOD_CREATE,
    BAD_CREATE,

    GOOD_DELETE,
    BAD_DELETE,
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


#endif

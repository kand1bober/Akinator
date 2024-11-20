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

#ifndef TREE_FUNCTIONS_HEADER
#define TREE_FUNCTIONS_HEADER

const int STRING_SIZE = 100;
const int STRING_ARRAY_SIZE = 100;
typedef char* DataElem; //указатель на строку 
typedef char TreeElem[STRING_SIZE]; // строка

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

    FOUND_EMPTY_STRING,
    NOT_FOUND_EMPTY_STRING,
    SAME_STRING_EXISTS,
    SAME_STRING_NOT_EXISTS,
    GOOD_STRING_DELETE,
    BAD_STRING_DELETE,

    GOOD_INSERT,
    BAD_INSERT,

    GOOD_EXTRACT,
    BAD_EXTRACT,

    GOOD_DELETE,
    BAD_DELETE,

    GOOD_FIND,
    BAD_FIND,

    GOOD_DATA,
    BAD_DATA,

    GOOD_INPUT,
    BAD_INPUT
};

enum Direction
{
    LEFT = 1,
    RIGHT = 2,
    NO_BRANCH = 3,
};

struct SmartString
{
    TreeElem string;
    int links_amount;
};

struct Node_t
{   
    DataElem data;
    Node_t* left;
    Node_t* right;
    Node_t* parent;
};

struct Tree 
{
    Node_t* root;
    SmartString strings[STRING_ARRAY_SIZE]; //массив структур со строкой и кол-ввом ссылок на неё
    TreeErrors status;
};

//-------------------------------OPERATIONS WITH TREE------------------------------------
enum TreeErrors TreeCtor( struct Tree* tree );
enum TreeErrors TreeDtor( struct Tree* tree );
void FreeTree( struct Tree* tree, struct Node_t* node ); //-------- recursive

//--------------------------------OPERATIONS WITH NODES----------------------------------
enum TreeErrors CreateNode( struct Tree* tree, TreeElem data, struct Node_t** new_node );
enum TreeErrors FindString( struct Tree* tree, TreeElem to_find, int* string_position );
enum TreeErrors Find( struct Tree* tree, TreeElem to_find, struct Node_t** answer);
enum TreeErrors NodeDelete( struct Tree* tree, struct Node_t* node );
enum TreeErrors InsertNode( struct Node_t* left, struct Node_t* right, struct Node_t* node );
enum TreeErrors InsertLeave( struct Tree* tree, struct Node_t* parent, enum Direction branch, struct Node_t* to_connect );

//----------------------------RECURSIVE FUNCTIONS----------------------------------------
void FindNode( struct Node_t* node_search, TreeElem to_find, struct Node_t** answer );

//---------------------------- STRING FUCTIONS ------------------------------------------
enum TreeErrors FindString( struct Tree* tree, TreeElem to_find, int* string_position );
enum TreeErrors FindSameString( struct Tree* tree, TreeElem to_find, int* string_position );
enum TreeErrors FindEmptyString( struct Tree* tree, int* string_position );
enum TreeErrors DeleteString( struct Tree* tree, TreeElem string );
void StringDump( struct Tree* tree );

#endif

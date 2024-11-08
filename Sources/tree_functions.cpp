#include "../Headers/tree_functions.h"

// Node root;
// TreeCtor(Tree* tree)
// TreeDtor() // рекурснивно
// CreateNode(data, Node_t left, Node_t right) {Node_t new_node = calloc(), new_node->data = data, left->parent = new_node}
// NodeDelete
// NodeInsert
// TreeDump


enum Errors TreeCtor( struct Tree* tree )
{
    tree->root = (Node_t*)calloc( 1, sizeof( Node_t ) );
    if(tree->root)
    {
        tree->status = GOOD_TREE;
        return GOOD_CTOR;
    }
    else 
    {
        tree->status = BAD_TREE;
        return BAD_CTOR;
    }

    return GOOD_CTOR;
}

enum Errors TreeDtor( struct Tree* tree )
{
    free( tree->root );

    if( !tree->root )
    {
        tree->status = GOOD_TREE;
        return GOOD_DTOR;
    }
    else 
    {
        tree->status = BAD_TREE;
        return BAD_DTOR;
    }

    return GOOD_DTOR;
}


enum Errors CreateNode( struct Tree* tree, TreeElem data, )
{


    return GOOD_CREATE;
}

//extract + delete
enum Errors NodeDelete( struct Node_t* node )
{


    return GOOD_DELETE;
}

//insert already existing node
enum Errors NodeInsert( struct Node_t* node )
{


    return GOOD_INSERT;
}


enum Errors ExtractNode( struct Node_t* node )
{


    return GOOD_EXTRACT;
}



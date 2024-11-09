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
    // free( tree->root );

    FreeTree( tree->root );

    return GOOD_DTOR;
}


void FreeTree( struct Node_t* node)
{   
    struct Node_t* left = node->left;
    struct Node_t* right = node->right;

    if( left )
    {
        FreeTree(left);
    }

    if( right )
    {
        FreeTree(right);
    }

    free( node );
}


enum Errors CreateNode( TreeElem data, struct Node_t* new_node )
{
    new_node = (Node_t*)calloc( 1, sizeof( Node_t ) );

    new_node->data = data;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;

    return GOOD_CREATE;
}

//extract + delete
enum Errors NodeDelete( struct Tree* tree, struct Node_t* node )
{
    ExtractNode( tree, node );

    node->data = 0;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    free(node);

    return GOOD_DELETE;
}

//insert already existing node
enum Errors NodeInsert( struct Tree* tree, struct Node_t* left, struct Node_t* right, struct Node_t* node )
{
    if( (left != nullptr) && (right != nullptr) )
    {
        if( left->parent == right->parent )
        {
            left->parent->left = node;
            left->parent->right = nullptr; // всегда освобождаем правый элемент при вставке

            left->parent = node;
            right->parent = node;

            node->left = left;
            node->right = right;

            return GOOD_INSERT;
        }
        else
        {
            tree->status = BAD_TREE;
            printf(YELLOW "Pointers don't connect\n" DELETE_COLOR);
        }   
    }
    if( (left == nullptr) && (right==nullptr) )
    {
        if()
        {

        }
        else 
        {
        
        }
        printf(YELLOW "Two null pointers, wrong insert\n" DELETE_COLOR);
        return GOOD_INSERT;
    }
    if( (left != nullptr) && (right == nullptr) )
    {
        left->parent->left = node;

        left->parent = node;

        node->left = left;

        return GOOD_INSERT;
    }
    if( (left == nullptr) && (right != nullptr) )
    {
        right->parent->left = node;

        right->parent = node;

        node->right = right;

        return GOOD_INSERT;
    }

    tree->status = BAD_TREE;
    return BAD_INSERT;  
}


enum Errors ExtractNode( struct Tree* tree, struct Node_t* node )
{
    //------ RECURSIVE GO DOWN -------
    
    //--------------------------------

    return GOOD_EXTRACT;
}


enum Errors Find( struct Tree* tree, TreeElem to_find, struct Node_t* answer)
{
    FindNode(tree->root, to_find, answer);
}


void FindNode( struct Node_t* node_search, TreeElem to_find, struct Node_t* answer )
{
    struct Node_t* left_search = nullptr;
    struct Node_t* right_search = nullptr;
    //---------------------------------------------------
    if( fabs(left_search->data - to_find) > EPSILON )
    {
        FindNode( left_search, to_find, answer);
    }

    if( fabs(left_search->data - to_find) > EPSILON )
    {   
        FindNode( right_search, to_find, answer );
    }
    //----------------------------------------------------
    if( fabs(left_search->data - to_find) <= EPSILON )
    {
        answer = left_search;
    }
    else if( fabs(left_search->data - to_find) <= EPSILON)
    {
        answer = right_search;
    }
    else 
    { 
        answer = nullptr;
    }
}

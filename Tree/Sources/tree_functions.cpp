#include "../Headers/tree_functions.h"

// Node root;
// TreeCtor(Tree* tree)
// TreeDtor() // рекурснивно
// CreateNode(data, Node_t left, Node_t right) {Node_t new_node = calloc(), new_node->data = data, left->parent = new_node}
// NodeDelete
// NodeInsert
// TreeDump


enum TreeErrors TreeCtor( struct Tree* tree )
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

enum TreeErrors TreeDtor( struct Tree* tree )
{
    FreeTree( tree->root );

    return GOOD_DTOR;
}


void FreeTree( struct Node_t* node)
{   
    struct Node_t* left = node->left;
    struct Node_t* right = node->right;

    if( left != nullptr)
    {
        FreeTree(left);
    }

    if( right != nullptr )
    {
        FreeTree(right);
    }

    free( node );
}


enum TreeErrors CreateNode( TreeElem data, struct Node_t** new_node )
{
    *new_node = (Node_t*)calloc( 1, sizeof( Node_t ) );

    (*new_node)->data = data;
    (*new_node)->left = nullptr;
    (*new_node)->right = nullptr;

    return GOOD_CREATE;
}


//extract + delete
enum TreeErrors NodeDelete( struct Node_t* node )
{
    ExtractNode( node );

    node->data = 0;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    free(node);

    return GOOD_DELETE;
}


enum TreeErrors InsertLeave( struct Node_t* parent, enum Direction branch, struct Node_t* to_connect )
{   
    if( branch == LEFT )
    {
        if(parent->left == nullptr)
        {
            parent->left = to_connect;
            to_connect->parent = parent;

            return GOOD_INSERT;
        } 
        else 
        {
            printf(RED "your parent node have leaves\n"
            "So call InsertNode function instead of this function\n"
            "And your node deleted for programm to not catch seg-fault\n"
            "So create it again\n" DELETE_COLOR);

            free(to_connect);

            return BAD_INSERT;
        }
    }   
    else if( branch == RIGHT )
    {
        if( parent->right == nullptr)
        {
            parent->right = to_connect;
            to_connect->parent = parent;
        }
        else 
        {
            printf(RED "your parent node have leaves\n"
            "So call InsertNode function instead of this function\n"
            "And your node deleted for programm to not catch seg-fault\n"
            "So create it again\n" DELETE_COLOR);
            
            free(to_connect);

            return BAD_INSERT;
        }

        return GOOD_INSERT;
    }

    return GOOD_INSERT;
}

//insert already existing node
enum TreeErrors NodeInsert( struct Node_t* left, struct Node_t* right, struct Node_t* node )
{
    if( (left != nullptr) && (right != nullptr) )
    {
        ON_DEBUG( printf(SINIY "inserting in the middle of tree\n" DELETE_COLOR); )

        if( left->parent == right->parent )
        {
            left->parent->left = node;
            left->parent->right = nullptr; // всегда освобождаем правый элемент при вставке

            node->parent = left->parent;

            left->parent = node;
            right->parent = node;

            node->left = left;
            node->right = right;

            return GOOD_INSERT;
        }
        else
        {
            // tree->status = BAD_TREE;
            printf(YELLOW "Pointers don't connect\n" DELETE_COLOR);
        }   
    }
    if( (left == nullptr) && (right == nullptr) ) //TODO: этот пункт пока хз
    {
        printf(RED "Two null pointers pasted -- means yout parent node have no leaves.\n"
        "free is used to avoid memory leaks\n"
        "Call InsertLeave To create leaves\n" DELETE_COLOR);

        free( node );

        return GOOD_INSERT;
    }
    if( (left != nullptr) && (right == nullptr) )
    {
        ON_DEBUG( printf(SINIY "insert, left exists, right doesn't\n" DELETE_COLOR); )
        if( left->parent->left == left)
        {
            left->parent->left = node;
        }
        else if( left->parent->right == left)
        {
            left->parent->right = node;
        }

        node->parent = left->parent;

        left->parent = node;

        node->left = left;


        return GOOD_INSERT;
    }
    if( (left == nullptr) && (right != nullptr) )
    {
        ON_DEBUG( printf(SINIY "insert, right exists, left doesn't\n" DELETE_COLOR); )

        if( right->parent->left == right)
        {
            right->parent->left = node;
        }
        else if( right->parent->right == right)
        {
            right->parent->right = node;
        }

        node->parent = right->parent;

        right->parent = node;

        node->right = right;

        return GOOD_INSERT;
    }

    // tree->status = BAD_TREE;
    return BAD_INSERT;  
}


enum TreeErrors ExtractNode( struct Node_t* node )
{
    if( node )
    {
        if( (node->left == nullptr) && (node->right == nullptr) )
        {
            ON_DEBUG( printf(SINIY "extracting \"leave\" node\n" DELETE_COLOR); )

            free(node);
        }
        if( (node->left != nullptr) && (node->right != nullptr) )
        {
            ON_DEBUG( printf(SINIY "extracting node with both branches\n( causes deletion of all nodes under )\n" DELETE_COLOR); )
 
            struct Node_t* tmp_parent = node->parent;

            // printf(YELLOW "pointers:\ntmp_parent: %p\nnode: %p\n\n" DELETE_COLOR, tmp_parent, node);

            if( tmp_parent->left == node )
            {
                tmp_parent->left = nullptr;
            }
            else if(  tmp_parent->right == node )
            {
                tmp_parent->right = nullptr;
            }
            
            FreeTree( node );

            return GOOD_EXTRACT;
        }
        if( (node->left != nullptr) && (node->right == nullptr) ) //TODO: вопрос, удалять ли полностью или оставлять, пока оставляю, удаление сделать просто
        {
            ON_DEBUG( printf(SINIY "extracring node with only left branch\n" DELETE_COLOR); )

            if( node->parent->left == node )
            {
                node->parent->left = node->left;
            }
            else if(  node->parent->parent->right == node )
            {
                node->parent->right = node->left;
            }

            free( node );

            return GOOD_EXTRACT;
        }
        if( (node->left == nullptr) && (node->right != nullptr) )
        {
            ON_DEBUG( printf(SINIY "extracting node with only right branch\n" DELETE_COLOR); )

            if( node->parent->left == node )
            {
                node->parent->left = node->right;
            }
            else if(  node->parent->parent->right == node )
            {
                node->parent->right = node->right;
            }

            free( node );

            return GOOD_EXTRACT;    
        }
    }
    else 
    {   
        printf(RED "wrong node pointer pasted to extract");
        return BAD_EXTRACT;
    }

    return BAD_EXTRACT;
}


void FindEmpty( struct Node_t* node, struct Node_t** answer )
{
    struct Node_t* left = node->left;
    struct Node_t* right = node->right;

    if( *answer == nullptr )
    {
        if ( (left == nullptr) && (right == nullptr) )
        {
            *answer = node;
            return;
        }
        else if( (left != nullptr) && (right != nullptr) )
        {
            FindEmpty( left, answer );
            FindEmpty( right, answer );
        }
        else if( (left == nullptr) && (right != nullptr) )
        {
            FindEmpty( right, answer );
        }
        else if( (left != nullptr) && (right == nullptr) )
        {
            FindEmpty( left, answer );
        }
    }
    else 
    {
        return;
    }
}


enum TreeErrors Find( struct Tree* tree, TreeElem to_find, struct Node_t** answer)
{
    printf("need to find: %.2lf\n", to_find);
    FindNode(tree->root, to_find, answer);

    return GOOD_FIND;
}


void FindNode( struct Node_t* node_search, TreeElem to_find, struct Node_t** answer )
{
        ON_DEBUG( printf(YELLOW "====== Start of FindNode ======\n" DELETE_COLOR); )
    struct Node_t* left_search = node_search->left;
        ON_DEBUG( printf(PURPLE "    left: %p\n" DELETE_COLOR, node_search->left); )
        ON_DEBUG( printf(PURPLE "    right: %p\n" DELETE_COLOR, node_search->right); )
    struct Node_t* right_search = node_search->right;

    if( fabs( node_search->data - to_find) > EPSILON )
    {
        if( left_search != nullptr)
        {
            ON_DEBUG( printf(PURPLE "        going left\n" DELETE_COLOR); )
            FindNode( left_search, to_find, answer);
        }

        if( right_search != nullptr )
        {   
            ON_DEBUG( printf(PURPLE "        going right\n" DELETE_COLOR); )
            FindNode( right_search, to_find, answer );
        }
    }
    else 
    {
        ON_DEBUG( printf("node: %p, data: %.2lf\n", node_search, node_search->data); )
        *answer = node_search;
            ON_DEBUG( printf(YELLOW "====== End of FindNode ======\n" DELETE_COLOR); )
        return;
    }
}

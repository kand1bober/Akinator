#include "../Headers/tree_functions.h"
#include "../Headers/tree_output.h"

int main()
{
        struct File_graph graph_file = {};

        // struct Node_t n_17 = { 17, nullptr, nullptr, nullptr };
        // struct Node_t n_80 = { 80, nullptr, nullptr, nullptr };
        // struct Node_t n_65 = { 65, nullptr, nullptr, nullptr };
        // struct Node_t n_10 = { 10, nullptr, &n_17, nullptr };
        // struct Node_t n_30 = { 30, &n_10, nullptr, nullptr };
        // struct Node_t n_70 = { 70, &n_65, &n_80, (Node_t*)0XBADBABA };
        // struct Node_t n_50 = { 50, &n_30, &n_70, nullptr };
        // struct Tree tree = {&n_50, GOOD_TREE };

        // Output( &graph_file, &tree );

        

        
    struct Tree my_tree = {};
    TreeCtor( &my_tree );

    // ========== PREKOLES ==========
    struct Node_t* tmp_node = nullptr;
    CreateNode( 14.88, tmp_node);
    NodeInsert( &my_tree, my_tree.root->left, my_tree.root->right, tmp_node );
    // ==============================

    if(my_tree.status == GOOD_TREE)
    {
        Output( &graph_file, &my_tree);
    }
    else 
    {
        printf(RED "Bad Tree :(\n" DELETE_COLOR);
    }
    TreeDtor( &my_tree );

    return 0;
}

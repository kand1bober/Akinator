#include "../Headers/tree_functions.h"
#include "../Headers/tree_output.h"

int main()
{
    struct Node_t tree{};

        struct File_graph graph = {};
        struct Node_t n_17 = { 17, nullptr, nullptr };
        struct Node_t n_80 = { 80, nullptr, nullptr };
        struct Node_t n_65 = { 65, nullptr, nullptr };
        struct Node_t n_10 = { 10, nullptr, &n_17 };
        struct Node_t n_30 = { 30, &n_10, nullptr };
        struct Node_t n_70 = { 70, &n_65, &n_80 };
        struct Node_t n_50 = { 50, &n_30, &n_70 };

        Output( &graph, &n_50 );

        
    struct Tree my_tree = {};
    TreeCtor( &my_tree );
    Output();

    return 0;
}

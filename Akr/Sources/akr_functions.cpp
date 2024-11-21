#include "../Headers/akr_functions.h"

enum AkrErrors Game( )
{
    struct Tree game_tree = {};          //tree structure
    struct File_input file_input = {};  //file with illustration of tree; to read from; used only in one function to create tree;

    struct File_text file_output = {}; //file with illustration of tree; to write into
    struct File_text file_graph = {}; //file with code for graphviz

    MakeTreeData( &file_graph, &file_input, &game_tree );
    
    int* answer_path = (int*)calloc( MAX_DEPTH, sizeof( int ) );

    Run( &file_graph, &file_output, &game_tree, &answer_path );

    free( answer_path );    

    TreeDtor( &game_tree );

    return GOOD;
}


enum AkrErrors Run( struct File_text* file_graph, struct File_text* file_output, struct Tree* tree, int** answer_path )
{
    while(1)
    {   
        free( *answer_path );
        *answer_path = (int*)calloc( MAX_DEPTH, sizeof( int ) );

        printf("==============================\n"
               "Choose option fo the programm:\n"
               "'q' -- quit                   \n"
               "'s' -- save data base         \n"
               "'p' -- play the game          \n"
               "'d' -- dump the game tree     \n"
               "==============================\n");

        //---------Input--------       
        char* option = nullptr;
        option = readline(">>> ");
        //----------------------
        switch( *option )
        {
            case 'q':
            {
                printf(YELLOW "You chose to " RED "quit" YELLOW "\n"
                              "Closing programm\n" DELETE_COLOR);
                free( option );
                return GOOD;
                break;
            }
            case 's':
            {
                printf(YELLOW "You chose to " SINIY "save data" YELLOW "\n" DELETE_COLOR);  
                TreeData( tree, file_output );
                free( option );   
                // return GOOD;
                break;
            }
            case 'p':
            { 
                printf(YELLOW "You chose to " SINIY "play" YELLOW "\n" DELETE_COLOR);
                Play( tree, answer_path );
                free( option );   
                break;
            }         
            case 'd':
            {
                printf(YELLOW "You chose to " SINIY "dump tree graph" YELLOW  "\n" DELETE_COLOR);
                Output( file_graph, tree );
                free( option );   
                break;
            }
            default: 
            {
                printf(RED "\n\nHUUUUUUUUUUUUUUUY\ninputed symbol: '%c'\n" DELETE_COLOR, *option);
                free( option );   
                break;
            }
        }
    }
}


enum AkrErrors Play( struct Tree* tree, int** answer_path )
{
    printf(YELLOW "     ====== You started Akinator ======\n"
                  "Think of the charachter you want me to guess\n" DELETE_COLOR);

    Guess( tree, tree->root, answer_path );

    printf(YELLOW "     ====== End of the game ======\n" DELETE_COLOR);

    return GOOD;
}   


enum AkrErrors Guess( struct Tree* tree, struct Node_t* node, int** answer_path )
{
    static int path_depth_count = 1;
        ON_DEBUG( printf(PURPLE "path_dump:\n" DELETE_COLOR); )
        ON_DEBUG( PathDump( *answer_path ); )
    enum Answer tmp_answer = EMPTY_ANSWER;

    if( (node->left != nullptr ) || (node->right != nullptr ) )
    {
        printf(GREEN "%s\n" DELETE_COLOR, node->data ); //QUESTION

        tmp_answer = GetAnswer();
        printf("tmp_answer: %d\n", tmp_answer); 

        switch( (int)tmp_answer )
        {
            case YES:
            {
                (*answer_path)[path_depth_count++] = (int)YES;
                Guess( tree, node->left, answer_path );
                break;
            }
            case NO:
            {
                (*answer_path)[path_depth_count++] = (int)NO;
                Guess( tree, node->right, answer_path );
                break;
            }
            default:
            {
                printf(RED "Something went wrong with the answer :(\n" DELETE_COLOR);
                (*answer_path)[path_depth_count] = (int)EMPTY_ANSWER;
                return BAD;
                break;  
            }
        }
    }
    else 
    {
        printf("\n    your character is " SINIY "%s" DELETE_COLOR "\n" , node->data);
        tmp_answer = GetAnswer();

        switch( (int)tmp_answer )
        {
            case YES:
            {
                printf(GREEN "=== Great ===\n" DELETE_COLOR);
                break;
            }
            case NO:
            {
                printf(SINIY "=== I don't know who was your character ===\n"
                         " Do you want to add him to my data base?\n" DELETE_COLOR);

                tmp_answer = EMPTY_ANSWER;
                tmp_answer = GetAnswer();
                switch( (int)tmp_answer )
                    {   
                        case YES:
                        {   
                            printf(GREEN "=== Great! Type the name of your character ===\n" DELETE_COLOR);

                            //----DBEUG---
                            printf(PURPLE "before Adding character:\n"
                                   "answer[path_depth_count - 1]: %d\n" DELETE_COLOR, (*answer_path)[path_depth_count - 1] );
                            //------------
                            AddCharacter( tree, node, (*answer_path)[path_depth_count - 1] );
                            break;
                        }
                        case NO:
                        {
                            printf(SINIY"                           \n"
                                        "      -----    -----      \n"
                                        "        ***    ***        \n"
                                        "       *(O)*  *(O)*       \n"
                                        "                          \n"
                                        "        **********        \n"
                                        "      *            *      \n"
                                        "        Why so ? ...      \n"
                                        "                          \n" DELETE_COLOR);

                            break;
                        }
                        default:
                        {
                            printf(RED "Something went wrong with the answer :(\n" DELETE_COLOR);
                            return BAD;
                            break;
                        }
                    }

                break;
            }
            default:
            {
                printf(RED "Something wrong with the last answer\n" DELETE_COLOR);
                return BAD;
                break;
            }
        }
    }

    return GOOD;
}


enum AkrErrors AddCharacter( struct Tree* tree, struct Node_t* node, int last_answer )
{
    assert(node);
    assert(tree);

    struct Node_t* tmp_node_1 = nullptr; //узел с новым обьектом 
    struct Node_t* tmp_node_2 = nullptr; //узел с вопросом 

    //-------Connecting node with new question--------
    printf(YELLOW "Type the name of your character.\n" DELETE_COLOR);
    char* character = nullptr;
    character = readline(">>> ");
    printf("Echo: %s\n", character);
    CreateNode( tree, character, &tmp_node_1);
    free(character);
    //-------------------------------

    //-----Changing connection with parent node-------
    printf(YELLOW "OK. Now type a specifying question.\n" DELETE_COLOR);
    char* question = nullptr;
    question = readline(">>> ");
    CreateNode( tree, question, &tmp_node_2);
    free( question );
    //--------------------------------------

    if( last_answer == YES )
    {
        InsertNode( nullptr, node, tmp_node_2 );
        InsertLeave( tree, tmp_node_2, LEFT, tmp_node_1 );
    }
    else if( last_answer == NO )
    {
        InsertNode( nullptr, node, tmp_node_2 );
        InsertLeave( tree, tmp_node_2, LEFT, tmp_node_1 );

    } 
    else
    {
        printf(RED "Something wrong in adding character\n" DELETE_COLOR);
        return BAD;
    }
    //------------------------------------------------

    return GOOD;
}

//----------------------------ANSWER PARSER------------------------------------
enum Answer GetAnswer( void ) 
{
    char* input = readline(">>> ");

    for(int i = 0; i < (int)strlen(input); i++)
    {
        *(input + i) = toupper( *(input + i) );
    }

    if( input == nullptr )
    {   
        free(input);
        return EMPTY_ANSWER;
    }   
    else if( strcmp( input, "YES" ) == 0 )
    {
        free(input);
        return YES;
    }
    else if( strcmp( input, "NO" ) == 0 )
    {
        free(input);
        return NO;
    }
    else 
    {
        free(input);
        return EMPTY_ANSWER;
    }

    return EMPTY_ANSWER;
}
//-----------------------------------------------------------------------------


//---------------------------------DEBUG---------------------------------------

void PathDump( int* path )
{
    printf(PURPLE "=== Dump Begin ===");
    for(int i = 0; i < 10; i++)
    {
        printf("[%i]: %d\n", i, *(path + i) );
    }   
    printf(PURPLE "=== Dump End ===\n" DELETE_COLOR);
}
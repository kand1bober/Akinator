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
    //--------MUSIC--------------
    SDL_Init(SDL_INIT_AUDIO); //запускает аудиоподсистему

    SDL_AudioSpec wav_spec;
    Uint32 wav_length = 0;
    Uint8 *wav_buffer = nullptr;
    SDL_AudioDeviceID device = 0;

    StartMusic( wav_spec, wav_length, &wav_buffer, &device );
    //---------------------------

    while(1)
    {   
        free( *answer_path );
        *answer_path = (int*)calloc( MAX_DEPTH, sizeof( int ) );

        printf("==================================\n"
               "Choose option for the programm:    \n"
               "'q' -- quit                       \n"
               "'s' -- save data base             \n"
               "'p' -- play the game              \n"
               "'d' -- dump the game tree         \n"
               "'t' -- make description of object \n"
               "'c' -- compare objects            \n"
               "==================================\n\n");

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

                //--------------MUSIC------------------------------
                StopMusic( &device, &wav_buffer );
                //---------------------------------------------------

                return GOOD;
                break;
            }
            case 's':
            {
                printf(YELLOW "You chose to " SINIY "save data" YELLOW "\n" DELETE_COLOR);  
                TreeData( tree, file_output );
                free( option );   
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
            case 't':
            {
                DescribeCharacter( tree );
                free( option );
                break;
            }
            case 'c':
            {
                CompareCharacters( tree );
                free( option );
                break;
            }
            default: 
            {
                printf(RED "\nbad inputed symbol: '%c'\n" DELETE_COLOR, *option);
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

    printf(YELLOW "====== End of the game ======\n" DELETE_COLOR);

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
        printf(GREEN "\n========  %s ? ========\n\n" DELETE_COLOR, node->data ); //QUESTION

        tmp_answer = GetAnswer();

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
        printf("\n    your character is " SINIY "%s" DELETE_COLOR "\n\n" , node->data);
        tmp_answer = GetAnswer();

        switch( (int)tmp_answer )
        {
            case YES:
            {
                printf(GREEN "======== Great ! ========\n" DELETE_COLOR);
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

                            AddCharacter( tree, node, (*answer_path)[path_depth_count - 1] );
                            break;
                        }
                        case NO:
                        {
                            printf(SINIY"                          \n"
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
    CreateNode( tree, character, &tmp_node_1);
    //-------------------------------

    if( last_answer == YES )
    {
        //-----Changing connection with parent node-------
        printf(YELLOW "OK. Whats the difference between " RED "%s " YELLOW "and " RED "%s.\n" DELETE_COLOR, tmp_node_1->data, node->data );
        char* question = nullptr;
        question = readline(">>> ");
        CreateNode( tree, question, &tmp_node_2);
        free( question );
        //--------------------------------------

        InsertNode( nullptr, node, tmp_node_2 );
        InsertLeave( tree, tmp_node_2, LEFT, tmp_node_1 );
    }
    else if( last_answer == NO )
    {
        //-----Changing connection with parent node-------
        printf(YELLOW "OK. Whats the new characteristic of " RED "%s " YELLOW "that " RED "%s " YELLOW "doesn't have.\n" DELETE_COLOR, tmp_node_1->data, node->data );
        char* question = nullptr;
        question = readline(">>> ");
        CreateNode( tree, question, &tmp_node_2);
        free( question );
        //--------------------------------------

        InsertNode( nullptr, node, tmp_node_2 );
        InsertLeave( tree, tmp_node_2, LEFT, tmp_node_1 );
    } 
    else
    {
        printf(RED "The tree of characters is empty\n" DELETE_COLOR);
        free(character);
        return BAD;
    }
    //------------------------------------------------

    free(character);           
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

//======================= FINDING AND COMPARING ===============================
enum AkrErrors DescribeCharacter( struct Tree* tree)
{
    struct ToSearch object = {};
    CharacterCtor( &object );

    Find( tree, object.to_search, &object.curr_node );

    MakePath( &object );

    WriteDescription( tree, &object );

    PathDump( object.path );
    
    CharacterDtor( &object );

    return GOOD;
}


enum AkrErrors CharacterCtor( struct ToSearch* object )
{
    object->to_search = nullptr;
    object->to_search = readline(">>> ");  
    object->curr_node = nullptr;
    object->path = (int*)calloc( MAX_DEPTH, sizeof( int ) );
    object->path_size = 0, object->path_capacity = MAX_DEPTH;

    return GOOD;
}


enum AkrErrors CharacterDtor( struct ToSearch* object )
{
    free( object->to_search );
    object->to_search = nullptr;
    free( object->path );
    object->path = nullptr;
    object->path_size = 0;
    object->path_capacity = MAX_DEPTH;

    return GOOD;
}


enum AkrErrors MakePath( struct ToSearch* object )
{
    while( object->curr_node->parent != nullptr )
    {
        if( object->curr_node->parent->left == object->curr_node )
        {
            object->path[object->path_size] = LEFT;
            object->path_size++;
        }
        else 
        {
            object->path[object->path_size] = RIGHT;
            object->path_size++;
        }
        object->curr_node = object->curr_node->parent;
    }
    return GOOD;
}


enum AkrErrors WriteDescription( struct Tree* tree, struct ToSearch* object )
{
    object->curr_node = tree->root;

    printf("**********************************\n");
    for(int i = object->path_size - 1; i >=0; i-- )
    {
        if( object->path[i] == LEFT  )
        { 
            printf("%s " YELLOW "IS" DELETE_COLOR " %s\n", object->to_search, object->curr_node->data );
            object->curr_node = object->curr_node->left;
        }
        else if( object->path[i] == RIGHT )
        {
            printf("%s " YELLOW "IS NOT" DELETE_COLOR " %s\n", object->to_search, object->curr_node->data );
            object->curr_node = object->curr_node->right;
        }
        else 
        {
            ;
        }
    }
    printf("**********************************\n\n");

    return GOOD;
}


enum AkrErrors ResizeToSearch( struct ToSearch* object )
{
    if( (object->to_search != nullptr) && (object->path != nullptr) )
    {
        if( object->path_size >= object->path_capacity )
        {   
            object->path = (int*)realloc( object->path, object->path_capacity * 2 );
            object->path_capacity = object->path_capacity * 2;
            return GOOD;
        }
        else 
        {
            return GOOD;
        }
    }
    else 
    {
        return BAD;
    }
}


enum AkrErrors CompareCharacters( struct Tree* tree )
{
    printf(SINIY "    Type first character to compare\n" DELETE_COLOR );
    struct ToSearch object_1 = {};
    CharacterCtor( &object_1 );
    Find( tree, object_1.to_search, &object_1.curr_node);
    MakePath( &object_1 );

    printf(SINIY "    Type second character to compare\n" DELETE_COLOR );
    struct ToSearch object_2 = {};
    CharacterCtor( &object_2 );
    Find( tree, object_2.to_search, &object_2.curr_node);
    MakePath( &object_2 );
    

    struct Node_t* node_1 = nullptr;
    struct Node_t* node_2 = nullptr;

    //---------EXCHANGE----------
    if(object_1.path_size < object_2.path_size)
    {
        struct ToSearch object_tmp = {};
        object_tmp = object_2;
        object_2 = object_1;
        object_1 = object_tmp;
    }
    //---------------------------

    //---------COMPARE(first is longer)---------
    for( int i = 0; i < object_2.path_size; i++ )
    {
        node_1 = RecursiveTake( tree, &object_1, i );
        node_2 = RecursiveTake( tree, &object_2, i );

        if( object_1.path[ object_1.path_size - i] == object_2.path[object_2.path_size - i] )
        {
            // if( )
            // {
                printf("Both \n");
                printf("%s  %s  %d  %d\n", node_1->data, node_2->data, object_1.path[ object_1.path_size - i], object_2.path[object_2.path_size - i] );
            // }
            // else 
            // {
                // printf("Both are not ");
            // }
        }
    }
    //--------------------------------------

    CharacterDtor( &object_1 );
    CharacterDtor( &object_2 );
    
    return GOOD;
}
//=============================================================================

struct Node_t* RecursiveTake( struct Tree* tree, struct ToSearch* object, int dest )
{   
    struct Node_t* node = tree->root;

    for( int i = object->path_size - 1; i >= object->path_size - dest; i-- )
    {   
        if( object->path[i] == LEFT )
        {
            node = node->left;
        }
        else if( object->path[i] == RIGHT )
        {
            node = node->right;
        }
        else 
        {
            printf(RED "strange problem in recursive take\n" DELETE_COLOR);
        }
    }

    return node;
}

//---------------------------------DEBUG---------------------------------------
void PathDump( int* path )
{
    printf(PURPLE "=== Dump Begin ===\n");
    for(int i = 0; i < 10; i++)
    {
        printf("[%i]: %d\n", i, *(path + i) );
    }   
    printf(PURPLE "=== Dump End ===\n" DELETE_COLOR);
}
//-----------------------------------------------------------------------------

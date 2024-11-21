#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "../../Tree/MyTreeLib.h"
#include "akr_utilities.h"


#ifndef AKINATOR_FUNCTIONS_HEADER
#define AKINATOR_FUNCTIONS_HEADER

const size_t MAX_DEPTH = 100;

enum AkrErrors
{
    GOOD,
    BAD,
};

enum Answer
{
    YES = 1,
    NO = 2,
    EMPTY_ANSWER = 3,
};

//-------------------------------AKINATOR--------------------------------------
enum AkrErrors Game();
enum AkrErrors Run( struct File_text* file_graph, struct File_text* file_output, struct Tree* tree, int** answer_path );
enum AkrErrors Play( struct Tree* tree, int** answer_path );
enum AkrErrors Guess( struct Tree* tree, struct Node_t* node, int** answer_path );
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
enum AkrErrors AddCharacter( struct Tree* tree, struct Node_t* node, int last_answer );
//-----------------------------------------------------------------------------

//---------------HELPING FUNCTIONS------------------
void PathDump( int* path );
//--------------------------------------------------

//----------- PARSER ------------
enum Answer GetAnswer( void );
enum Direction GetBranch( void );
//-------------------------------
#endif

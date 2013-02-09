#include <fstream>
#include <iostream>

// the quex-produced lexical analyzer
#include "tiny_lexer"

// the LEMON_ token ids
#include "pascal.h"

// the classes that make up the AST
#include "astnode.hpp"
#include "nodes/typenode.h"
#include "nodes/ast.h"

// the single instantiation of the base-type nodes
TypeNode IntegerType( "INTEGER", NULL );
TypeNode StringType ( "STRING",  NULL );
TypeNode BooleanType( "BOOLEAN", NULL );
TypeNode CharType   ( "CHAR",    NULL );


// defined in auto-generated pascal.c
extern void *ParseAlloc( void *(*mallocProc)(size_t) );
extern void ParseFree( void *p, void (*freeProc)(void*) );
extern void Parse( void *yyp, int yymajor, quex::Token* yyminor, AST *ast );

static int map_id( int quex_id );
static void display_syntax( void );

int main(int argc, char** argv)
    {
    quex::Token*       token_p = 0x0;
    std::string source_filename;

    switch( argc )
        {
        case 1:
            source_filename = "example.txt";
            break;

        case 2:
            source_filename = argv[1];
            break;

        case 3:
            source_filename = argv[2];
            break;

        default:
            display_syntax();
            return( -1 );
        };

    quex::tiny_lexer   qlex( source_filename );
    void *pParser;
    int hTokenId;

    pParser = ParseAlloc( malloc );
    if( pParser == NULL )
        {
        printf( "\nERROR: Unable to create parser\n" );
        return( -1 );
        }

    AST ast;

    do
        {
        qlex.receive(&token_p);

        if( token_p->type_id() != QUEX_TKN_TERMINATION )
            {
            hTokenId = map_id( token_p->type_id() );
            Parse( pParser, hTokenId, token_p, &ast );
            }
        else // parser must be given special "0" token id to indicate termination
            Parse( pParser, 0, token_p, &ast );
        } while( token_p->type_id() != QUEX_TKN_TERMINATION );

    ParseFree( pParser, free );

    if( argc <= 2 )
        {
        ast.pretty_print();
        return( 0 );
        }
    else if( argc == 3 )
        {
        if( std::string(argv[1]) == std::string("-eval") )
            {
            printf( "\n" );
            ast.evaluate();
            printf( "\n\n" );
            return( 0 );
            }
        if( std::string(argv[1]) == std::string("-code") )
            {
            printf( "\nNOT YET IMPLEMENTED" );
            return( -1 );
            }
        else
            {
            printf( "\nUnknown argument '%s'", argv[1] );
            display_syntax();
            return( -1 );
            }
        }
    else
        {
        printf( "\nUnexpected number of arguments." );
        display_syntax();
        return( -1 );
        }
    }


/* convert from QUEX_TKN_xxx's to the equivalent LEMON_xxx's */
int map_id( int quex_id )
    {
    int lemon_id = 0;

    switch( quex_id )
        {
        case QUEX_TKN_SEMICOLON:
            lemon_id = LEMON_SEMICOLON; break;
    
        case QUEX_TKN_PAREN_OPEN:
            lemon_id = LEMON_LPAREN; break;

        case QUEX_TKN_PAREN_CLOSE:
            lemon_id = LEMON_RPAREN; break;

        case QUEX_TKN_BRACKET_OPEN:
            lemon_id = LEMON_LBRACKET; break;

        case QUEX_TKN_BRACKET_CLOSE:
            lemon_id = LEMON_RBRACKET; break;

        case QUEX_TKN_PLUS:
            lemon_id = LEMON_PLUS; break;

        case QUEX_TKN_MINUS:
            lemon_id = LEMON_MINUS; break;

        case QUEX_TKN_STAR:
            lemon_id = LEMON_STAR; break;

        case QUEX_TKN_SLASH:
            lemon_id = LEMON_SLASH; break;

        case QUEX_TKN_CAROT:
            lemon_id = LEMON_POINTS_TO; break;

        case QUEX_TKN_AT:
            lemon_id = LEMON_ADDRESS_OF; break;

        case QUEX_TKN_DOTDOT:
            lemon_id = LEMON_DOTDOT; break;

        case QUEX_TKN_PERIOD:
            lemon_id = LEMON_PERIOD; break;

        case QUEX_TKN_COMMA:
            lemon_id = LEMON_COMMA; break;

        case QUEX_TKN_LESS_EQUAL:
            lemon_id = LEMON_LESS_EQUAL; break;

        case QUEX_TKN_GREATER_EQUAL:
            lemon_id = LEMON_GREATER_EQUAL; break;

        case QUEX_TKN_EQUALS:
            lemon_id = LEMON_EQUALS; break;

        case QUEX_TKN_NOT_EQUAL:
            lemon_id = LEMON_NOTEQUAL; break;

        case QUEX_TKN_LESS_THAN:
            lemon_id = LEMON_LESS_THAN; break;

        case QUEX_TKN_GREATER_THAN:
            lemon_id = LEMON_GREATER_THAN; break;

        case QUEX_TKN_OR:
            lemon_id = LEMON_OR; break;

        case QUEX_TKN_AND:
            lemon_id = LEMON_AND; break;

        case QUEX_TKN_DIV:
            lemon_id = LEMON_DIV; break;

        case QUEX_TKN_MOD:
            lemon_id = LEMON_MOD; break;

        case QUEX_TKN_NIL:
            lemon_id = LEMON_NIL; break;

        case QUEX_TKN_NOT:
            lemon_id = LEMON_NOT; break;

        case QUEX_TKN_ASSIGNMENT:
            lemon_id = LEMON_ASSIGNMENT; break;

        case QUEX_TKN_COLON:
            lemon_id = LEMON_COLON; break;

        case QUEX_TKN_PROGRAM:
            lemon_id = LEMON_PROGRAM; break;

        case QUEX_TKN_BEGIN:
            lemon_id = LEMON_BEGIN; break;

        case QUEX_TKN_END:
            lemon_id = LEMON_END; break;

        case QUEX_TKN_VAR:
            lemon_id = LEMON_VAR; break;

        case QUEX_TKN_ARRAY:
            lemon_id = LEMON_ARRAY; break;

        case QUEX_TKN_OF:
            lemon_id = LEMON_OF; break;

        case QUEX_TKN_RECORD:
            lemon_id = LEMON_RECORD; break;

        case QUEX_TKN_CASE:
            lemon_id = LEMON_CASE; break;

        case QUEX_TKN_SET:
            lemon_id = LEMON_SET; break;

        case QUEX_TKN_FILE:
            lemon_id = LEMON_FILE; break;

        case QUEX_TKN_PROCEDURE:
            lemon_id = LEMON_PROCEDURE; break;

        case QUEX_TKN_FUNCTION:
            lemon_id = LEMON_FUNCTION; break;

        case QUEX_TKN_LABEL:
            lemon_id = LEMON_LABEL; break;

        case QUEX_TKN_CONST:
            lemon_id = LEMON_CONST; break;

        case QUEX_TKN_FORWARD:
            lemon_id = LEMON_FORWARD; break;

        case QUEX_TKN_GOTO:
            lemon_id = LEMON_GOTO; break;

        case QUEX_TKN_WHILE:
            lemon_id = LEMON_WHILE; break;

        case QUEX_TKN_DO:
            lemon_id = LEMON_DO; break;

        case QUEX_TKN_REPEAT:
            lemon_id = LEMON_REPEAT; break;

        case QUEX_TKN_UNTIL:
            lemon_id = LEMON_UNTIL; break;

        case QUEX_TKN_FOR:
            lemon_id = LEMON_FOR; break;

        case QUEX_TKN_DOWNTO:
            lemon_id = LEMON_DOWNTO; break;

        case QUEX_TKN_TO:
            lemon_id = LEMON_TO; break;

        case QUEX_TKN_IF:
            lemon_id = LEMON_IF; break;

        case QUEX_TKN_THEN:
            lemon_id = LEMON_THEN; break;

        // NOT YET IMPLEMENTED IN GRAMMAR (causes parsing conflict with IF-THEN)
        //case QUEX_TKN_ELSE:
        //    lemon_id = LEMON_ELSE; break;

        case QUEX_TKN_WITH:
            lemon_id = LEMON_WITH; break;

        // NOT YET IMPLEMENTED IN GRAMMAR
        //case QUEX_TKN_BREAK:
        //    lemon_id = LEMON_BREAK; break;

        // NOT YET IMPLEMENTED IN GRAMMAR
        //case QUEX_TKN_CONTINUE:
        //    lemon_id = LEMON_CONTINUE; break;

        case QUEX_TKN_TYPE:
            lemon_id = LEMON_TYPE; break;

        case QUEX_TKN_UNIT:
            lemon_id = LEMON_UNIT; break;

        case QUEX_TKN_INTERFACE:
            lemon_id = LEMON_INTERFACE; break;

        case QUEX_TKN_IMPLEMENTATION:
            lemon_id = LEMON_IMPLEMENTATION; break;

        case QUEX_TKN_USES:
            lemon_id = LEMON_USES; break;

        case QUEX_TKN_TYPE_INTEGER:
            lemon_id = LEMON_TYPE_INTEGER; break;

        case QUEX_TKN_TYPE_STRING:
            lemon_id = LEMON_TYPE_STRING; break;

        case QUEX_TKN_TYPE_BOOLEAN:
            lemon_id = LEMON_TYPE_BOOLEAN; break;

        case QUEX_TKN_TYPE_CHAR:
            lemon_id = LEMON_TYPE_CHAR; break;

        case QUEX_TKN_STRING:
            lemon_id = LEMON_STRING; break;

        case QUEX_TKN_NUMBER:
            lemon_id = LEMON_NUMBER; break;
            
        case QUEX_TKN_BOOLEAN:
            lemon_id = LEMON_BOOLEAN; break;

        case QUEX_TKN_IDENTIFIER:
            lemon_id = LEMON_IDENTIFIER; break;

        default:
            lemon_id = 0;
        }

    return( lemon_id );
    }


void display_syntax( void )
    {
    printf( "\nparser.exe [-eval | -code] [source file]" );
    printf( "\n\n\tIf neither -eval nor -code are specified," );
    printf( "\n\tbehavior is to pretty-print the source file." );
    printf( "\n\n\tIf no source file name is specified, data is read from example.txt\n" );
    }

#include <cstdio>

#include "ast.h"
#include "../astnode.hpp"
#include "programnode.h"
#include "unitnode.h"
#include "variablenode.h"
#include "expressionnode.h"

AST::AST()
    {
    program = NULL;
    }

AST::~AST()
    {
    if( program )
        delete program;
    }

void AST::set_program( ProgramNode *p )
    {
    if( program )
        delete program;
    program = p;
    }

void AST::set_program( UnitNode *p )
    {
    if( program )
        delete program;
    program = p;
    }

void AST::pretty_print() const
    {
    if( program )
        printf( "\n%s\n", program->pretty_print(0).c_str() );
    }


void AST::evaluate()
    {
    if( program )
        program->evaluate(NULL, NULL);
    else
        {
        printf( "\nERROR: AST does not contain a ProgramNode to evaluate." );
        fflush( stdout );
        }
    }

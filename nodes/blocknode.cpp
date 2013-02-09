#include <cassert>

#include "blocknode.h"
#include "typenode.h"
#include "statementnode.h"
#include "subroutinenode.h"
#include "expressionnode.h"
#include "numberexpressionnode.h"
#include "variablenode.h"

BlockNode::BlockNode( std::list<StatementNode *> *_body )
    {
    assert( _body );
    body = *_body;
    types = NULL;
    variables = NULL;
    subroutines = NULL;
    constants = NULL;
    }


bool BlockNode::add_types( std::map<std::string, TypeNode *> *_t )
    {
    assert( _t != NULL );
    types = _t;

    return( false ); // no unresolvable types
    }


bool BlockNode::add_variables( std::map<std::string, TypeNode *> *_v )
    {
    assert( _v != NULL );
    variables = _v;

    return( false ); // no variables had unresolvable types
    }


bool BlockNode::add_labels( std::list<int> *_l )
    {
    assert( _l != NULL );
    labels = _l;

    return( false ); // no labels had issues
    }


bool BlockNode::add_subroutines( std::list<SubroutineNode *> *_r )
    {
    assert( _r != NULL );
    subroutines = _r;

    return( false ); // no subroutines had issues
    }


bool BlockNode::add_constants( std::map<std::string, ExpressionNode *> *_c )
    {
    assert( _c != NULL );
    constants = _c;
    
    return( false ); // no constants had issues
    }
    

BlockNode::~BlockNode()
    {
    while( body.empty() == false )
        body.pop_back(); // reminder: This calls the removed element's destructor.

    if( types )
        {
        types->clear(); // reminder: this calls the removed elements' destructors.
        delete types;
        }

    if( variables )
        {
        variables->clear(); // reminder: this calls the removed elements' destructors.
        delete variables;
        }
        
    if( constants )
        {
        constants->clear();
        delete constants;
        }
    }


std::string BlockNode::pretty_print( int indent ) const
    {
    std::string tabs;
    for( int i = 0; i < indent; ++i )
        tabs += "\t";

    std::string result;
    
    if( constants )
        {
        result += "\n\n" + tabs + "CONSTANTS:";
        for( std::map<std::string, ExpressionNode *>::const_iterator it = constants->begin();
            it != constants->end();
            ++it )
            {
            result += "\n\t" + tabs + it->first + " = " + it->second->pretty_print(0);
            }
        }

    if( types )
        {
        result += std::string( "\n\n" + tabs + "TYPES:" );
        for( std::map<std::string, TypeNode *>::const_iterator it = types->begin();
            it != types->end();
            ++it )
            {
            result += "\n\t" + tabs + it->first + " = " + it->second->pretty_print(indent + 2);
            }
        }

    if( variables )
        {
        result += std::string( "\n\n" + tabs +"VARIABLES:" );
        for( std::map<std::string, TypeNode *>::const_iterator it = variables->begin();
            it != variables->end();
            ++it )
            {
            result += "\n\t" + tabs + it->first + " : " + it->second->pretty_print(0);
            }
        }

    if( subroutines )
        {
        result += std::string( "\n\n" + tabs + "SUBROUTINES:" );
        for( std::list<SubroutineNode *>::const_iterator it = subroutines->begin();
            it != subroutines->end();
            ++it )
            {
            result += "\n" + (*it)->pretty_print(indent + 1);
            }
        }

    result += std::string( "\n\n" + tabs + "BODY:" );
    if( body.empty() == false )
        {
        for( std::list<StatementNode *>::const_iterator it = body.begin();
            it != body.end();
            ++it )
            {
            assert( *it != NULL );
            result = result + std::string("\n") + (*it)->pretty_print(indent + 1);
            }
        }
    else
        result += std::string("\n\t" + tabs + "empty" );

    return( result );
    }


ASTNode *BlockNode::evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env )
    {
    assert( types_env != NULL );
    assert( vars_env != NULL );

    TypeEnvironment body_types( *types_env );
    VariableEnvironment body_variables( *vars_env );

    if( types )
        {
        // first, expand the environments of the body by adding in the types and variables
        // declared globally within this block
        //for( t in types )
        //    body_types->push_front( t );
        }

    if( variables )
        {
        for( std::map<std::string, TypeNode *>::const_iterator it = variables->begin();
            it != variables->end();
            ++it )
            {
            VariableNode *v = new VariableNode( it->first.c_str() );
            v->set_type( it->second );
            body_variables.push_front( std::pair<VariableNode*, ExpressionNode*>(v, NULL) );
            }
        }

    // secondly, evaluate the body in this larger environment
    for( std::list<StatementNode *>::iterator it = body.begin();
        it != body.end();
        ++it )
        {
        assert( (*it) != NULL ); // bodies aren't supposed to end up empty
        (*it)->evaluate( &body_types, &body_variables );
        }
        

    printf( "\nFinal variable environment is: " );
    fflush( stdout );
    for( VariableEnvironment::const_iterator it = body_variables.begin();
        it != body_variables.end();
        ++it )
        {
        assert( it->first != NULL );

        const char *var_name = it->first->pretty_print(0).c_str();
        const char *var_type = NULL;
        const char *var_value = NULL;

        if( it->first->result_type() == NULL )
            var_type = "UNKNOWN";
        else
            var_type = it->first->result_type()->pretty_print(0).c_str();

        if( it->second == NULL )
            var_value = "uninitialized";
        else
            var_value = it->second->pretty_print(0).c_str();

        assert( var_name != NULL );
        assert( var_type != NULL );
        assert( var_value != NULL );

        printf( "\n\t%s:%s = %s", var_name, var_type, var_value );
        }

    // but a block is a list of statements, and statements have side-effects, not values.
    // so what is the resulting value of a block?
    return( new NumberExpressionNode(0) );
    }

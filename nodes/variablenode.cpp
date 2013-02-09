#include "variablenode.h"
#include "environment.h"


VariableNode::~VariableNode()
    {
    if( root )
        delete root;
        
    if( dimensions )
        {
        dimensions->clear();
        delete dimensions;
        }
    }


std::string VariableNode::pretty_print( int indent ) const
    {
    std::string result;
    if( root )
        result = root->pretty_print(indent);
    else
        result = identifier_name;

    if( dimensions )
        {
        result += "[";
        for( std::list<ExpressionNode *>::const_iterator it = dimensions->begin();
            it != dimensions->end();
            ++it )
            {
            result += (*it)->pretty_print( 0 );
            result += ", ";
            }

        result += "]";
        }

    if( field_name.length() > 0 )
        result += "." + field_name;


    if( is_dereference )
        result += "(points_to)";

    return( result );
    }


bool VariableNode::operator==(const VariableNode &rhs) const
    {
    if( (identifier_name == rhs.identifier_name) &&
        (field_name == rhs.field_name) &&
        (is_dereference == rhs.is_dereference) )
        {
        if( root == rhs.root ) // if both roots are the same physical object
            return( true );
        else // they might point to equivalent objects
            {
            if( root && rhs.root ) // only compare root objects, if both are non-NULL
                return( (*root) == (*(rhs.root)) );
            else
                return( false );
            }
        }
    else
        {
        return( false );
        }
    }


ASTNode *VariableNode::evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env )
    {
    return( get_value(this, vars_env) );
    }

#include <cstdio>

#include "typenode.h"
#include "binaryexpressionnode.h"
#include "booleanexpressionnode.h"
#include "numberexpressionnode.h"

static ExpressionNode *eval_binop_lt  (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_le  (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_eq  (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_ne  (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_ge  (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_gt  (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_add (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_sub (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_or  (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_mult(ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_div (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_mod (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_and (ExpressionNode *lhs, ExpressionNode *rhs);
static ExpressionNode *eval_binop_in  (ExpressionNode *lhs, ExpressionNode *rhs);

std::string binop2string( BinaryOperator op )
    {
    switch( op )
        {
        case BINOP_LESS_THAN:
            return( std::string("<") );

        case BINOP_LESS_EQUAL:
            return( std::string("<=") );

        case BINOP_EQUAL:
            return( std::string("=") );

        case BINOP_NOTEQUAL:
            return( std::string("<>") );

        case BINOP_GREATER_EQUAL:
            return( std::string(">=") );

        case BINOP_GREATER_THAN:
            return( std::string(">") );

        case BINOP_PLUS:
            return( std::string("+") );

        case BINOP_MINUS:
            return( std::string("-") );

        case BINOP_OR:
            return( std::string("OR") );

        case BINOP_MULTIPLY:
            return( std::string("*") );

        case BINOP_REAL_DIVIDE:
            return( std::string("/") );

        case BINOP_INTEGER_DIVIDE:
            return( std::string("DIV") );

        case BINOP_MOD:
            return( std::string("MOD") );

        case BINOP_AND:
            return( std::string("AND") );

        case BINOP_IN:
            return( std::string("IN") );

        default:
            return( std::string("UNKNOWN BINOP") );
        }
    }


BinaryExpressionNode::~BinaryExpressionNode()
    {
    if( lhs )
        delete lhs;

    if( rhs )
        delete rhs;
    }

std::string BinaryExpressionNode::pretty_print( int indent ) const
    {
    assert( lhs );
    assert( rhs );

    return( std::string("LHS(") +
            lhs->pretty_print(0) +
            std::string(") ") +
            binop2string(op) +
            std::string(" RHS(") +
            rhs->pretty_print(0) +
            std::string(")") );
    }


ASTNode *BinaryExpressionNode::evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env )
    {
    ExpressionNode *lhs_value = dynamic_cast<ExpressionNode *>( lhs->evaluate(types_env, vars_env) );
    ExpressionNode *rhs_value = dynamic_cast<ExpressionNode *>( rhs->evaluate(types_env, vars_env) );
    
    if( lhs_value == NULL )
        {
        printf( "\n'%s' is not a valid value in the expression:\n%s\n", lhs->pretty_print(0).c_str(),
                this->pretty_print(2).c_str() );
        return( NULL );
        }

    else if( rhs_value == NULL )
        {
        printf( "\n'%s' is not a valid value in the expression:\n%s\n", rhs->pretty_print(0).c_str(),
                this->pretty_print(2).c_str() );
        return( NULL );
        }

    else
        {
        if( rhs_value->result_type() == NULL )
            {
            printf( "\nExpression on right-hand side of expression seems to be missing a result type." );
            printf( "\n%s\n", this->pretty_print(2).c_str() );
            return( NULL );
            }
        else if( lhs_value->result_type() == NULL )
            {
            printf( "\nExpression on left-hand side of expression seems to be missing a result type." );
            printf( "\n%s\n", this->pretty_print(2).c_str() );
            return( NULL );
            }
        else if( rhs_value->result_type() == lhs_value->result_type() )
            {
            // evaluate the operator with rhs_value and rhs_value
            switch( op )
                {
                case BINOP_LESS_THAN:      return( eval_binop_lt(lhs_value,rhs_value) );
                case BINOP_LESS_EQUAL:     return( eval_binop_le(lhs_value,rhs_value) );
                case BINOP_EQUAL:          return( eval_binop_eq(lhs_value,rhs_value) );
                case BINOP_NOTEQUAL:       return( eval_binop_ne(lhs_value,rhs_value) );
                case BINOP_GREATER_EQUAL:  return( eval_binop_ge(lhs_value,rhs_value) );
                case BINOP_GREATER_THAN:   return( eval_binop_gt(lhs_value,rhs_value) );
                case BINOP_PLUS:           return( eval_binop_add(lhs_value,rhs_value) );
                case BINOP_MINUS:          return( eval_binop_sub(lhs_value,rhs_value) );
                case BINOP_OR:             return( eval_binop_or(lhs_value,rhs_value) );
                case BINOP_MULTIPLY:       return( eval_binop_mult(lhs_value,rhs_value) );
                case BINOP_REAL_DIVIDE:    return( eval_binop_div(lhs_value,rhs_value) );
                case BINOP_INTEGER_DIVIDE: return( eval_binop_div(lhs_value,rhs_value) );
                case BINOP_MOD:            return( eval_binop_mod(lhs_value,rhs_value) );
                case BINOP_AND:            return( eval_binop_and(lhs_value,rhs_value) );
                case BINOP_IN:             return( eval_binop_in(lhs_value,rhs_value) );

                default: return( NULL );
                }
            }
        else
            {
            printf( "\nType '%s' of '%s' is not compatible with type '%s' of '%s' in:\n%s\n",
                    lhs_value->result_type()->pretty_print(0).c_str(),
                    lhs_value->pretty_print(0).c_str(),
                    rhs_value->result_type()->pretty_print(0).c_str(),
                    rhs_value->pretty_print(0).c_str(),
                    this->pretty_print(2).c_str() );
            return( NULL );
            }
        }
    }


/****
Assumptions coming into these eval_binop_*() routines:
    - both lhs and rhs pointers point to valid ExpressionNode objects
    - both lhs and rhs ExpressionNode objects report the same result_type()
****/


ExpressionNode *eval_binop_lt  (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new BooleanExpressionNode(lhs_int->get_value() < rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform < operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_le  (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new BooleanExpressionNode(lhs_int->get_value() <= rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform <= operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_eq  (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new BooleanExpressionNode(lhs_int->get_value() == rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform = operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_ne  (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new BooleanExpressionNode(lhs_int->get_value() != rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform <> operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_ge  (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new BooleanExpressionNode(lhs_int->get_value() >= rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform >= operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_gt  (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new BooleanExpressionNode(lhs_int->get_value() > rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform > operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_add (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new NumberExpressionNode(lhs_int->get_value() + rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform + operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_sub (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new NumberExpressionNode(lhs_int->get_value() - rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform - operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_or  (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new NumberExpressionNode(lhs_int->get_value() | rhs_int->get_value()) );
        }
    else if( lhs->result_type() == &BooleanType )
        {
        BooleanExpressionNode *lhs_bool = dynamic_cast<BooleanExpressionNode*>(lhs);
        BooleanExpressionNode *rhs_bool = dynamic_cast<BooleanExpressionNode*>(rhs);

        assert( lhs_bool != NULL );
        assert( rhs_bool != NULL );

        return( new BooleanExpressionNode(lhs_bool->get_value() || rhs_bool->get_value()) );
        }
    else
        {
        printf( "\nCannot perform * operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_mult(ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new NumberExpressionNode(lhs_int->get_value() * rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform * operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_div (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new BooleanExpressionNode(lhs_int->get_value() / rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform / operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_mod (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new BooleanExpressionNode(lhs_int->get_value() % rhs_int->get_value()) );
        }
    else
        {
        printf( "\nCannot perform MOD operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_and (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    if( lhs->result_type() == &IntegerType )
        {
        NumberExpressionNode *lhs_int = dynamic_cast<NumberExpressionNode*>(lhs);
        NumberExpressionNode *rhs_int = dynamic_cast<NumberExpressionNode*>(rhs);

        assert( lhs_int != NULL );
        assert( rhs_int != NULL );

        return( new NumberExpressionNode(lhs_int->get_value() & rhs_int->get_value()) );
        }
    else if( lhs->result_type() == &BooleanType )
        {
        BooleanExpressionNode *lhs_bool = dynamic_cast<BooleanExpressionNode*>(lhs);
        BooleanExpressionNode *rhs_bool = dynamic_cast<BooleanExpressionNode*>(rhs);

        assert( lhs_bool != NULL );
        assert( rhs_bool != NULL );

        return( new BooleanExpressionNode(lhs_bool->get_value() && rhs_bool->get_value()) );
        }
    else
        {
        printf( "\nCannot perform * operation on type '%s'",
            lhs->result_type()->pretty_print(0).c_str() );
        return( NULL );
        }
    }


ExpressionNode *eval_binop_in  (ExpressionNode *lhs, ExpressionNode *rhs)
    {
    printf( "\nTODO: Implement eval_binop_in()" );
    return( NULL );
    }

#ifndef _BINARYEXPRESSIONNODE_H_
#define _BINARYEXPRESSIONNODE_H_

#include <string>
#include <cassert>

#include "expressionnode.h"
#include "typenode.h"

typedef enum
    {
    BINOP_LESS_THAN,
    BINOP_LESS_EQUAL,
    BINOP_EQUAL,
    BINOP_NOTEQUAL,
    BINOP_GREATER_EQUAL,
    BINOP_GREATER_THAN,

    BINOP_PLUS,
    BINOP_MINUS,
    BINOP_OR,

    BINOP_MULTIPLY,
    BINOP_REAL_DIVIDE,
    BINOP_INTEGER_DIVIDE,
    BINOP_MOD,
    BINOP_AND,
    BINOP_IN
    } BinaryOperator;


class BinaryExpressionNode : public ExpressionNode
    {
    public:
        BinaryExpressionNode( ExpressionNode *_lhs, BinaryOperator _op, ExpressionNode *_rhs ) :
            op(_op), lhs(_lhs), rhs(_rhs)
            {
            assert( _lhs != NULL );
            assert( _rhs != NULL );
            }

        virtual ~BinaryExpressionNode();
        virtual std::string pretty_print( int indent ) const;
        virtual ASTNode *evaluate( TypeEnvironment *types_env, VariableEnvironment *vars_env );

    protected:
        BinaryOperator op;
        ExpressionNode *lhs, *rhs;
    };

#endif

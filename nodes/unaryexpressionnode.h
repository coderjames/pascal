#ifndef _UNARYEXPRESSIONNODE_H_
#define _UNARYEXPRESSIONNODE_H_

#include <string>

#include "expressionnode.h"

typedef enum
    {
    UNOP_PLUS,
    UNOP_MINUS,
    UNOP_NOT,
    UNOP_ADDRESS_OF
    } UnaryOperator;


class UnaryExpressionNode : public ExpressionNode
    {
    public:
        UnaryExpressionNode( UnaryOperator _op, ExpressionNode *_rhs ) :
            op(_op), rhs(_rhs)
            {
            assert( _rhs != NULL );
            }

        virtual ~UnaryExpressionNode();
        virtual std::string pretty_print( int indent ) const;

    protected:
        UnaryOperator op;
        ExpressionNode *rhs;
    };


#endif

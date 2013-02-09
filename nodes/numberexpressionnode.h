#ifndef _NUMBEREXPRESSIONNODE_H_
#define _NUMBEREXPRESSIONNODE_H_

#include <string>

#include "expressionnode.h"
#include "typenode.h"

class NumberExpressionNode : public ExpressionNode
    {
    public:
        NumberExpressionNode( const char *_val );
        NumberExpressionNode( int _val ) : value(_val) { result_type( &IntegerType ); };

        virtual std::string pretty_print( int indent ) const;

        int get_value() const;

    protected:
        int value;
    } ;

#endif

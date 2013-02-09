#ifndef _BOOLEANEXPRESSIONNODE_H_
#define _BOOLEANEXPRESSIONNODE_H_

#include <string>

#include "expressionnode.h"
#include "typenode.h"

class BooleanExpressionNode : public ExpressionNode
    {
    public:
        BooleanExpressionNode( const char *_val );
        BooleanExpressionNode( bool _val ) : value(_val) { result_type( &BooleanType ); };

        virtual std::string pretty_print( int indent ) const;

        bool get_value() const;

    protected:
        bool value;
    } ;

#endif

#ifndef _STRINGEXPRESSIONNODE_H_
#define _STRINGEXPRESSIONNODE_H_

#include <string>

#include "expressionnode.h"
#include "typenode.h"

class StringExpressionNode : public ExpressionNode
    {
    public:
        StringExpressionNode( std::string _str ) : value(_str)
            {
            result_type( &StringType );
            };

        virtual std::string pretty_print( int indent ) const;

        std::string get_value() const;

    protected:
        std::string value;
    } ;

#endif

#ifndef _FUNCTIONCALLNODE_H_
#define _FUNCTIONCALLNODE_H_

#include <string>
#include <list>

#include "expressionnode.h"

class FunctionCallNode : public ExpressionNode
    {
    public:
        FunctionCallNode( const char *_f, std::list<ExpressionNode *> *_a ) : function_name(_f),
            args(_a) { assert(_f != NULL); };

        virtual ~FunctionCallNode();

        virtual std::string pretty_print( int indent ) const;

    private:
        std::string function_name;
        std::list<ExpressionNode *> *args;
    } ;

#endif

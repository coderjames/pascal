#ifndef _ARRAYINDEXNODE_H_
#define _ARRAYINDEXNODE_H_

#include <string>
#include <list>

#include "expressionnode.h"

class ArrayIndexNode : public ExpressionNode
    {
    public:
        ArrayIndexNode( std::list<ExpressionNode *> *_e ) : elements(_e) { assert(_e != NULL); };
        virtual ~ArrayIndexNode();
        virtual std::string pretty_print( int indent ) const;

    private:
        std::list<ExpressionNode *> *elements;
    } ;

#endif

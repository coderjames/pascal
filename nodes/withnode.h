#ifndef _WITHNODE_H_
#define _WITHNODE_H_

#include <list>
#include <string>
#include <cassert>

#include "statementnode.h"

class VariableNode;

class WithNode : public StatementNode
    {
    public:
        WithNode( std::list<VariableNode *> *_r, StatementNode *_b ) : records(_r), body(_b)
            { assert( _r != NULL ); assert( _b != NULL ); };
        virtual ~WithNode();

        virtual std::string pretty_print( int indent ) const;

    private:
        std::list<VariableNode *> *records;
        StatementNode *body;
    } ;

#endif

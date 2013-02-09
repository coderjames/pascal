#ifndef _BLOCKSTATEMENTNODE_H_
#define _BLOCKSTATEMENTNODE_H_

#include <string>
#include <list>
#include <cassert>

#include "statementnode.h"

class BlockStatementNode : public StatementNode
    {
    public:
        BlockStatementNode( std::list< StatementNode *> *_stmts ) : statements(_stmts)
            { assert(_stmts != NULL); };
        virtual ~BlockStatementNode();
        virtual std::string pretty_print( int indent ) const;

    private:
        std::list<StatementNode *> *statements;
    } ;

#endif

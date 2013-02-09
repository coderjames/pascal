#ifndef _FORLOOPNODE_H_
#define _FORLOOPNODE_H_

#include <string>
#include <cassert>

#include "statementnode.h"

class ForRange;

class ForLoopNode : public StatementNode
    {
    public:
        ForLoopNode( const char *_c, ForRange *_r, StatementNode *_b ) :
            counter_name(_c), range(_r), body(_b)
            {
            assert( _c != NULL );
            assert( _r != NULL );
            assert( _b != NULL );
            } ;

        virtual ~ForLoopNode();
        virtual std::string pretty_print( int indent ) const;

    private:
        std::string counter_name;
        ForRange *range;
        StatementNode *body;
    } ;

#endif

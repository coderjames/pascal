#ifndef _FORRANGE_H_
#define _FORRANGE_H_

#include <string>
#include <cassert>

class ExpressionNode;

class ForRange
    {
    public:
        ForRange( ExpressionNode *_b, ExpressionNode *_e, bool incr ) :
            begin(_b), end(_e), incrementing(incr)
            {
            assert( _b != NULL );
            assert( _e != NULL );
            };

        ~ForRange();

        std::string pretty_print() const;

    private:
        ExpressionNode *begin;
        ExpressionNode *end;
        bool incrementing;
    } ;


#endif

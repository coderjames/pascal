#ifndef _SUBROUTINE_H_
#define _SUBROUTINE_H_

#include <string>
#include <map>
#include <cstdio>

class TypeNode;
class BlockNode;

class SubroutineNode
    {
    public:
        SubroutineNode( std::string _n, std::map<std::string, TypeNode *> *_p,
                BlockNode *_b, TypeNode *_r ) :
            name(_n), parameters(_p), body(_b), result_type(_r)
            {
            printf( "\nDBUG(subrnode.h): ctor(_n @ %p) == %s", &_n, _n.c_str() );
            };
            // not checking _p or _b for NULL because:
            //     _p: not all subroutines take parameters
            //     _b: this particular node might be a forward declaration
            //     _r: procedures don't have a result type (only functions do)

        ~SubroutineNode();

        std::string pretty_print( int indent ) const;

    protected:
        std::string name;
        std::map<std::string, TypeNode *> *parameters;
        BlockNode *body;
        TypeNode *result_type;
    } ;

#endif

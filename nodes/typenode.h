#ifndef _TYPENODE_H_
#define _TYPENODE_H_

#include <string>
#include <cassert>

#include "../astnode.hpp"

class TypeNode : public ASTNode
    {
    public:
        // scaled-down constructor for when a type is just renaming an existing type
        //       nodes of this Type will get replaced during the type-compaction phase
        //       with the type they are aliasing
        TypeNode( std::string _n ) :
                base_type(NULL), name(_n) {};

        // most types use this basic constructor
        TypeNode( std::string _name, TypeNode *_base ) :
                base_type(_base), name(_name) {};
                // no NULL check on _base, since it is allowed to be NULL

        virtual ~TypeNode();
        virtual std::string pretty_print( int indent ) const;

    protected:
        TypeNode *base_type;
        std::string name;
    } ;

extern TypeNode IntegerType;
extern TypeNode StringType;
extern TypeNode BooleanType;
extern TypeNode CharType;

#endif

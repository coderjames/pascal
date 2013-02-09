#ifndef _ARRAYTYPENODE_H_
#define _ARRAYTYPENODE_H_

#include "typenode.h"

#include <list>

class ArrayTypeNode : public TypeNode
    {
    public:
        // arrays use this constructor to provide the dimensions of the array
        ArrayTypeNode( std::list<int> *_dm, TypeNode *_base ) :
                TypeNode("ARRAY", _base), dimensions(_dm)
                {
                assert( _base != NULL ); // arrays are not self-contained types
                assert( _dm != NULL );   // and arrays must have dimensions
                };

        virtual ~ArrayTypeNode()
            {
            if( dimensions )
                delete dimensions;
            } ;

        virtual std::string pretty_print( int indent ) const
            {
            std::string result("ARRAY[");

            for( std::list<int>::const_iterator it = dimensions->begin();
                it != dimensions->end();
                ++it )
                {
                //result += std::string(*it);
                result += ", ";
                }

            result += "] OF " + base_type->pretty_print(indent);

            return( result );
            } ;

    protected:
        std::list<int> *dimensions;
    } ;

#endif

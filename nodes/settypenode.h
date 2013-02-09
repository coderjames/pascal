#ifndef _SETTYPENODE_H_
#define _SETTYPENODE_H_

#include "typenode.h"

#include <list>

class SetTypeNode : public TypeNode
    {
    public:
        SetTypeNode( TypeNode *_b ) : TypeNode("SET", _b)
            {};
        SetTypeNode( std::list<std::string> _elements ) : TypeNode("SET"), elements(_elements)
            {};

        virtual std::string pretty_print( int indent ) const
            {
            std::string result("SET OF ");

            if( base_type )
                result += base_type->pretty_print(indent);
            else
                {
                result = "( ";

                for( std::list<std::string>::const_iterator it = elements.begin();
                    it != elements.end();
                    ++it )
                    {
                    result += *it;
                    result += ", "; // TODO: don't add if last element
                    }

                result += ")";
                }

            return( result );
            };

    protected:
        std::list<std::string> elements;
    } ;

#endif

#ifndef _RECORDTYPENODE_H_
#define _RECORDTYPENODE_H_

#include "typenode.h"

#include <map>

class RecordTypeNode : public TypeNode
    {
    public:
        // records use this constructor to provide the fields
        RecordTypeNode( std::map<std::string, TypeNode *> *_f ) : TypeNode("RECORD"), fields(_f)
            {
            assert( _f != NULL ); // no empty record types allowed
            };

        virtual ~RecordTypeNode()
            {
            fields->clear();
            delete fields;
            };
            
        virtual std::string pretty_print(int indent) const
            {
            std::string tabs;
            for( int i = 0; i < indent; ++i )
                tabs += "\t";

            std::string result( "\n" + tabs + "RECORD" );

            for( std::map<std::string, TypeNode *>::const_iterator it = fields->begin();
                it != fields->end();
                ++it )
                {
                result += "\n\t" + tabs + it->first + " : " + it->second->pretty_print(indent);
                }

            result += "\n" + tabs + "END";
            return( result );
            };

    protected:
        std::map<std::string, TypeNode *> *fields;
    } ;

#endif

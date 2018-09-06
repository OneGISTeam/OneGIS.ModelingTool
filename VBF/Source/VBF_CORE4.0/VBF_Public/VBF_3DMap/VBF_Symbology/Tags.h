#ifndef OSGEARTHSYMBOLOGY_TAGS_H
#define OSGEARTHSYMBOLOGY_TAGS_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_Common/VBF_Utils/VBF_StringUtils.h>
#include <vector>
#include <set>
#include <algorithm>


namespace osgEarth { namespace Symbology
{
    typedef std::vector<std::string> TagVector;
    typedef std::set<std::string>    TagSet;

    template<typename T>
    class Taggable : public T
    {
    public:
        void addTag( const std::string& tag ) {
            _tags.insert( normalize( tag ) );
        }
        void addTags( const TagVector& tags ) {
            for( TagVector::const_iterator i = tags.begin(); i != tags.end(); ++i )
                _tags.insert( normalize(*i) );
        }
        void addTags( const std::string& tagString ) {
            TagVector tags;
            CVBF_StringTokenizer( tagString, tags, " ", "\"'", false, true );
            addTags( tags );
        }
        void removeTag( const std::string& tag ) {
            _tags.erase( normalize( tag ) );
        }
        bool containsTag( const std::string& tag ) const {
            return _tags.find( normalize( tag )) != _tags.end();
        }

        bool containsTags( const TagSet& tags) const {
            for( TagSet::const_iterator i = tags.begin(); i != tags.end(); i++ ) {
               if ( _tags.find( normalize( *i ) ) == _tags.end() )
                  return false;
            }
            return true;            
        }

        bool containsTags( const TagVector& tags) const {
            for( TagVector::const_iterator i = tags.begin(); i != tags.end(); i++ ) {
               if ( _tags.find( normalize( *i ) ) == _tags.end() )
                  return false;
            }
            return true;            
        }

        const TagSet& tags() const { return _tags; }

        static std::string tagString(const TagSet& tags) {
            std::stringstream buf;
            for( TagSet::const_iterator i = tags.begin(); i != tags.end(); i++ )
                buf << (i != tags.begin()? " " : "") << *i;
            std::string result = buf.str();
            return result;
        }

        static std::string tagString(const TagVector& tags) {
            std::stringstream buf;
            for( TagVector::const_iterator i = tags.begin(); i != tags.end(); i++ )
                buf << (i != tags.begin()? " " : "") << *i;
            std::string result = buf.str();
            return result;
        }

        std::string tagString() const {
            std::stringstream buf;
            for( TagSet::const_iterator i = _tags.begin(); i != _tags.end(); i++ )
                buf << (i != _tags.begin()? " " : "") << *i;
            std::string result = buf.str();
            return result;
        }

    protected:
        
        TagSet _tags;

    private:

        std::string normalize( const std::string& input ) const
        {
            std::string output = input;
            std::transform( output.begin(), output.end(), output.begin(), tolower );

            return output;
        }
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_QUERY_H

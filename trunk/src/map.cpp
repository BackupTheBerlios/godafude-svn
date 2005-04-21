#include "map.h"

#include <iostream> // kill me!

using wad::Wad;

namespace map
{
    Map::Map( Wad *w, Wad::iterator &l )
    {
        // TODO: Verify that l.name is a map start (and so on)
        for(;;)
        {
            const std::string &n = (++l)->name();
        
            w->seek( *l );
            QDataStream &d = w->stream();        
            bool isHexen = w->isHexen();
            
            std::cout << "processing " << n << " (" << l->len() << " bytes)"
             << std::endl;

            if( n == "THINGS" )
            {
                int thingsize = isHexen ? 20 : 10;
                for( unsigned i = 0 ; i < l->len() / thingsize ; ++i )
                    things_.push_back( Thing( d, isHexen ) );
            }         
             else if( n == "LINEDEFS" ||
                      n == "SIDEDEFS" )
            {
                // nothing - yet
            }
             else if( n == "VERTEXES" )
            {
                for( unsigned i = 0 ; i < l->len() / 8 ; ++i )
                    vertices_.push_back( Vertex( d ) );
            }
             else break;
        }
        
        QPoint i = things_[123].pos();

        std::cout << "Thing number 123: " << things_[123].type()
         << "(" << i.rx() << ", " << i.ry() << ")" << std::endl;
    }
}

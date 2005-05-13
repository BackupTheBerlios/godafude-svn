// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include "gamemap.h"

#include <iostream> // kill me!

using wad::Wad;

namespace gamemap
{
    Map::Map( Wad *w, Wad::iterator &l )
    : undostack_()
    {
        // TODO: Verify that l.name is a map start
        for(;;)
        {
            const std::string &n = (++l)->name();
        
            w->seek( *l );
            QDataStream &d = w->stream();        
            const bool isHexen = w->isHexen();
            
            std::cout << "processing " << n << " (" << l->len() << " bytes)"
             << std::endl;

            if( n == "THINGS" )
            {
                const int thingsize = isHexen ? 20 : 10;
                for( unsigned i = 0 ; i < l->len() / thingsize ; ++i )
                    things_.push_back( Thing( d, isHexen ) );
                
            }         
             else if( n == "LINEDEFS" )
            {
                const int linedefsize = isHexen ? 16 : 14;
                for( unsigned i = 0 ; i < l->len() / linedefsize ; ++i )
                    linedefs_.push_back( Linedef( d, isHexen ) );
            }
             else if( n == "SIDEDEFS" )
            {
                // nothing - yet
            }
             else if( n == "VERTEXES" )
            {
                for( unsigned i = 0 ; i < l->len() / 4 ; ++i )
                    vertices_.push_back( Vertex( d ) );
            }
             else break;
        }
    }
}

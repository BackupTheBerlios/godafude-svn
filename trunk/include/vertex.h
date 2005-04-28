// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include <QPoint>

class QDataStream;

namespace map
{
    //! This class represents a vertex
    class Vertex: public QPoint
    {
        public:
            Vertex( int x = 0, int y = 0 )
            : QPoint( x, y ) {}

            inline void set( const QPoint &v )
            { rx() = v.x(), ry() = v.y(); }
        
            //! Load a vertex from a QDataStream
            Vertex( QDataStream &s );
    };
}

#endif

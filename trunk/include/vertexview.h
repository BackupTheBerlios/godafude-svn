// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef VERTEXVIEW_H
#define VERTEXVIEW_H

#include <set>

#include "gamemap.h"
#include "mapview.h"
#include "vertex.h"

class QMouseEvent;
class QPaintEvent;
class QPoint;

namespace Ui
{
    //! The Vertex view
    class VertexView: public MapView
    {
        public:
            VertexView( gamemap::Map *myMap )
            : MapView( myMap ), orig_() {}

        protected:
            virtual void paintEvent( QPaintEvent * );
            
            virtual int getID( const QPoint &p ) const;
            virtual void getSelectedVertices();

        private:
            std::map<int,gamemap::Vertex> orig_;

            //! Relative size of the green crosses that mark each vertex
            static const int markSize;
            
            //! Relative size of the rectangle for hover/selection
            static const int selectSize;

            //! Relative size of the are around the vertex that the mouse must be in to find it
            static const int findSize;
    };
}

#endif

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

#include "mapview.h"

class QPaintEvent;

namespace Ui
{
    //! The Vertex view
    class VertexView: public MapView
    {
        public:
            VertexView( map::Map *myMap )
            : MapView( myMap ) {}

        protected:
            virtual void paintEvent( QPaintEvent * );            
    };
}

#endif

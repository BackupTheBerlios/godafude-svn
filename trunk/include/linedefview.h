// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef LINEDEFVIEW_H
#define LINEDEFVIEW_H

#include "mapview.h"

class QPaintEvent;
class QPoint;

namespace Ui
{
    class LinedefView : public MapView
    {
        public:
            LinedefView( gamemap::Map *mymap )
            : MapView( mymap ) {}

        protected:
            virtual void paintEvent( QPaintEvent* );
            
            virtual int getID( const QPoint &p ) const;
            virtual void getSelectedVertices();
    };
}

#endif

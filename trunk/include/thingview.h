// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef THINGVIEW_H
#define THINGVIEW_H

#include "mapview.h"

//! All user interface classes are defined in this namespace
namespace Ui
{
    //! The thing view
    class ThingView: public MapView
    {
        public:
            ThingView( map::Map *myMap )
             : MapView( myMap ) {}

        protected:
            virtual void paintEvent( QPaintEvent* );
    };
}

#endif

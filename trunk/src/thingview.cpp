// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include <iostream>     // debug only
#include <vector>

#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QRect>

#include "map.h"
#include "thingview.h"

namespace Ui
{
    void ThingView::paintEvent( QPaintEvent *e )
    {
        MapView::paintEvent(e); // Draw the grid
        
        QRect r(view2map(e->rect().topLeft()),
                view2map(e->rect().bottomRight()));
        
        QPainter paint(this);
        paint.setPen( Qt::green );
        
        std::vector<map::Thing> &things = mymap_->things();

        for( std::vector<map::Thing>::iterator it = things.begin() ;
          it != things.end() ; ++it )
        {
            if( r.contains( it->pos() ) )
            {
                QPoint center = map2view( it->pos() );
                paint.drawLine( center + QPoint(-3,-3),
                                center + QPoint( 3, 3) );
                paint.drawLine( center + QPoint( 3,-3),
                                center + QPoint(-3, 3) );
            }
        }
    }
}

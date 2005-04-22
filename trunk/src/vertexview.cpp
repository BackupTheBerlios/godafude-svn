// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QRect>

#include "vertexview.h"

namespace Ui
{
    void VertexView::paintEvent( QPaintEvent *e )
    {
        MapView::paintEvent( e );       // Draw the grid

        QRect r(view2map(e->rect().topLeft()),
                view2map(e->rect().bottomRight()));

        QPainter paint(this);

        paint.setPen( Qt::lightGray );
        drawOutline( r, paint );
                
        paint.setPen( Qt::green );
        
        std::vector<map::Vertex> &vertices = mymap_->vertices();

        for( std::vector<map::Vertex>::iterator it = vertices.begin() ;
          it != vertices.end() ; ++it )
        {
            // Draw the vertex
            if( r.contains( *it ) )
            {
                QPoint center = map2view( *it );
                paint.drawLine( center + QPoint(-3,-3),
                                center + QPoint( 3, 3) );
                paint.drawLine( center + QPoint( 3,-3),
                                center + QPoint(-3, 3) );
                // Is it selected?
                bool selected = std::find( selection.begin(), selection.end(), &(*it) )
                                   != selection.end();
                if( selected )
                    paint.drawRect( QRect( center + QPoint( -4, -4 ),
                                           center + QPoint(  4,  4 ) ) );

            }
        }
    }
}


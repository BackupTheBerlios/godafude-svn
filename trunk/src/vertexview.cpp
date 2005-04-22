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
                bool selected = std::find( selection_.begin(), selection_.end(), it-vertices.begin() )
                                   != selection_.end();
                bool focussed = this == focusView_ && it-vertices.begin() == focusID_;

                if( selected || focussed )
                {
                    if( selected && focussed )
                     paint.setPen( Qt::red );
                    else if( focussed )
                     paint.setPen( Qt::yellow );

                     paint.drawRect( QRect( center + QPoint( -4, -4 ),
                                            center + QPoint(  4,  4 ) ) );
                    paint.setPen( Qt::green );
                }
            }
        }
    }

    int VertexView::getID( const QPoint &p ) const
    {
        QRect r( p + QPoint( -4, -4 ), p + QPoint( 4, 4 ) );
        
        int nearestID = -1;
        int nearestDist = 100;
        
        std::vector<map::Vertex> &vertices = mymap_->vertices();

        for( std::vector<map::Vertex>::iterator it = vertices.begin() ;
            it != vertices.end() ; ++it )
        {
            QPoint tmp;

            if( r.contains( tmp = map2view( *it ) ) )
            {
                int newdist = (p.x() - tmp.x()) * (p.x() - tmp.x()) +
                              (p.y() - tmp.y()) * (p.y() - tmp.y());
                if( newdist < nearestDist )
                {
                    nearestID = it - vertices.begin();
                    nearestDist = newdist;
                }
            }
        }

        return nearestID;
    }
}


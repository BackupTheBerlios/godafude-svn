// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

#include "godafude.h"
#include "vertexview.h"

using gamemap::Vertex;

namespace Ui
{
    const int VertexView::markSize = 3;
    const int VertexView::selectSize = 4;
    const int VertexView::findSize = 10;

    void VertexView::paintEvent( QPaintEvent *e )
    {
        MapView::paintEvent( e );       // Draw the grid

        // Translate the view rect to the corresponding map rect
        QRect r(view2map(e->rect().topLeft()),
                view2map(e->rect().bottomRight()));

        QPainter paint(this);

        // Draw the outline of the map
        paint.setPen( Qt::lightGray );
        drawOutline( r, paint );

        paint.setPen( Qt::green );

        // Precalculate the QPoints of the four corners of the green
        // crosses that are used to mark a vertex
        int m = static_cast<int>(zoom()*markSize + 0.5);
        const QPoint tl = QPoint( -m, -m ),
                     tr = QPoint(  m, -m ),
                     bl = QPoint( -m,  m ),
                     br = QPoint(  m,  m );

        // Precalculate the QRect for a selected/focussed vertex
        int m2 = static_cast<int>(zoom()*selectSize + 0.5);
        if( m2 <= m ) m2 = m + 1; 
        const QRect selRect( -m2, -m2, 2*m2 + 1, 2*m2 + 1 );

        // The actual drawing starts here
        std::vector<gamemap::Vertex> &vertices = mymap_->vertices();

        for( std::vector<gamemap::Vertex>::iterator it = vertices.begin() ;
          it != vertices.end() ; ++it )
        {
            // Draw the vertex
            if( r.contains( *it ) )
            {
                // Draw the vertex
                QPoint center = map2view( *it );
                paint.drawLine( center + tl, center + br );
                paint.drawLine( center + tr, center + bl );

                // Is it selected?
                bool selected = selection_.find( it-vertices.begin() ) != selection_.end();

                // Is this object focussed?
                bool focussed = this == focusView_ && it-vertices.begin() == focusID_;

                if( selected || focussed )
                {
                    if( selected && focussed )
                     paint.setPen( Qt::red );
                    else if( focussed )
                     paint.setPen( Qt::yellow ); // else it's only selected and remains green

                    paint.drawRect( selRect.translated(center) );

                    paint.setPen( Qt::green );
                }
            }
        }
    }

    int VertexView::getID( const QPoint &p ) const
    {
        // Of all vertices inside the rect around the mouse pointer
        // find the one that is closest to the mouse pointer
        int m = static_cast<int>(zoom()*findSize + 0.5);
        const QRect r( view2map( p + QPoint( -m, -m ) ),
                       view2map( p + QPoint(  m,  m ) ) );

        int px = view2map(p).x(),
            py = view2map(p).y();
        
        int nearestID = -1;
        int nearestDist = findSize*findSize*2 + 1;    // Impossibly large
        
        std::vector<gamemap::Vertex> &vertices = mymap_->vertices();

        for( std::vector<gamemap::Vertex>::iterator it = vertices.begin() ;
            it != vertices.end() ; ++it )
        {
            if( r.contains( *it ) )
            {
                int newdist = (px - it->x()) * (px - it->x()) +
                              (py - it->y()) * (py - it->y());

                if( newdist < nearestDist )
                {
                    nearestID = it - vertices.begin();
                    nearestDist = newdist;
                }
            }
        }

        return nearestID;
    }

    void VertexView::getSelectedVertices()
    {
        selectedVertices_.clear();

        const std::vector<gamemap::Vertex>  &vertices = mymap_->vertices();

        std::set<int>::const_iterator it;
        for( it = selection_.begin() ; it != selection_.end() ; ++it)
          selectedVertices_[*it] = vertices[*it];
    }
}


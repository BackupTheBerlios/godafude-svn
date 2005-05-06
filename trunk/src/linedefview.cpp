// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include <cmath>
#include <set>
#include <vector>

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QPoint>
 
#include "linedef.h"
#include "linedefview.h"
#include "gamemap.h"
#include "godafude.h"
#include "vertex.h"

namespace Ui
{
    void LinedefView::paintEvent( QPaintEvent *e )
    {
        MapView::paintEvent( e );       // Draw the grid

        // Translate the view rect to the corresponding map rect
        QRect r(view2map(e->rect().topLeft()),
                view2map(e->rect().bottomRight()));

        QPainter p(this);
        
        // The actual drawing starts here
        const std::vector<gamemap::Linedef> &linedefs = mymap_->linedefs();
        const std::vector<gamemap::Vertex>  &vertices = mymap_->vertices();

        for( std::vector<gamemap::Linedef>::const_iterator it = linedefs.begin() ;
          it != linedefs.end() ; ++it )
        {
            const QPoint &v1 = vertices[it->v1()],
                         &v2 = vertices[it->v2()];

            int o1 = outcode( v1, r ),
                o2 = outcode( v2, r );

            if( (o1 & o2) != 0 ) continue;

            bool selected = selection_.find( it-linedefs.begin() ) != selection_.end();
            bool focussed = this == focusView_ && it-linedefs.begin() == focusID_;
            
            if( focussed || selected )
            {
                // Get the normal vector
                QPointF norm( v2-v1 );
                float tmp = -norm.x(); norm.rx() = norm.y(); norm.ry() = tmp;
                norm /= length(norm);

                // Get the middle of the line
                QPoint middle(v1 + (v2-v1)/2);

                QPen pen;
                pen.setWidth(2);
                
                if( selected && focussed ) pen.setColor( Qt::red );
                 else if( focussed ) pen.setColor( Qt::yellow );
                 else pen.setColor( Qt::green );
                p.setPen(pen);
                p.drawLine( map2view(v1), map2view(v2) );

                pen.setWidth(1); p.setPen(pen);
                p.drawLine(map2view(middle), map2view(middle+(norm*10/zoom()).toPoint()));
            }
             else
            {
                if( it->action() != 0 )
                  if( it->arg(1) != 0 )
                    p.setPen( Qt::green );
                  else
                    p.setPen( Qt::magenta );
                else if( it->side2() != -1 )
                 p.setPen( Qt::gray );
                else
                 p.setPen( Qt::white );

                p.drawLine( map2view(v1), map2view(v2) );
            }
        }
    }

    void LinedefView::getSelectedVertices()
    {
        selectedVertices_.clear();

        const std::vector<gamemap::Vertex>  &vertices = mymap_->vertices();
        const std::vector<gamemap::Linedef> &linedefs = mymap_->linedefs();

        for( std::set<int>::iterator it = selection_.begin()
         ; it != selection_.end() ; ++it )
        {
            selectedVertices_[linedefs[*it].v1()] = vertices[linedefs[*it].v1()];
            selectedVertices_[linedefs[*it].v2()] = vertices[linedefs[*it].v2()];
        }
    }

    int LinedefView::getID( const QPoint &p ) const
    {
        int px = view2map(p).x(),
            py = view2map(p).y();

        const std::vector<gamemap::Linedef> &linedefs = mymap_->linedefs();
        const std::vector<gamemap::Vertex>  &vertices = mymap_->vertices();

        const int maxdiff = 1000;        // Maximal distance from point to line we consider
        float mindiff = maxdiff+1;
        int minID = -1;             // ID of the linedef with mindiff
        
        for( std::vector<gamemap::Linedef>::const_iterator it = linedefs.begin() ;
          it != linedefs.end() ; ++it )
        {
            const QPoint &v1 = vertices[it->v1()],
                         &v2 = vertices[it->v2()];

            const int TRESH = 10;

            // Try to quickly dismiss this line
            // by checking if the point is outside of the bounding rect
            if( v1.x() <= v2.x() )
             if( px <= v1.x()-TRESH || px >= v2.x()+TRESH ) continue; else;
            else
             if( px <= v2.x()-TRESH || px >= v1.x()+TRESH ) continue;

            if( v1.y() <= v2.y() )
             if( py <= v1.y()-TRESH || py >= v2.y()+TRESH ) continue; else;
            else
             if( py <= v2.y()-TRESH || py >= v1.y()+TRESH ) continue;

            // ...  it's not, so calculate the distance from point to line
            int nom = abs( px * (v1.y() - v2.y()) +
                           py * (v2.x() - v1.x()) +
                           v1.x()*v2.y() - v2.x()*v1.y() );

            float m = static_cast<float>(nom) /
                      length(v2-v1);

            if(m < mindiff) {mindiff = m; minID = it-linedefs.begin();}
        }

        return mindiff <= maxdiff ? minID:-1;
    }
}

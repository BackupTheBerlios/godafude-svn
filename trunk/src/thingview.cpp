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

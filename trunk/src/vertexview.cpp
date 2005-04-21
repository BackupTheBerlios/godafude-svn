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
        paint.setPen( Qt::green );
        
        std::vector<map::Vertex> &vertices = mymap_->vertices();

        for( std::vector<map::Vertex>::iterator it = vertices.begin() ;
          it != vertices.end() ; ++it )
        {
            if( r.contains( *it ) )
            {
                QPoint center = map2view( *it );
                paint.drawLine( center + QPoint(-3,-3),
                                center + QPoint( 3, 3) );
                paint.drawLine( center + QPoint( 3,-3),
                                center + QPoint(-3, 3) );
            }
        }
    }
}


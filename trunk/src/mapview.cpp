#include <QAction>
#include <QActionGroup>
#include <QPaintEvent>
#include <QPalette>
#include <QResizeEvent>

#include "mapview.h"

namespace Ui
{
    MapView::MapView( map::Map *mymap )
     : QWidget(),
       mymap_( mymap ),
       pal_(),
       mappos_(0,0),
       zoom_(1.0)
    {
        // Set the palette: background -> black
        pal_.setColor( QPalette::Background, QColor(0, 0, 0 ) );
        this->setPalette( pal_ );
        
        // Let the user move the map
        QActionGroup *moveActions = new QActionGroup(this);
        
        QAction *act = new QAction(moveActions);
        act->setShortcut( QKeySequence( Qt::Key_Left ) );
        addAction( act );
        connect( act, SIGNAL(triggered()), this, SLOT(mapLeft()) );        
        
        act = new QAction(moveActions);
        act->setShortcut( QKeySequence( Qt::Key_Right ) );
        addAction( act );
        connect( act, SIGNAL(triggered()), this, SLOT(mapRight()) );
        
        act = new QAction(moveActions);
        act->setShortcut( QKeySequence( Qt::Key_Up ) );
        addAction( act );
        connect( act, SIGNAL(triggered()), this, SLOT(mapUp()) );
        
        act = new QAction(moveActions);
        act->setShortcut( QKeySequence( Qt::Key_Down ) );
        addAction( act );
        connect( act, SIGNAL(triggered()), this, SLOT(mapDown()) );
        
        // Zoom keys
        QActionGroup *zoomActions = new QActionGroup(this);
        
        act = new QAction(zoomActions);
        act->setShortcut( QKeySequence( Qt::Key_Plus ) );
        addAction( act );
        connect( act, SIGNAL(triggered()), this, SLOT(zoomIn()) );
        
        act = new QAction(zoomActions);
        act->setShortcut( QKeySequence( Qt::Key_Minus ) );
        addAction( act );
        connect( act, SIGNAL(triggered()), this, SLOT(zoomOut()) );
    }
    
    void MapView::mapLeft()
    {
        mappos().rx() -= movestep(); update();
    }
    
    void MapView::mapRight()
    {
        mappos().rx() += movestep(); update();
    }
    
    void MapView::mapUp()
    {
        mappos().ry() -= movestep(); update();
    }
    
    void MapView::mapDown()
    {
        mappos().ry() += movestep(); update();
    }

    void MapView::zoomIn()
    {
        zoom() *= 1.2; update();
    }
    
    void MapView::zoomOut()
    {
        zoom() /= 1.2; update();
    }

    void MapView::paintEvent( QPaintEvent *e )
    {
        Q_UNUSED(e)
    }
    
    void MapView::resizeEvent( QResizeEvent *e )
    {
        center_.rx() = e->size().width()/2;
        center_.ry() = e->size().height()/2;
    }
    
    QPoint MapView::map2view( const QPoint &p ) const
    {
        return (p-mappos())*zoom()+center();
    }
    
    QPoint MapView::view2map( const QPoint &p ) const
    {
        return (p-center())/zoom()+mappos();
    }
    
    int MapView::movestep() const
    {
        return static_cast<int>(5.0 / zoom()) + 1;
    }
    
}

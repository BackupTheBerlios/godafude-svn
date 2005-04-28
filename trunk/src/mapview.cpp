// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPalette>
#include <QRect>
#include <QResizeEvent>

#include "mapview.h"

namespace Ui
{
    MapView *MapView::focusView_ = static_cast<MapView*>(NULL);
    int MapView::focusID_ = -1;
    const int MapView::maxGridSize_ = 1024;

    MapView::MapView( map::Map *mymap )
     : QWidget(),
       mymap_( mymap ),
       selection_(),       
       pal_(),
       mappos_(0,0),
       zoom_(1.0),
       gridSize_(64),
       showGrid_(true)
    {
        // TODO: Tool tips

        // Set the palette: background -> black
        pal_.setColor( QPalette::Background, QColor(0, 0, 0 ) );
        this->setPalette( pal_ );
        
        setMouseTracking(true);
        
        // Let the user move the map
        QActionGroup *moveActions = new QActionGroup(this);
        
        QAction *act = new QAction(moveActions);
        act->setShortcut( QKeySequence( Qt::Key_Left ) );
        connect( act, SIGNAL(triggered()), this, SLOT(mapLeft()) );        
        
        act = new QAction(moveActions);
        act->setShortcut( QKeySequence( Qt::Key_Right ) );
        connect( act, SIGNAL(triggered()), this, SLOT(mapRight()) );
        
        act = new QAction(moveActions);
        act->setShortcut( QKeySequence( Qt::Key_Up ) );
        connect( act, SIGNAL(triggered()), this, SLOT(mapUp()) );
        
        act = new QAction(moveActions);
        act->setShortcut( QKeySequence( Qt::Key_Down ) );
        connect( act, SIGNAL(triggered()), this, SLOT(mapDown()) );
        
        addActions(moveActions->actions());

        // Zoom keys
        zoomActions = new QActionGroup(this);
        
        act = new QAction( tr("Zoom In"), zoomActions);
        act->setShortcut( QKeySequence( Qt::Key_Plus ) );
        connect( act, SIGNAL(triggered()), this, SLOT(zoomIn()) );
        
        act = new QAction( tr("Zoom Out"), zoomActions);
        act->setShortcut( QKeySequence( Qt::Key_Minus ) );
        connect( act, SIGNAL(triggered()), this, SLOT(zoomOut()) );
        
        act = new QAction( tr("Zoom to 100%"), zoomActions);
        act->setShortcut( QKeySequence( Qt::Key_Asterisk ) );
        connect( act, SIGNAL(triggered()), this, SLOT(zoom100()) );
        
        addActions(zoomActions->actions());

        // Grid keys
        gridActions = new QActionGroup(this);
        
        act = new QAction( tr("Increase grid size"), gridActions );
        act->setShortcut( QKeySequence( Qt::SHIFT | Qt::Key_G ) );
        connect( act, SIGNAL(triggered()), this, SLOT(gridInc()) );
        gridIncAct_ = act;

        act = new QAction( tr("Decrease grid size"), gridActions );
        act->setShortcut( QKeySequence( Qt::Key_G ) );
        connect( act, SIGNAL(triggered()), this, SLOT(gridDec()) );
        gridDecAct_ = act;
        
        addActions(gridActions->actions());
        
        act = new QAction( tr("Show grid"), this );
        act->setCheckable(true); act->setChecked(showGrid_);
        act->setShortcut( QKeySequence( Qt::Key_H ) );
        connect( act, SIGNAL(toggled(bool)), this, SLOT(gridToggle(bool)) );
        gridToggleAct_ = act;
        addAction( gridToggleAct_ );
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
        zoom() *= 1.5; update();
    }
    
    void MapView::zoomOut()
    {
        zoom() /= 1.5; update();
    }
    
    void MapView::zoom100()
    {
        zoom() = 1.0; update();
    }

    void MapView::gridInc()
    { 
        gridSize_ <<= 1;
        gridDecAct_->setEnabled(true);
        
        if( gridSize_ == maxGridSize_ )
            gridIncAct_->setEnabled(false);
        update();
    }

    void MapView::gridDec()
    { 
        gridSize_ >>= 1;
        gridIncAct_->setEnabled(true);
        
        if( gridSize_ == 1 )
            gridDecAct_->setEnabled(false);
        update();
    }

    void MapView::gridToggle( bool b )
    {
        showGrid_ = b;
        update();
    }

    void MapView::mouseMoveEvent( QMouseEvent *e )
    {
        int id = getID( e->pos() );

        if( id != -1 )
        {
            focusView_ = this;
            focusID_ = id;
            update();
        }
    }
    
    void MapView::mousePressEvent( QMouseEvent *e )
    {
        if( e->button() == Qt::RightButton )
        {
            QMenu m;

            m.addActions( zoomActions->actions() );
            m.addActions( gridActions->actions() );
            m.addAction( gridToggleAct_ );
            
            m.exec( e->globalPos() );

            return;
        }

        // Handle selections
        if( focusView_ == this )
        {
            // If the Ctrl key is not pressed while clicking,
            // unselect all previously selected objects
            if( (e->modifiers() & Qt::ControlModifier) == 0 )
             selection_.clear();

            // If the object is already selected, deselect it
            std::set<int>::iterator it = selection_.find( focusID_ );
            
            if( it != selection_.end() )
              selection_.erase(it);
            else
              selection_.insert( focusID_ );

            update();
        }
    }

    void MapView::paintEvent( QPaintEvent *e )
    {
        if( showGrid_ )
        {
            QPainter p(this);
            p.setPen( Qt::blue );
            // Translate the view rect to the corresponding map rect
            QRect r(view2map(e->rect().topLeft()),
                    view2map(e->rect().bottomRight()));

            // Get the upper left grid point of r
            QPoint upperleft = snap2grid( r.topLeft(), ul );

            // Vertical grid lines
            for( int i = upperleft.x() ; i <= r.right() ; i += gridSize_ )
                p.drawLine( mapx2viewx(i), e->rect().top(),
                            mapx2viewx(i), e->rect().bottom() );

            // Horizontal grid lines
            for( int i = upperleft.y() ; i <= r.bottom() ; i += gridSize_ )
                p.drawLine( e->rect().left(), mapy2viewy(i),
                            e->rect().right(), mapy2viewy(i) );
        }
    }
    
    void MapView::resizeEvent( QResizeEvent *e )
    {
        QSize s = e->size()/2;
        center_ = QPoint( s.width(), s.height() );
    }
    
    QPoint MapView::map2view( const QPoint &p ) const
    {
        return (p-mappos())*zoom()+center();
    }

    int MapView::mapx2viewx( int x ) const
    {
        return static_cast<int>((x-mappos().x())*zoom()) + center().x();
    }

    int MapView::mapy2viewy( int y ) const
    {
        return static_cast<int>((y-mappos().y())*zoom()) + center().y();
    }

    QPoint MapView::view2map( const QPoint &p ) const
    {
        return (p-center())/zoom()+mappos();
    }
    
    void MapView::drawOutline( const QRect &r, QPainter &p )
    {
        for( std::vector<map::Linedef>::iterator it = mymap_->linedefs().begin() ;
          it != mymap_->linedefs().end() ; ++it )
        {
            QPoint &v1 = mymap_->vertices()[it->v1()],
                   &v2 = mymap_->vertices()[it->v2()];
                   
            int o1 = outcode( v1, r ),
                o2 = outcode( v2, r );
                
            if( (o1 & o2) == 0 )
              p.drawLine( map2view(v1), map2view(v2) );
        }
    }
    
    int MapView::outcode( const QPoint &p, const QRect &r ) const
    {
        return
         ((p.y() < r.top()    ) << 3) |
         ((p.y() > r.bottom() ) << 2) |
         ((p.x() < r.left()   ) << 1) |
         ( p.x() > r.right());
    }
    
    QPoint MapView::snap2grid( const QPoint &p, snaptype dir ) const
    {
        if( !showGrid_ ) return QPoint(p);

        int bitmask = ~(gridSize_ - 1);
        
        int x = p.x() & bitmask,
            y = p.y() & bitmask;
        
        if( dir == ul || p.x() == x && p.y() == y ) return QPoint( x, y );
        
        if( dir == nearest )
            return QPoint(  (p.x() & (gridSize_ >> 1)) == 0 ? x : x + gridSize_,
                            (p.y() & (gridSize_ >> 1)) == 0 ? y : y + gridSize_ );

        return QPoint( p.x() == x ? x : x + gridSize_,
                       p.y() == y ? y : y + gridSize_ );
    }                            
    
    int MapView::movestep() const
    {
        return static_cast<int>(5.0 / zoom()) + 1;
    }
    
}

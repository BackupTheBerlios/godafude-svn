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

    MapView::MapView( map::Map *mymap )
     : QWidget(),
       mymap_( mymap ),
       selection_(),       
       pal_(),
       mappos_(0,0),
       zoom_(1.0)
    {
        // Set the palette: background -> black
        pal_.setColor( QPalette::Background, QColor(0, 0, 0 ) );
        this->setPalette( pal_ );
        
        setMouseTracking(true);
        
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
        if( focusView_ == this )
        {
            if( (e->modifiers() & Qt::ControlModifier) == 0 )
             selection_.clear();

            std::vector<int>::iterator it = selection_.begin();
            
            while( it != selection_.end() && *it != focusID_ ) ++it;
            
            if( it != selection_.end() )
              selection_.erase(it);
            else
              selection_.push_back( focusID_ );

            update();
        }
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
    
    int MapView::movestep() const
    {
        return static_cast<int>(5.0 / zoom()) + 1;
    }
    
}

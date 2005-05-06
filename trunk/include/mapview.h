// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <map>
#include <set>

#include <QWidget>
#include "gamemap.h"
#include "vertex.h"

class QActionGroup;
class QMouseEvent;
class QPainter;
class QPaintEvent;
class QPalette;
class QPoint;
class QRect;
class QResizeEvent;

namespace Ui
{
    //! Base class for all widgets that let the user edit the map
    /*!
     * A lot of the editor functionality is implemented
     * in this class:
     +
     * It supports drawing of the grid, moving around in the
     * map, zooming in, out, etc
     *
     * Note to self:
     * Figure out an efficient way to draw the grid
     */
    class MapView : public QWidget
    {
        Q_OBJECT

        public:
            MapView( gamemap::Map *mymap );
            
            //! The map position of the center point
            inline QPoint &mappos() { return mappos_; }
            inline const QPoint mappos() const { return mappos_; }
	    
	    //! Zoom factor of the map
            inline float &zoom() { return zoom_; }
            inline float zoom() const { return zoom_; }
            
        public slots:
            void mapLeft();
            void mapRight();
            void mapUp();
            void mapDown();
            
            void zoomIn();
            void zoomOut();
            void zoom100();

            void gridInc();
            void gridDec();
            void gridToggle(bool);

        protected:
            //! Mouse hover
            virtual void mouseMoveEvent( QMouseEvent* );

            //! Selection
            virtual void mousePressEvent( QMouseEvent* );

            //! This draws a grid (and nothing else)
            virtual void paintEvent( QPaintEvent* );
            virtual void resizeEvent( QResizeEvent* );
            
            //! Returns the ID of the object at (view) position p or -1
            virtual int getID( const QPoint &p ) const = 0;

            //! Fill the selectedVertices_ container
            virtual void getSelectedVertices() = 0;

            inline const QPoint center() const { return center_; }
            QPoint map2view( const QPoint &p ) const;
            int mapx2viewx( int x ) const;
            int mapy2viewy( int y ) const;
            QPoint view2map( const QPoint &p ) const;

            //! Draw an ouline of the map inside the specified (map) rect
            void drawOutline( const QRect &r, QPainter &p );
            
            //! Returns a cohan sutherland outcode (above, below, left, right)
            int outcode( const QPoint &p, const QRect &r ) const;

            //! Where to snap to grid
            enum snaptype { ul, lr, nearest };
            
            //! Returns the QPoint of the grid intersection that is nearest to the given one
            /*!
                \param p The reference point in map coordinates
                \param dir Where to snap
            */
            QPoint snap2grid( const QPoint &p, snaptype dir = nearest ) const;

            gamemap::Map *mymap_;
            
            static MapView *focusView_; // View that has the ID focus
            static int focusID_;        // ID of focussed object or -1 if none

            std::set<int> selection_;

            //! Pairs: (vertexID, originalVertexPosition) for all vertices induced by selection_
            std::map<int,gamemap::Vertex> selectedVertices_;

            QActionGroup *zoomActions, *gridActions;

        private:
            //! How many (map-)units to move if a cursor key is pressed
            int movestep() const;
                            
            QPalette pal_;
            QPoint mappos_;
            float zoom_;
            int gridSize_;
            static const int maxGridSize_;
            bool showGrid_;
            QPoint center_;       // center of the widget
            
            QAction *gridIncAct_, *gridDecAct_, *gridToggleAct_;
    };
}

#endif

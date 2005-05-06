// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef GODAFUDE_H
#define GODAFUDE_H

#include <cmath>

#include <QPoint>
#include <QSize>

inline const QPoint operator+( const QPoint &p, const QSize &size )
{
    return QPoint( p.x() + size.width(),
                   p.y() + size.height() );
}

inline float length( const QPointF &p )
{
    return sqrt( p.x()*p.x() + p.y()*p.y() );
}

inline float operator*( const QPointF &a, const QPointF &b )
{
    return a.x()*b.x()+a.y()*b.y();
}

#endif

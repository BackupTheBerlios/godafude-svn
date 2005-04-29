// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include <QDataStream>

#include "vertex.h"

namespace gamemap
{
    Vertex::Vertex( QDataStream &s )
     : QPoint()
    {
        qint16 n;
        
        s >> n; rx() = n;
        s >> n; ry() = n;
    }
}
    
    

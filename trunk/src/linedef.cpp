// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include <QDataStream>
#include "linedef.h"

namespace map
{
    Linedef::Linedef( QDataStream &s, bool isHexen )
    {
        qint16 n;
        
        s >> n; v1_ = n;
        s >> n; v2_ = n;
        
        s >> n;
        
        flags_.impassable     = n & 0x0001 == 1;
        flags_.blocksmonsters = n & 0x0002 == 1;
        flags_.twosided       = n & 0x0004 == 1;
        flags_.upperunpegged  = n & 0x0008 == 1;
        flags_.lowerunpegged  = n & 0x0010 == 1;
        flags_.secret         = n & 0x0020 == 1;
        flags_.blockssound    = n & 0x0040 == 1;
        flags_.notonmap       = n & 0x0080 == 1;
        flags_.alreadyonmap   = n & 0x0100 == 1;
        flags_.repeatable = isHexen ? (n & 0x0200 == 1) : 1;
        flags_.activation = isHexen ? (n & 0x1c00) >> 10 : 0; 
        
        if( isHexen )
        {
            quint8 b;
            
            s >> b; action_ = b;
            s >> b; args_[0] = b;
            s >> b; args_[1] = b;
            s >> b; args_[2] = b;
            s >> b; args_[3] = b;
            s >> b; args_[4] = b;
        }
         else
        {
            s >> n; action_ = n;
            s >> n; args_[0] = n;
            args_[1] = args_[2] = args_[3] = args_[4] = 0;
        }
        
        s >> n; side1_ = n;
        s >> n; side2_ = n;
    }
}

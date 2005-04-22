// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef LINEDEF_H
#define LINEDEF_H

#include <QPoint>

class QDataStream;

namespace map
{
    //! This class represents a linedef
    class Linedef
    {
        public:
            //! Creates a linedef with some default values
            // TODO: Linedef( int v1, int v2 );
            
            //! Load a linedef from a QDataStream
            Linedef( QDataStream &s, bool isHexen );
            
            inline int v1() { return v1_; }
            inline int v2() { return v2_; }
  
        private:
            int v1_, v2_;
            struct
            {
                bool impassable     : 1;
                bool blocksmonsters : 1;
                bool twosided       : 1;
                bool upperunpegged  : 1;
                bool lowerunpegged  : 1;
                bool secret         : 1;
                bool blockssound    : 1;
                bool notonmap       : 1;
                bool alreadyonmap   : 1;
                bool repeatable     : 1;
                bool activation     : 3;
            } flags_;
            int action_;
            int args_[5];
            int side1_, side2_;
    };   
}

#endif

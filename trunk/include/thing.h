// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef THING_H
#define THING_H

#include <QPoint>

class QDataStream;

namespace gamemap
{
    //! This class represents a Thing
    class Thing
    {
        public:
            //! Creates a thing with some default values
            Thing( int x = 0, int y = 0, int type = 1 );
            
            //! Loads a thing from a QDataStream
            /*!
             * \param s The stream to read from
             * \param  isHexen Is this stream in Hexen format?
             */
            Thing( QDataStream &s, bool isHexen );
            
            //! Does this thing have some Hexen specific feature?
            bool isHexen() const;

            //! Does this thing have some BOOM specific feature?
            bool isBoom() const;
            
            inline int type() const { return type_; }
            inline QPoint pos() const { return QPoint( x_, y_ ); }

        private:
            int tid_;
            int x_, y_, z_;
            int angle_;
            int type_;

            struct
            {
                bool easy   : 1;
                bool normal : 1;
                bool hard   : 1;
                
                bool deaf   : 1;
                bool dormant: 1;
                
                bool fighter: 1;
                bool cleric : 1;
                bool mage   : 1;
                
                bool sp     : 1;
                bool coop   : 1;
                bool dm     : 1;
            } flags_;
            
            int special_;
            int arg1_, arg2_, arg3_, arg4_, arg5_;
    };
}

#endif

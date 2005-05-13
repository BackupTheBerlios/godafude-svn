// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef UNDOABLEACTION_H
#define UNDOABLEACTION_H

#include "gamemap.h"

typedef enum ActionType
{
    MOVEACTION
};

namespace actions
{
    class UndoableAction
    {
        public:
        
            UndoableAction( gamemap::Map *mymap )
            : mymap_(mymap) {}

            virtual ~UndoableAction() {};
            
            virtual const ActionType actionType() const = 0;

            virtual void undo() = 0;

        protected:
            gamemap::Map *mymap_;
    };
}

#endif

// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/
 
#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <map>
#include <set>

#include "gamemap.h"
#include "undoableaction.h"
#include "vertex.h"

namespace actions
{
    class MoveAction : public UndoableAction
    {
        public:
            MoveAction( std::set<int> selectedVertices, gamemap::Map *mymap );
            virtual const ActionType actionType() const;
            virtual void undo();

            inline std::map<int,gamemap::Vertex> &vertices()
            { return movedVertices_; }

            inline const gamemap::Vertex &vertex( int ID )
            { return movedVertices_[ID]; }

        private:
            //! Pairs: (vertexID, originalVertexPosition) for all vertices induced by selection_
            std::map<int,gamemap::Vertex> movedVertices_;
    };
}

#endif

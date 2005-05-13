// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/
 
 #include <vector>
 
 #include "moveaction.h"
 
 namespace actions
 {
    MoveAction::MoveAction( std::set<int> selectedVertices, gamemap::Map *mymap )
    : UndoableAction( mymap ),
      movedVertices_()
    {
        const std::vector<gamemap::Vertex>  &vertices = mymap->vertices();

        // Hm ... can this be done with copy()?
        std::set<int>::const_iterator it;
        for( it = selectedVertices.begin() ; it != selectedVertices.end() ; ++it)
          movedVertices_[*it] = vertices[*it];
    }
    
    const ActionType MoveAction::actionType() const
    {
        return MOVEACTION;
    }

    void MoveAction::undo()
    {
        std::map<int,gamemap::Vertex>::iterator it;

        for( it = movedVertices_.begin() ; it != movedVertices_.end() ; ++it )
        {
            mymap_->vertices()[it->first] = it->second;
        }
    }
 }

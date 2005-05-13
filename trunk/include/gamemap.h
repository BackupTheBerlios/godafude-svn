// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#ifndef MAP_H
#define MAP_H

#include <stack>
#include <vector>

#include "linedef.h"
#include "thing.h"
#include "vertex.h"
#include "wad.h"

// Forward declaration to avoid circular inclusion
namespace actions { class UndoableAction; }

//! Namespace for everything related to DOOM maps
namespace gamemap
{
    //! A container for everything you would want to know about a map
    class Map
    {
        public:
            //! Load a map
            /*!
             * \param d The Wad where the map is
             * \param l Wad iterator that points to a "MAPxx" or "ExMx" lump
             */
            Map( wad::Wad *w, wad::Wad::iterator &l );

            inline std::vector<Linedef> &linedefs() { return linedefs_; }
            inline std::vector<Thing> &things() { return things_; }
            inline std::vector<Vertex> &vertices() { return vertices_; }

            inline std::stack<actions::UndoableAction*> &undostack() { return undostack_; }

        private:
            std::vector<Linedef> linedefs_;
            std::vector<Thing> things_;
            std::vector<Vertex> vertices_;

            std::stack<actions::UndoableAction*> undostack_;
    };
}

#endif

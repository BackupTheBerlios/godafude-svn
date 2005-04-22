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

#include <vector>

#include "thing.h"
#include "vertex.h"
#include "wad.h"

//! Namespace for everything related to DOOM maps
namespace map
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

            //! A vector containing all things of this map
            std::vector<Thing> &things() { return things_; }
            std::vector<Vertex> &vertices() { return vertices_; }

        private:
            std::vector<Thing> things_;
            std::vector<Vertex> vertices_;
    };
}

#endif

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

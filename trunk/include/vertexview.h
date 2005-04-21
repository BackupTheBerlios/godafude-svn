#ifndef VERTEXVIEW_H
#define VERTEXVIEW_H

#include "mapview.h"

class QPaintEvent;

namespace Ui
{
    //! The Vertex view
    class VertexView: public MapView
    {
        public:
            VertexView( map::Map *myMap )
            : MapView( myMap ) {}

        protected:
            virtual void paintEvent( QPaintEvent * );            
    };
}

#endif

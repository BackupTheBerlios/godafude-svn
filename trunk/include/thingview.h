#ifndef THINGVIEW_H
#define THINGVIEW_H

#include "mapview.h"

//! All user interface classes are defined in this namespace
namespace Ui
{
    //! The thing view
    class ThingView: public MapView
    {
        public:
            ThingView( map::Map *myMap )
             : MapView( myMap ) {}

        protected:
            virtual void paintEvent( QPaintEvent* );
    };
}

#endif

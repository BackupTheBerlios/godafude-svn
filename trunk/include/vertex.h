#ifndef VERTEX_H
#define VERTEX_H

#include <QPoint>

class QDataStream;

namespace map
{
    //! This class represents a vertex
    class Vertex: public QPoint
    {
        public:
            Vertex( int x = 0, int y = 0 )
            : QPoint( x, y ) {}
        
            //! Load a vertex from a QDataStream
            Vertex( QDataStream &s );
    };
}

#endif

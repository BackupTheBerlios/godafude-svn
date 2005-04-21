#include <QDataStream>

#include "vertex.h"

namespace map
{
    Vertex::Vertex( QDataStream &s )
     : QPoint()
    {
        qint16 n;
        
        s >> n; rx() = n;
        s >> n; ry() = n;
    }
}
    
    

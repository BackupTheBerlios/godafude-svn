#include <QDataStream>
#include "thing.h"

namespace map
{
    Thing::Thing( int x, int y, int type )
    : tid_(0), x_(x), y_(y), z_(0), angle_(0), type_(type),
      special_(0), arg1_(0), arg2_(0), arg3_(0), arg4_(0), arg5_(0)
    {
        // How can I set these in the constructor list?
        flags_.easy = flags_.normal = flags_.hard = 1,
        flags_.deaf = flags_.dormant = 0,
        flags_.fighter = flags_.cleric = flags_.mage = 1,
        flags_.sp = flags_.coop = flags_.dm = 1;
    }
    
    Thing::Thing( QDataStream &s, bool isHexen )
    {
        qint16 n;

        if( isHexen ) { s >> n; tid_ = n; } else tid_ = 0;
        s >> n; x_ = n;
        s >> n; y_ = n;
        if( isHexen ) { s >> n; z_ = n; } else z_ = 0;
        s >> n; angle_ = n;
        s >> n; type_ = n;

        s >> n;

        flags_.easy   = n & 0x0001 == 1;
        flags_.normal = n & 0x0002 == 1;
        flags_.hard   = n & 0x0004 == 1;
        
        flags_.deaf   = n & 0x0008 == 1;
        flags_.dormant = isHexen?(n & 0x0010 == 1):0;

        flags_.fighter = isHexen?(n & 0x0020 == 1):1;
        flags_.cleric  = isHexen?(n & 0x0040 == 1):1;
        flags_.mage    = isHexen?(n & 0x0080 == 1):1;
        
        flags_.sp   = n & (isHexen?0x0100:0x0010) == 1;
        flags_.coop = n & (isHexen?0x0200:0x0040) == 1;
        flags_.dm   = n & (isHexen?0x0400:0x0020) == 1;
        
        if( !isHexen )
        {
            flags_.sp   = !flags_.sp;
            flags_.coop = !flags_.coop;
            flags_.dm   = !flags_.dm;
            
            special_ = arg1_ = arg2_ = arg3_ = arg4_ = arg5_ = 0;
            
        }
         else
        {
            quint8 c;
            
            s >> c; special_ = c;
            s >> c; arg1_ = c;
            s >> c; arg2_ = c;
            s >> c; arg3_ = c;
            s >> c; arg4_ = c;
            s >> c; arg5_ = c;            
        }
    }
    
    bool Thing::isHexen() const
    {
        return !
            (tid_ == 0 && z_ == 0 &&
            flags_.fighter == 0 && flags_.cleric == 0 && flags_.mage == 0 &&
            special_ == 0 && arg1_ == 0 && arg2_ == 0 && arg3_ == 0 &&
            arg4_ == 0 && arg5_ == 0);
    }
    
    bool Thing::isBoom() const
    {
        return !(flags_.sp != flags_.coop && flags_.coop == flags_.dm );
    }
}

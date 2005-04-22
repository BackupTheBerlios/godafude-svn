// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

#include <QDataStream>
#include <QFile>
#include <QIODevice>
#include "wad.h"

using std::string;

namespace wad
{
    // Class Lump
    Lump::Lump() : ofs_(0), len_(0), name_("") {};

    Lump::Lump( quint32 ofs, quint32 len, const string &name )
     : ofs_(ofs), len_(len), name_(name) {}

    // Class Wad
    Wad::Wad( QIODevice *source )
    : source_(source),
      stream_(source),
      isiwad_(false),
      ishexen_(unknown)
    {
        try
        {
	    // We need the source to be readable and
	    // non-sequential (so we can use seek() ) 
            if( !source_->open( QIODevice::ReadOnly ) ||
                source_->isSequential() )
              throw IOError();

            QDataStream &s = stream_;
            s.setByteOrder( QDataStream::LittleEndian );
        
            // Read in and check the header
            quint32 d;
            s >> d;
            if( d == 0x44415749 ) isiwad_ = true;
             else if( d != 0x44415750 ) throw BadFormat();
         
             // The following two statements might be conversions,
             // if unsigned != quint32
             s >> d; numberOfLumps_ = d;
             s >> d; directoryOffset_ = d;
         
             // Seek to WAD directory
             if( ! source_->seek( directoryOffset_ ) )
               throw BadFormat();

            // Load the WAD directory
            for( unsigned i = 0 ; i < numberOfLumps_ ; ++i )
            {
                quint32 ofs, len;
                char name[9];
    
                s >> ofs >> len;
                s.readRawData( name, 8 );
                name[8]='\0';

                dir_.push_back( Lump( ofs, len, name ) );
             }
        }
         catch(...)
        {
	    // Avoids a memory leak if the constructor throws
            delete( source );
            throw;
        }
    }
    
    Wad::~Wad()
    {
        delete source_;
    }
    
    bool Wad::isHexen() const
    {
        if( ishexen_ == unknown )
         ishexen_ = find( "MAPINFO")!=end()?yes:no;
        return ishexen_ == yes;
    }
    
    Wad::const_iterator Wad::find( const string &lumpName ) const
    {
        const_iterator it = dir_.begin();
        
        for( ; it != dir_.end() && (*it).name_ != lumpName ; ++it );
        
        return const_iterator(it);
    }
    
    Wad::iterator Wad::find( const string &lumpName )
    {
        iterator it = dir_.begin();
        
        for( ; it != dir_.end() && (*it).name_ != lumpName ; ++it );
        
        return iterator(it);
    }
    
    void Wad::seek( const Lump &l )
    {
        if( !source_->seek(l.ofs_) ) throw IOError();
    }
    
    // Class File
    File::File( const QString &filename )
     : Wad( new QFile( filename ) ),
       filename_( filename )
    {
    }
    
    const QString &File::name() const
    {
        return filename_;
    }
}

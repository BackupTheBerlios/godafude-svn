// Godafude - A Map Editor for DOOM 
// Copyright (c) 2005 Sascha Mueller <dev@saschamueller.com>

/******************************************************************
 * This program is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License    *
 * as published by the Free Software Foundation; either version 2 *
 * of the License, or (at your option) any later version.         *
 ******************************************************************/

/* Nothing useful here yet ... just tests */

#include <iostream>

#include <QApplication>
#include <QFile>

#include "gamemap.h"
#include "linedefview.h"
//#include "vertexview.h"
#include "wad.h"

using namespace std;

class mapnotfound {};

gamemap::Map getMap( const char *filename, const char *mapname )
{
    wad::File f( filename );

    cout << "Number of lumps: " << f.numberOfLumps() << endl;
    cout << "The file is " << (f.isHexen()?"":"not ") << "Hexen format\n";
    
    wad::File::iterator it = f.find( mapname );
    
    if( it == f.end() ) throw mapnotfound();
    
    return gamemap::Map( &f, it );
}

int main( int argc, char **argv )
{
    if( argc < 3 )
    {
        cerr << "Must supply a 1. WAD file and 2. a MAP number!\n"
                "like \"godafude cool.wad MAP01\"" << endl;
        return 0;
    }

    cout << "GODAFUDE 1.0 - Copyright(c) 2005 by Sascha Mueller\n"
#ifndef NDEBUG
         << "This is no release version!\n"
#endif
         << "Opening WAD file " << argv[1] << endl;
    
    try
    {
        gamemap::Map m = getMap( argv[1], argv[2] );
        QApplication app( argc, argv );

        Ui::LinedefView vv(&m);

        vv.show();

        app.exec();
    }
     catch( wad::File::IOError )
    {
        cerr << "IO Error" << endl; abort();
    }
     catch( wad::File::BadFormat )
    {
        cerr << "Bad Format" << endl; abort();
    }
     catch( mapnotfound )
    {
        cerr << "Map " << argv[2] << " not found in " << argv[1] << endl;
        abort();
    }
}

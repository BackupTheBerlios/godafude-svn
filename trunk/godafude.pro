CONFIG += qt warn_on debug exceptions stl

HEADERS = include/linedef.h \
          include/map.h include/mapview.h \
          include/thing.h include/thingview.h \
          include/vertex.h include/vertexview.h \
          include/wad.h

SOURCES = src/main.cpp \
          src/linedef.cpp \
          src/map.cpp src/mapview.cpp \
          src/thing.cpp src/thingview.cpp \
          src/vertex.cpp src/vertexview.cpp \
          src/wad.cpp

INCLUDEPATH = include
OBJECTS_DIR = obj
MOC_DIR = obj

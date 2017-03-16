CONFIG  += qt debug

HEADERS += Cache.h
HEADERS += MainMemory.h
HEADERS += MemoryInterface.h
HEADERS += QueryResult.h
HEADERS += Register.h
HEADERS += ../architecture.h
HEADERS += serialization.h

SOURCES += MainMemory.cpp
SOURCES += Cache.cpp
SOURCES += QueryResult.cpp
SOURCES += Register.cpp
SOURCES += serialization.cpp
SOURCES += MemoryInterface.cpp
SOURCES += test.cpp

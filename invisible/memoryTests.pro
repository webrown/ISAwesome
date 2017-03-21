CONFIG  += qt debug c++11

HEADERS += ../src/memory/Cache.h
HEADERS += ../src/memory/MainMemory.h
HEADERS += ../src/memory/MemoryInterface.h
HEADERS += ../src/memory/QueryResult.h
HEADERS += ../src/memory/Register.h
HEADERS += ../src/memory/../architecture.h
HEADERS += ../src/memory/serialization.h

SOURCES += ../src/memory/MainMemory.cpp
SOURCES += ../src/memory/Cache.cpp
SOURCES += ../src/memory/QueryResult.cpp
SOURCES += ../src/memory/Register.cpp
SOURCES += ../src/memory/serialization.cpp
SOURCES += ../src/memory/MemoryInterface.cpp
SOURCES += memoryTests.cpp

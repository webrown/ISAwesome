CONFIG  += qt debug c++11


#HEADERS += PipelineGlobals.h
#HEADERS += Pipeline.h
HEADERS += ../src/pipeline/Baseline.h
HEADERS += ../src/Utility.h
HEADERS += ../src/Utility.h
HEADERS += ../src/pipeline/Banana.h
#HEADERS += StageData.h

#SOURCES += Pipeline.cpp
#SOURCES += StageData.cpp
SOURCES += pipelineTests.cpp
SOURCES += ../src/pipeline/Baseline.cpp
SOURCES += ../src/Utility.cpp
SOURCES += ../src/memory/MemoryStructure.cpp
SOURCES += ../src/memory/MemoryInterface.cpp
SOURCES += ../src/memory/Register.cpp
SOURCES += ../src/memory/QueryResult.cpp
SOURCES += ../src/memory/MainMemory.cpp
SOURCES += ../src/memory/Cache.cpp
SOURCES += ../src/memory/serialization.cpp


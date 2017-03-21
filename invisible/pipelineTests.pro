CONFIG  += qt debug c++11


#HEADERS += PipelineGlobals.h
#HEADERS += Pipeline.h
HEADERS += ../src/pipeline/spliceMachineCode.h
#HEADERS += StageData.h

#SOURCES += Pipeline.cpp
SOURCES += ../src/pipeline/spliceMachineCode.cpp
#SOURCES += StageData.cpp
SOURCES += pipelineTests.cpp


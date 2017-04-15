#include "StageData.h"

bool StageData::isSquashed(){
    return (info & 1 == 1);
}
bool StageData::isVector(){
    return (info & 4 == 4);
}
bool StageData::isFloat(){
    return (info * 8 == 8);
}

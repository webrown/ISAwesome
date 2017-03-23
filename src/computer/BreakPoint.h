#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#include <QVariant>

enum BreakPoint{
    SKIP, ONCE, EVERY
};

// class BreakPoint{
//     public:
//         BreakPointType type;
//         uint address;
//         BreakPoint(uint address, BreakPointType type){
//             this->type = type;
//             this->address = address;
//         }
//         bool operator<(const BreakPoint& right) const
//         {
//             return address < right.address;
//         }
//         bool operator==(const BreakPoint &right) const
//         {
//             return address == right.address;
//         }
// };
/*  */
#endif

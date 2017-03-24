#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#include <QVariant>

namespace BreakPoint{
    enum BreakPoint{
        NONE = 0, SKIP = 1, SKIP_ALL = 2, BREAK = 3, BREAK_ALL =4
    };
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

#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <QVector>

/* De facto class that contains any information about assembled code
 * User can assume that nInstructions == nAddresses; in fact they are corresponding to one another.
 */
class Assembly {
    public:
        int nInstructions;
        uint* instructions;
        int nAddresses;
        uint* addresses;

};

#endif

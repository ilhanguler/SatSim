#ifndef ELECTROMAGNETICS_H
#define ELECTROMAGNETICS_H

#include "base_definitions.h"

enum CEMPATTERN{
    SPHERE,
    PLANE,
    FOCUSED
};

class cem{
public:
    cem(CEMPATTERN pattern, PreciseVector3D sourcePos, PreciseVector3D focusPos,
        PreciseVector3D propagation);

    CEMPATTERN pattern;

    PreciseVector3D sourcePos;
    PreciseVector3D focusPos;
    PreciseVector3D propagation;
};

#endif // ELECTROMAGNETICS_H

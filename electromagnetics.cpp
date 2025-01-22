#include "electromagnetics.h"


cem::cem(CEMPATTERN pattern, PreciseVector3D sourcePos, PreciseVector3D focusPos, PreciseVector3D propagation)
    : pattern(pattern), sourcePos(std::move(sourcePos)),
    focusPos(std::move(focusPos)), propagation(std::move(propagation)) {}

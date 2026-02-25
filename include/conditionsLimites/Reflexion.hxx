#ifndef REFLEXION_HXX
#define REFLEXION_HXX

#include "ConditionLimite.hxx"

class Reflexion : public ConditionLimite {
public:
    void appliquer(Particule& p, Univers& u) const override;
    bool estHorsLimites(const Particule& p, const Univers& u) const override;
};

#endif

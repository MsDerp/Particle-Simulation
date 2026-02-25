#ifndef ABSORPTION_HXX
#define ABSORPTION_HXX

#include "ConditionLimite.hxx"

class Absorption : public ConditionLimite {
public:
    void appliquer(Particule& p, Univers& u) const override;
    bool estHorsLimites(const Particule& p, const Univers& u) const override;
};

#endif

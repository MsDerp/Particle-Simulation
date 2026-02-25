#ifndef PERIODIQUE_HXX
#define PERIODIQUE_HXX

#include "ConditionLimite.hxx"

class Periodique : public ConditionLimite {
public:
    void appliquer(Particule& p, Univers& u) const override;
    bool estHorsLimites(const Particule& p, const Univers& u) const override;
};

#endif

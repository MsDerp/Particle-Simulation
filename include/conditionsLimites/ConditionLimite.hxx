#ifndef CONDITION_LIMITE_HXX
#define CONDITION_LIMITE_HXX

class Univers;
class Particule;

class ConditionLimite {
public:
    virtual ~ConditionLimite() = default;

    virtual void appliquer(Particule& p, Univers& u) const = 0;

    virtual bool estHorsLimites(const Particule& p, const Univers& u) const = 0;
};

#endif

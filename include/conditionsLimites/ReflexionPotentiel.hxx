    #ifndef REFLEXION_POTENTIEL_HXX
    #define REFLEXION_POTENTIEL_HXX

    #include "ConditionLimite.hxx"

    class ReflexionPotentiel : public ConditionLimite {
    public:
        ReflexionPotentiel(double epsilon, double sigma);

        void appliquer(Particule& p, Univers& u) const override;
        bool estHorsLimites(const Particule& p, const Univers& u) const override;

    private:
        double epsilon;
        double sigma;
        double rcut;
    };

    #endif // REFLEXION_POTENTIEL_HXX

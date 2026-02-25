#ifndef UNIVERS_HXX
#define UNIVERS_HXX

#include <vector>
#include <iostream>
#include "Particule.hxx"
#include "Cellule.hxx"
#include "conditionsLimites/ReflexionPotentiel.hxx"

class Univers {
public:
// Dans Univers.hxx
    Univers(int d, int n, double rcut, const std::vector<double>& Ld, double epsilon = 1.0, double sigma = 1.0);
    Univers(int d, int n);
    ~Univers();

    void add(const Particule& p);  // <-- mise à jour ici

    int getNumber() const;
    int getParticlesNumber() const;
    void displayInfo(int step) const;
    void updateForces(double eps, double sigma);
    void calculateLennardJonesForce(Particule& p1, Particule& p2, double epsilon, double sigma);
    void generateCubicParticles();
    void updateVelocities(double deltaTime);
    void updatePositions(double deltaTime);
    void genererVTK(int step,const std::string& directoryName) const;
    void mettreAJourCellules();
    void initialiserGrille();
    void initialiserVoisines();
    void initialiserVoisines1D();
    void initialiserVoisines2D();
    void initialiserVoisines3D();

    void applyStormerVerlet(double deltaTime, int steps, double eps, double sigma,const std::string& directoryName,double Ec_cible=0);

    int getDimension(int i) const;
    void supprimerParticule(const Particule& p);
    int getDim() const;

    const std::vector<Particule>& getParticules() const;
    std::vector<Particule>& getParticules();

    void sauvegarderAnciennesForces();
    void regulariserEnergieCinetique(double Ec_cible);




private:
    int dim;
    int number;
    int rcut;
    std::vector<Particule> particules;
    std::vector<Cellule> cellules;
    int taillesGrilles[3] = { 100,100,100 };  // Exemple
    double tailleCellule;
    double rayonDeCoupure;
    ReflexionPotentiel conditionLim;

    int indexCellule(const Vecteur& pos) const;
    double constanteGravite = 9.81; // constante gravitationnelle
};

#endif // UNIVERS_HXX

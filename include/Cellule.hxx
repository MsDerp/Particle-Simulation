#ifndef CELLULE_H
#define CELLULE_H

#include <vector>
#include "Particule.hxx"

class Cellule {
private:
    std::vector<Particule*> particules;
    std::vector<Cellule*> voisines;

public:
    Cellule();

    void ajouterParticule(Particule* p);
    void ajouterVoisine(Cellule* c);

    void clearParticules(); // Réinitialise les particules de la cellule

    // Accès modifiable aux particules
    std::vector<Particule*>& getParticules();

    // Accès en lecture seule aux particules
    const std::vector<Particule*>& getParticules() const;

    // Accès modifiable aux cellules voisines
    std::vector<Cellule*>& getVoisines();

    // Accès en lecture seule aux cellules voisines
    const std::vector<Cellule*>& getVoisines() const;
};

#endif // CELLULE_H

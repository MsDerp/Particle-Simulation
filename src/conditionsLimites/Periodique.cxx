/**
 * @file Periodique.cxx
 * @brief Implémentation de la condition aux limites périodique.
 */

#include "conditionsLimites/Periodique.hxx"
#include "Univers.hxx"
#include "Particule.hxx"

/**
 * @brief Applique la condition périodique : rebouclage des coordonnées.
 * 
 * Si une particule dépasse une borne du domaine, elle est translatée
 * pour réapparaître de l'autre côté selon une topologie de tore.
 *
 * @param p Particule à repositionner.
 * @param u Univers contenant les dimensions du domaine.
 */
void Periodique::appliquer(Particule& p, Univers& u) const {
    auto pos = p.getPosition();

    for (int i = 0; i < u.getDim(); ++i) {
        double lim = u.getDimension(i);
        if (pos[i] < 0)      pos[i] += lim;
        else if (pos[i] >= lim) pos[i] -= lim;
    }

    p.setPosition(pos);
}

/**
 * @brief Vérifie si la particule est en dehors du domaine (avant rebouclage).
 * 
 * Cette vérification sert à déterminer si le rebouclage est nécessaire.
 *
 * @param p Particule à tester.
 * @param u Univers contenant les dimensions du domaine.
 * @return true si la particule est en dehors d’au moins une dimension.
 */
bool Periodique::estHorsLimites(const Particule& p, const Univers& u) const {
    auto pos = p.getPosition();
    for (int i = 0; i < u.getDim(); ++i) {
        if (pos[i] < 0 || pos[i] >= u.getDimension(i)) return true;
    }
    return false;
}

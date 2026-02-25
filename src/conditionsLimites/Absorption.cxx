/**
 * @file Absorption.cxx
 * @brief Implémentation de la condition aux limites par absorption.
 */

#include "conditionsLimites/Absorption.hxx"
#include "Univers.hxx"
#include "Particule.hxx"

/**
 * @brief Applique la condition d’absorption à une particule.
 * 
 * Supprime définitivement la particule du système lorsqu’elle sort du domaine.
 *
 * @param p Particule concernée.
 * @param u Univers dans lequel la particule évolue.
 */
void Absorption::appliquer(Particule& p, Univers& u) const {
    u.supprimerParticule(p);
}

/**
 * @brief Vérifie si la particule se trouve en dehors des limites du domaine.
 * 
 * Une particule est considérée hors limites si elle dépasse les bornes dans au moins une dimension.
 *
 * @param p Particule à tester.
 * @param u Univers délimitant l’espace de simulation.
 * @return true si la particule est hors du domaine, false sinon.
 */
bool Absorption::estHorsLimites(const Particule& p, const Univers& u) const {
    auto pos = p.getPosition();
    for (int i = 0; i < u.getDim(); ++i) {
        if (pos[i] < 0 || pos[i] >= u.getDimension(i))
            return true;
    }
    return false;
}

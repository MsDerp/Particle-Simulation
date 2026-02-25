/**
 * @file Reflexion.cxx
 * @brief Implémentation de la condition aux limites par réflexion élastique.
 */

#include "conditionsLimites/Reflexion.hxx"
#include "Univers.hxx"
#include "Particule.hxx"

/**
 * @brief Applique une réflexion élastique lorsque la particule sort du domaine.
 * 
 * Si une composante de la position dépasse les bornes du domaine dans une dimension donnée,
 * elle est reflétée de manière symétrique et la composante de la vitesse est inversée.
 *
 * @param p Particule à modifier.
 * @param espace Univers dans lequel évolue la particule.
 */
void Reflexion::appliquer(Particule& p, Univers& espace) const {
    Vecteur localisation = p.getPosition();
    Vecteur impulsion    = p.getVelocity();

    for (int axe = 0; axe < espace.getDim(); ++axe) {
        double bord = espace.getDimension(axe);

        if (localisation[axe] < 0.0) {
            localisation[axe] = -localisation[axe];
            impulsion[axe]    = -impulsion[axe];
        }
        else if (localisation[axe] >= bord) {
            localisation[axe] = 2.0 * bord - localisation[axe];
            impulsion[axe]    = -impulsion[axe];
        }
    }

    p.setPosition(localisation);
    p.setVelocity(impulsion);
}

/**
 * @brief Vérifie si une particule est en dehors du domaine défini.
 * 
 * Cette vérification est faite composante par composante dans chaque dimension.
 *
 * @param p Particule à tester.
 * @param espace Univers contenant les dimensions du domaine.
 * @return true si la particule est hors limites.
 */
bool Reflexion::estHorsLimites(const Particule& p, const Univers& espace) const {
    const Vecteur& localisation = p.getPosition();

    for (int axe = 0; axe < espace.getDim(); ++axe) {
        double ext = espace.getDimension(axe);
        if (!(localisation[axe] >= 0.0 && localisation[axe] < ext)) {
            return true;
        }
    }

    return false;
}

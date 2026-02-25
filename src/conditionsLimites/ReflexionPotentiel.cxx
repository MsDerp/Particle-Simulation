/**
 * @file ReflexionPotentiel.cxx
 * @brief Implémentation de la condition aux limites par potentiel de réflexion (Lennard-Jones inverse).
 */

#include "conditionsLimites/ReflexionPotentiel.hxx"
#include "Univers.hxx"
#include "Particule.hxx"
#include <cmath>

/**
 * @brief Constructeur du potentiel de réflexion basé sur Lennard-Jones tronqué.
 * 
 * @param eps Profondeur du puits de potentiel.
 * @param sig Distance caractéristique du potentiel.
 */
ReflexionPotentiel::ReflexionPotentiel(double eps, double sig)
    : epsilon(eps), sigma(sig), rcut(std::pow(2.0, 1.0 / 6.0) * sig) {}
    
/**
 * @brief Vérifie si une particule est proche d’un mur (critère de distance rcut).
 * 
 * @param p Particule à vérifier.
 * @param u Univers dans lequel se trouve la particule.
 * @return true si la particule est proche d'un mur.
 */
bool ReflexionPotentiel::estHorsLimites(const Particule& p, const Univers& u) const {
    const auto pos = p.getPosition();
    for (int k = 0; k < u.getDim(); ++k) {
        double L = u.getDimension(k);
        if (pos[k] < rcut || pos[k] > L - rcut)
            return true;
    }
    return false;
}

/**
 * @brief Applique une force répulsive (type Lennard-Jones) pour simuler une réflexion douce.
 * 
 * Si la particule est proche d’un mur (gauche ou droite dans chaque dimension),
 * une force de répulsion est appliquée proportionnellement à la distance au mur.
 * 
 * @param particule Particule à laquelle appliquer la force.
 * @param espace Univers dans lequel évolue la particule.
 */
void ReflexionPotentiel::appliquer(Particule& particule, Univers& espace) const {
    Vecteur position = particule.getPosition();
    Vecteur force = particule.getForce();

    for (int axe = 0; axe < espace.getDim(); ++axe) {
        double L = espace.getDimension(axe);

        // Mur gauche
        if (position[axe] < rcut && position[axe] > 1e-9) {
            double r = position[axe];
            double inv_r = sigma / r;
            double inv_r6 = std::pow(inv_r, 6);
            double f_val = 24 * epsilon * (2 * inv_r6 * inv_r6 - inv_r6) / r;
            force[axe] += f_val;
        }

        // Mur droit
        double d = L - position[axe];
        if (d < rcut && d > 1e-9) {
            double inv_r = sigma / d;
            double inv_r6 = std::pow(inv_r, 6);
            double f_val = 24 * epsilon * (2 * inv_r6 * inv_r6 - inv_r6) / d;
            force[axe] -= f_val;
        }
    }

    particule.setForce(force);
}

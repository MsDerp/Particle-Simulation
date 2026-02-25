/**
 * @file ConditionLimite.hxx
 * @brief Définition de l'interface abstraite pour les conditions aux limites.
 */

#ifndef CONDITION_LIMITE_HXX
#define CONDITION_LIMITE_HXX

#include "Particule.hxx"
#include "Univers.hxx"

/**
 * @class ConditionLimite
 * @brief Classe abstraite représentant une condition aux limites.
 *
 * Les classes dérivées implémentent des comportements spécifiques tels que :
 * - Réflexion (rebond),
 * - Absorption (suppression),
 * - Périodique (rebouclage),
 * - Potentiel de réflexion (Lennard-Jones).
 */
class ConditionLimite {
public:
    /// Destructeur virtuel pour permettre un polymorphisme propre
    virtual ~ConditionLimite() = default;

    /**
     * @brief Applique la condition aux limites à une particule.
     *
     * Cette méthode est appelée lorsque la particule franchit les bornes du domaine.
     * Elle modifie potentiellement la position, la vitesse, ou supprime la particule.
     *
     * @param p Référence vers la particule à traiter.
     * @param dim Dimension du domaine.
     * @param taillesGrilles Tableau des tailles de grille dans chaque dimension.
     * @param tailleCellule Taille d’une cellule spatiale (pour éventuel traitement spatial).
     */
    virtual void appliquer(Particule& p, int dim, const int taillesGrilles[3], double tailleCellule) const = 0;

    /**
     * @brief Vérifie si une particule est hors des bornes du domaine.
     *
     * Utilisé avant d’appliquer la condition aux limites.
     *
     * @param p Référence vers la particule à tester.
     * @param u Univers contenant les dimensions limites.
     * @return true si la particule est hors domaine, false sinon.
     */
    virtual bool estHorsLimites(const Particule& p, const Univers& u) const = 0;
};

#endif // CONDITION_LIMITE_HXX

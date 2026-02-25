/**
 * @file solar_simulation.cxx
 * @brief Simulation gravitationnelle d’un petit système solaire avec méthode de Stormer-Verlet.
 */

#include "Particule.hxx"
#include "Vecteur.hxx"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

/**
 * @brief Réinitialise les forces et recalcule les interactions gravitationnelles entre toutes les particules.
 *
 * Cette fonction parcourt toutes les paires distinctes de particules pour appliquer la loi de Newton
 * de la gravitation.
 *
 * @param entites Référence vers le vecteur de particules du système.
 */
void recalculerInteractions(std::vector<Particule>& entites) {
    for (auto& e : entites) {
        e.setForce(Vecteur(0.0, 0.0, 0.0));
    }

    std::size_t total = entites.size();
    for (std::size_t a = 0; a < total; ++a) {
        for (std::size_t b = a + 1; b < total; ++b) {
            entites[a].calculateGravitationalForce(entites[b]);
        }
    }
}

/**
 * @brief Point d’entrée de la simulation gravitationnelle d’un mini système solaire.
 *
 * Cette fonction simule les trajectoires du Soleil, de la Terre, de Jupiter et de la comète de Halley
 * sur une période donnée en utilisant l'intégration de Stormer-Verlet.
 *
 * @return 0 en cas de succès.
 */
int main()
{
    std::vector<Particule> corps;
    corps.reserve(4);

    // Création des corps célestes
    corps.emplace_back(0, "Soleil",   1.0,       Vecteur(0, 0, 0),        Vecteur(0, 0, 0), Vecteur(0, 0, 0));
    corps.emplace_back(1, "Terre",    3.0e-6,    Vecteur(-1.0, 0, 0),     Vecteur(0, 0, 0), Vecteur(0, 1.0, 0));
    corps.emplace_back(2, "Jupiter",  9.55e-4,   Vecteur(-0.425, 0, 0),   Vecteur(0, 0, 0), Vecteur(0, 5.36, 0));
    corps.emplace_back(3, "Halley",   1.0e-14,   Vecteur(0, 0.0296, 0),   Vecteur(0, 0, 0), Vecteur(34.75, 0, 0));

    const double pasTemps = 0.015;        ///< Pas de temps pour l'intégration
    const double tempsFinal = 468.5;      ///< Durée totale de la simulation
    const int nombreEtapes = static_cast<int>(tempsFinal / pasTemps); ///< Nombre d'étapes de simulation

    // Fichier de sortie pour les trajectoires
    std::ofstream fichierTrajectoire("trajectory.txt");
    fichierTrajectoire << std::setprecision(10);

    // Initialiser les forces
    recalculerInteractions(corps);

    // Boucle principale de simulation
    for (int etape = 0; etape <= nombreEtapes; ++etape) {

        // Étape 0 : enregistrer les positions actuelles
        for (const auto& ent : corps)
            fichierTrajectoire << ent.getPosition().getxCoordinate() << ' '
                               << ent.getPosition().getyCoordinate() << ' ';
        fichierTrajectoire << '\n';

        // Étape 1 : mettre à jour les positions
        for (auto& ent : corps) {
            Vecteur acceleration = (1.0 / ent.getMass()) * ent.getForce();
            Vecteur posSuivante = ent.getPosition() +
                                  (ent.getVelocity() + 0.5 * pasTemps * acceleration) * pasTemps;
            ent.setPosition(posSuivante);
            ent.setOldForce(ent.getForce());
        }

        // Étape 2 : recalcul des forces après déplacement
        recalculerInteractions(corps);

        // Étape 3 : mise à jour des vitesses
        for (auto& ent : corps) {
            Vecteur accActuelle = (1.0 / ent.getMass()) * ent.getForce();
            Vecteur accPrecedente = (1.0 / ent.getMass()) * ent.getOldForce();
            Vecteur vitesseCorrigee = ent.getVelocity() + 0.5 * pasTemps * (accActuelle + accPrecedente);
            ent.setVelocity(vitesseCorrigee);
        }
    }

    std::cout << "Trajectoire enregistrée dans trajectory.txt\n";
    return 0;
}

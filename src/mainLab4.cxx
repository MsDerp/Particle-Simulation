/**
 * @file main.cxx
 * @brief Simulation de collision entre deux blocs de particules avec conditions aux limites.
 */

#include <cmath>
#include "Univers.hxx"
#include "Particule.hxx"
#include "Vecteur.hxx"

/**
 * @brief Initialise la scène avec deux groupes de particules : un bloc fixe en bas et un bloc mobile au-dessus.
 *
 * Ce scénario simule une collision verticale entre un bloc mobile descendant à grande vitesse
 * et une base de particules statiques.
 *
 * @param monde Référence vers l'objet Univers dans lequel les particules sont ajoutées.
 */
void initialiserSceneCollision(Univers& monde) {
    double espacement = std::pow(2.0, 1.0 / 6.0); ///< Espacement optimal pour contact Lennard-Jones

    int largeurBlocMobile = 40, hauteurBlocMobile = 40;
    int largeurBase = 160, hauteurBase = 40;

    Vecteur vitesseMobile(0.0, -10.0, 0.0);  ///< Vitesse initiale du bloc mobile (descend)
    Vecteur vitesseFixe(0.0, 0.0, 0.0);      ///< Vitesse initiale du bloc fixe (immobile)

    int identifiant = 0;

    // Création du socle (rectangle fixe bleu)
    for (int col = 0; col < largeurBase; ++col) {
        for (int ligne = 0; ligne < hauteurBase; ++ligne) {
            Vecteur coord((col + 60) * espacement, ligne * espacement, 0.0);
            monde.add(Particule(identifiant++, "fond", 1.0, vitesseFixe, Vecteur(0, 0, 0), coord));
        }
    }

    // Création du bloc mobile (carré rouge centré horizontalement au-dessus)
    int centrageX = (largeurBase - largeurBlocMobile) / 2;
    for (int u = 0; u < largeurBlocMobile; ++u) {
        for (int v = 0; v < hauteurBlocMobile; ++v) {
            Vecteur coord((u + centrageX + 60) * espacement, (v + hauteurBase + 5) * espacement, 0.0);
            monde.add(Particule(identifiant++, "mobile", 1.0, vitesseMobile, Vecteur(0, 0, 0), coord));
        }
    }

    monde.initialiserGrille();  ///< Initialise la structure de cellules pour interactions optimisées
}

/**
 * @brief Fonction principale de la simulation.
 *
 * Crée un univers en 2D, initialise une scène de collision, puis exécute une simulation
 * numérique en utilisant l'algorithme de Stormer-Verlet avec régularisation d’énergie.
 *
 * @return 0 si l’exécution s’est bien passée.
 */
int main() {
    int dim = 2;
    double L2 = 40;
    double L1 = 250;

    double eps = 5.0;
    double sigma = 1.0;
    double rcut = 2.5 * sigma;

    std::vector<double> Ld = {L1, L2};

    Univers univers(dim, 0, rcut, Ld);

    initialiserSceneCollision(univers);

    double deltaTime = 0.005;
    int steps = static_cast<int>(15 / deltaTime);

    univers.applyStormerVerlet(deltaTime, steps, eps, sigma, "mainLab4");
    return 0;
}

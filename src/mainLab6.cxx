#include <cmath>
#include "Univers.hxx"      
#include "Particule.hxx"
#include "Vecteur.hxx"

// Déclaration de la fonction d'initialisation
void initialiserSceneCollision(Univers& univers) {
    double d = std::pow(2.0, 1.0 / 6.0);
    int nx2 = 215, ny2 = 80;  // Rectangle bas

    Vecteur velocityCercle(0.0, -10.0, 0.0);
    Vecteur velocityRectangle(0.0, 0.0, 0.0);

    int id = 0;

    // --- Rectangle (bas) : ≈ 17 200 particules ---
    for (int i = 0; i < nx2; ++i) {
        for (int j = 0; j < ny2; ++j) {
            Vecteur pos((i + 20) * d, j * d, 0);
            univers.add(Particule(id++, "blue", 1.0, velocityRectangle, Vecteur(0, 0, 0), pos));
        }
    }

    // --- Cercle (haut, espacé, petit) : 395 particules ---
    double centre_x = 125.0;
    double centre_y = 140.0;
    double rayon = 17.0;                 // rayon raisonnable
    double pas = 1.5 * d;                // espacement aéré
    int compteur = 0;
    const int N_cercle = 395;

    for (double x = -rayon; x <= rayon; x += pas) {
        for (double y = -rayon; y <= rayon; y += pas) {
            if (x * x + y * y <= rayon * rayon) {
                Vecteur pos(centre_x + x, centre_y + y, 0.0);
                univers.add(Particule(id++, "red", 1.0, velocityCercle, Vecteur(0, 0, 0), pos));
                compteur++;
                if (compteur >= N_cercle) break;
            }
        }
        if (compteur >= N_cercle) break;
    }

    univers.initialiserGrille();
}


int main() {
    int dim = 2;

    // --- Paramètres du domaine ---
    double L1 = 250.0;
    double L2 = 180.0;
    std::vector<double> Ld = {L1, L2};

    // --- Paramètres physiques ---
    double sigma = 1.0;
    double epsilon = 1.0;
    double rcut = 2.5 * sigma;

    double deltaTime = 0.005;
    double T = 29.5;
    int steps = static_cast<int>(T / deltaTime);  // 59000 étapes

    // --- Energie cinétique cible ---
    int N1 = 395;
    int N2 = 17227;
    double Ec_cible = 0.005 * (N1 + N2);

    // --- Création de l'univers ---
    Univers univers(dim, 0, rcut, Ld, epsilon, sigma);

    // --- Initialisation de la scène ---
    initialiserSceneCollision(univers);

    const std::string& directoryName = "mainLab6";

    // --- Lancement de la simulation ---
    univers.applyStormerVerlet(deltaTime, steps, epsilon, sigma,directoryName);

    return 0;
}

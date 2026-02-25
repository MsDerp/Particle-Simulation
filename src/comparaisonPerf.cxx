/**
 * @file benchmark_containers.cxx
 * @brief Évalue les temps de remplissage de différents conteneurs STL avec des objets Particule.
 */

#include <chrono>
#include <deque>
#include <iostream>
#include <iomanip>
#include <list>
#include <random>
#include <vector>

#include "Particule.hxx"
#include "Vecteur.hxx"

/**
 * @brief Point d’entrée du programme de benchmark.
 *
 * Compare les temps de construction (insertion d’objets `Particule`) dans trois conteneurs :
 * `std::vector`, `std::list`, et `std::deque`, pour différentes tailles.
 *
 * @return 0 si succès.
 */
int main() {
    /// Tailles des conteneurs testés
    const int tailles[] = {64, 128, 256, 512, 1024, 2048, 4096};

    /// Générateur pseudo-aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> uni(0.0, 100.0);

    std::cout << std::fixed << std::setprecision(6);  // formatage fixe des durées

    for (int n : tailles) {

        // --- Benchmark vector ---
        {
            auto start = std::chrono::steady_clock::now();

            std::vector<Particule> cont;
            cont.reserve(n);  ///< allocation anticipée
            for (int i = 0; i < n; ++i) {
                Vecteur pos(uni(gen), uni(gen), uni(gen));
                Vecteur vel(uni(gen), uni(gen), uni(gen));
                cont.emplace_back(i, "randType", uni(gen), vel, Vecteur(0, 0, 0), pos);
            }

            double sec = std::chrono::duration<double>(
                std::chrono::steady_clock::now() - start
            ).count();
            std::cout << "vector(" << n << ") : " << sec << " s\n";
        }

        // --- Benchmark list ---
        {
            auto start = std::chrono::steady_clock::now();

            std::list<Particule> cont;
            for (int i = 0; i < n; ++i) {
                Vecteur pos(uni(gen), uni(gen), uni(gen));
                Vecteur vel(uni(gen), uni(gen), uni(gen));
                cont.emplace_back(i, "randType", uni(gen), vel, Vecteur(0, 0, 0), pos);
            }

            double sec = std::chrono::duration<double>(
                std::chrono::steady_clock::now() - start
            ).count();
            std::cout << "list(" << n << ") : " << sec << " s\n";
        }

        // --- Benchmark deque ---
        {
            auto start = std::chrono::steady_clock::now();

            std::deque<Particule> cont;
            for (int i = 0; i < n; ++i) {
                Vecteur pos(uni(gen), uni(gen), uni(gen));
                Vecteur vel(uni(gen), uni(gen), uni(gen));
                cont.emplace_back(i, "randType", uni(gen), vel, Vecteur(0, 0, 0), pos);
            }

            double sec = std::chrono::duration<double>(
                std::chrono::steady_clock::now() - start
            ).count();
            std::cout << "deque(" << n << ") : " << sec << " s\n";
        }

        std::cout << "****************\n";
    }

    return 0;
}

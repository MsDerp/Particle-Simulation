#include "Particule.hxx"
#include "Vecteur.hxx"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>

#include "Univers.hxx"

void computeForces(std::vector<Particule>& P) {
    for (auto& p : P) p.setForce(Vecteur(0,0,0));
    
    const std::size_t N = P.size();
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = i + 1; j < N; ++j) {
            P[i].calculateGravitationalForce(P[j]);
        }
    }
}



void benchmarkInteractions(int max_k) {
    std::ofstream perf_file("cubic_interaction_perf.txt");
    perf_file << "k n_particles time_ms\n";

    for (int k = 1; k <= max_k; ++k) {
        const int n_per_dim = std::pow(2, k);
        const int total_particles = n_per_dim * n_per_dim * n_per_dim;

        Univers univers(3, total_particles);
        univers.generateCubicParticles();

        auto start = std::chrono::high_resolution_clock::now();
        computeForces(univers.getParticules());
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        perf_file << k << " " << total_particles << " " << duration.count() << "\n";
        std::cout << "k=" << k << " (" << n_per_dim << "^3 = " << total_particles 
                  << " particules) : " << duration.count() << " ms\n";
    }
}

int main() {
    const int max_k = 7; // recommandé
    benchmarkInteractions(max_k);
    
    std::cout << "Donnees enregistrees dans cubic_interaction_perf.txt\n";
    return 0;
}
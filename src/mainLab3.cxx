#include "Univers.hxx"
#include "Particule.hxx"
#include "Vecteur.hxx"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>
#include <vector>

struct BenchmarkResult {
    int particleCount;
    double insertionTime;
    double timePerParticle;
};

void writePerformanceData(const std::vector<BenchmarkResult>& results) {
    std::ofstream outFile("performance.txt");
    if (!outFile) {
        std::cerr << "Erreur lors de la creation du fichier performance.txt" << std::endl;
        return;
    }

    // En-tête du fichier
    outFile << "# Particules\tTempsTotal(ms)\tTempsParParticule(ms)\n";

    // Données
    for (const auto& result : results) {
        outFile << result.particleCount << "\t"
                << result.insertionTime << "\t"
                << result.timePerParticle << "\n";
    }

    outFile.close();
}

void generateGnuplotScript() {
    std::ofstream scriptFile("plot_performance.gp");
    scriptFile << "set terminal pngcairo enhanced font 'Verdana,12'\n"
               << "set output 'performance_plot.png'\n"
               << "set title 'Performance Insertion Particules'\n"
               << "set xlabel 'Nombre de Particules'\n"
               << "set ylabel 'Temps (ms)'\n"
               << "set logscale x\n"
               << "set logscale y\n"
               << "set grid\n"
               << "set key top left\n"
               << "plot 'performance.txt' using 1:2 with linespoints title 'Temps Total', \\\n"
               << "     'performance.txt' using 1:3 with linespoints title 'Temps par Particule'\n";
    scriptFile.close();
}

int main() {
    int dim = 3;
    std::vector<BenchmarkResult> results;

    for (int k = 1; k < 9; ++k) {

        std::cout << "k = " << k << std::endl;

        const int n = std::pow(2, k);
        const double cubeSize = 1.0;
        const double spacing = cubeSize / (n + 1);
        const int totalParticles = n * n * n;

        std::cout << "Creation univers avec " << totalParticles
                  << " particules (" << n << "^3)" << std::endl;

        Univers univers(dim,totalParticles);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> vel_dist(-0.1, 0.1);
        std::uniform_real_distribution<double> mass_dist(0.5, 2.0);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= n; ++k) {
                    Vecteur position(i * spacing, j * spacing, k * spacing);
                    Vecteur vitesse(vel_dist(gen), vel_dist(gen), vel_dist(gen));
                    Particule particule(
                        i*n*n + j*n + k,
                        "p" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k),
                        mass_dist(gen),
                        vitesse,
                        Vecteur(0, 0, 0),
                        position
                    );
                    univers.add(particule);
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        BenchmarkResult element;
        element.particleCount = totalParticles;
        element.insertionTime = duration.count();
        element.timePerParticle = duration.count() / static_cast<double>(totalParticles);
        results.push_back(element);

        std::cout << "Termine - Temps: " << duration.count() << " ms\n\n";


    }


    writePerformanceData(results);
    generateGnuplotScript();

    std::cout << "\nFichiers generes:\n"
              << "- performance.txt (donnees brutes)\n"
              << "- plot_performance.gp (script gnuplot)\n\n"
              << "Pour generer le graphique, exécutez:\n"
              << "gnuplot plot_performance.gp\n"
              << "Le graphique sera sauvegarde dans 'performance_plot.png'\n";

    return 0;
}
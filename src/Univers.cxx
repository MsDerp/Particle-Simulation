#include "Univers.hxx"
#include <random>
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <unistd.h>  // For Linux/Mac


/// Vecteur de vitesse uniforme utilisé pour initialiser les particules.
const Vecteur uniformVelocity(1, 0, 0);


/**
 * @brief Récupère le chemin racine du projet en cherchant le fichier CMakeLists.txt.
 * @return Chemin absolu vers la racine du projet.
 */
std::string getProjectRoot() {
    namespace fs = std::filesystem;
    fs::path current = fs::current_path();

    while (current.has_parent_path()) {
        if (fs::exists(current / "CMakeLists.txt")) {
            return current.string();  // racine du projet
        }
        current = current.parent_path();
    }
    return fs::current_path().string();  // fallback
}


void clearDirectoryIfExists(const std::string& dirPath) {
    namespace fs = std::filesystem;
    try {
        if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
            // Vérifier si le répertoire contient des fichiers
            bool hasFiles = false;
            for (const auto& entry : fs::directory_iterator(dirPath)) {
                if (fs::is_regular_file(entry.path())) {
                    hasFiles = true;
                    break;
                }
            }

            if (hasFiles) {
                std::cout << "Nettoyage du répertoire existant: " << dirPath << std::endl;

                // Supprimer tous les fichiers du répertoire
                for (const auto& entry : fs::directory_iterator(dirPath)) {
                    if (fs::is_regular_file(entry.path())) {
                        fs::remove(entry.path());
                    }
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Erreur lors du nettoyage du répertoire: " << e.what() << std::endl;
        throw;
    }
}


/**
 * @brief Constructeur principal de l'univers avec paramètres complets.
 */
Univers::Univers(int d, int n, double rcut_, const std::vector<double>& Ld, double eps, double sigma)
    : dim(d), number(n), rcut(rcut_), conditionLim(eps, sigma) {

    // Définir la taille des cellules
    tailleCellule = rcut;
    rayonDeCoupure = rcut;

    // Calcul des tailles de grille (taillesGrilles[i] = floor(Ld[i] / rcut))
    for (int i = 0; i < 3; ++i) {
        if (i < dim && i < static_cast<int>(Ld.size())) {
            taillesGrilles[i] = static_cast<int>(std::floor(Ld[i] / rcut));
        } else {
            taillesGrilles[i] = 1;
        }
    }

    particules.reserve(n);
}


/**
 * @brief Constructeur simplifié de l'univers sans résolution de grille.
 */
Univers::Univers(int d, int n)
    : dim(d), number(n), conditionLim(1.0, 1.0) {
    particules.reserve(n);
}


Univers::~Univers() {
    particules.clear();
}

void Univers::add(const Particule& p) {
    particules.emplace_back(p);
    ++number;
}


int Univers::getNumber() const {
    return number;
}

int Univers::getParticlesNumber() const {
    return particules.size();
}


/**
 * @brief Affiche les informations de toutes les particules toutes les 10 étapes.
 */
void Univers::displayInfo(int step) const {
    if (step % 10 == 0) {
        std::cout << "À l'étape " << step << " :\n";
        for (const auto& p : particules) {
            p.toString();
        }
    }
}


/**
 * @brief Met à jour les forces inter-particules.
 */
void Univers::updateForces(double eps, double sigma) {
    for (auto& p : particules) {
        p.setForce(Vecteur(0, 0, 0));
    }

        for (Cellule& cellule : cellules) {
        for (Particule* p1 : cellule.getParticules()) {
            for (Cellule* voisine : cellule.getVoisines()) {
                for (Particule* p2 : voisine->getParticules()) {
                    if (p1 < p2) {
                        p1->calculateGravitationalForce(*p2);

                        double distance = (p1->getPosition() - p2->getPosition()).norm();
                        if (distance < rayonDeCoupure) {
                            calculateLennardJonesForce(*p1, *p2, eps, sigma);
                        }
                    }
                }
            }
        }
    }

   /* for (auto& p : particules) {
        double m = p.getMass();
        Vecteur g(0, - m * constanteGravite, 0);
        p.addForce(g);
    }  */
}



/**
 * @brief Génère un fichier de sortie VTK pour visualisation.
 */

void Univers::genererVTK(int step,const std::string& directoryName) const {
    const std::string dir = getProjectRoot() +"/out/" + directoryName;
    namespace fsys = std::filesystem;


    try {

        // Création du répertoire si inexistant
        if (!fsys::exists(dir)) {
            if (!fsys::create_directories(dir)) {
                std::cerr << "Error: Cannot create directory " << dir << std::endl;
                return;
            }
        }

        std::string filename = dir + "/output_step_" + std::to_string(step) + ".vtu";
        std::ofstream file(filename);

        // Add at the start of your function
        std::cout << "Current working directory: "
                  << fsys::current_path() << std::endl;

        if (!file.is_open()) {
            std::cerr << "Error: Failed to open file " << filename
                      << " - " << strerror(errno) << std::endl;
            return;
        }


        file << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
        file << "  <UnstructuredGrid>\n";
        file << "    <Piece NumberOfPoints=\"" << particules.size() << "\" NumberOfCells=\"0\">\n";

        // Points (Positions des particules)
        file << "      <Points>\n";
        file << "        <DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";
        for (const auto& p : particules) {
            const Vecteur& pos = p.getPosition();
            file << "          " << pos.getxCoordinate() << " " << pos.getyCoordinate() << " " << pos.getzCoordinate() << "\n";
        }
        file << "        </DataArray>\n";
        file << "      </Points>\n";

        // Point Data (Vitesse et Masse)
        file << "      <PointData Vectors=\"vector\">\n";

        // Vitesse
        file << "        <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n";
        for (const auto& p : particules) {
            const Vecteur& vel = p.getVelocity();
            file << "          " << vel.getxCoordinate() << " " << vel.getyCoordinate() << " " << vel.getzCoordinate() << "\n";
        }
        file << "        </DataArray>\n";

        // Masse
        file << "        <DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n";
        for (const auto& p : particules) {
            file << "          " << p.getMass() << "\n";
        }
        file << "        </DataArray>\n";

        file << "      </PointData>\n";

        // Cellules (vide ici)
        file << "      <Cells>\n";
        file << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n";
        file << "        </DataArray>\n";
        file << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n";
        file << "        </DataArray>\n";
        file << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n";
        file << "        </DataArray>\n";
        file << "      </Cells>\n";

        file << "    </Piece>\n";
        file << "  </UnstructuredGrid>\n";
        file << "</VTKFile>\n";

        file.close();
        std::cout << "Successfully generated VTK file: " << filename << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }


}




/**
 * @brief Calcule et applique la force de Lennard-Jones entre deux particules.
 *
 * @param p1 Référence vers la première particule.
 * @param p2 Référence vers la seconde particule.
 * @param epsilon Profondeur du potentiel.
 * @param sigma Distance à laquelle le potentiel est nul.
 */
void Univers::calculateLennardJonesForce(Particule& p1, Particule& p2, double epsilon, double sigma) {
    Vecteur r = p1.getPosition() - p2.getPosition();
    double distance = r.norm();

    if (distance > rayonDeCoupure || distance == 0.0 || distance < 1e-2) return;

    double inv_r = sigma / distance;
    double inv_r6 = pow(inv_r, 6);
    double inv_r12 = inv_r6 * inv_r6;

    double forceMagnitude = 24 * epsilon * (2 * inv_r12 - inv_r6) / distance;
    Vecteur force = forceMagnitude * r.normalized();

    p1.addForce(force);
    p2.addForce(-force);
}


/**
 * @brief Vide et remplit les cellules en fonction de la position des particules.
 */
void Univers::mettreAJourCellules() {
    for (auto& cellule : cellules) {
        cellule.getParticules().clear();
    }

    for (auto& p : particules) {
        int index = indexCellule(p.getPosition());
        cellules[index].ajouterParticule(&p);
    }
}


/**
 * @brief Met à jour la vitesse des particules via l'intégration de Verlet.
 *
 * @param deltaTime Pas de temps de la simulation.
 */
void Univers::updateVelocities(double deltaTime) {
    for (auto& p : particules) {
        double scalar = 0.5 * deltaTime / p.getMass();
        Vecteur newVelocity = (p.getForce() + p.getOldForce()) * scalar;
        newVelocity.add(p.getVelocity());
        p.setVelocity(newVelocity);
    }
}



/**
 * @brief Met à jour la position des particules via l'intégration de Verlet.
 *
 * @param deltaTime Pas de temps de la simulation.
 */
void Univers::updatePositions(double deltaTime) {
    for (auto& p : particules) {
        Vecteur acceleration = p.getForce() * (1.0 / p.getMass());
        Vecteur newPosition = p.getPosition() + (p.getVelocity() + acceleration * (0.5 * deltaTime)) * deltaTime;
        p.setPosition(newPosition);
    }
}


/**
 * @brief Exécute la simulation avec le schéma de Stormer-Verlet.
 *
 * @param deltaTime Pas de temps.
 * @param steps Nombre d'étapes à simuler.
 * @param eps Valeur de epsilon pour Lennard-Jones.
 * @param sigma Valeur de sigma pour Lennard-Jones.
 * @param Ec_cible Énergie cinétique cible à régulariser (0 = aucune régularisation).
 */
void Univers::applyStormerVerlet(double deltaTime, int steps, double eps, double sigma, const std::string& directoryName, double Ec_cible) {

    genererVTK(0,directoryName);
    mettreAJourCellules();
    updateForces(eps, sigma);

    for (int step = 1; step < steps; ++step) {
        updatePositions(deltaTime);         
        sauvegarderAnciennesForces();  
        mettreAJourCellules();
        updateForces(eps, sigma);
        updateVelocities(deltaTime); 
        genererVTK(step,directoryName);

        if (Ec_cible!= 0 & step % 1000 == 0) {
            regulariserEnergieCinetique(Ec_cible);
        }
    }


}

/**
 * @brief Initialise les cellules spatiales et place les particules dedans.
 */
void Univers::initialiserGrille() {
    int total = taillesGrilles[0] * taillesGrilles[1] * taillesGrilles[2];
    cellules.resize(total);

    for (auto& p : particules) {
        int index = indexCellule(p.getPosition());
        cellules[index].ajouterParticule(&p);
    }

    initialiserVoisines();
}

/**
 * @brief Calcule l'indice de la cellule associée à une position.
 *
 * @param pos Position 3D.
 * @return Indice de la cellule dans le tableau `cellules`.
 */

int Univers::indexCellule(const Vecteur& pos) const {
    int ix = std::clamp(int(pos.getxCoordinate() / tailleCellule), 0, taillesGrilles[0] - 1);
    int iy = (dim >= 2) ? std::clamp(int(pos.getyCoordinate() / tailleCellule), 0, taillesGrilles[1] - 1) : 0;
    int iz = (dim == 3) ? std::clamp(int(pos.getzCoordinate() / tailleCellule), 0, taillesGrilles[2] - 1) : 0;

    return ix + taillesGrilles[0] * (iy + taillesGrilles[1] * iz);
}


/**
 * @brief Initialise les voisines des cellules selon la dimension.
 */

void Univers::initialiserVoisines() {
    if (dim == 1) initialiserVoisines1D();
    else if (dim == 2) initialiserVoisines2D();
    else if (dim == 3) initialiserVoisines3D();
}


void Univers::initialiserVoisines1D()
{
    int nx = taillesGrilles[0];

    for (int x = 0; x < nx; ++x) {
        Cellule& cellule = cellules[x];

        // --- NOUVEAU : la cellule se considère elle-même comme voisine ---
        cellule.ajouterVoisine(&cellule);

        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0) continue;                // on garde ce filtre
            int nx_ = x + dx;
            if (nx_ >= 0 && nx_ < nx) {
                cellule.ajouterVoisine(&cellules[nx_]);
            }
        }
    }
}

void Univers::initialiserVoisines2D()
{
    int nx = taillesGrilles[0];
    int ny = taillesGrilles[1];

    for (int x = 0; x < nx; ++x) {
        for (int y = 0; y < ny; ++y) {
            int index = x + nx * y;
            Cellule& cellule = cellules[index];

            // --- NOUVEAU ---
            cellule.ajouterVoisine(&cellule);

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    int nx_ = x + dx;
                    int ny_ = y + dy;
                    if (nx_ >= 0 && nx_ < nx && ny_ >= 0 && ny_ < ny) {
                        int voisinIndex = nx_ + nx * ny_;
                        cellule.ajouterVoisine(&cellules[voisinIndex]);
                    }
                }
            }
        }
    }
}

void Univers::initialiserVoisines3D()
{
    int nx = taillesGrilles[0];
    int ny = taillesGrilles[1];
    int nz = taillesGrilles[2];

    for (int x = 0; x < nx; ++x) {
        for (int y = 0; y < ny; ++y) {
            for (int z = 0; z < nz; ++z) {
                int index = x + nx * (y + ny * z);
                Cellule& cellule = cellules[index];

                // --- NOUVEAU ---
                cellule.ajouterVoisine(&cellule);

                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        for (int dz = -1; dz <= 1; ++dz) {
                            if (dx == 0 && dy == 0 && dz == 0) continue;
                            int nx_ = x + dx;
                            int ny_ = y + dy;
                            int nz_ = z + dz;
                            if (nx_ >= 0 && nx_ < nx &&
                                ny_ >= 0 && ny_ < ny &&
                                nz_ >= 0 && nz_ < nz) {
                                int voisinIndex = nx_ + nx * (ny_ + ny * nz_);
                                cellule.ajouterVoisine(&cellules[voisinIndex]);
                            }
                        }
                    }
                }
            }
        }
    }
}


/**
 * @brief Donne la taille physique d'une dimension de l'univers.
 *
 * @param i Index de dimension (0 = x, 1 = y, 2 = z).
 * @return Longueur dans cette dimension.
 */
int Univers::getDimension(int i) const {
    return taillesGrilles[i] * tailleCellule;
}

/**
 * @brief Supprime une particule du vecteur de particules.
 *
 * @param p Référence vers la particule à supprimer.
 */
void Univers::supprimerParticule(const Particule& p) {
    particules.erase(std::remove_if(particules.begin(), particules.end(),
        [&](const Particule& other) { return &other == &p; }), particules.end());
}


int Univers::getDim() const {
    return dim;
}

const std::vector<Particule>& Univers::getParticules() const {
    return particules;
}

std::vector<Particule>& Univers::getParticules() {
    return particules;
}


/**
 * @brief Sauvegarde la force actuelle comme \"ancienne force\" dans chaque particule.
 */
void Univers::sauvegarderAnciennesForces() {
    for (auto& p : particules) {
        p.setOldForce(p.getForce());
    }
}

/**
 * @brief Ajuste les vitesses pour que l'énergie cinétique corresponde à une valeur cible.
 *
 * @param Ec_cible Valeur d'énergie cinétique cible à atteindre.
 */
void Univers::regulariserEnergieCinetique(double Ec_cible) {
    double Ec_totale = 0.0;
    for (const auto& p : particules) {
        double vitesse_norm = p.getVelocity().norm();
        Ec_totale += 0.5*p.getMass() * vitesse_norm * vitesse_norm;
    }

    if (Ec_totale <= 1e-9) return;

    double beta = std::sqrt(Ec_cible / Ec_totale);

    for (auto& p : particules) {
        Vecteur velocityRegularise = p.getVelocity() * beta;
        p.setVelocity(velocityRegularise);
    }
}
void Univers::generateCubicParticles() {

    const int n_per_dim = static_cast<int>(std::round(std::pow(number, 1.0/dim)));
    const double spacing = 1.0 / (n_per_dim + 1); // Espacement régulier


    int id = 0;
    for (int x = 1; x <= n_per_dim; ++x) {
        for (int y = 1; y <= n_per_dim; ++y) {
            for (int z = 1; z <= n_per_dim; ++z) {
                Vecteur position(x * spacing, y * spacing, z * spacing);
                particules.emplace_back(
                    id++,
                    "P_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z),
                    1.0, // Masse unitaire
                    Vecteur(0,0,0), // Vitesse initiale nulle
                    Vecteur(0,0,0), // Force initiale nulle
                    position
                );
            }
        }
    }
}



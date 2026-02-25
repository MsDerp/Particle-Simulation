/**
 * @file Cellule.cxx
 * @brief Implémentation de la classe Cellule utilisée pour la décomposition spatiale de l’univers.
 */

#include "Cellule.hxx"

/// @brief Constructeur par défaut d’une cellule.
Cellule::Cellule() = default;

/**
 * @brief Ajoute un pointeur vers une particule dans la cellule.
 * 
 * @param p Pointeur vers la particule à ajouter.
 */
void Cellule::ajouterParticule(Particule* p) {
    particules.push_back(p);
}

/**
 * @brief Ajoute une cellule voisine à la liste des voisines.
 * 
 * @param c Pointeur vers la cellule voisine.
 */
void Cellule::ajouterVoisine(Cellule* c) {
    voisines.push_back(c);
}

/**
 * @brief Vide la liste des particules contenues dans la cellule.
 */
void Cellule::clearParticules() {
    particules.clear();
}

/**
 * @brief Accès modifiable à la liste des particules.
 * 
 * @return Référence vers le vecteur de pointeurs de particules.
 */
std::vector<Particule*>& Cellule::getParticules() {
    return particules;
}

/**
 * @brief Accès constant à la liste des particules.
 * 
 * @return Référence constante vers le vecteur de pointeurs de particules.
 */
const std::vector<Particule*>& Cellule::getParticules() const {
    return particules;
}

/**
 * @brief Accès modifiable à la liste des cellules voisines.
 * 
 * @return Référence vers le vecteur de pointeurs de cellules voisines.
 */
std::vector<Cellule*>& Cellule::getVoisines() {
    return voisines;
}

/**
 * @brief Accès constant à la liste des cellules voisines.
 * 
 * @return Référence constante vers le vecteur de pointeurs de cellules voisines.
 */
const std::vector<Cellule*>& Cellule::getVoisines() const {
    return voisines;
}

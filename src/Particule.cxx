/**
 * @file Particule.cxx
 * @brief Implémentation de la classe Particule représentant une entité physique dans l'univers simulé.
 */

#include "Particule.hxx"
#include <iostream>
#include <cmath>
#include <Vecteur.hxx>

/// Constante gravitationnelle (valeur arbitraire)
constexpr double G = 1;

/**
 * @brief Constructeur de la particule avec initialisation complète.
 * @param id Identifiant unique de la particule
 * @param category Nom ou type de la particule
 * @param mass Masse de la particule
 * @param v Vitesse initiale
 * @param f Force initiale
 * @param p Position initiale
 */
Particule::Particule(int id, const std::string &category, double mass, Vecteur v,
                     Vecteur f, Vecteur p)
    : id(id), category(category), mass(mass), velocity(v), force(f), position(p),
      oldForce(Vecteur(0, 0, 0)) {}

/// Destructeur
Particule::~Particule() = default;

/**
 * @brief Affiche les caractéristiques internes de la particule.
 */
void Particule::toString() const {
    std::cout << "ID : " << id << "\n"
              << "Catégorie : " << category << "\n"
              << "Masse : " << mass << "\n"
              << "Vecteur Position : " << position << "\n"
              << "Vecteur Vitesse : " << velocity << "\n"
              << "Vecteur Force : " << force << "\n";
}

/**
 * @brief Calcule et applique la force gravitationnelle entre deux particules.
 * @param p2 Particule cible avec laquelle interagir
 *
 * Applique la force à la particule courante et à `p2` (action-réaction).
 */
void Particule::calculateGravitationalForce(Particule& p2) {
    Vecteur deltaPos = position - p2.position;
    double distance = deltaPos.norm();

    if (distance < 1e-10) return;  // éviter les divisions par 0

    double invDist = 1.0 / distance;
    double forceMagnitude = (G * mass * p2.mass) * invDist * invDist;

    Vecteur direction = deltaPos.normalized();
    Vecteur forceVec = direction * forceMagnitude;

    this->addForce(-forceVec);
    p2.addForce(forceVec);
}

// ---------------------- Mutateurs ------------------------

/**
 * @brief Définit la force appliquée à la particule.
 * @param f Nouveau vecteur force
 */
void Particule::setForce(const Vecteur f) {
    force.set(f);
}

/**
 * @brief Définit la position de la particule.
 * @param p Nouveau vecteur position
 */
void Particule::setPosition(const Vecteur p) {
    position.set(p);
}

/**
 * @brief Définit la vitesse de la particule.
 * @param v Nouveau vecteur vitesse
 */
void Particule::setVelocity(const Vecteur v) {
    velocity.set(v);
}

/**
 * @brief Met à jour la masse de la particule.
 * @param m Masse en double
 */
void Particule::setMass(double m) {
    mass = m;
}

/**
 * @brief Mémorise la force précédente.
 * @param f Ancienne force à sauvegarder
 */
void Particule::setOldForce(const Vecteur f) {
    oldForce.set(f);
}

/**
 * @brief Ajoute une force au vecteur force courant.
 * @param deltaF Force à ajouter
 */
void Particule::addForce(const Vecteur& deltaF) {
    force = force + deltaF;
}

// ---------------------- Accesseurs ------------------------

/// @return Force appliquée à la particule
Vecteur Particule::getForce() const {
    return force;
}

/// @return Position de la particule
Vecteur Particule::getPosition() const {
    return position;
}

/// @return Vitesse de la particule
Vecteur Particule::getVelocity() const {
    return velocity;
}

/// @return Masse de la particule
double Particule::getMass() const {
    return mass;
}

/// @return Ancienne force appliquée à la particule (avant mise à jour)
Vecteur Particule::getOldForce() const {
    return oldForce;
}

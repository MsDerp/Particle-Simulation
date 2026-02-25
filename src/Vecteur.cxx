/**
 * @file Vecteur.cxx
 * @brief Implémentation de la classe Vecteur représentant un vecteur 3D.
 */

#include <iostream>
#include <string>
#include <cmath>
#include "Vecteur.hxx"

using namespace std;

/**
 * @brief Constructeur du vecteur à partir de 3 coordonnées.
 * @param c_x abscisse
 * @param c_y ordonnée
 * @param c_z cote
 */
Vecteur::Vecteur(double c_x, double c_y, double c_z) : c_x(c_x), c_y(c_y), c_z(c_z) {}

/**
 * @brief Remplace les coordonnées du vecteur courant par celles d’un autre.
 * @param other Vecteur à copier
 */
void Vecteur::set(const Vecteur& other) {
    this->c_x = other.c_x;
    this->c_y = other.c_y;
    this->c_z = other.c_z;
}

/// @return Coordonnée X
double Vecteur::getxCoordinate() const { return c_x; }

/// @return Coordonnée Y
double Vecteur::getyCoordinate() const { return c_y; }

/// @return Coordonnée Z
double Vecteur::getzCoordinate() const { return c_z; }

/**
 * @brief Additionne un autre vecteur au vecteur courant (modifie ce dernier).
 * @param rhs Vecteur à ajouter
 */
void Vecteur::add(const Vecteur& rhs) {
    c_x += rhs.c_x;
    c_y += rhs.c_y;
    c_z += rhs.c_z;
}

/**
 * @brief Soustrait un autre vecteur au vecteur courant (modifie ce dernier).
 * @param rhs Vecteur à soustraire
 */
void Vecteur::sub(const Vecteur& rhs) {
    c_x -= rhs.c_x;
    c_y -= rhs.c_y;
    c_z -= rhs.c_z;
}

/**
 * @brief Multiplie le vecteur courant par un scalaire (modifie ce dernier).
 * @param lambda Scalaire multiplicatif
 */
void Vecteur::mul(double lambda) {
    c_x *= lambda;
    c_y *= lambda;
    c_z *= lambda;
}

/// @brief Surcharge de l'opérateur + pour addition de vecteurs
Vecteur Vecteur::operator+(const Vecteur& rhs) {
    return Vecteur(c_x + rhs.c_x, c_y + rhs.c_y, c_z + rhs.c_z);
}

/// @brief Surcharge de l'opérateur - pour soustraction de vecteurs
Vecteur Vecteur::operator-(const Vecteur& rhs) {
    return Vecteur(c_x - rhs.c_x, c_y - rhs.c_y, c_z - rhs.c_z);
}

/// @brief Surcharge de l'opérateur * pour produit scalaire à droite
Vecteur Vecteur::operator*(double lambda) {
    return Vecteur(c_x * lambda, c_y * lambda, c_z * lambda);
}

/// @brief Opposé du vecteur
Vecteur Vecteur::operator-() const {
    return Vecteur(-c_x, -c_y, -c_z);
}

/// @brief Représentation textuelle du vecteur
std::string Vecteur::toString() const {
    return "Vecteur (" + std::to_string(c_x) + ", " + std::to_string(c_y) + ", " + std::to_string(c_z) + ")";
}

/// @brief Affichage du vecteur dans un flux de sortie
std::ostream& operator<<(std::ostream& os, const Vecteur& v) {
    os << "Vecteur (" << v.getxCoordinate() << ", " << v.getyCoordinate() << ", " << v.getzCoordinate() << ")";
    return os;
}

/// @brief Norme euclidienne du vecteur
double Vecteur::norm() const {
    return std::sqrt(c_x * c_x + c_y * c_y + c_z * c_z);
}

/// @brief Vecteur unitaire dans la même direction
Vecteur Vecteur::normalized() const {
    double n = norm();
    if (n == 0) {
        throw std::runtime_error("Division by zero in Vecteur::normalized");
    }
    return Vecteur(c_x / n, c_y / n, c_z / n);
}

/**
 * @brief Produit scalaire à gauche : scalaire * vecteur
 * @param scalaire Coefficient multiplicatif
 * @param vec Vecteur cible
 * @return Résultat du produit
 */
Vecteur operator*(double scalaire, const Vecteur& vec) {
    return Vecteur(vec.getxCoordinate() * scalaire,
                   vec.getyCoordinate() * scalaire,
                   vec.getzCoordinate() * scalaire);
}

/**
 * @brief Accès en lecture à une composante du vecteur par indice.
 * @param index 0 (x), 1 (y), ou 2 (z)
 * @return Valeur de la composante
 * @throws std::out_of_range si l’index est invalide
 */
double Vecteur::operator[](int index) const {
    switch (index) {
        case 0: return getxCoordinate();
        case 1: return getyCoordinate();
        case 2: return getzCoordinate();
        default: throw std::out_of_range("Index invalide dans Vecteur::operator[] const");
    }
}

/**
 * @brief Accès en écriture à une composante du vecteur par indice.
 * @param index 0 (x), 1 (y), ou 2 (z)
 * @return Référence à la composante
 * @throws std::out_of_range si l’index est invalide
 */
double& Vecteur::operator[](int index) {
    switch (index) {
        case 0: return c_x;
        case 1: return c_y;
        case 2: return c_z;
        default: throw std::out_of_range("Index invalide dans Vecteur::operator[]");
    }
}

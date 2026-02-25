#ifndef VECTEUR_HXX
#define VECTEUR_HXX

#include <iostream>
#include <string>

class Vecteur {
   public:
     Vecteur(double c_x, double c_y, double c_z);

     // Utilisation de référence constante pour éviter les copies inutiles
     void set(const Vecteur& other);

     double getxCoordinate() const;
     double getyCoordinate() const;
     double getzCoordinate() const;

     void add(const Vecteur& rhs);
     void sub(const Vecteur& rhs);
     void mul(double lambda);

     // Opérateurs définis directement dans la classe
     Vecteur operator+(const Vecteur& rhs);
     Vecteur operator-(const Vecteur& rhs);
     Vecteur operator*(double lambda);
     Vecteur operator-() const;

     std::string toString() const;
     friend std::ostream& operator<<(std::ostream& os, const Vecteur& v);
     
     double norm() const;
     Vecteur normalized() const;

     double& operator[](int index);              // accès en écriture (modifiable)
     double operator[](int index) const;         // accès en lecture seule

   private:
     double c_x, c_y, c_z;
};

// Opérateur scalaire * vecteur (hors classe)
Vecteur operator*(double scalaire, const Vecteur& vec);

#endif // VECTEUR_HXX

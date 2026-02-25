#ifndef PARTICULE_HXX
#define PARTICULE_HXX

#include <string>
#include "Vecteur.hxx"

class Particule {
public:
    Particule(int id, const std::string &category, double mass, 
              Vecteur v, Vecteur f, Vecteur p);
    ~Particule();

    void toString() const;
    void calculateGravitationalForce(Particule& other);
    void updatePosition(double deltaTime);

    // Accesseurs
    Vecteur getForce() const;
    Vecteur getPosition() const;
    Vecteur getVelocity() const;
    double getMass() const;
    Vecteur getOldForce() const;

    // Mutateurs
    void setForce(Vecteur f);
    void setPosition(Vecteur p);
    void setVelocity(Vecteur v);
    void setMass(double m);
    void setOldForce(Vecteur f);
    void addForce(const Vecteur& deltaF);

private:
    int id;
    std::string category;
    double mass;
    Vecteur velocity;
    Vecteur position;
    Vecteur force;
    Vecteur oldForce;
};

#endif // PARTICULE_HXX

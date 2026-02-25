//
// Created by belfaidm on 5/2/25.
//

#include <gtest/gtest.h>
#include "Particule.hxx"
#include "Vecteur.hxx"
#include <cmath>
#include <sstream>

constexpr double EPS = 1e-9;

TEST(ParticuleTest, ConstructorAndGetters) {
    Vecteur v(1, 2, 3);
    Vecteur f(0, 0, 0);
    Vecteur p(4, 5, 6);
    Particule part(1, "test", 10.0, v, f, p);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    part.toString();
    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_NE(output.find("ID : 1"), std::string::npos);
    EXPECT_NE(output.find("Catégorie : test"), std::string::npos);
    EXPECT_NE(output.find("Masse : 10"), std::string::npos);
}

TEST(ParticuleTest, SettersWorkCorrectly) {
    Particule part(0, "cat", 1.0, Vecteur(0, 0, 0), Vecteur(0, 0, 0), Vecteur(0, 0, 0));
    part.setMass(2.0);
    part.setVelocity(Vecteur(1, 0, 0));
    part.setPosition(Vecteur(0, 1, 0));
    part.setForce(Vecteur(0, 0, 1));
    part.setOldForce(Vecteur(0.5, 0.5, 0.5));

    EXPECT_NEAR(part.getForce().getzCoordinate(), 1.0, EPS);
    EXPECT_NEAR(part.getVelocity().getxCoordinate(), 1.0, EPS);
    EXPECT_NEAR(part.getPosition().getyCoordinate(), 1.0, EPS);
}

TEST(ParticuleTest, GravitationalForceCalculation) {
    Vecteur f(0, 0, 0);
    Vecteur v(0, 0, 0);
    Vecteur p1(0, 0, 0);
    Vecteur p2(1, 0, 0);

    Particule a(1, "A", 10.0, v, f, p1);
    Particule b(2, "B", 5.0, v, f, p2);

    a.calculateGravitationalForce(b);

    Vecteur fa = a.getForce();
    EXPECT_NE(fa.getxCoordinate(), 0);
    EXPECT_NEAR(fa.getyCoordinate(), 0, EPS);
    EXPECT_NEAR(fa.getzCoordinate(), 0, EPS);
}



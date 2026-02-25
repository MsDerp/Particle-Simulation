#include <gtest/gtest.h>
#include "Particule.hxx"
#include "Univers.hxx"
#include "Vecteur.hxx"
#include "conditionsLimites/Reflexion.hxx"
#include "conditionsLimites/Absorption.hxx"
#include "conditionsLimites/Periodique.hxx"

constexpr double EPS = 1e-8;

// --- REFLEXION ---
TEST(ConditionLimiteTest, ReflexionRebonds) {
    Univers u(2, 0);  
    Reflexion cl;
    Particule p(0, "particule_reflexion", 1.0, Vecteur(1, 0, 0), Vecteur(0, 0, 0), Vecteur(-5, 99, 0));
    
    ASSERT_TRUE(cl.estHorsLimites(p, u));
    cl.appliquer(p, u);
    EXPECT_GE(p.getPosition().getxCoordinate(), 0);
    EXPECT_NEAR(p.getVelocity().getxCoordinate(), -1.0, EPS);
}

// --- PERIODIQUE ---
TEST(ConditionLimiteTest, PeriodiqueWrapsAround) {
    Univers u(2, 0, 2.5, {120.0, 100.0});  

    Periodique cl;
    Particule p(1, "B", 1.0, Vecteur(0, 0, 0), Vecteur(0, 0, 0), Vecteur(125, 50, 0));  // ⬅️ hors limite

    ASSERT_TRUE(cl.estHorsLimites(p, u));  
    cl.appliquer(p, u);

    EXPECT_LE(p.getPosition().getxCoordinate(), u.getDimension(0));
    EXPECT_GE(p.getPosition().getxCoordinate(), 0);
}


// --- ABSORPTION ---
TEST(ConditionLimiteTest, AbsorptionSupprimeParticule) {
    Univers u(2, 0);
    Particule p(2, "C", 1.0, Vecteur(0, 0, 0), Vecteur(0, 0, 0), Vecteur(-1, 0, 0));
    u.add(p);

    Absorption cl;

    ASSERT_EQ(u.getParticlesNumber(), 1);
    ASSERT_TRUE(cl.estHorsLimites(u.getParticules()[0], u));

    cl.appliquer(u.getParticules()[0], u);

    EXPECT_EQ(u.getParticlesNumber(), 0);
}

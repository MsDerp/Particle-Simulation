//
// Created by belfaidm on 5/2/25.
//


#include <gtest/gtest.h>
#include "Cellule.hxx"
#include "Particule.hxx"
#include "Vecteur.hxx"

TEST(CelluleTest, AjouterEtRecupererParticules) {
    Cellule c;
    Particule* p1 = new Particule(1, "A", 1.0, Vecteur(0,0,0), Vecteur(0,0,0), Vecteur(0,0,0));
    Particule* p2 = new Particule(2, "B", 2.0, Vecteur(1,0,0), Vecteur(0,1,0), Vecteur(0,0,1));

    c.ajouterParticule(p1);
    c.ajouterParticule(p2);

    auto& particules = c.getParticules();
    EXPECT_EQ(particules.size(), 2);
    EXPECT_EQ(particules[0], p1);
    EXPECT_EQ(particules[1], p2);

    delete p1;
    delete p2;
}

TEST(CelluleTest, AjouterEtRecupererVoisines) {
    Cellule c1, c2, c3;
    c1.ajouterVoisine(&c2);
    c1.ajouterVoisine(&c3);

    auto& voisines = c1.getVoisines();
    EXPECT_EQ(voisines.size(), 2);
    EXPECT_EQ(voisines[0], &c2);
    EXPECT_EQ(voisines[1], &c3);
}

TEST(CelluleTest, ClearParticulesVideLaListe) {
    Cellule c;
    Particule* p = new Particule(1, "test", 1.0, Vecteur(0,0,0), Vecteur(0,0,0), Vecteur(2,0,0));
    c.ajouterParticule(p);
    EXPECT_FALSE(c.getParticules().empty());

    c.clearParticules();
    EXPECT_TRUE(c.getParticules().empty());

    delete p;
}

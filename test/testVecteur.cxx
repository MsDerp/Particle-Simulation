//
// Created by belfaidm on 5/2/25.
//

#include "Vecteur.hxx"
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>

TEST(VecteurTest, ConstructorAndGetters) {
    Vecteur v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.getxCoordinate(), 1.0);
    EXPECT_DOUBLE_EQ(v.getyCoordinate(), 2.0);
    EXPECT_DOUBLE_EQ(v.getzCoordinate(), 3.0);
}

TEST(VecteurTest, SetMethod) {
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2(4.0, 5.0, 6.0);
    v1.set(v2);
    EXPECT_DOUBLE_EQ(v1.getxCoordinate(), 4.0);
    EXPECT_DOUBLE_EQ(v1.getyCoordinate(), 5.0);
    EXPECT_DOUBLE_EQ(v1.getzCoordinate(), 6.0);
}

TEST(VecteurTest, AddAndSubMethods) {
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2(4.0, 5.0, 6.0);
    v1.add(v2);
    EXPECT_DOUBLE_EQ(v1.getxCoordinate(), 5.0);
    EXPECT_DOUBLE_EQ(v1.getyCoordinate(), 7.0);
    EXPECT_DOUBLE_EQ(v1.getzCoordinate(), 9.0);
    v1.sub(v2);
    EXPECT_DOUBLE_EQ(v1.getxCoordinate(), 1.0);
    EXPECT_DOUBLE_EQ(v1.getyCoordinate(), 2.0);
    EXPECT_DOUBLE_EQ(v1.getzCoordinate(), 3.0);
}

TEST(VecteurTest, ScalarMultiplication) {
    Vecteur v(1.0, -2.0, 3.0);
    v.mul(2.0);
    EXPECT_DOUBLE_EQ(v.getxCoordinate(), 2.0);
    EXPECT_DOUBLE_EQ(v.getyCoordinate(), -4.0);
    EXPECT_DOUBLE_EQ(v.getzCoordinate(), 6.0);
}

TEST(VecteurTest, OperatorOverloads) {
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2(4.0, 5.0, 6.0);
    Vecteur sum = v1 + v2;
    Vecteur diff = v1 - v2;
    Vecteur scaled = v1 * 2.0;
    Vecteur neg = -v1;

    EXPECT_DOUBLE_EQ(sum.getxCoordinate(), 5.0);
    EXPECT_DOUBLE_EQ(diff.getyCoordinate(), -3.0);
    EXPECT_DOUBLE_EQ(scaled.getzCoordinate(), 6.0);
    EXPECT_DOUBLE_EQ(neg.getxCoordinate(), -1.0);
}

TEST(VecteurTest, ScalarLeftMultiplication) {
    Vecteur v(1.0, 2.0, 3.0);
    Vecteur result = 2.0 * v;
    EXPECT_DOUBLE_EQ(result.getxCoordinate(), 2.0);
    EXPECT_DOUBLE_EQ(result.getyCoordinate(), 4.0);
    EXPECT_DOUBLE_EQ(result.getzCoordinate(), 6.0);
}

TEST(VecteurTest, NormAndNormalize) {
    Vecteur v(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(v.norm(), 5.0);

    Vecteur normed = v.normalized();
    EXPECT_NEAR(normed.getxCoordinate(), 0.6, 1e-6);
    EXPECT_NEAR(normed.getyCoordinate(), 0.8, 1e-6);
    EXPECT_NEAR(normed.getzCoordinate(), 0.0, 1e-6);
}

TEST(VecteurTest, NormalizeZeroVectorThrows) {
    Vecteur zero(0.0, 0.0, 0.0);
    EXPECT_THROW(zero.normalized(), std::runtime_error);
}

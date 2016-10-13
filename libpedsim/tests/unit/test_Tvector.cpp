#include "gtest/gtest.h"

#include "ped_vector.h"

class TvectorTest : public testing::Test {
public:
  Ped::Tvector a;
  Ped::Tvector b;
 
  virtual void SetUp() {
    a.x = 1;
    a.y = 2;
    a.z = 3;

    b.x = 4;
    b.y = 5;
    b.z = 6;
  }
 
  virtual void TearDown() {
  }
};
 
TEST_F(TvectorTest, intialLength) {
  Ped::Tvector c;
  ASSERT_EQ(0, c.length());
}

TEST_F(TvectorTest, length) {
  ASSERT_NEAR(3.74, a.length(), 0.01);
}

TEST_F(TvectorTest, lengthSquared) {
  ASSERT_EQ(14.0, a.lengthSquared());
}

TEST_F(TvectorTest, normalize) {
  a.normalize();
  ASSERT_EQ(1.0, a.length());
}

TEST_F(TvectorTest, normalized) {
  Ped::Tvector c = a.normalized();
  ASSERT_EQ(1.0, c.length());
}

TEST_F(TvectorTest, normalizeZeroLength) {
  Ped::Tvector c;
  c.normalize();
  ASSERT_EQ(0.0, c.length());
}

TEST_F(TvectorTest, normalizedZeroLength) {
  Ped::Tvector c;
  Ped::Tvector d = c.normalized();
  ASSERT_EQ(d.length(), c.length());
}

TEST_F(TvectorTest, dotProduct) {
  ASSERT_EQ(32.0, Ped::Tvector::dotProduct(a, b));
}

TEST_F(TvectorTest, scalar) {
  ASSERT_NEAR(0.23, Ped::Tvector::scalar(a, b), 0.01);
}

TEST_F(TvectorTest, crossProduct) {
  Ped::Tvector c;
  c.x = 1;
  c.y = 1;
  c.z = 1;
  Ped::Tvector d;
  d.x = 0;
  d.y = 1;
  d.z = 0;
  ASSERT_EQ(-1.0, Ped::Tvector::crossProduct(c, d).x);
  ASSERT_EQ( 0.0, Ped::Tvector::crossProduct(c, d).y);
  ASSERT_EQ( 1.0, Ped::Tvector::crossProduct(c, d).z);
}

TEST_F(TvectorTest, scale) {
  ASSERT_EQ(56.0, a.scaled(2.0).lengthSquared());
  a.scale(2.0);
  ASSERT_EQ(56.0, a.lengthSquared());
}

TEST_F(TvectorTest, leftNormalVector) {
  Ped::Tvector c = a.leftNormalVector();
  ASSERT_EQ(-2.0, c.x);
  ASSERT_EQ( 1.0, c.y);
}

TEST_F(TvectorTest, rightNormalVector) {
  Ped::Tvector c = a.rightNormalVector();
  ASSERT_EQ( 2.0, c.x);
  ASSERT_EQ(-1.0, c.y);
}

TEST_F(TvectorTest, polarRadius) {
  ASSERT_NEAR(3.74, a.polarRadius(), 0.01);
}

TEST_F(TvectorTest, polarAngle) {
  ASSERT_NEAR(1.11, a.polarAngle(), 0.01);
}

TEST_F(TvectorTest, angleTo) {
  ASSERT_NEAR(-0.21, a.angleTo(b), 0.01);
}

TEST_F(TvectorTest, operatorAddition) {
  Ped::Tvector c = a + b;
  ASSERT_EQ(5.0, c.x);
  ASSERT_EQ(7.0, c.y);
  ASSERT_EQ(9.0, c.z);
}

TEST_F(TvectorTest, operatorDifference) {
  Ped::Tvector c = a - b;
  ASSERT_EQ(-3.0, c.x);
  ASSERT_EQ(-3.0, c.y);
  ASSERT_EQ(-3.0, c.z);
}

TEST_F(TvectorTest, operatorMultiplication) {
  Ped::Tvector c = 2.0 * a;
  ASSERT_EQ(2.0, c.x);
  ASSERT_EQ(4.0, c.y);
  ASSERT_EQ(6.0, c.z);
}

TEST_F(TvectorTest, operatorDivision) {
  Ped::Tvector c = a / 2.0;
  ASSERT_EQ(0.5, c.x);
  ASSERT_EQ(1.0, c.y);
  ASSERT_EQ(1.5, c.z);
}

TEST_F(TvectorTest, operatorAdditionAssignment) {
  a += b;
  ASSERT_EQ(5.0, a.x);
  ASSERT_EQ(7.0, a.y);
  ASSERT_EQ(9.0, a.z);
}

TEST_F(TvectorTest, operatorSubtractionAssignment) {
  a -= b;
  ASSERT_EQ(-3.0, a.x);
  ASSERT_EQ(-3.0, a.y);
  ASSERT_EQ(-3.0, a.z);
}

TEST_F(TvectorTest, operatorMultiplicationAssignmentScalar) {
  a *= 2.0;
  ASSERT_EQ(2.0, a.x);
  ASSERT_EQ(4.0, a.y);
  ASSERT_EQ(6.0, a.z);
}

TEST_F(TvectorTest, operatorMultiplicationAssignmentVector) {
  a *= b;
  ASSERT_EQ( 4.0, a.x);
  ASSERT_EQ(10.0, a.y);
  ASSERT_EQ(18.0, a.z);
}

TEST_F(TvectorTest, operatorDivisionAssignmentScalar) {
  a /= 2.0;
  ASSERT_EQ(0.5, a.x);
  ASSERT_EQ(1.0, a.y);
  ASSERT_EQ(1.5, a.z);
}

TEST_F(TvectorTest, operatorEqualTo) {
  ASSERT_EQ(true, a == a);
  ASSERT_EQ(false, a == b);
}

TEST_F(TvectorTest, operatorNotEqualTo) {
  ASSERT_EQ(false, a != a);
  ASSERT_EQ(true, a != b);
}

TEST_F(TvectorTest, operatorUnaryMinus) {
  Ped::Tvector b = -a;  
  ASSERT_EQ(-a.x, b.x);
  ASSERT_EQ(-a.y, b.y);
  ASSERT_EQ(-a.z, b.z);
}

TEST_F(TvectorTest, lineIntersection) {
  Ped::Tvector p0;
  p0.x = 0;
  p0.y = 0;
  p0.z = 0;
  Ped::Tvector p1;
  p1.x = 0;
  p1.y = 2;
  p1.z = 0;
  Ped::Tvector p2;
  p2.x = -1;
  p2.y = 1;
  p2.z = 0;
  Ped::Tvector p3;
  p3.x = 1;
  p3.y = 1;
  p3.z = 0;

  Ped::Tvector i;
  bool ret = Ped::Tvector::lineIntersection(p0, p1, p2, p3, &i);

  ASSERT_EQ(0, i.x);
  ASSERT_EQ(1, i.y);
  ASSERT_EQ(0, i.z);
  ASSERT_TRUE(ret);
}

TEST_F(TvectorTest, rotate) {
  Ped::Tvector r = a.rotated(3.1415/2);  
  ASSERT_NEAR(-2, r.x, 0.001);
  ASSERT_NEAR(1, r.y, 0.001);
  ASSERT_NEAR(0, r.z, 0.001); // z unused, set to 0 as per initializer

  a.rotate(3.1415/2);
  ASSERT_NEAR(-2, a.x, 0.001);
  ASSERT_NEAR(1, a.y, 0.001);
  ASSERT_NEAR(3, a.z, 0.001); // z unused, left as it was.
}

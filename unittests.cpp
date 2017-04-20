#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

// IMPORTANT NOTE:
// These are just a few examples from my solution and **should be removed**.
// Depending on your code design your class and functions names would differ

// #include "geometry.hpp"

// TEST_CASE( "Test Basic Geometry: Vec3d ", "[geometry]" ) {

//   Vec3d a(2,0,0), b(0,4,0);
  
//   REQUIRE(a.x == Approx(2));
//   REQUIRE(a.y == Approx(0));
//   REQUIRE(a.z == Approx(0));

//   REQUIRE(b.x == Approx(0));
//   REQUIRE(b.y == Approx(4));
//   REQUIRE(b.z == Approx(0));

//   double adotb = dot(a,b);
//   REQUIRE(adotb == Approx(0));

//   Vec3d anorm = norm(a);
//   REQUIRE(anorm.x == Approx(1));
//   REQUIRE(anorm.y == Approx(0));
//   REQUIRE(anorm.z == Approx(0));

//   Vec3d bnorm = norm(b);
//   REQUIRE(bnorm.x == Approx(0));
//   REQUIRE(bnorm.y == Approx(1));
//   REQUIRE(bnorm.z == Approx(0));
// }

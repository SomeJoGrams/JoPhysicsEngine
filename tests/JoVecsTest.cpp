#include "gtest/gtest.h"

#include "JoVecs.hpp"


// TEST(TestSuite, TestName){

namespace JoVecs{
// The fixture for testing class Foo.
class JVecTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  JVecTest() {
    // You can do set-up work for each test here.
  }

  ~JVecTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
    //myVec[0] = 3;
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
    JoVecs::JVec<int,3> myVec;
    JoVecs::JVec<int,3> myVec2;
    JoVecs::JVec<int,3> myVec3;
    JoVecs::JVec<int,3> myVec4;

};


// }

TEST(JVecTest, VALUEADD){
  JoVecs::JVec<int,3> myVec3(5);
  JoVecs::JVec<int,3> myVec4(10);
  EXPECT_EQ(myVec3 + myVec3,myVec4); 
}
TEST(JVecTest, VALUESUBSTRACT){
  JoVecs::JVec<int,3> myVec3(5);
  JoVecs::JVec<int,3> myVec4(0);
  EXPECT_EQ(myVec3 - myVec3,myVec4) << myVec3[0] << " " << myVec3[1] << " " << myVec3[2]; 
}
TEST(JVecTest, VALUESUBSTRACT2){
  JoVecs::JVec<int,3> myVec2(3);
  JoVecs::JVec<int,3> myVec3(10);
  JoVecs::JVec<int,3> myVec4(7);
  EXPECT_EQ(myVec3 - myVec4,myVec2); 
}
TEST(JVecTest, VALUESUBSTRACT3){
  JoVecs::JVec<int,3> myVec2(3);
  JoVecs::JVec<int,3> myVec3(3);
  JoVecs::JVec<int,3> myVec4(0);
  EXPECT_EQ(myVec3 - myVec2,myVec4); 
}
TEST(JVecTest, VALUEADD2){
  JoVecs::JVec<int,3> myVec3(5);
  JoVecs::JVec<int,3> myVec4(11);
  EXPECT_NE(myVec3 + myVec3,myVec4); 
}

TEST(JVecTest, VALUEMULTIPLYPOS){
  JoVecs::JVec<int,3> myVec3(5);
  JoVecs::JVec<int,3> myVec4(15);
  int multVal = 3;
  EXPECT_EQ(myVec3 * multVal,myVec4); 
}
TEST(JVecTest, VALUEMULTIPLYPOS2){
  JoVecs::JVec<int,3> myVec3(50);
  JoVecs::JVec<int,3> myVec4(100);
  int multVal = 2;
  EXPECT_EQ(myVec3 * multVal,myVec4); 
}





TEST(JVecTest, EMPTYCTOR){
    JoVecs::JVec<int,3> myVec;
    JoVecs::JVec<int,3> myVec2;
    // myVec2();
    EXPECT_EQ(myVec,myVec2); 
    //EXPECT_EQ(0,1);   
}

TEST(JVecTest, JVecAdditionPos){

}

TEST(JVecTest, Woah){
    EXPECT_EQ(addOne(1), 2);
}

}




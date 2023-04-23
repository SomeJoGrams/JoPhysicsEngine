#include <iostream>
#include "JoVecs.hpp"

using newVec = JoVecs::JVec<double,3>;

int main(){

    newVec myVec3(150);
    newVec resultVec;
    double rot = 0.4;
    // JoVecs::rotateVectorAroundZ<double>(myVec3, rot);
    JoVecs::JVec<double,3> myVec4(3);
    // JoVecs::JMat<double,3,3> myMat(4);
    // myMat.element(1,0) = 7;
    // myMat.element(2,2) = 9;
    // std::cout << (myMat * myVec4);
    // resultVec = JoVecs::rotateVectorAroundX(myVec4, JoVecs::AngleConv::degreesToRad(static_cast<double>(90)));
    // std::cout << resultVec;
    // resultVec = JoVecs::rotateVectorAroundY(myVec4, JoVecs::AngleConv::degreesToRad(static_cast<double>(90)));
    // std::cout << resultVec;
    // resultVec = JoVecs::rotateVectorAroundZ(myVec4, JoVecs::AngleConv::degreesToRad(static_cast<double>(90)));
    // std::cout << resultVec;
    // resultVec = JoVecs::rotateVectorX(myVec4, JoVecs::AngleConv::degreesToRad(static_cast<double>(90)));
    // std::cout << resultVec;
    // resultVec = JoVecs::rotateVectorY(myVec4, JoVecs::AngleConv::degreesToRad(static_cast<double>(90)));
    // std::cout << resultVec;
    // resultVec = JoVecs::rotateVectorZ(myVec4, JoVecs::AngleConv::degreesToRad(static_cast<double>(90)));
    // std::cout << resultVec;


}


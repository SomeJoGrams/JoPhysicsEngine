#include <vector>
#include <cmath>
#include "JoVecs.hpp"

namespace JoVecs{

template <typename Val>
JVec<Val,3> rotateVectorAroundZ(const JVec<Val,3>& vec1, const Val rotation){ // rotation in rad
    JVec<Val,3> resultVec;
    JMat<Val,3,3> newMat;
    newMat.element(0,0) = std::cos(rotation);
    newMat.element(1,0) = -1 * std::sin(rotation);
    newMat.element(2,0) = 0;
    newMat.element(0,1) = std::sin(rotation);
    newMat.element(1,1) = std::cos(rotation);
    newMat.element(2,1) = 0;
    newMat.element(0,2) = 0;
    newMat.element(1,2) = 0;
    newMat.element(2,2) = 1;
    resultVec = newMat * vec1;
    return resultVec;
}

template <typename Val>
JVec<Val,3> rotateVectorAroundY(const JVec<Val,3>& vec1, const Val rotation){
    JVec<Val,3> resultVec;
    JMat<Val,3,3> newMat;
    newMat.element(0,0) = std::cos(rotation);
    newMat.element(1,0) = 0;
    newMat.element(2,0) = std::sin(rotation);
    newMat.element(0,1) = 0;
    newMat.element(1,1) = 1;
    newMat.element(2,1) = 0;
    newMat.element(0,2) = -1 * std::sin(rotation);
    newMat.element(1,2) = 0;
    newMat.element(2,2) = std::cos(rotation);
    resultVec = newMat * vec1;
    return resultVec;
}


template <typename Val>
JVec<Val,3> rotateVectorAroundX(const JVec<Val,3>& vec1, const Val rotation){
    JVec<Val,3> resultVec;
    JMat<Val,3,3> newMat;
    newMat.element(0,0) = 1;
    newMat.element(1,0) = 0;
    newMat.element(2,0) = 0;
    newMat.element(0,1) = 0;
    newMat.element(1,1) = std::cos(rotation);
    newMat.element(2,1) = -1 * std::sin(rotation);
    newMat.element(0,2) = 0;
    newMat.element(1,2) = std::sin(rotation);
    newMat.element(2,2) = std::cos(rotation);
    resultVec = (newMat * vec1);
    return resultVec;
}

template<typename Val>
JVec<Val,3> rotateVector(const JVec<Val,3>& vec1,const JVec<Val,3>& rotationVector, const Val rotationDeg){ // deg in rad
    JVec<Val,3> scaledRotationVector = rotationVector * std::sin(rotationDeg/2);
    JoQuaternion::JQuaternion<Val> resultQuaternion;
    JoQuaternion::JQuaternion<Val> pointQuaternion{0, vec1[0], vec1[1], vec1[2]};
    JoQuaternion::JQuaternion<Val> leftQuaternion{std::cos(rotationDeg/2),scaledRotationVector[0],scaledRotationVector[1],scaledRotationVector[2]};
    resultQuaternion = leftQuaternion * pointQuaternion * JoQuaternion::inverse(leftQuaternion);
    JVec<Val,3> resultVec(resultQuaternion.bVal, resultQuaternion.cVal, resultQuaternion.dVal);
    return resultVec;
}

template<typename Val>
JVec<Val,3> rotateVectorX(const JVec<Val,3>& vec, const Val rotationDegrees){ // deg in rad
    JVec<Val,3> rotationVector(1,0,0);
    //JoQuaternion::JUnitQuaternion{std::cos(rotation/2),1,0,0};
    return rotateVector(vec, rotationVector, rotationDegrees);
}

template<typename Val>
JVec<Val,3> rotateVectorY(const JVec<Val,3>& vec, const Val rotationDegrees){
    JVec<Val,3> rotationVector(0,1,0);
    //JoQuaternion::JUnitQuaternion{std::cos(rotation/2),1,0,0};
    return rotateVector(vec, rotationVector, rotationDegrees);
}

template<typename Val>
JVec<Val,3> rotateVectorZ(const JVec<Val,3>& vec, const Val rotationDegrees){
    JVec<Val,3> rotationVector(0,0,1);
    //JoQuaternion::JUnitQuaternion{std::cos(rotation/2),1,0,0};
    return rotateVector(vec, rotationVector, rotationDegrees);
}

template <typename Val>
Val dotproduct(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2){
    Val sum;
    for (size_t curDim = 0; curDim < 3; curDim++){
        sum += vec1[curDim]*vec2[curDim];
    }
    return sum;
}

template <typename Val, size_t dimension> 
Val ndimNorm(const JVec<Val,dimension>& vec){ // TODO should this maybe be float or use int auto round for int Vectors?
    Val sum;
    for (size_t curDim = 0; curDim < dimension; curDim++){
        sum += vec[curDim] * vec[curDim];
    }
    return std::sqrt(sum);
}


// template <typename Val> 
// Val magnitude(const JVec<Val,3>& vec){ // TODO should this maybe be float or use int auto round for int Vectors?
//     return std::hypot(vec[0],vec[1],vec[2]);
// }

template <typename Val> 
Val magnitude(const JVec<Val,3>& vec){ // TODO should this maybe be float or use int auto round for int Vectors?
    return std::hypot(vec[0],vec[1],vec[2]);
}

template <typename Val> 
Val euclideanNorm(const JVec<Val,3>& vec){ // TODO should this maybe be float or use int auto round for int Vectors?
    return magnitude(vec);
}

template <typename Val>
Val distance(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2){
    return std::hypot(vec2[0] - vec1[0],vec2[1] - vec1[1],vec2[2] - vec1[2]);
}

template <typename Val>
Val angle(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2){
    // u dot pro v = cos(theta) * || u || * || v ||
    // (u dot v) / (|| u || * || v ||) = cos(theta)
    // acos((u dot v) / (|| u || * || v ||)) = theta
    Val factor(dotproduct(vec1, vec2));
    Val factor2(euclideanNorm(vec1) * euclideanNorm(vec2));
    return std::acos(factor / factor2);
}


template <typename Val, size_t dimension>
JVec<Val,dimension> normalize(const JVec<Val,dimension>& vec){
    JVec<Val,dimension> resultVec;
    Val length = ndimNorm(vec);
    // calc percent of length for each coordinate
    resultVec = vec / length;
    return resultVec;
}

template <typename Val>
JVec<Val,3> normalize(const JVec<Val,3>& vec){
    JVec<Val,3> resultVec;
    Val length = magnitude(vec);
    // calc percent of length for each coordinate
    std::cout << length;
    resultVec = vec / length;
    return resultVec;
}

template<typename Val, size_t dimensionX, size_t dimensionY>
JMat<Val, dimensionY, dimensionX> transposeMatrix(const JMat<Val, dimensionX, dimensionY>& mat1){
    JMat<Val, dimensionY, dimensionX> resultMat;
    for (size_t row = 0; row < dimensionX; row++){
        for (size_t col = 0; col < dimensionY; col++){
            resultMat.element(row,col) = mat1.element(col,row);
        }
    }
    return resultMat;
}

template<typename Val, size_t dimensionX, size_t dimensionY>
JVec<Val, dimensionY> matrixCol(const JMat<Val, dimensionX, dimensionY>& mat1,const size_t col){
    JVec<Val, dimensionX> resultVec;
    for (size_t elIn = 0; elIn < dimensionX; elIn++){
        resultVec[elIn] = mat1.element(col, elIn);
    }
    return resultVec;
}

template<typename Val, size_t dimensionX, size_t dimensionY>
JVec<Val, dimensionX> matrixRow(const JMat<Val, dimensionX, dimensionY>& mat1,const size_t row){
    JVec<Val, dimensionX> resultVec;
    for (size_t elIn = 0; elIn < dimensionX; elIn++){
        resultVec[elIn] = mat1.element(elIn, row);
    }
    return resultVec;
}


template <typename Val>
Val determinant(const JMat<Val,3,3>& mat){
    Val posSum = mat.element(0,0) * mat.element(1,1)*mat.element(2,2) + mat.element(1,0) * mat.element(2,1) * mat.element(1,2) + mat.element(2,0) * mat.element(0,1)* mat.element(1,2);
    Val negSum = (-1) * mat.element(0,2) * mat.element(1,1) * mat.element(2,0) - mat.element(1,2) * mat.element(2,1) * mat.element(0,0) - mat.element(2,2) * mat.element(0,1) * mat.element(1,0);
    return posSum + negSum;
}
template <typename Val>
Val determinant(const JMat<Val,2,2>& mat){
    return mat.element(0,0) * mat.element(1,1) - mat.element(0,1) * mat.element(1,0);
}

template<typename Val, size_t dimensionX, size_t dimensionY> // remove row and column
JMat<Val,dimensionX-1,dimensionY-1> minorMatrix(const size_t row, const size_t col,const JMat<Val, dimensionX,dimensionY>& mat1){ // TODO add row and col check?
    JMat<Val, dimensionX-1, dimensionY-1> resultMatrix;
    size_t filledXDim = 0;
    size_t filledYDim = 0;
    for (size_t xDim = 0; xDim < dimensionX; xDim ++){
        if (xDim == row){
                // skip row and increase dim
                xDim += 1;
            }
        for (size_t yDim = 0; yDim < dimensionX; yDim ++){
            // skip col and increase dim
            if (yDim == col){
                yDim += 1;
            }
            resultMatrix.element(filledXDim, filledYDim) = mat1.element(xDim,yDim);
            filledYDim += 1;
        }
        filledXDim +=1;

    }
    return resultMatrix;
}

template<typename Val>
JMat<Val,3,3> adjMatrix(const JMat<Val, 3,3>& mat1){
    JMat<Val,3,3> resultMat;
    for (size_t xDim = 0; xDim < 3; xDim++){
        for (size_t yDim = 0; yDim < 3; yDim++){
            resultMat.element(xDim,yDim) = std::pow(-1, xDim+yDim) * determinant(minorMatrix(xDim,yDim,mat1));
        }
    }
    return resultMat;
}

template<typename Val>
JMat<Val,3,3> invertMatrix(const JMat<Val, 3,3>& mat1){
    JMat<Val,3,3> resultMat = adjMatrix(mat1);
    return (1/determinant(mat1)) * resultMat;
}


// template class JVec<double,3>;
//template double determinant(const JMat<double,3,3>& mat);
//template double magnitude(const JVec<double,3>& vec);
// // template JVec<double,3> rotateVectorAroundX(const JVec<double,3>& vec1, const double rotation);


// template <> JVec<double,3> rotateVectorAroundX(const JVec<double,3>& vec1,const double rotation);
//template JVec<double,3> rotateVectorAroundZ(const JVec<double,3>& vec1, const double rotation);




// template double magnitude(const JVec<double,3>& vec);

// template JVec<double,3> normalize(const JVec<double,3>& vec);

// template double dotproduct(const JVec<double,3>& vec1,const JVec<double,3>& vec2);

// template JVec<double,3> rotateVectorAroundZ(const JVec<double,3>& vec1, const double rotation);
// template JVec<double,3> rotateVectorAroundX(const JVec<double,3>& vec1, const double rotation);
// template JVec<double,3> rotateVectorAroundY(const JVec<double,3>& vec1, const double rotation);
// template JVec<double,3> rotateVectorX(const JVec<double,3>& vec, const double rotationDegrees);
// template JVec<double,3> rotateVectorY(const JVec<double,3>& vec, const double rotationDegrees);
// template JVec<double,3> rotateVectorZ(const JVec<double,3>& vec, const double rotationDegrees);

};

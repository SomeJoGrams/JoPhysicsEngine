#include <vector>
#include <cmath>

#include "JoQuaternion.hpp"

#define debug TRUE

#ifdef debug
#include <iostream>
#endif

namespace JoVecs{

// template <typename fpVal>
// struct VecAngle{
//     fpVal radians;
// };

namespace MathConst{
    template<typename Val>
    const Val pi = 3.1415926535897932384626433;
}

namespace AngleConv{
    template <typename fpVal>
    fpVal radiansToDegrees(fpVal rad){
        // 360 deg = 2 pi rad
        // deg = 2 pi rad / 360
        // deg = (pi*rad) / 180
        return (MathConst::pi<fpVal>*rad) / static_cast<fpVal>(180); // TODO does this need a static cast?
    }

    template <typename fpVal>
    fpVal radiansToGrad(fpVal rad){
        // 2 pi rad = 400 grad
        // (2 pi rad / 400) = grad
        // pi * rad / 200 = grad
        return (MathConst::pi<fpVal> * rad) / static_cast<fpVal>(200); // TODO does this need a static cast?
    }

    template <typename fpVal>
    fpVal degreesToRad(fpVal degrees){
        // 360 deg = 2 pi rad
        // 360 deg / 2 pi = rad
        // (180 deg) / pi = rad
        return (static_cast<fpVal>(180) * degrees ) / MathConst::pi<fpVal>; // TODO does this need a static cast?
    }

    template <typename fpVal>
    fpVal gradToRad(fpVal grad){
        // 2 pi rad = 400 grad
        // rad = (400 grad )/ 2 pi
        return (static_cast<fpVal>(400) * grad) / static_cast<fpVal>(2) * MathConst::pi<fpVal>;
    }
}

template <typename Val, size_t dimension>
class JVec{
    private:
        std::vector<Val> curVec;
    public:
        JVec() : curVec(dimension){
        };
        JVec(Val x): curVec(dimension,x){
            
        };
        JVec(Val x1, Val x2, Val x3): curVec(){
            curVec.push_back(x1);
            curVec.push_back(x2);
            curVec.push_back(x3);
            curVec.resize(dimension);
        };
        JVec(const JVec<Val,dimension>& x): curVec(x.curVec.begin(), x.curVec.end()){

        };

        // sollte 2 mal definiert sein + da garantiert mit eingebauten Typen benutzt wird kann return by value benutzt werden
        constexpr Val operator[](size_t index) const{
            // constexpr impliziert inline + erlaubt es dass typen zur kompilierzeit ausgewertet werden bspw, wenn int zurücktgibt erkennt compiler int typ
            return curVec[index];
        }
        constexpr Val& operator[](size_t index){
            // constexpr impliziert inline + erlaubt es dass typen zur kompilierzeit ausgewertet werden bspw, wenn int zurücktgibt erkennt compiler int typ
            return curVec[index];
        }
        // constexpr JVec& operator=(const JVec& vec2){
        //     for(int dim=0; dim < dimension; dim++){
        //         (*this)[dim] = vec2[dim];
        //     }
        //     return *this;
        // }
};



template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator+(const JVec<Val, dimension> vec1, const JVec<Val, dimension> vec2)
{
    JVec<Val, dimension> resultVec;
    for(int dim=0; dim < dimension; dim++){
        resultVec[dim] = vec1[dim] + vec2[dim];
    }
    return resultVec;
};

template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator+=(const JVec<Val,dimension> vec1, const JVec<Val,dimension>& vec2) // TODO Check if already uses operator "+"
{
    JVec<Val,dimension> resultVec;
    resultVec = vec1 + vec2;
    return resultVec;
};

template <typename Val>
bool operator==(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2){
    return vec1[0] == vec2[0] && vec1[1] == vec2[1] && vec1[2] == vec2[2];
}
template <typename Val>
bool operator!=(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2){
    return !(vec1 == vec2);
}

template <typename Val>
bool operator<=(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2){
    return vec1[0] <= vec2[0] && vec1[1] <= vec2[1] && vec1[2] <= vec2[2];
}

template <typename Val, size_t dimension>
JVec<Val,dimension> operator*(const JVec<Val,dimension>& vec1, const Val val){
    JVec<Val, dimension> resultVec;
    // JVec<Val,3> newVec(vec1);
    // newVec[0] *= val;
    // newVec[1] *= val;
    // newVec[2] *= val;
    for(size_t curEl = 0; curEl < dimension; curEl++){
        resultVec[curEl] = vec1[curEl] * val;
    }
    return resultVec;
}

template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator*(const Val val,const JVec<Val,dimension>& vec1){
    JVec<Val, dimension> resultVec;
    resultVec = val * vec1;
    // JVec<Val,3> newVec(vec1);
    // newVec[0] *= val;
    // newVec[1] *= val;
    // newVec[2] *= val;
    return resultVec;
}

template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator*=(const JVec<Val,dimension>& vec1,const Val val){
    JVec<Val,dimension> resultVec;
    // newVec[0] *= val;
    // newVec[1] *= val;
    // newVec[2] *= val;
    resultVec = vec1 * val;
    return resultVec;
}

template <typename Val,size_t dimension>
inline JVec<Val,dimension> operator-(const JVec<Val, dimension>& vec1,const JVec<Val, dimension>& vec2){
    JVec<Val,dimension> resultVec;
    JVec<Val,dimension> negatedVec2;
    negatedVec2 = (-1) * vec2;
    resultVec = vec1 + negatedVec2;
    return resultVec;
}


template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator/(const JVec<Val,dimension>& vec1, const Val val){
    JVec<Val,dimension> resultVec;
    resultVec = vec1 * (1/val);
    return resultVec;
}

template <typename Val, size_t dimension>
std::ostream& operator<<(std::ostream& os, const JVec<Val,dimension>& obj){
    for (size_t curDim = 0; curDim < dimension; curDim++){
        os << obj[curDim] << " ";
    }
    os << "\n";
    return os;
}

template <typename Val>
Val dotproduct(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2);

template <typename Val> 
Val magnitude(const JVec<Val,3>& vec);

template <typename Val, size_t dimension> 
Val ndimNorm(const JVec<Val,dimension>& vec);


template <typename Val> 
Val euclideanNorm(const JVec<Val,3>& vec);

template <typename Val>
Val distance(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2);

/*
*   Desc: return Value from acos from [0, pi]
*/
template <typename Val>
Val angle(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2);

template <typename Val>
JVec<Val,3> normalize(const JVec<Val,3>& vec);

template <typename Val, size_t dimension>
JVec<Val,dimension> normalize(const JVec<Val,dimension>& vec);


// vector with vector initializer
template<typename Val, size_t dimensionX, size_t dimensionY>
class JMat
{
    private:
        std::vector<Val> curVec;
    public:
        JMat() : curVec(dimensionX * dimensionY) {};
        JMat(Val x) : curVec(dimensionX * dimensionY,x) {};
        JMat(const JMat& otherMat) : curVec(otherMat.begin(), otherMat.end()) {};
        constexpr Val element(size_t xCoord, size_t yCoord) const{
            return curVec[xCoord + yCoord * dimensionY];
        }            
        constexpr Val& element(size_t xCoord, size_t yCoord){
            return curVec[xCoord + yCoord * dimensionY];
        }        
        constexpr Val element(int xCoord, int yCoord) const{
            return curVec[static_cast<size_t>(xCoord) + static_cast<size_t>(yCoord)*dimensionY];
        }
        constexpr Val& element(int xCoord, int yCoord){
            return curVec[static_cast<size_t>(xCoord) + static_cast<size_t>(yCoord)*dimensionY];
        }
        constexpr Val element(size_t oneDimCord) const{
            return curVec[oneDimCord];
        }
        constexpr Val& element(size_t oneDimCord){
            return curVec[oneDimCord];
        }
        JMat operator+(const Val curVal){
            for (size_t elIn = 0; elIn < dimensionX * dimensionY; elIn++){
                curVec[elIn] += curVal;
            }
            return *this;
        } 

        JMat operator*(const Val curVal){
            for (size_t elIn = 0; elIn < dimensionX * dimensionY; elIn++){
                curVec[elIn] *= curVal;
            }
            return *this;
        }
        JMat operator/(const Val curVal){
            return *this * (1/curVal);
        }
};

template<typename Val, size_t dimensionX, size_t dimensionY>
inline JMat<Val, dimensionX, dimensionY> operator+(const JMat<Val, dimensionX, dimensionY>& mat1,const JMat<Val, dimensionX, dimensionY>& mat2){
    JMat<Val, dimensionX, dimensionY> resultMat;
    for (size_t elIn = 0; elIn < dimensionX * dimensionY; elIn++){
        resultMat[elIn] = mat1.element(elIn) + mat2.element(elIn);
    }
    return resultMat;
} 

template<typename Val, size_t dimensionX, size_t dimensionY>
inline JMat<Val, dimensionX, dimensionY> operator+=(const JMat<Val, dimensionX, dimensionY>& mat1,const JMat<Val, dimensionX, dimensionY>& mat2){
    JMat<Val, dimensionX, dimensionY> resultMat = mat1 + mat2;
    return resultMat;
}

template<typename Val, size_t dimensionX, size_t dimensionY>
inline JMat<Val, dimensionX, dimensionY> operator*(const JMat<Val, dimensionX, dimensionY>& mat1,const JMat<Val, dimensionY, dimensionX>& mat2){ //TODO maybe define for other dimension instead of only x
    JMat<Val, dimensionX, dimensionY> resultMat;
    Val sum;
    for (size_t row = 0; row < dimensionX; row++){
        for (size_t col = 0; col < dimensionY; col++){
            // elment wise multiply row times column
            // product sum formula
            sum = 0;
            for (size_t elIndex = 0; elIndex < dimensionY; elIndex++){
                sum += mat1.element(row,elIndex) * mat2.element(elIndex, col); // TODO safe values that get used twice
            }
            resultMat.element(row, col) = sum;
        }
    }
    return resultMat;
}

template<typename Val, size_t dimensionX, size_t dimensionY>
inline JVec<Val, dimensionY> operator*(const JMat<Val, dimensionX, dimensionY>& mat1,const JVec<Val, dimensionY>& vec){ //TODO maybe define for other dimension instead of only x
    JVec<Val, dimensionY> resultVec;
    Val sum = 0;
    for (size_t col = 0; col < dimensionX; col++){
            // elment wise multiply col times column
            // product sum formula
            sum = 0;
            for (size_t elIndex = 0; elIndex < dimensionY; elIndex++){
                sum += mat1.element(elIndex,col) * vec[elIndex]; // TODO safe values that get used twice
            }
            resultVec[col] = sum;
    }
    return resultVec;
}

// a b * e f = a*e + b*g , a*f + b*h
// c d   g h   c*e + d*g , c*f + d*h


template<typename Val, size_t dimensionX, size_t dimensionY>
inline JMat<Val, dimensionY, dimensionX> transposeMatrix(const JMat<Val, dimensionX, dimensionY>& mat1);

template<typename Val, size_t dimensionX, size_t dimensionY>
inline JVec<Val, dimensionX> matrixRow(const JMat<Val, dimensionX, dimensionY>& mat1,const size_t row);

template<typename Val, size_t dimensionX, size_t dimensionY>
inline JVec<Val, dimensionY> matrixCol(const JMat<Val, dimensionX, dimensionY>& mat1,const size_t col);


template <typename Val, size_t dimensionX, size_t dimensionY>
std::ostream& operator<<(std::ostream& os, const JMat<Val,dimensionX,dimensionY>& obj){
    for (size_t yDim = 0; yDim < dimensionY; yDim++){
        for (size_t xDim = 0; xDim < dimensionX; xDim++){
            os << obj.element(xDim, yDim) << " ";
        }
        os << "\n";
    }
    os << "\n";
    return os;
}


template<typename Val, size_t dimensionX, size_t dimensionY>
inline JMat<Val, dimensionX, dimensionY> operator*=(const JMat<Val, dimensionX, dimensionY>& mat1,const JMat<Val, dimensionY, dimensionX>& mat2){
    JMat<Val, dimensionX, dimensionY> resultMat = mat1 * mat2;
    return resultMat;
}

template <typename Val>
Val determinant(const JMat<Val,3,3>& mat);
template <typename Val>
Val determinant(const JMat<Val,2,2>& mat);

// using rotation matrices
template <typename Val>
JVec<Val,3> rotateVectorAroundX(const JVec<Val,3>& vec1, const Val rotation);

template <typename Val>
JVec<Val,3> rotateVectorAroundY(const JVec<Val,3>& vec1, const Val rotation);

template <typename Val>
JVec<Val,3> rotateVectorAroundZ(const JVec<Val,3>& vec1, const Val rotation);

// using quaternion rotation
template<typename Val>
JVec<Val,3> rotateVector(const JVec<Val,3>& vec1,const JVec<Val,3>& rotationVector, const Val rotationDegrees);
template<typename Val>
JVec<Val,3> rotateVectorX(const JVec<Val,3>& vec1, const Val rotationDegrees);
template<typename Val>
JVec<Val,3> rotateVectorY(const JVec<Val,3>& vec1, const Val rotationDegrees);
template<typename Val>
JVec<Val,3> rotateVectorZ(const JVec<Val,3>& vec1, const Val rotationDegrees);



template<typename Val>
JMat<Val,3,3> adjMatrix(const JMat<Val, 3,3>& mat1);

template<typename Val, size_t dimensionX, size_t dimensionY> // remove row and column
JMat<Val,dimensionX-1,dimensionY-1> minorMatrix(const size_t row, const size_t col,const JMat<Val, dimensionX,dimensionY>& mat1);

template<typename Val>
JMat<Val,3,3> invertMatrix(const JMat<Val, 3,3>& mat1);



inline int addOne(int x){
    return x + 1;
}


#include "JoVecsTemplated.hpp"

};

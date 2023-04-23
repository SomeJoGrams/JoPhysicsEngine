#include <cmath>
#include <iostream>


namespace JoQuaternion{


template <typename Val>
struct JQuaternion{
        Val aVal;
        Val bVal;
        Val cVal;
        Val dVal;
};

template <typename Val>
struct JUnitQuaternion : public JQuaternion<Val> {
};

template <typename Val>
class JPolarQuaternion{
    Val phiAngle;
    Val cleanUnit;

    JPolarQuaternion(JUnitQuaternion<Val> unitQuat){
        phiAngle = std::acos(unitQuat.aVal); // real Part
        JUnitQuaternion<Val> removedRealPart{0, unitQuat.bVal, unitQuat.cVal, unitQuat.dVal}; // Imaginary Part
        cleanUnit = removedRealPart * (1 / std::sin(phiAngle));
    }

};
        
template <typename Val>
inline JQuaternion<Val> operator+(const JQuaternion<Val>& quat1,const JQuaternion<Val>& quat2){
    JQuaternion<Val> resultQuat;
    resultQuat.aVal = quat1.aVal + quat2.aVal;
    resultQuat.bVal = quat1.bVal + quat2.bVal;
    resultQuat.cVal = quat1.cVal + quat2.cVal;
    resultQuat.dVal = quat1.dVal + quat2.dVal;
    return resultQuat;
}

template <typename Val>
inline JQuaternion<Val> operator*(const JQuaternion<Val>& quat1,const JQuaternion<Val>& quat2){
    JQuaternion<Val> resultQuat;
    Val sumReal = quat1.aVal * quat2.aVal - quat1.bVal * quat2.bVal - quat1.cVal * quat2.cVal - quat1.dVal * quat2.dVal;
    Val sumCompl1 = quat1.aVal * quat2.bVal + quat1.bVal * quat2.aVal + quat1.cVal * quat2.dVal - quat1.dVal * quat2.cVal;
    Val sumCompl2 = quat1.aVal * quat2.cVal - quat1.bVal * quat2.dVal + quat1.cVal * quat2.aVal + quat1.dVal * quat2.bVal;
    Val sumCompl3 = quat1.aVal * quat2.dVal + quat1.bVal * quat2.cVal - quat1.cVal * quat2.bVal + quat1.dVal * quat2.aVal;
    resultQuat.aVal = sumReal;
    resultQuat.bVal = sumCompl1;
    resultQuat.cVal = sumCompl2;
    resultQuat.dVal = sumCompl3;
    return resultQuat;
}

template <typename Val>
std::ostream& operator<<(std::ostream& os, const JQuaternion<Val>& obj){
    os << obj.aVal << "  " << obj.bVal << " i " << obj.cVal << " j " << obj.dVal << " k ";
    os << "\n";
    return os;
}

template <typename Val>
inline JQuaternion<Val> operator*(const JQuaternion<Val>& quat, const Val scalar){
    JQuaternion<Val> resultQuat = quat;
    resultQuat.aVal *= scalar;
    resultQuat.bVal *= scalar;
    resultQuat.cVal *= scalar;
    resultQuat.dVal *= scalar;
    return resultQuat;
}

template <typename Val>
inline JQuaternion<Val> operator*(const Val scalar,const JQuaternion<Val>& quat){
    JQuaternion<Val> resultQuat = quat;
    resultQuat.aVal *= scalar;
    resultQuat.bVal *= scalar;
    resultQuat.cVal *= scalar;
    resultQuat.dVal *= scalar;
    return resultQuat;
}

template <typename Val>
inline JQuaternion<Val> adjunct(const JQuaternion<Val>& quat){
    JQuaternion<Val> resultQuat = quat;
    resultQuat.bVal *= -1;
    resultQuat.cVal *= -1;
    resultQuat.dVal *= -1;
    return resultQuat;
}

template <typename Val>
inline JQuaternion<Val> inverse(const JQuaternion<Val>& quat){ // TODO fix the inverse??
    JQuaternion<Val> resultQuat;
    //Val valFactor = 1 /  ((quat.aVal * quat.aVal) + (quat.bVal * quat.bVal) + (quat.cVal * quat.cVal) + (quat.dVal * quat.dVal));
    resultQuat = adjunct(quat); //* valFactor ;
    return resultQuat;
}

template <typename Val>
inline Val norm(const JQuaternion<Val>& quat){
    const Val exponent = 2;
    return std::sqrt(std::pow(quat.aVal,exponent) + std::pow(quat.bVal,exponent) + std::pow(quat.cVal,exponent) + std::pow(quat.dVal,exponent));
}

template <typename Val>
inline Val length(const JQuaternion<Val>& quat){
    return quat.aVal + quat.bVal + quat.cVal + quat.dVal;
}

template <typename Val>
inline JUnitQuaternion<Val> normalize(const JQuaternion<Val>& quat){
    JUnitQuaternion<Val> resultQuat;
    Val length = JoQuaternion::norm(quat);
    resultQuat.aVal = quat.aVal / length;
    resultQuat.bVal = quat.bVal / length;
    resultQuat.cVal = quat.cVal / length;
    resultQuat.dVal = quat.dVal / length;
    return resultQuat;
}

template <typename Val>
inline JUnitQuaternion<Val> operator+(const JUnitQuaternion<Val>& quat1,const JUnitQuaternion<Val>& quat2){
    JQuaternion<Val> transformQuat1{quat1.aVal,quat1.bVal,quat1.cVal,quat1.dVal};
    JQuaternion<Val> transformQuat2{quat2.aVal,quat2.bVal,quat2.cVal,quat2.dVal};
    return normalize(transformQuat1 + transformQuat2);
};

template <typename Val>
inline JUnitQuaternion<Val> operator*(const JUnitQuaternion<Val>& quat1,const JUnitQuaternion<Val>& quat2){
    JQuaternion<Val> transformQuat1{quat1.aVal,quat1.bVal,quat1.cVal,quat1.dVal};
    JQuaternion<Val> transformQuat2{quat2.aVal,quat2.bVal,quat2.cVal,quat2.dVal};
    return normalize(transformQuat1 + transformQuat2);
}


template <typename Val>
inline JUnitQuaternion<Val> operator*(const JUnitQuaternion<Val>& quat1,const Val scalar){
    JUnitQuaternion resultQuat = quat1;
    return resultQuat;
}
template <typename Val>
inline JUnitQuaternion<Val> operator*(const Val scalar,const JUnitQuaternion<Val>& quat1){
    JUnitQuaternion resultQuat = quat1;
    return resultQuat;
}



}

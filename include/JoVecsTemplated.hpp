

namespace JoVecs{

namespace AngleConv{
    template <typename fpVal>
    fpVal radiansToDegrees(fpVal rad);

    template <typename fpVal>
    fpVal radiansToGrad(fpVal rad);

    template <typename fpVal>
    fpVal degreesToRad(fpVal degrees);

    template <typename fpVal>
    fpVal gradToRad(fpVal grad);
};

// template <typename Val,size_t dimension>
// constexpr Val JVec<Val,dimension>::operator[](size_t index);

// template <typename Val,size_t dimension>
// constexpr Val& JVec<Val,dimension>::operator[](size_t index);

template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator+(const JVec<Val, dimension> vec1, const JVec<Val, dimension> vec2);

template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator+=(const JVec<Val,dimension> vec1, const JVec<Val,dimension>& vec2);

template <typename Val>
bool operator==(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2);

template <typename Val>
bool operator!=(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2);

template <typename Val>
bool operator<=(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2);

template <typename Val, size_t dimension>
JVec<Val,dimension> operator*(const JVec<Val,dimension>& vec1, const Val val);

template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator*(const Val val,const JVec<Val,dimension>& vec1);

template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator*=(const JVec<Val,dimension>& vec1,const Val val);

template <typename Val,size_t dimension>
inline JVec<Val,dimension> operator-(const JVec<Val, dimension>& vec1,const JVec<Val, dimension>& vec2);


template <typename Val, size_t dimension>
inline JVec<Val,dimension> operator/(const JVec<Val,dimension>& vec1, const Val val);

template <typename Val, size_t dimension>
std::ostream& operator<<(std::ostream& os, const JVec<Val,dimension>& obj);

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

template <typename Val>
Val angle(const JVec<Val,3>& vec1,const JVec<Val,3>& vec2);

template <typename Val>
JVec<Val,3> normalize(const JVec<Val,3>& vec);

template <typename Val, size_t dimension>
JVec<Val,dimension> normalize(const JVec<Val,dimension>& vec);




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



};
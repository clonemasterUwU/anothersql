#include "_macro.h"
template<class T>
std::ostream &operator<<(std::ostream &os,const std::vector<T>& v){
    os << '[';
    if(!v.empty()){
        os << v[0];
        for(size_t i=1;i<v.size();i++){
            os << ", " << v[i];
        }
    }
    os << ']';
    return os;
}

template<class T>
std::ostream &operator<<(std::ostream &os,const std::deque<T>& d){
    os << '[';
    if(!d.empty()){
        os << d[0];
        for(size_t i=1;i<d.size();i++){
            os << ", " << d[i];
        }
    }
    os << ']';
    return os;
};

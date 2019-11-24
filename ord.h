#ifndef ORD_H_INCLUDED
#define ORD_H_INCLUDED

#include "eq.h"

namespace pftl{

struct Ord : public Eq{
    template<class T>
    static const bool lessEqualT = false;
};


struct lessEqualTUncurry{
    template<class T, class S>
    static const bool value = T::template lessEqualT<S>;
};
using lessEqualT = Currying<lessEqualTUncurry,bool(Ord,Ord)>;


struct lessTUncurry{
    template<class T, class S>
    static const bool value = T::template lessEqualT<S> && diffT::let<T>::template let<S>;
};
using lessT = Currying<lessTUncurry,bool(Ord,Ord)>;


struct greaterEqualTUncurry{
    template<class T, class S>
    static const bool value = (not T::template lessEqual<S>) || equalT::let<T>::template let<S>;
};
using greateEqualT = Currying<greaterEqualTUncurry,bool(Ord,Ord)>;


struct greaterTUncurry{
    template<class T, class S>
    static const bool value = not T::template lessEqual<S>;
};
using greateT = Currying<greaterTUncurry,bool(Ord,Ord)>;


}

#endif // ORD_H_INCLUDED

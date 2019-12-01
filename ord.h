#ifndef ORD_H_INCLUDED
#define ORD_H_INCLUDED

#include "eq.h"
#include "bool.h"

namespace pftl{

struct Ord : public Eq{
    template<class T>
    using le = Undefined;
};


struct le : public Currying<le,Type(Ord,Ord)>{
    template<class T, class S>
    using value = typename T::template le<S>;
};


struct lt : public Currying<lt,Type(Ord,Ord)>{
    template<class T, class S>
    using value = typename andB::let<typename T::template le<S>>::template let<ne::let<T>::template let<S>>;
};


struct ge : Currying<ge,Type(Ord,Ord)>{
    template<class T, class S>
    using value = typename orB::let<notB::let<typename T::template le<S>>>::template let<typename eq::let<T>::template let<S>>;
};


struct gt : public Currying<gt,Type(Ord,Ord)>{
    template<class T, class S>
    using value = typename notB::let<typename T::template le<S>>;
};


}

#endif // ORD_H_INCLUDED

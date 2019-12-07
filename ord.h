#ifndef ORD_H_INCLUDED
#define ORD_H_INCLUDED

#include "eq.h"
#include "bool.h"

namespace pftl{

struct Ord_t : public Eq_t{
    template<class T>
    using le = Undefined;
};


struct le : public Currying<le,Type(Ord_t,Ord_t)>{
    template<class T, class S>
    using value = typename T::template le<S>;
};


struct lt : public Currying<lt,Type(Ord_t,Ord_t)>{
    template<class T, class S>
    using value = typename and_logic::let<typename T::template le<S>>::template let<ne::let<T>::template let<S>>;
};


struct ge : Currying<ge,Type(Ord_t,Ord_t)>{
    template<class T, class S>
    using value = typename or_logic::let<not_logic::let<typename T::template le<S>>>::template let<typename eq::let<T>::template let<S>>;
};


struct gt : public Currying<gt,Type(Ord_t,Ord_t)>{
    template<class T, class S>
    using value = typename not_logic::let<typename T::template le<S>>;
};


struct max : public Currying<max,Type(Ord_t,Ord_t)>{
    template<class T, class S>
    using value = typename If<typename le::let<T>::template let<S>>
                                ::template Then<T>
                                ::template Else<S>;
};


}

#endif // ORD_H_INCLUDED

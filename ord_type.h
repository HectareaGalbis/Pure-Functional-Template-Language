#ifndef ORD_H_INCLUDED
#define ORD_H_INCLUDED

#include "eq_type.h"
#include "bool_type.h"

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class A, class W1 = Where<Eq_c,A>>
struct Ord_c : Class{
    template<class T>
    using le = Undefined;
};

//--------------------------------------------------------------------------------

struct le : public Currying<le,Bool_t(Type,Type)>{
    template<class T, class S, class W1 = Where<Ord_c,T>, class W2 = Where<Ord_c,S>>
    using value = typename Ord_c<T>::template le<S>;
};

//--------------------------------------------------------------------------------

struct lt : public Currying<lt,Bool_t(Type,Type)>{
    template<class T, class S, class W1 = Where<Ord_c,T>, class W2 = Where<Ord_c,S>>
    using value = typename and_logic::let<typename le::let<T>::template let<S>>::template let<typename ne::let<T>::template let<S>>;
};


struct ge : Currying<ge,Bool_t(Type,Type)>{
    template<class T, class S, class W1 = Where<Ord_c,T>, class W2 = Where<Ord_c,S>>
    using value = typename or_logic::let<not_logic::let<typename le::let<T>::template let<S>>>::template let<typename eq::let<T>::template let<S>>;
};


struct gt : public Currying<gt,Bool_t(Type,Type)>{
    template<class T, class S, class W1 = Where<Ord_c,T>, class W2 = Where<Ord_c,S>>
    using value = typename not_logic::let<typename le::let<T>::template let<S>>;
};


struct max : public Currying<max,Type(Type,Type)>{
    template<class T, class S, class W1 = Where<Ord_c,T>, class W2 = Where<Ord_c,S>>
    using value = typename If<typename le::let<T>::template let<S>>
                                ::template Then<S>
                                ::template Else<T>;
};


struct min : public Currying<min,Type(Type,Type)>{
    template<class T, class S, class W1 = Where<Ord_c,T>, class W2 = Where<Ord_c,S>>
    using value = typename If<typename le::let<T>::template let<S>>
                                ::template Then<T>
                                ::template Else<S>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}

#endif // ORD_H_INCLUDED

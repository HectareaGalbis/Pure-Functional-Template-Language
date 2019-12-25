#ifndef EQ_TYPE_H_INCLUDED
#define EQ_TYPE_H_INCLUDED

#include "curry.h"

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

struct Bool_t;

template<bool b>
struct Bool;

//********************************************************************************

template<class A>
struct Eq_c : Class{

    template<class T>
    using eq = Undefined;

};

//--------------------------------------------------------------------------------

struct eq : public Currying<eq,Bool_t(Type,Type)>{
    template<class S, class T, class W1 = Where<Eq_c,S>, class W2 = Where<Eq_c,T>>
    using value = typename Eq_c<S>::template eq<T>;
};

//--------------------------------------------------------------------------------

template<class B>
struct neAux{
    using value = Bool<true>;
};

template<>
struct neAux<Bool<true>>{
    using value = Bool<false>;
};

struct ne : Currying<ne,Bool_t(Type,Type)>{
    template<class S, class T, class W1 = Where<Eq_c,S>, class W2 = Where<Eq_c,T>>
    using value = typename neAux<typename eq::let<S>::template let<T>>::value;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}

#endif // EQ_TYPE_H_INCLUDED

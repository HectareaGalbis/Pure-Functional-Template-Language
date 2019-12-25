#ifndef INTEGRAL_TYPE_H_INCLUDED
#define INTEGRAL_TYPE_H_INCLUDED


namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class A>
struct Integral_c : public Class{

    template<class I>
    using div = Undefined;

    template<class I>
    using mod = Undefined;

};

//--------------------------------------------------------------------------------

struct div : public Currying<div,Type(Type,Type)>{
    template<class I, class J, class W1 = Where<Integral_c,I>, class W2 = Where<Integral_c,J>>
    using value = typename Integral_c<I>::template div<J>;
};

struct mod : public Currying<mod,Type(Type,Type)>{
    template<class I, class J, class W1 = Where<Integral_c,I>, class W2 = Where<Integral_c,J>>
    using value = typename Integral_c<I>::template mod<J>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}

#endif // INTEGRAL_TYPE_H_INCLUDED

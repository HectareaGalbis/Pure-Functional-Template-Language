#ifndef PAIR_TYPE_H_INCLUDED
#define PAIR_TYPE_H_INCLUDED


namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class X, class Y>
struct Pair_t{

    using fst = Undefined;

    using snd = Undefined;

};

//********************************************************************************

struct fst : public Currying<fst,Type(Pair_t<Type,Type>)>{
    template<class P>
    using value = typename P::fst;
};

struct snd : public Currying<snd,Type(Pair_t<Type,Type>)>{
    template<class P>
    using value = typename P::snd;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class X, class Y>
struct Pair{

    using fst = X;

    using snd = Y;

};

//--------------------------------------------------------------------------------
//********************************************************************************

}

namespace std{

template<class B1, class B2, class D1, class D2>
struct is_base_of<Pair_t<B1,B2>,Pair<D1,D2>>{
    constexpr bool value = is_base_of<B1,D1>::value && is_base_of<B2,D2>::value;
}

}


#endif // PAIR_TYPE_H_INCLUDED

#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include "curry.h"
#include "tuple.h"

template<int k>
struct ChInt{

    template<class F, class X>
    using value = typename Rep<k>::template let<F>::template let<X>;;

    template<class... Args>
    using let = typename curry<ChInt<k>::value,2,Args...>::value;

};

struct ChSuc{

    template<class N, class F, class X>
    using value = typename N::template let<F>::template let<typename F::template let<X>>;

    template<class... Args>
    using let = typename curry<ChSuc::value,3,Args...>::value;

};

//------------------------


template<int k>
struct Int{

    static const int value = k;

};

struct Plus{

    template<class N, class M>
    using value = Int<N::value+M::value>;

    template<class... Args>
    using let = typename curry<Plus::value,2,Args...>::value;

};

struct Minus{

    template<class N, class M>
    using value = Int<N::value-M::value>;

    template<class... Args>
    using let = typename curry<Minus::value,2,Args...>::value;

};

struct Mult{

    template<class N, class M>
    using value = Int<N::value*M::value>;

    template<class... Args>
    using let = typename curry<Mult::value,2,Args...>::value;

};

struct Div{

    template<class N, class M>
    using value = Int<N::value/M::value>;

    template<class... Args>
    using let = typename curry<Div::value,2,Args...>::value;

};

struct Mod{

    template<class N, class M>
    using value = Int<N::value%M::value>;

    template<class... Args>
    using let = typename curry<Mod::value,2,Args...>::value;

};

struct Opp{

    template<class N>
    using value = Int<-N::value>;

    template<class... Args>
    using let = typename curry<Opp::value,1,Args...>::value;

};

struct Equal{

    template<class N, class M>
    using value = typename Bool<N::value==M::value>::value;

    template<class... Args>
    using let = typename curry<Equal::value,2,Args...>::value;

};

struct Greater{

    template<class N, class M>
    using value = typename Bool<(N::value>M::value)>::value;

    template<class... Args>
    using let = typename curry<Greater::value,2,Args...>::value;

};

struct Less{

    template<class N, class M>
    using value = typename Bool<N::value<M::value>::value;

    template<class... Args>
    using let = typename curry<Less::value,2,Args...>::value;

};

struct GreaterEqual{

    template<class N, class M>
    using value = typename Bool<N::value>=M::value>::value;

    template<class... Args>
    using let = typename curry<GreaterEqual::value,2,Args...>::value;

};

struct LessEqual{

    template<class N, class M>
    using value = typename Bool<N::value<=M::value>::value;

    template<class... Args>
    using let = typename curry<LessEqual::value,2,Args...>::value;

};

struct Suc{

    template<class N>
    using value = Int<N::value+1>;

    template<class... Args>
    using let = typename curry<Suc::value,1,Args...>::value;

};

struct IsDivisor{

    template<class N, class M>
    using value = typename Bool<(M::value%N::value)==0>::value;

    template<class... Args>
    using let = typename curry<IsDivisor::value,2,Args...>::value;

};

template<class P, class N>
struct IsPrimeAux{

    using value = Or::value<IsDivisor::value<N,P>, typename IsPrimeAux<P,Int<N::value-1>>::value>;

};

template<class P>
struct IsPrimeAux<P,Int<1>>{

    using value = False;

};

struct IsPrime{

    template<class N>
    using value = Not::value<typename IsPrimeAux<N,Int<N::value-1>>::value>;

    template<class... Args>
    using let = typename curry<IsPrime::value,1,Args...>::value;

};


#endif // INTEGER_H_INCLUDED

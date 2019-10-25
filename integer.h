#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include "curry.h"
#include "tuple.h"

//template<int k>
//struct ChI{
//
//    template<class F, class X>
//    using value = typename Rep<k>::template let<F>::template let<X>;;
//
//    template<class... Args>
//    using let = typename curry<ChI<k>::value,2,Args...>::value;
//
//};
//
//struct ChSuc{
//
//    template<class N, class F, class X>
//    using value = typename N::template let<F>::template let<typename F::template let<X>>;
//
//    template<class... Args>
//    using let = typename curry<ChSuc::value,3,Args...>::value;
//
//};
//
////------------------------


template<int k>
struct I{

    static const int value = k;

};

struct Plus{

    template<class N, class M>
    using uncurry = I<N::value+M::value>;

    template<class... Args>
    using let = curry<Plus::uncurry,2,Args...>;

};

struct Minus{

    template<class N, class M>
    using uncurry = I<N::value-M::value>;

    template<class... Args>
    using let = curry<Minus::uncurry,2,Args...>;

};

struct Mult{

    template<class N, class M>
    using uncurry = I<N::value*M::value>;

    template<class... Args>
    using let = curry<Mult::uncurry,2,Args...>;

};

struct Div{

    template<class N, class M>
    using uncurry = I<N::value/M::value>;

    template<class... Args>
    using let = curry<Div::uncurry,2,Args...>;

};

struct Mod{

    template<class N, class M>
    using uncurry = I<N::value%M::value>;

    template<class... Args>
    using let = curry<Mod::uncurry,2,Args...>;

};

struct Opp{

    template<class N>
    using uncurry = I<-N::value>;

    template<class... Args>
    using let = curry<Opp::uncurry,1,Args...>;

};

struct Equal{

    template<class N, class M>
    using uncurry = typename B<N::value==M::value>::value;

    template<class... Args>
    using let = curry<Equal::uncurry,2,Args...>;

};

struct Greater{

    template<class N, class M>
    using uncurry = typename B<(N::value>M::value)>::value;

    template<class... Args>
    using let = curry<Greater::uncurry,2,Args...>;

};

struct Less{

    template<class N, class M>
    using uncurry = typename B<N::value<M::value>::value;

    template<class... Args>
    using let = curry<Less::uncurry,2,Args...>;

};

struct GreaterEqual{

    template<class N, class M>
    using uncurry = typename B<N::value>=M::value>::value;

    template<class... Args>
    using let = curry<GreaterEqual::uncurry,2,Args...>;

};

struct LessEqual{

    template<class N, class M>
    using uncurry = typename B<N::value<=M::value>::value;

    template<class... Args>
    using let = curry<LessEqual::uncurry,2,Args...>;

};

struct Suc{

    template<class N>
    using uncurry = I<N::value+1>;

    template<class... Args>
    using let = curry<Suc::uncurry,1,Args...>;

};

struct IsDivisor{

    template<class N, class M>
    using uncurry = typename B<(M::value%N::value)==0>::value;

    template<class... Args>
    using let = curry<IsDivisor::uncurry,2,Args...>;

};

template<class P, class N>
struct IsPrimeAux{

    using value = Or::uncurry<IsDivisor::uncurry<N,P>, typename IsPrimeAux<P,I<N::value-1>>::value>;

};

template<class P>
struct IsPrimeAux<P,I<1>>{

    using value = False;

};

struct IsPrime{

    template<class N>
    using uncurry = Not::let<typename IsPrimeAux<N,I<N::value-1>>::value>;

    template<class... Args>
    using let = curry<IsPrime::uncurry,1,Args...>;

};


#endif // INTEGER_H_INCLUDED

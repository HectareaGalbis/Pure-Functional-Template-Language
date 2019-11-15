#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include "curry.h"

#define DEF_TYPE int64_t

namespace pftl{

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


template<class S>
struct plus_gUncurry{

    template<S m, S n>
    static const S value = m+n;

};

template<class S>
using plus_g = Curryfication<plus_gUncurry<S>,S(S,S)>;

using plus = plus_g<DEF_TYPE>;


template<class S>
struct minus_gUncurry{

    template<S m, S n>
    static const S value = m-n;

};

template<class S>
using minus_g = Curryfication<minus_gUncurry<S>,S(S,S)>;

using minus = minus_g<DEF_TYPE>;


template<class S>
struct mult_gUncurry{

    template<S m, S n>
    static const S value = m*n;

};

template<class S>
using mult_g = Curryfication<mult_gUncurry<S>,S(S,S)>;

using mult = mult_g<DEF_TYPE>;


template<class S>
struct div_gUncurry{

    template<S m, S n>
    static const S value = m/n;

};

template<class S>
using div_g = Curryfication<div_gUncurry<S>,S(S,S)>;

using div = div_g<DEF_TYPE>;


template<class S>
struct mod_gUncurry{

    template<S m, S n>
    static const S value = m%n;

};

template<class S>
using mod_g = Curryfication<mod_gUncurry<S>,S(S,S)>;

using mod = mod_g<DEF_TYPE>;


template<class S>
struct equal_gUncurry{

    template<S m, S n>
    static const bool value = m==n;

};

template<class S>
using equal_g = Curryfication<equal_gUncurry<S>,bool(S,S)>;

using equal = equal_g<DEF_TYPE>;


template<class S>
struct greater_gUncurry{

    template<S m, S n>
    static const bool value = m>n;

};

template<class S>
using greater_g = Curryfication<greater_gUncurry<S>,bool(S,S)>;

using greater = greater_g<DEF_TYPE>;


template<class S>
struct less_gUncurry{

    template<S m, S n>
    static const bool value = m<n;

};

template<class S>
using less_g = Curryfication<less_gUncurry<S>,bool(S,S)>;

using less = less_g<DEF_TYPE>;


template<class S>
struct greaterEqual_gUncurry{

    template<S m, S n>
    static const bool value = m>=n;

};

template<class S>
using greaterEqual_g = Curryfication<greaterEqual_gUncurry<S>,bool(S,S)>;

using greaterEqual = greaterEqual_g<DEF_TYPE>;


template<class S>
struct lessEqual_gUncurry{

    template<S m, S n>
    static const bool value = m<=n;

};

template<class S>
using lessEqual_g = Curryfication<lessEqual_gUncurry<S>,bool(S,S)>;

using lessEqual = lessEqual_g<DEF_TYPE>;


template<class S>
struct suc_g{

    template<S n>
    static const S let = n+1;

};

using suc = suc_g<DEF_TYPE>;


template<class S>
struct pre_g{

    template<S n>
    static const S let = n-1;

};

using pre = pre_g<DEF_TYPE>;

//template<class S>
//struct isDivisor_gUncurry{
//
//    template<S m, S n>
//    static const bool value = m<n ? equal<S>::template let<mod<S>::template let<n>::template let<m>> :: template let<0> : false;
//
//    template<class... Args>
//    using let = curry<IsDivisor::_gUncurry,2,Args...>;
//
//};
//
//template<class P, class N>
//struct IsPrimeAux{
//
//    using value = Or::uncurry<IsDivisor::uncurry<N,P>, typename IsPrimeAux<P,I<N::value-1>>::value>;
//
//};
//
//template<class P>
//struct IsPrimeAux<P,I<1>>{
//
//    using value = False;
//
//};
//
//struct IsPrime{
//
//    template<class N>
//    using uncurry = Not::let<typename IsPrimeAux<N,Pre::let<N>>::value>;
//
//    template<class... Args>
//    using let = curry<IsPrime::uncurry,1,Args...>;
//
//};
//
//
//template<class N>
//struct FiboAux{
//
//    using value = typename Plus::let< typename FiboAux<Pre::let<N>>::value >:: template let< typename FiboAux<Pre::let<Pre::let<N>>>::value >;
//
//};
//
//template<>
//struct FiboAux<I<0>>{
//
//    using value = I<0>;
//
//};
//
//template<>
//struct FiboAux<I<1>>{
//
//    using value = I<1>;
//
//};
//
//struct Fibo{
//
//    template<class N>
//    using uncurry = typename FiboAux<N>::value;
//
//    template<class... Args>
//    using let = curry<Fibo::uncurry, 1, Args...>;
//
//};


}


#endif // INTEGER_H_INCLUDED

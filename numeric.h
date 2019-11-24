#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include "curry.h"

#define DEF_TYPE intmax_t

namespace pftl{


template<class S>
struct plus_gUncurry{

    template<S m, S n>
    static const S value = m+n;

};

template<class S>
using plus_g = Currying<plus_gUncurry<S>,S(S,S)>;

using plus = plus_g<DEF_TYPE>;


template<class S>
struct minus_gUncurry{

    template<S m, S n>
    static const S value = m-n;

};

template<class S>
using minus_g = Currying<minus_gUncurry<S>,S(S,S)>;

using minus = minus_g<DEF_TYPE>;


template<class S>
struct mult_gUncurry{

    template<S m, S n>
    static const S value = m*n;

};

template<class S>
using mult_g = Currying<mult_gUncurry<S>,S(S,S)>;

using mult = mult_g<DEF_TYPE>;


template<class S>
struct div_gUncurry{

    template<S m, S n>
    static const S value = m/n;

};

template<class S>
using div_g = Currying<div_gUncurry<S>,S(S,S)>;

using div = div_g<DEF_TYPE>;


template<class S>
struct mod_gUncurry{

    template<S m, S n>
    static const S value = m%n;

};

template<class S>
using mod_g = Currying<mod_gUncurry<S>,S(S,S)>;

using mod = mod_g<DEF_TYPE>;


template<class S>
struct equal_gUncurry{

    template<S m, S n>
    static const bool value = m==n;

};

template<class S>
using equal_g = Currying<equal_gUncurry<S>,bool(S,S)>;

using equal = equal_g<DEF_TYPE>;


template<class S>
struct greater_gUncurry{

    template<S m, S n>
    static const bool value = m>n;

};

template<class S>
using greater_g = Currying<greater_gUncurry<S>,bool(S,S)>;

using greater = greater_g<DEF_TYPE>;


template<class S>
struct less_gUncurry{

    template<S m, S n>
    static const bool value = m<n;

};

template<class S>
using less_g = Currying<less_gUncurry<S>,bool(S,S)>;

using less = less_g<DEF_TYPE>;


template<class S>
struct greaterEqual_gUncurry{

    template<S m, S n>
    static const bool value = m>=n;

};

template<class S>
using greaterEqual_g = Currying<greaterEqual_gUncurry<S>,bool(S,S)>;

using greaterEqual = greaterEqual_g<DEF_TYPE>;


template<class S>
struct lessEqual_gUncurry{

    template<S m, S n>
    static const bool value = m<=n;

};

template<class S>
using lessEqual_g = Currying<lessEqual_gUncurry<S>,bool(S,S)>;

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


template<class S>
struct not_bit_g{

    template<S n>
    static const S let = ~n;

};

using not_bit = not_bit_g<DEF_TYPE>;


template<class S>
struct and_bit_gUncurry{

    template<S m, S n>
    static const S value = m&n;

};

template<class S>
using and_bit_g = Currying<and_bit_gUncurry<S>,S(S,S)>;

using and_bit = and_bit_g<DEF_TYPE>;


template<class S>
struct or_bit_gUncurry{

    template<S m, S n>
    static const S value = m|n;

};

template<class S>
using or_bit_g = Currying<or_bit_gUncurry<S>,S(S,S)>;

using or_bit = or_bit_g<DEF_TYPE>;


template<class S>
struct xor_bit_gUncurry{

    template<S m, S n>
    static const S value = m^n;

};

template<class S>
using xor_bit_g = Currying<xor_bit_gUncurry<S>,S(S,S)>;

using xor_bit = xor_bit_g<DEF_TYPE>;


template<class S>
struct shift_left_gUncurry{

    template<S m, S n>
    static const S value = m << n;

};

template<class S>
using shift_left_g = Currying<shift_left_gUncurry<S>,S(S,S)>;

using shift_left = shift_left_g<DEF_TYPE>;


template<class S>
struct shift_right_gUncurry{

    template<S m, S n>
    static const S value = m >> n;

};

template<class S>
using shift_right_g = Currying<shift_right_gUncurry<S>,S(S,S)>;

using shift_right = shift_right_g<DEF_TYPE>;


template<class S, bool nZero, S m, S n>
struct mcd_gAux{
    static const S value = mcd_gAux<S,m%n==0,n,m%n>::value;
};

template<class S, S m, S n>
struct mcd_gAux<S,true,m,n>{
    static const S value = m;
};

template<class S>
struct mcd_gUncurry{

    template<S m, S n>
    static const S value = mcd_gAux<S,n==0,m,n>::value;

};

template<class S>
using mcd_g = Currying<mcd_gUncurry<S>,S(S,S)>;

using mcd = mcd_g<DEF_TYPE>;


template<class S>
struct mcm_gUncurry{

    template<S m, S n>
    static const S value = (m*n) / mcd_g<S>::template let<m>::template let<n>;

};

template<class S>
using mcm_g = Currying<mcm_gUncurry<S>,S(S,S)>;

using mcm = mcm_g<DEF_TYPE>;


template<class S>
struct signum_g{

    template<S n>
    static const int let = n>0 ? 1 : (n==0 ? 0 : -1);

};

using signum = signum_g<DEF_TYPE>;


template<class S>
struct abs_g{

    template<S n>
    static const S let = n>=0 ? n : -n;

};

using abs = abs_g<DEF_TYPE>;


template<uintmax_t n>
struct isqrtAux{
    static const uintmax_t value = ((isqrtAux<(n>>2)>::value<<1)+1)*((isqrtAux<(n>>2)>::value<<1)+1) > n ? isqrtAux<(n>>2)>::value<<1 : ((isqrtAux<(n>>2)>::value<<1)+1);
};

template<>
struct isqrtAux<1>{
    static const uintmax_t value = 1;
};

template<>
struct isqrtAux<0>{
    static const uintmax_t value = 0;
};

struct isqrt : public Currying<isqrt,uintmax_t(uintmax_t)>{
    template<uintmax_t n>
    static const uintmax_t value = isqrtAux<n>::value;
};


template<bool While, uintmax_t i, uintmax_t n>
struct isPrimeAux3{
    static const bool value = (n%i==0) or (n%(i+2)==0) ? false : isPrimeAux3<((i+6)*(i+6)<=n),i+6,n>::value;
};

template<uintmax_t i, uintmax_t n>
struct isPrimeAux3<false,i,n>{
    static const bool value = true;
};

template<bool If, uintmax_t n>
struct isPrimeAux2{
    static const bool value = false;
};

template<uintmax_t n>
struct isPrimeAux2<false,n>{
    static const bool value = isPrimeAux3<(25<=n),5,n>::value;
};

template<bool If, uintmax_t n>
struct isPrimeAux1{
    static const bool value = n>1;
};

template<uintmax_t n>
struct isPrimeAux1<false,n>{
    static const bool value = isPrimeAux2<(n%2==0) or (n%3==0),n>::value;
};

struct isPrime : public Currying<isPrime,bool(uintmax_t)>{
    template<uintmax_t n>
    static const uintmax_t value = isPrimeAux1<(n<=3),n>::value;
};


template<bool If, uintmax_t n>
struct nextPrimeAux{
    static const uintmax_t value = n;
};

template<uintmax_t n>
struct nextPrimeAux<false,n>{
    static const uintmax_t value = nextPrimeAux<isPrime::let<n+1>,n+1>::value;
};

struct nextPrime : Currying<nextPrime,uintmax_t(uintmax_t)>{
    template<uintmax_t n>
    static const uintmax_t value = nextPrimeAux<isPrime::let<n+1>,n+1>::value;
};


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

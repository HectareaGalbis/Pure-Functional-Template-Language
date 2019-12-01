#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include "curry.h"

#define DEF_TYPE intmax_t

namespace pftl{


template<class S>
struct plus_g : public Currying<plus_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m+n;
};
using plus = plus_g<DEF_TYPE>;


template<class S>
struct minus_g : public Currying<minus_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m-n;
};
using minus = minus_g<DEF_TYPE>;


template<class S>
struct mult_g : public Currying<mult_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m*n;
};
using mult = mult_g<DEF_TYPE>;


template<class S>
struct div_g : public Currying<div_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m/n;
};
using div = div_g<DEF_TYPE>;


template<class S>
struct mod_g : public Currying<mod_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m%n;
};
using mod = mod_g<DEF_TYPE>;


template<class S>
struct equal_g : public Currying<equal_g<S>,bool(S,S)>{
    template<S m, S n>
    static const bool value = m==n;
};
using equal = equal_g<DEF_TYPE>;


template<class S>
struct greater_g : public Currying<greater_g<S>,bool(S,S)>{
    template<S m, S n>
    static const bool value = m>n;
};
using greater = greater_g<DEF_TYPE>;


template<class S>
struct less_g : public Currying<less_g<S>,bool(S,S)>{
    template<S m, S n>
    static const bool value = m<n;
};
using less = less_g<DEF_TYPE>;


template<class S>
struct greaterEqual_g : public Currying<greaterEqual_g<S>,bool(S,S)>{
    template<S m, S n>
    static const bool value = m>=n;
};
using greaterEqual = greaterEqual_g<DEF_TYPE>;


template<class S>
struct lessEqual_g : public Currying<lessEqual_g<S>,bool(S,S)>{
    template<S m, S n>
    static const bool value = m<=n;
};
using lessEqual = lessEqual_g<DEF_TYPE>;


template<class S>
struct suc_g : public Currying<suc_g<S>,S(S)>{
    template<S n>
    static const S value = n+1;
};
using suc = suc_g<DEF_TYPE>;


template<class S>
struct pre_g{
    template<S n>
    static const S let = n-1;
};
using pre = pre_g<DEF_TYPE>;


template<class S>
struct not_bit_g : public Currying<not_bit_g<S>,S(S)>{
    template<S n>
    static const S value = ~n;
};
using not_bit = not_bit_g<DEF_TYPE>;


template<class S>
struct and_bit_g : public Currying<and_bit_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m&n;
};
using and_bit = and_bit_g<DEF_TYPE>;


template<class S>
struct or_bit_g : public Currying<or_bit_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m|n;
};
using or_bit = or_bit_g<DEF_TYPE>;


template<class S>
struct xor_bit_g : public Currying<xor_bit_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m^n;
};
using xor_bit = xor_bit_g<DEF_TYPE>;


template<class S>
struct shift_left_g : public Currying<shift_left_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m << n;
};
using shift_left = shift_left_g<DEF_TYPE>;


template<class S>
struct shift_right_g : public Currying<shift_right_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = m >> n;
};
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
struct mcd_g : public Currying<mcd_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = mcd_gAux<S,n==0,m,n>::value;
};
using mcd = mcd_g<DEF_TYPE>;


template<class S>
struct mcm_g : Currying<mcm_g<S>,S(S,S)>{
    template<S m, S n>
    static const S value = (m*n) / mcd_g<S>::template let<m>::template let<n>;
};
using mcm = mcm_g<DEF_TYPE>;


template<class S>
struct signum_g : public Currying<signum_g<S>,int(S)>{
    template<S n>
    static const int value = n>0 ? 1 : (n==0 ? 0 : -1);
};
using signum = signum_g<DEF_TYPE>;


template<class S>
struct abs_g : Currying<abs_g<S>,S(S)>{
    template<S n>
    static const S value = n>=0 ? n : -n;
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





}


#endif // INTEGER_H_INCLUDED

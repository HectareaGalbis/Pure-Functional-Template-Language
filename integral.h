#ifndef INTEGRAL_H_INCLUDED
#define INTEGRAL_H_INCLUDED

#include "curry.h"
#include "ord.h"

namespace pftl{


struct Integral_t : public Ord_t{

    template<class I>
    using plus = Undefined;

    template<class I>
    using minus = Undefined;

    template<class I>
    using mult = Undefined;

    template<class I>
    using div = Undefined;

    template<class I>
    using mod = Undefined;

    using suc = Undefined;

    using pre = Undefined;

    using not_bit = Undefined;

    template<class I>
    using and_bit = Undefined;

    template<class I>
    using or_bit = Undefined;

    template<class I>
    using xor_bit = Undefined;

    template<class I>
    using shift_left = Undefined;

    template<class I>
    using shift_right = Undefined;

    template<class I>
    using mcd = Undefined;

    template<class I>
    using mcm = Undefined;

    using signum = Undefined;

    using abs = Undefined;

    using sqrt = Undefined;

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

struct plus : public Currying<plus,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template plus<J>;
};

struct minus : public Currying<minus,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template minus<J>;
};

struct mult : public Currying<mult,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template mult<J>;
};

struct div : public Currying<div,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template div<J>;
};

struct mod : public Currying<mod,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template mod<J>;
};

struct suc : public Currying<suc,Type(Integral_t)>{
    template<class I>
    using value = typename I::suc;
};

struct pre : public Currying<pre,Type(Integral_t)>{
    template<class I>
    using value = typename I::pre;
};

struct not_bit : public Currying<not_bit,Type(Integral_t)>{
    template<class I>
    using value = typename I::not_bit;
};

struct and_bit : public Currying<and_bit,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template and_bit<J>;
};

struct or_bit : public Currying<or_bit,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template or_bit<J>;
};

struct xor_bit : public Currying<xor_bit,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template xor_bit<J>;
};

struct shift_left : public Currying<shift_left,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template shift_left<J>;
};

struct shift_right : public Currying<shift_right,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template shift_right<J>;
};

struct mcd : public Currying<mcd,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template mcd<J>;
};

struct mcm : public Currying<mcm,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template mcm<J>;
};

struct signum : public Currying<signum,Type(Integral_t)>{
    template<class I>
    using value = typename I::signum;
};

struct abs : public Currying<abs,Type(Integral_t)>{
    template<class I>
    using value = typename I::abs;
};

struct sqrt : public Currying<sqrt,Type(Integral_t,Integral_t)>{
    template<class I, class J>
    using value = typename I::template sqrt<J>;
};


}


#endif // INTEGRAL_H_INCLUDED

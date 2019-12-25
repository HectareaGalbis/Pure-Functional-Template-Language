#ifndef NUM_TYPE_H_INCLUDED
#define NUM_TYPE_H_INCLUDED

#include "curry.h"

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class A>
struct Num_c : Class{

    template<class I>
    using plus = Undefined;

    template<class I>
    using minus = Undefined;

    template<class I>
    using mult = Undefined;

    using negate = Undefined;

    using abs = Undefined;

    using signum = Undefined;

};

//********************************************************************************

struct plus : public Currying<plus,Type(Type,Type)>{
    template<class I, class J, class W1 = Where<Num_c,I>, class W2 = Where<Num_c,J>>
    using value = typename Num_c<I>::template plus<J>;
};

struct minus : public Currying<minus,Type(Type,Type)>{
    template<class I, class J, class W1 = Where<Num_c,I>, class W2 = Where<Num_c,J>>
    using value = typename Num_c<I>::template minus<J>;
};

struct mult : public Currying<mult,Type(Type,Type)>{
    template<class I, class J, class W1 = Where<Num_c,I>, class W2 = Where<Num_c,J>>
    using value = typename Num_c<I>::template mult<J>;
};

struct negate : public Currying<negate,Type(Type)>{
    template<class I, class W1 = Where<Num_c,I>>
    using value = typename Num_c<I>::negate;
};

struct abs : public Currying<abs,Type(Type)>{
    template<class I, class W1 = Where<Num_c,I>>
    using value = typename Num_c<I>::abs;
};

struct signum : public Currying<signum,Type(Type)>{
    template<class I, class W1 = Where<Num_c,I>>
    using value = typename Num_c<I>::signum;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}

#endif // NUM_TYPE_H_INCLUDED

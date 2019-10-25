#ifndef BOLEANCHURCH_H_INCLUDED
#define BOLEANCHURCH_H_INCLUDED

#include "curry.h"



struct True{

    static const bool value = true;

    template<class X, class Y>
    using uncurry = X;

    template<class... Args>
    using let = curry<True::uncurry,2,Args...>;

};

struct False{

    static const bool value = false;

    template<class X, class Y>
    using uncurry = Y;

    template<class... Args>
    using let = curry<False::uncurry,2,Args...>;

};

template<bool b>
struct B{
    using value = True;
};

template<>
struct B<false>{
    using value = False;
};

struct Not{

    template<class X>
    using uncurry = typename X::template let<False>::template let<True>;

    template<class... Args>
    using let = curry<Not::uncurry,1,Args...>;

};

struct And{

    template<class X, class Y>
    using uncurry = typename X::template let<Y>::template let<False>;

    template<class... Args>
    using let = curry<And::uncurry,2,Args...>;

};

struct Or{

    template<class X, class Y>
    using uncurry = typename X::template let<True>::template let<Y>;

    template<class... Args>
    using let = curry<Or::uncurry,2,Args...>;

};

struct IfThenElse{

    template<class P, class Q, class R>
    using uncurry = typename P::template let<Q>::template let<R>;

    template<class... Args>
    using let = curry<IfThenElse::uncurry,3,Args...>;

};



#endif // BOLEANCHURCH_H_INCLUDED

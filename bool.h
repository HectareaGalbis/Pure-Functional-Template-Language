#ifndef BOLEANCHURCH_H_INCLUDED
#define BOLEANCHURCH_H_INCLUDED

#include "curry.h"



struct True{

    static const bool b_value = true;

    template<class X, class Y>
    using value = X;

    template<class... Args>
    using let = typename curry<True::value,2,Args...>::value;

};

struct False{

    static const bool b_value = false;

    template<class X, class Y>
    using value = Y;

    template<class... Args>
    using let = typename curry<False::value,2,Args...>::value;

};

template<bool b>
struct Bool{
    using value = True;
};

template<>
struct Bool<false>{
    using value = False;
};

struct Not{

    template<class X>
    using value = typename X::template let<False>::template let<True>;

    template<class... Args>
    using let = typename curry<Not::value,1,Args...>::value;

};

struct And{

    template<class X, class Y>
    using value = typename X::template let<Y>::template let<False>;

    template<class... Args>
    using let = typename curry<And::value,2,Args...>::value;

};

struct Or{

    template<class X, class Y>
    using value = typename X::template let<True>::template let<Y>;

    template<class... Args>
    using let = typename curry<Or::value,2,Args...>::value;

};

struct IfThenElse{

    template<class P, class Q, class R>
    using value = typename P::template let<Q>::template let<R>;

    template<class... Args>
    using let = typename curry<IfThenElse::value,3,Args...>::value;

};



#endif // BOLEANCHURCH_H_INCLUDED

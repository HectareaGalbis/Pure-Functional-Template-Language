#ifndef BUCLE_H_INCLUDED
#define BUCLE_H_INCLUDED

#include "solve.h"

struct Loop{};


template<class X, class... Args>
struct solve<Loop,X,Args...>{

    template<int k>
    using value = typename solve<X,X,Args...>::template value<k>;

    using beta = solve<X,X,Args...>;

};





#endif // BUCLE_H_INCLUDED

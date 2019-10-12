#ifndef BOLEANCHURCH_H_INCLUDED
#define BOLEANCHURCH_H_INCLUDED

#include "solve.h"


struct True{};


template<class T, class F, class... Args>
struct solve<True,T,F,Args...>{

    template<int k>
    using value = typename solve<T,Args...>::template value<k>;

};


//----------------


struct False{};


template<class T, class F, class... Args>
struct solve<False,T,F,Args...>{

    template<int k>
    using value = typename solve<F,Args...>::template value<k>;

};


//---------------


struct Not{};


template<class X, class... Args>
struct solve<Not,X,Args...>{

    template<int k>
    using value = typename solve<X,False,True,Args...>::template value<k>;

};


//-------------------


struct And{};


template<class X, class Y, class... Args>
struct solve<And,X,Y,Args...>{

    template<int k>
    using value = typename solve<X,Y,False,Args...>::template value<k>;

};


//--------------------


struct Or{};


template<class X, class Y, class... Args>
struct solve<Or,X,Y,Args...>{

    template<int k>
    using value = typename solve<X,True,Y,Args...>::template value<k>;

};


//-----------------


template<bool b>
struct Bool{};


template<class... Args>
struct solve<Bool<true>,Args...>{

    template<int k>
    using value = typename solve<True,Args...>::template value<k>;

};


template<class... Args>
struct solve<Bool<false>,Args...>{

    template<int k>
    using value = typename solve<False,Args...>::template value<k>;

};




#endif // BOLEANCHURCH_H_INCLUDED

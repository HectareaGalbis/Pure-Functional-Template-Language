#ifndef BOLEANCHURCH_H_INCLUDED
#define BOLEANCHURCH_H_INCLUDED

#include "solve.h"


struct True{

    static const bool value = true;

};


template<class T, class F, class... Args>
struct solve<True,T,F,Args...>{

    template<int k>
    using value = typename solve<T,Args...>::template value<k>;

    using beta = solve<T,Args...>;

};


//----------------


struct False{

    static const bool value = false;

};


template<class T, class F, class... Args>
struct solve<False,T,F,Args...>{

    template<int k>
    using value = typename solve<F,Args...>::template value<k>;

    using beta = solve<F,Args...>;

};


//---------------


struct Not{};


template<class X, class... Args>
struct solve<Not,X,Args...>{

    template<int k>
    using value = typename solve<X,False,True,Args...>::template value<k>;

    using beta = typename solve<X,False,True,Args...>::beta;

};


//-------------------


struct And{};


template<class X, class Y, class... Args>
struct solve<And,X,Y,Args...>{

    template<int k>
    using value = typename solve<X,Y,False,Args...>::template value<k>;

    using beta = typename solve<X,Y,False,Args...>::beta;

};


//--------------------


struct Or{};


template<class X, class Y, class... Args>
struct solve<Or,X,Y,Args...>{

    template<int k>
    using value = typename solve<X,True,Y,Args...>::template value<k>;

    using beta = typename solve<X,True,Y,Args...>::beta;

};


//-----------------


template<bool b>
struct Bool{};


template<class... Args>
struct solve<Bool<true>,Args...>{

    template<int k>
    using value = typename solve<True,Args...>::template value<k>;

    using beta = solve<True,Args...>;

};


template<class... Args>
struct solve<Bool<false>,Args...>{

    template<int k>
    using value = typename solve<False,Args...>::template value<k>;

     using beta = solve<False,Args...>;

};




#endif // BOLEANCHURCH_H_INCLUDED

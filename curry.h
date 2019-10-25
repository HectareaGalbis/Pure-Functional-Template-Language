#ifndef CURRY_H_INCLUDED
#define CURRY_H_INCLUDED


template<class... Args>
struct length{
    static const int value = 0;
};

template<class T, class... Args>
struct length<T,Args...>{
    static const int value = 1+length<Args...>::value;
};


template<template<class...> class F, bool positive, int k, class... Args>
struct aux{
    struct value{
        template<class... Args2>
        using let = typename aux<F,((k-length<Args2...>::value)>=0),k-length<Args2...>::value,Args...,Args2...>::value;
    };
};

template<template<class...> class F, int k, class... Args>
struct aux<F,false,k,Args...>{};

template<template<class...> class F, class... Args>
struct aux<F,true,0,Args...>{
    using value = F<Args...>;
};


template<template<class...> class F, int k, class... Args>
using curry = typename aux<F,((k-length<Args...>::value)>=0),k-length<Args...>::value,Args...>::value;


/**
    Ejemplo de como definir una funcion curryficada.
        - value define la funcion.
        - let permite la currificacion.
*/
struct TrueExample{

    template<class X, class Y>
    using uncurry = X;

    template<class... Args>
    using let = curry<TrueSample::uncurry,2,Args...>;

};



#endif // CURRY_H_INCLUDED

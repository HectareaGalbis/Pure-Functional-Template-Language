
#include <iostream>
using namespace std;

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
    template<class... Args2>
    using value = aux<F,((k-length<Args2...>::value)>=0),k-length<Args2...>::value,Args...,Args2...>;
};

template<template<class...> class F, int k, class... Args>
struct aux<F,false,k,Args...>{};

template<template<class...> class F, class... Args>
struct aux<F,true,0,Args...>{
    using value = F<Args...>;
};


template<template<class...> class F, int k, class... Args>
struct curry{
    using value = aux<F,((k-length<Args...>::value)>=0),k-length<Args...>::value,Args...>;
};


struct TrueSample{

    template<class X, class Y>
    using real_value = X;//Aqui se define la clase.

    template<class... Args>
    using value = typename curry<TrueSample::real_value,2,Args...>::value;

};



int main(){

    TrueSample::value<int,float>::value variable = 3.5;
    TrueSample::value<int>::value<float>::value variable2 = 3.5;


    cout << variable << endl;
    cout << variable2 << endl;

    return 0;

}

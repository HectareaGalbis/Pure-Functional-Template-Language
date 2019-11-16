#ifndef CURRY_H_INCLUDED
#define CURRY_H_INCLUDED

#include <string>

namespace pftl{


struct Type{};

template<class S>
struct ArgLit{
    template<S k>
    struct Arg{
        static const S value = k;
    };
};

template<class F, class T, class Mv, class Mc>
struct Curry{};

template<class F, class Ret, class S, class... Args, class... MvArgs, class... McArgs>
struct Curry<F,Ret(S,Args...),void(MvArgs...),void(McArgs...)>{

    struct value{
        template<S k>
        using let = typename Curry<F,Ret(Args...),void(MvArgs...,typename ArgLit<S>::template Arg<k>),void(McArgs...)>::value;
    };

};

template<class F, class Ret, class... Args, class... MvArgs, class... McArgs>
struct Curry<F,Ret(Type,Args...),void(MvArgs...),void(McArgs...)>{

    struct value{
        template<class X>
        using let = typename Curry<F,Ret(Args...),void(MvArgs...),void(McArgs...,X)>::value;
    };

};

template<class F, class Ret, class S, class... MvArgs, class... McArgs>
struct Curry<F,Ret(S),void(MvArgs...),void(McArgs...)>{

    struct value{
        template<S k>
        static const Ret let = F::template value<MvArgs::value...,k,McArgs...>;
    };

};

template<class F, class S, class... MvArgs, class... McArgs>
struct Curry<F,Type(S),void(MvArgs...),void(McArgs...)>{

    struct value{
        template<S k>
        using let = typename F::template value<MvArgs::value...,k,McArgs...>;
    };

};

template<class F, class Ret, class... MvArgs, class... McArgs>
struct Curry<F,Ret(Type),void(MvArgs...),void(McArgs...)>{

    struct value{
        template<class X>
        static const Ret let = F::template value<MvArgs::value...,McArgs...,X>;
    };

};

template<class F, class... MvArgs, class... McArgs>
struct Curry<F,Type(Type),void(MvArgs...),void(McArgs...)>{

    struct value{
        template<class X>
        using let = typename F::template value<MvArgs::value...,McArgs...,X>;
    };

};


template<class F, class T>
using Curryfication = typename Curry<F,T,void(),void()>::value;



//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------



template<bool c>
struct If{
    template<class X>
    struct Then{
        template<class Y>
        using Else = typename std::conditional<c,X,Y>::type;
    };
};



//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------



///Metafuncion con lazy-parameters.

///Ejemplo1
struct TrueExampleUncurry{
    template<class X, class Y>
    using value = X;
};

using TrueExample = Curryfication<TrueExampleUncurry,Type(Type,Type)>;



///Ejemplo2
struct ConditionalExampleUncurry{
    template<bool b, class X, class Y>
    using value = typename If<b>::template Then<X>::template Else<Y>;
};

using ConditionalExample = Curryfication<ConditionalExampleUncurry,Type(bool,Type,Type)>;



///Ejemplo3 (Un único argumento)
struct IsPairExample{
    template<int n>
    static const bool let = (n%2 == 0);
};



///Ejemplo4 (Alteracion del orden de los argumentos) (En la definicion: non-types a la izquierda y types a la derecha)
struct LeftOrRightExampleUncurry{
    template<int k, class X, class Y>
    using value = typename If<(k<0)>::template Then<X>::template Else<Y>;
};

using LeftOrRightExample = Curryfication<LeftOrRightExampleUncurry,Type(Type,int,Type)>;  ///Se pide primero un type, luego un int, y luego otro type.



//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------

///Curryfication 2

//template<class... Args>
//using Tuple = void(Args...);
//
//
//template<class NonTypes, class Types>
//struct Curryfication2{};
//
//template<class... NonTypes, class... Types>
//struct Curryfication2<Tuple<NonTypes...>,Tuple<Types...>>{
//
//    template<template<NonTypes...,class...> class Func>
//    struct Using{
//
//        template<NonTypes... vargs,class... targs>
//        using value = Func<vargs...,targs...>;
//
//        template<class FuncType>
//        using OfType = typename Curryfication<Curryfication2<Tuple<NonTypes...>,Tuple<Types...>>::template Using<Func>,FuncType>;
//
//    };
//
//};

}

#endif // CURRY_H_INCLUDED

#ifndef CURRY_H_INCLUDED
#define CURRY_H_INCLUDED

#include <string>

namespace pftl{

struct Undefined{};

struct Type{};

template<class S>
struct ArgLit{
    template<S k>
    struct Arg{
        static const S value = k;
    };
};

//template<class F, class T, class Mv, class Mc>
//struct Curry{};
//
//template<class F, class Ret, class S, class... Args, class... MvArgs, class... McArgs>
//struct Curry<F,Ret(S,Args...),void(MvArgs...),void(McArgs...)>{
//
//    struct value{
//        template<S k>
//        using let = typename Curry<F,Ret(Args...),void(MvArgs...,typename ArgLit<S>::template Arg<k>),void(McArgs...)>::value;
//    };
//
//};
//
//template<class F, class Ret, class... Args, class... MvArgs, class... McArgs>
//struct Curry<F,Ret(Type,Args...),void(MvArgs...),void(McArgs...)>{
//
//    struct value{
//        template<class X>
//        using let = typename Curry<F,Ret(Args...),void(MvArgs...),void(McArgs...,X)>::value;
//    };
//
//};
//
//template<class F, class Ret, class S, class... MvArgs, class... McArgs>
//struct Curry<F,Ret(S),void(MvArgs...),void(McArgs...)>{
//
//    struct value{
//        template<S k>
//        static const Ret let = F::template value<MvArgs::value...,k,McArgs...>;
//    };
//
//};
//
//template<class F, class S, class... MvArgs, class... McArgs>
//struct Curry<F,Type(S),void(MvArgs...),void(McArgs...)>{
//
//    struct value{
//        template<S k>
//        using let = typename F::template value<MvArgs::value...,k,McArgs...>;
//    };
//
//};
//
//template<class F, class Ret, class... MvArgs, class... McArgs>
//struct Curry<F,Ret(Type),void(MvArgs...),void(McArgs...)>{
//
//    struct value{
//        template<class X>
//        static const Ret let = F::template value<MvArgs::value...,McArgs...,X>;
//    };
//
//};
//
//template<class F, class... MvArgs, class... McArgs>
//struct Curry<F,Type(Type),void(MvArgs...),void(McArgs...)>{
//
//    struct value{
//        template<class X>
//        using let = typename F::template value<MvArgs::value...,McArgs...,X>;
//    };
//
//};
//
//
//template<class F, class T>
//using Curryfication = typename Curry<F,T,void(),void()>::value;



//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------


template<bool b, class Ret, Ret x>
struct enable_if_int{};

template<class Ret, Ret x>
struct enable_if_int<true,Ret,x>{
    static const Ret value = x;
};



template<class F, bool isInt, class T, class In, class Ty>
struct CurryInt{};

template<class F, class Ret, class Next, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryInt<F,true,Ret(Next,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<Next x>
        using let = typename CurryInt<F,std::is_integral<Next2>::value,Ret(Next2,Args...),void(InArgs...,typename ArgLit<Next>::template Arg<x>),void(TyArgs...)>::value;
    };
};

template<class F, class Ret, class Next, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryInt<F,false,Ret(Next,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename std::enable_if<std::is_base_of<Next,x>::value,typename CurryInt<F,std::is_integral<Next2>::value,Ret(Next2,Args...),void(InArgs...),void(TyArgs...,x)>::value>::type;
    };
};

template<class F, class Ret, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryInt<F,false,Ret(Type,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename CurryInt<F,std::is_integral<Next2>::value,Ret(Next2,Args...),void(InArgs...),void(TyArgs...,x)>::value;
    };
};

template<class F, class Ret, class Next, class... InArgs, class... TyArgs>
struct CurryInt<F,true,Ret(Next),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<Next x>
        static const Ret let = F::template value<InArgs::value...,x,TyArgs...>;
    };
};

template<class F, class Ret, class Next, class... InArgs, class... TyArgs>
struct CurryInt<F,false,Ret(Next),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        static const Ret let = enable_if_int<std::is_base_of<Next,x>::value,Ret,F::template value<InArgs::value...,TyArgs...,x>>::value;
    };
};

template<class F, class Ret, class... InArgs, class... TyArgs>
struct CurryInt<F,false,Ret(Type),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        static const Ret let = F::template value<InArgs::value...,TyArgs...,x>;
    };
};


template<class F, bool isInt, class T, class In, class Ty>
struct CurryType{};

template<class F, class Next, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryType<F,true,Type(Next,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<Next x>
        using let = typename CurryType<F,std::is_integral<Next2>::value,Type(Next2,Args...),void(InArgs...,typename ArgLit<Next>::template Arg<x>),void(TyArgs...)>::value;
    };
};

template<class F, class Next, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryType<F,false,Type(Next,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename std::enable_if<std::is_base_of<Next,x>::value,typename CurryType<F,std::is_integral<Next2>::value,Type(Next2,Args...),void(InArgs...),void(TyArgs...,x)>::value>::type;
    };
};

template<class F, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryType<F,false,Type(Type,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename CurryType<F,std::is_integral<Next2>::value,Type(Next2,Args...),void(InArgs...),void(TyArgs...,x)>::value;
    };
};

template<class F, class Next, class... InArgs, class... TyArgs>
struct CurryType<F,true,Type(Next),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<Next x>
        using let = typename F::template value<InArgs::value...,x,TyArgs...>;
    };
};

template<class F, class Next, class... InArgs, class... TyArgs>
struct CurryType<F,false,Type(Next),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename std::enable_if<std::is_base_of<Next,x>::value,typename F::template value<InArgs::value...,TyArgs...,x>>::type;
    };
};

template<class F, class... InArgs, class... TyArgs>
struct CurryType<F,false,Type(Type),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename F::template value<InArgs::value...,TyArgs...,x>;
    };
};


template<class F, bool isRetInt, class T>
struct CurryficationAux2{};

template<class F, class Ret, class Next, class... Args>
struct CurryficationAux2<F,true,Ret(Next,Args...)>{
    using value = typename CurryInt<F,std::is_integral<Next>::value,Ret(Next,Args...),void(),void()>::value;
};

template<class F, class Next, class... Args>
struct CurryficationAux2<F,false,Type(Next,Args...)>{
    using value = typename CurryType<F,std::is_integral<Next>::value,Type(Next,Args...),void(),void()>::value;
};


template<class F, class T>
struct CurryficationAux{};

template<class F, class Ret, class... Args>
struct CurryficationAux<F,Ret(Args...)>{
    using value = typename CurryficationAux2<F,std::is_integral<Ret>::value,Ret(Args...)>::value;
};

template<class F, class T>
using Curryfication = typename CurryficationAux<F,T>::value;

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

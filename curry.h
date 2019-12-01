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
        constexpr static const S value = k;
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
//using Currying = typename Curry<F,T,void(),void()>::value;



//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------


template<bool b, class Ret, Ret x>
struct enable_if_int{};

template<class Ret, Ret x>
struct enable_if_int<true,Ret,x>{
    static const Ret value = x;
};


template<class S>
struct is_nontype{
    static const bool value = std::is_integral<S>::value || std::is_enum<S>::value ||
                              std::is_pointer<S>::value || //std::is_lvalue_reference<S>::value ||
                              std::is_null_pointer<S>::value;
};


template<class F, class In, class Ty>
struct RetType{};

template<class F, class... InArgs, class... TyArgs>
struct RetType<F,void(InArgs...),void(TyArgs...)>{
    using value = typename F::template value<InArgs::value...,TyArgs...>;
};


template<class F, class Ret, class In, class Ty>
struct RetInt{};

template<class F, class Ret, class... InArgs, class... TyArgs>
struct RetInt<F,Ret,void(InArgs...),void(TyArgs...)>{
    static const Ret value = F::template value<InArgs::value...,TyArgs...>;
};


template<class F, bool isInt, class T, class In, class Ty>
struct CurryInt{};

template<class F, class Ret, class Next, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryInt<F,true,Ret(Next,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<Next x>
        using let = typename CurryInt<F,is_nontype<Next2>::value,Ret(Next2,Args...),void(InArgs...,typename ArgLit<Next>::template Arg<x>),void(TyArgs...)>::value;

        using type = Ret(Next,Next2,Args...);
        using type_ret = Ret;
        using type_arg = Next;
    };
};

template<class F, class Ret, class Next, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryInt<F,false,Ret(Next,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename std::enable_if<std::is_base_of<Next,x>::value,typename CurryInt<F,is_nontype<Next2>::value,Ret(Next2,Args...),void(InArgs...),void(TyArgs...,x)>::value>::type;

        using type = Ret(Next,Next2,Args...);
        using type_ret = Ret;
        using type_arg = Next;
    };
};

template<class F, class Ret, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryInt<F,false,Ret(Type,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename CurryInt<F,is_nontype<Next2>::value,Ret(Next2,Args...),void(InArgs...),void(TyArgs...,x)>::value;

        using type = Ret(Type,Next2,Args...);
        using type_ret = Ret;
        using type_arg = Type;
    };
};

template<class F, class Ret, class Next, class... InArgs, class... TyArgs>
struct CurryInt<F,true,Ret(Next),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<Next x>
        static const Ret let = RetInt<F,Ret,void(InArgs...,typename ArgLit<Next>::template Arg<x>),void(TyArgs...)>::value; //F::template value<InArgs::value...,x,TyArgs...>;

        using type = Ret(Next);
        using type_ret = Ret;
        using type_arg = Next;
    };
};

template<class F, class Ret, class Next, class... InArgs, class... TyArgs>
struct CurryInt<F,false,Ret(Next),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        static const Ret let = enable_if_int<std::is_base_of<Next,x>::value,Ret,RetInt<F,Ret,void(InArgs...),void(TyArgs...,x)>::value>::value; //enable_if_int<std::is_base_of<Next,x>::value,Ret,F::template value<InArgs::value...,TyArgs...,x>>::value;

        using type = Ret(Next);
        using type_ret = Ret;
        using type_arg = Next;
    };
};

template<class F, class Ret, class... InArgs, class... TyArgs>
struct CurryInt<F,false,Ret(Type),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        static const Ret let = RetInt<F,Ret,void(InArgs...),void(TyArgs...,x)>::value; //F::template value<InArgs::value...,TyArgs...,x>;

        using type = Ret(Type);
        using type_ret = Ret;
        using type_arg = Type;
    };
};


template<class F, bool isInt, class T, class In, class Ty>
struct CurryType{};

template<class F, class Next, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryType<F,true,Type(Next,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<Next x>
        using let = typename CurryType<F,is_nontype<Next2>::value,Type(Next2,Args...),void(InArgs...,typename ArgLit<Next>::template Arg<x>),void(TyArgs...)>::value;

        using type = Type(Next,Next2,Args...);
        using type_ret = Type;
        using type_arg = Next;
    };
};

template<class F, class Next, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryType<F,false,Type(Next,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename std::enable_if<std::is_base_of<Next,x>::value,typename CurryType<F,is_nontype<Next2>::value,Type(Next2,Args...),void(InArgs...),void(TyArgs...,x)>::value>::type;

        using type = Type(Next,Next2,Args...);
        using type_ret = Type;
        using type_arg = Next;
    };
};

template<class F, class Next2, class... Args, class... InArgs, class... TyArgs>
struct CurryType<F,false,Type(Type,Next2,Args...),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename CurryType<F,is_nontype<Next2>::value,Type(Next2,Args...),void(InArgs...),void(TyArgs...,x)>::value;

        using type = Type(Type,Next2,Args...);
        using type_ret = Type;
        using type_arg = Type;
    };
};

template<class F, class Next, class... InArgs, class... TyArgs>
struct CurryType<F,true,Type(Next),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<Next x>
        using let = typename RetType<F,void(InArgs...,typename ArgLit<Next>::template Arg<x>),void(TyArgs...)>::value; //typename F::template value<InArgs::value...,x,TyArgs...>;

        using type = Type(Next);
        using type_ret = Type;
        using type_arg = Next;
    };
};

template<class F, class Next, class... InArgs, class... TyArgs>
struct CurryType<F,false,Type(Next),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename std::enable_if<std::is_base_of<Next,x>::value,typename RetType<F,void(InArgs...),void(TyArgs...,x)>::value>::type; //typename std::enable_if<std::is_base_of<Next,x>::value,typename F::template value<InArgs::value...,TyArgs...,x>>::type;

        using type = Type(Next);
        using type_ret = Type;
        using type_arg = Next;
    };
};

template<class F, class... InArgs, class... TyArgs>
struct CurryType<F,false,Type(Type),void(InArgs...),void(TyArgs...)>{
    struct value{
        template<class x>
        using let = typename RetType<F,void(InArgs...),void(TyArgs...,x)>::value; //typename F::template value<InArgs::value...,TyArgs...,x>;

        using type = Type(Type);
        using type_ret = Type;
        using type_arg = Type;
    };
};


template<class F, bool isRetInt, class T>
struct CurryingAux2{};

template<class F, class Ret, class Next, class... Args>
struct CurryingAux2<F,true,Ret(Next,Args...)>{
    using value = typename CurryInt<F,is_nontype<Next>::value,Ret(Next,Args...),void(),void()>::value;
};

template<class F, class Next, class... Args>
struct CurryingAux2<F,false,Type(Next,Args...)>{
    using value = typename CurryType<F,is_nontype<Next>::value,Type(Next,Args...),void(),void()>::value;
};


template<class F, class T>
struct CurryingAux{};

template<class F, class Ret, class... Args>
struct CurryingAux<F,Ret(Args...)>{
    using value = typename CurryingAux2<F,is_nontype<Ret>::value,Ret(Args...)>::value;
};

template<class F, class T>
using Currying = typename CurryingAux<F,T>::value;

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

template<class f, class g, bool isfRetNonType, bool isgRetNonType, bool isgArgNonType>
struct compAux{};

template<class f, class g>
struct compAux<f,g,true,true,true> : public Currying<compAux<f,g,true,true,true>,typename f::type_ret(typename g::type_arg)>{
    template<typename g::type_arg x>
    static const typename f::type_ret value = f::template let<g::template let<x>>;
};

template<class f, class g>
struct compAux<f,g,true,true,false> : public Currying<compAux<f,g,true,true,false>,typename f::type_ret(typename g::type_arg)>{
    template<class x>
    static const typename f::type_ret value = f::template let<g::template let<x>>;
};

template<class f, class g>
struct compAux<f,g,true,false,true> : public Currying<compAux<f,g,true,false,true>,typename f::type_ret(typename g::type_arg)>{
    template<typename g::type_arg x>
    static const typename f::type_ret value = f::template let<typename g::template let<x>>;
};

template<class f, class g>
struct compAux<f,g,true,false,false> : public Currying<compAux<f,g,true,false,false>,typename f::type_ret(typename g::type_arg)>{
    template<class x>
    static const typename f::type_ret value = f::template let<typename g::template let<x>>;
};

template<class f, class g>
struct compAux<f,g,false,true,true> : public Currying<compAux<f,g,false,true,true>,typename f::type_ret(typename g::type_arg)>{
    template<typename g::type_arg x>
    using value = typename f::template let<g::template let<x>>;
};

template<class f, class g>
struct compAux<f,g,false,true,false> : public Currying<compAux<f,g,false,true,false>,typename f::type_ret(typename g::type_arg)>{
    template<class x>
    using value = typename f::template let<g::template let<x>>;
};

template<class f, class g>
struct compAux<f,g,false,false,true> : public Currying<compAux<f,g,false,false,true>,typename f::type_ret(typename g::type_arg)>{
    template<typename g::type_arg x>
    using value = typename f::template let<typename g::template let<x>>;
};

template<class f, class g>
struct compAux<f,g,false,false,false> : public Currying<compAux<f,g,false,false,false>,typename f::type_ret(typename g::type_arg)>{
    template<class x>
    using value = typename f::template let<typename g::template let<x>>;
};

template<class f, class g>
using comp = compAux<f,g,is_nontype<typename f::type_ret>::value,is_nontype<typename g::type_ret>::value,is_nontype<typename g::type_arg>::value>;

//-----------------------------------------------------------

template<auto x>
struct toTypeAux{};

template<auto x>
using toType = typename toTypeAux<x>::value;


template<class T>
struct toNonTypeAux{};

template<class T>
auto toNonType = toNonTypeAux<T>::value;

//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------



///Metafuncion con lazy-parameters.

///Ejemplo1
struct TrueExample : public Currying<TrueExample,Type(Type,Type)>{
    template<class X, class Y>
    using value = X;
};




///Ejemplo2
struct ConditionalExample : public Currying<ConditionalExample,Type(bool,Type,Type)>{
    template<bool b, class X, class Y>
    using value = typename If<b>::template Then<X>::template Else<Y>;
};



///Ejemplo3 (Un único argumento)
struct IsEvenExample : public Currying<IsEvenExample,bool(int)>{
    template<int n>
    static const bool value = (n%2 == 0);
};



///Ejemplo4 (Alteracion del orden de los argumentos) (En la definicion: non-types a la izquierda y types a la derecha)
struct LeftOrRightExample : Currying<LeftOrRightExample,Type(Type,int,Type)>{
    template<int k, class X, class Y>
    using value = typename If<(k<0)>::template Then<X>::template Else<Y>;
};



//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------

///Currying 2

//template<class... Args>
//using Tuple = void(Args...);
//
//
//template<class NonTypes, class Types>
//struct Currying2{};
//
//template<class... NonTypes, class... Types>
//struct Currying2<Tuple<NonTypes...>,Tuple<Types...>>{
//
//    template<template<NonTypes...,class...> class Func>
//    struct Using{
//
//        template<NonTypes... vargs,class... targs>
//        using value = Func<vargs...,targs...>;
//
//        template<class FuncType>
//        using OfType = typename Currying<Currying2<Tuple<NonTypes...>,Tuple<Types...>>::template Using<Func>,FuncType>;
//
//    };
//
//};

}

#endif // CURRY_H_INCLUDED

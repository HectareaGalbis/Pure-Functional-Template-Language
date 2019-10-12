#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include "solve.h"

template<int k>
struct Int{

    static const int value = k;

};


//------------------------


struct Plus{};


template<class X, class Y, class... Args>
struct solve<Plus,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value+Y::value>,Args...>::template value<k>;

};


//------------------------


struct Minus{};


template<class X, class Y, class... Args>
struct solve<Minus,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value-Y::value>,Args...>::template value<k>;

};


//------------------------


struct Mult{};


template<class X, class Y, class... Args>
struct solve<Mult,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value*Y::value>,Args...>::template value<k>;

};


//------------------------


struct Div{};


template<class X, class Y, class... Args>
struct solve<Div,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value/Y::value>,Args...>::template value<k>;

};


//-----------------------


struct Opp{};


template<class X, class... Args>
struct solve<Opp,X,Args...>{

    template<int k>
    using value = typename solve<Int<-X::value>,Args...>::template value<k>;

};


//--------------------------


struct Equal{};


template<class X, class Y, class... Args>
struct solve<Equal,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<X::value==Y::value>,Args...>::template value<k>;

};


//--------------------------


struct Greater{};


template<class X, class Y, class... Args>
struct solve<Greater,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<(X::value>Y::value)>,Args...>::template value<k>;

};


//--------------------------


struct Less{};


template<class X, class Y, class... Args>
struct solve<Less,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<X::value<Y::value>,Args...>::template value<k>;

};


//--------------------------


struct GreaterEqual{};


template<class X, class Y, class... Args>
struct solve<GreaterEqual,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<(X::value>=Y::value)>,Args...>::template value<k>;

};


//--------------------------


struct LessEqual{};


template<class X, class Y, class... Args>
struct solve<LessEqual,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<X::value<=Y::value>,Args...>::template value<k>;

};



#endif // INTEGER_H_INCLUDED

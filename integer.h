#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include "solve.h"

template<int k>
struct Int{

    static const int value = k;

};


//-------------------


struct Church{};


template<class N, class F, class A, class... Args>
struct solve<Church,N,F,A,Args...>{

    template<int k>
    using value = typename solve<Church,Int<N::value-1>, F, typename solve<F,A>::template value<0>, Args...>::template value<k>;

    using beta = solve<Church,Int<N::value-1>, F, typename solve<F,A>::template value<0>, Args...>;

};


template<class F, class A, class... Args>
struct solve<Church,Int<0>,F,A,Args...>{

    template<int k>
    using value = typename solve<A, Args...>::template value<k>;

    using beta = solve<A, Args...>;

};


//------------------------


struct Plus{};


template<class X, class Y, class... Args>
struct solve<Plus,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value+Y::value>,Args...>::template value<k>;

    using beta = solve< Int<X::value+Y::value>, Args...>;

};


//------------------------


struct Minus{};


template<class X, class Y, class... Args>
struct solve<Minus,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value-Y::value>,Args...>::template value<k>;

    using beta = solve< Int<X::value-Y::value>, Args...>;

};


//------------------------


struct Mult{};


template<class X, class Y, class... Args>
struct solve<Mult,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value*Y::value>,Args...>::template value<k>;

    using beta = solve< Int<X::value*Y::value>, Args...>;

};


//------------------------


struct Div{};


template<class X, class Y, class... Args>
struct solve<Div,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value/Y::value>,Args...>::template value<k>;

    using beta = solve< Int<X::value/Y::value>, Args...>;

};


//---------------------


struct Mod{};


template<class X, class Y, class... Args>
struct solve<Mod,X,Y,Args...>{

    template<int k>
    using value = typename solve<Int<X::value/Y::value>,Args...>::template value<k>;

    using beta = solve< Int<X::value%Y::value>, Args...>;

};


//-----------------------


struct Opp{};


template<class X, class... Args>
struct solve<Opp,X,Args...>{

    template<int k>
    using value = typename solve<Int<-X::value>,Args...>::template value<k>;

    using beta = solve< Int<-X::value>, Args...>;

};


//--------------------------


struct Equal{};


template<class X, class Y, class... Args>
struct solve<Equal,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<X::value==Y::value>,Args...>::template value<k>;

    using beta = solve< Bool<X::value==Y::value>, Args...>;

};


//--------------------------


struct Greater{};


template<class X, class Y, class... Args>
struct solve<Greater,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<(X::value>Y::value)>,Args...>::template value<k>;

    using beta = solve< Bool<(X::value>Y::value)>, Args...>;

};


//--------------------------


struct Less{};


template<class X, class Y, class... Args>
struct solve<Less,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<(X::value<Y::value)>,Args...>::template value<k>;

    using beta = solve< Bool<(X::value<Y::value)>, Args...>;

};


//--------------------------


struct GreaterEqual{};


template<class X, class Y, class... Args>
struct solve<GreaterEqual,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<(X::value>=Y::value)>,Args...>::template value<k>;

    using beta = solve< Bool<(X::value>=Y::value)>, Args...>;

};


//--------------------------


struct LessEqual{};


template<class X, class Y, class... Args>
struct solve<LessEqual,X,Y,Args...>{

    template<int k>
    using value = typename solve<Bool<(X::value<=Y::value)>,Args...>::template value<k>;

    using beta = solve< Bool<(X::value<=Y::value)>, Args...>;

};


//----------------------------


struct Suc{};


template<class N, class... Args>
struct solve<Suc,N,Args...>{

    template<int k>
    using value = typename solve<Int<N::value+1>,Args...>::template value<k>;

    using beta = solve<Int<N::value+1>,Args...>;

};


//----------------------------


struct Pre{};


template<class N, class... Args>
struct solve<Pre,N,Args...>{

    template<int k>
    using value = typename solve<Int<N::value-1>,Args...>::template value<k>;

    using beta = solve<Int<N::value-1>,Args...>;

};


//-----------------------------


struct IsDivisor{};


template<class N, class M, class... Args>
struct solve<IsDivisor,N,M,Args...>{

    template<int k>
    using value = typename solve<Bool<(M::value%N::value)==0>,Args...>::template value<k>;

    using beta = typename solve<Bool<(M::value%N::value)==0>,Args...>::beta;

};


//------------------------------


struct IsPrime{};
struct IsPrimeAux{};


template<class P, class N, class... Args>
struct solve<IsPrimeAux,P,N,Args...>{

    template<int k>
    using value = typename solve<Or,
                                    typename solve<IsDivisor,N,P>::template value<0>,
                                    typename solve<IsPrimeAux,P,Int<N::value-1>>::template value<0>,
                                 Args...>::template value<k>;

    using beta = solve<Or,
                          typename solve<IsDivisor,N,P>::template value<0>,
                          typename solve<IsPrimeAux,P,Int<N::value-1>>::template value<0>,
                       Args...>;

};


template<class P, class... Args>
struct solve<IsPrimeAux,P,Int<1>,Args...>{

    template<int k>
    using value = typename solve<False, Args...>::template value<k>;

    using beta = solve<False, Args...>;

};


template<class N, class... Args>
struct solve<IsPrime,N,Args...>{

    template<int k>
    using value = typename solve<Not,
                                     typename solve<IsPrimeAux,N,Int<N::value-1>>::template value<0>,
                                 Args...>::template value<k>;

    using beta = solve<Not,
                           typename solve<IsPrimeAux,N,Int<N::value-1>>::template value<0>,
                       Args...>;

};



#endif // INTEGER_H_INCLUDED

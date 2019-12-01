#ifndef TUPLE_H_INCLUDED
#define TUPLE_H_INCLUDED

#include "curry.h"
#include "container.h"
#include "bool.h"


namespace pftl{

//----------------------
//----------------------
//----------------------

struct Vector_t : public Container, public IO{};


template<auto...>
struct Vector{};


template<class L, class M>
struct Vector_concat{};


template<class L, class f>
struct Vector_filter{};


//----------------------


template<>
struct Vector<> : public Vector_t{

    static const bool null = true;

    static const size_t length = 0;

    template<class L>
    using concat = L;

    template<class f>
    using map = Vector<>;

    using reverse = Vector<>;

    template<class f>
    using filter = Vector<>;

    static void print(){
        std::cout << std::endl;
    }

};

template<class S, S x, S... xs>
struct Vector<x,xs...> : public Vector_t{

    static const bool null = false;

    static const size_t length = 1+Vector<xs...>::length;

    template<class L>
    using concat = typename Vector_concat<Vector<x,xs...>,L>::value;

    template<class f>
    using map = typename Vector<f::template let<x>>::template concat<typename Vector<xs...>::template map<f>>;

    using reverse = typename Vector<xs...>::reverse::template concat<Vector<x>>;

    template<class f>
    using filter = typename Vector_filter<Vector<x,xs...>,f>::value;

    static void print(){
        std::cout << x;
        Vector<xs...>::print();
    }

};

//----------------------


template<class S, S... xls, S... xms>
struct Vector_concat<Vector<xls...>,Vector<xms...>>{
    using value = Vector<xls...,xms...>;
};


template<bool isFiltered, class L, class f>
struct Vector_filterAux{};

template<class S, S x, S... xs, class f>
struct Vector_filterAux<true,Vector<x,xs...>,f>{
    using value = typename Vector<xs...>::template filter<f>;
};

template<class S, S x, S... xs, class f>
struct Vector_filterAux<false,Vector<x,xs...>,f>{
    using value = typename Vector<x>::template concat<typename Vector<xs...>::template filter<f>>;
};

template<class f, class S, S x, S... xs>
struct Vector_filter<Vector<x,xs...>,f>{
    using value = typename Vector_filterAux<f::template let<x>,Vector<x,xs...>,f>::value;
};

//----------------------
//----------------------
//----------------------


//Hay que pasarle constexpr const char var[].
template<const char* text, int i, char c>
struct makeStringAux{
    using value = typename concat::let<Vector<c>>::template let<typename makeStringAux<text,i+1,text[i+1]>::value>;
};

template<const char* text, int i>
struct makeStringAux<text,i,'\0'>{
    using value = Vector<'\0'>;
};

struct makeString : public Currying<makeString,Type(const char*)>{
    template<const char* text>
    using value = typename makeStringAux<text,0,text[0]>::value;
};


//----------------------
//----------------------
//----------------------




//template<uintmax_t n, class S, S s, class F>
//struct getSeqAux{
//    using value = typename concat::let<Vector<s>>::template let<typename getSeqAux<n-1,S,F::template let<s>,F>::value>;
//};
//
//template<class S, S s, class F>
//struct getSeqAux<0,S,s,F>{
//    using value = Vector<>;
//};
//
//
//template<class S>
//struct getSeq : Currying<getSeq<S>,Type(uintmax_t,S,Type)>{
//    template<uintmax_t n, S s, class F>
//    using value = typename getSeqAux<n,S,s,F>::value;
//};



}


#endif // TUPLE_H_INCLUDED

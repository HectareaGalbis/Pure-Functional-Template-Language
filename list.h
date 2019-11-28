#ifndef TUPLE_H_INCLUDED
#define TUPLE_H_INCLUDED

#include "curry.h"
#include "container.h"
#include "bool.h"


namespace pftl{

//----------------------
//----------------------
//----------------------

template<auto...>
struct List;


template<class L, class M>
struct List_concat : public Container{};


template<class L, class f>
struct List_filter{};


//----------------------


template<auto... xs>
struct List : public Container{

    static const bool null = true;

    static const size_t length = 0;

    template<class L>
    using concat = L;

    template<class f>
    using map = List<>;

    using reverse = List<>;

    template<class f>
    using filter = List<>;

    static void print(){
        std::cout << std::endl;
    }

};

template<auto x, auto... xs>
struct List<x,xs...> : public Container{

    static const bool null = false;

    static const size_t length = 1+List<xs...>::length;

    template<class L>
    using concat = typename List_concat<List<x,xs...>,L>::value;

    template<class f>
    using map = typename List<f::template let<x>>::template concat<typename List<xs...>::template map<f>>;

    using reverse = typename List<x>::template concat<typename List<xs...>::reverse>;

    template<class f>
    using filter = typename List_filter<List<x,xs...>,f>::value;

    static void print(){
        std::cout << x;
        List<xs...>::print();
    }

};

//----------------------


template<class S, S... xls, S... xms>
struct List_concat<List<xls...>,List<xms...>>{
    using value = List<xls...,xms...>;
};


template<bool isFiltered, class L, class f>
struct List_filterAux{};

template<class S, S x, S... xs, class f>
struct List_filterAux<true,List<x,xs...>,f>{
    using value = typename List<xs...>::template filter<f>;
};

template<class S, S x, S... xs, class f>
struct List_filterAux<false,List<x,xs...>,f>{
    using value = typename List<x>::template concat<typename List<xs...>::template filter<f>>;
};

template<class f, class S, S x, S... xs>
struct List_filter<List<x,xs...>,f>{
    using value = typename List_filterAux<f::template let<x>,List<x,xs...>,f>::value;
};

//----------------------
//----------------------
//----------------------


//Hay que pasarle constexpr const char var[].
template<const char* text, int i, char c>
struct makeStringAux{
    using value = typename concat::let<List<c>>::template let<typename makeStringAux<text,i+1,text[i+1]>::value>;
};

template<const char* text, int i>
struct makeStringAux<text,i,'\0'>{
    using value = List<'\0'>;
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
//    using value = typename concat::let<List<s>>::template let<typename getSeqAux<n-1,S,F::template let<s>,F>::value>;
//};
//
//template<class S, S s, class F>
//struct getSeqAux<0,S,s,F>{
//    using value = List<>;
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

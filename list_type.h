#ifndef LIST_TYPE_H_INCLUDED
#define LIST_TYPE_H_INCLUDED

#include "curry.h"
#include "show_type.h"
#include "eq_type.h"

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

struct Int_t;
struct Bool_t;

template<int k>
struct Int;

template<bool b>
struct Bool;

template<char c>
struct Char;

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class T>
struct List_t{};

//--------------------------------------------------------------------------------

struct head : public Currying<head,Type(List_t<Type>)>{
    template<class L>
    using value = typename L::head;
};


struct tail : public Currying<tail,List_t<Type>(List_t<Type>)>{
    template<class L>
    using value = typename L::tail;
};


struct last : public Currying<last,Type(List_t<Type>)>{
    template<class L>
    using value = typename L::last;
};


struct init : public Currying<init,List_t<Type>(List_t<Type>)>{
    template<class L>
    using value = typename L::init;
};


struct take : public Currying<take,List_t<Type>(Int_t,List_t<Type>)>{
    template<class I,class L>
    using value = typename L::template take<I>;
};


struct drop : public Currying<drop,List_t<Type>(Int_t,List_t<Type>)>{
    template<class I,class L>
    using value = typename L::template drop<I>;
};


struct elem : public Currying<head,Bool_t(Type,List_t<Type>)>{
    template<class T,class L, class W1 = Where<Eq_c,T>, class W2 = Where<Eq_c,L>>
    using value = typename L::template elem<T>;
};


struct get : public Currying<get,Type(List_t<Type>,Int_t)>{
    template<class L,class I>
    using value = typename L::template get<I>;
};


struct null : public Currying<null,Bool_t(List_t<Type>)>{
    template<class S>
    using value = typename S::null;
};


struct length : public Currying<length,Int_t(List_t<Type>)>{
    template<class S>
    using value = typename S::length;
};

struct cons : public Currying<cons,List_t<Type>(Type,List_t<Type>)>{
    template<class X, class L>
    using value = typename L::template cons<X>;
};

struct concat : public Currying<concat,List_t<Type>(List_t<Type>,List_t<Type>)>{
    template<class L, class M>
    using value = typename L::template concat<M>;
};


struct map : public Currying<map,List_t<Type>(Type,List_t<Type>)>{
    template<class f, class L>
    using value = typename L::template map<f>;
};


struct reverse : public Currying<reverse,List_t<Type>(List_t<Type>)>{
    template<class S>
    using value = typename S::reverse;
};


struct filter : public Currying<filter,List_t<Type>(Type,List_t<Type>)>{
    template<class f, class L>
    using value = typename L::template filter<f>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class L, class M>
struct List_concat{};

template<class L, class f>
struct List_filter{};

template<class L>
struct last_List{};

template<class L>
struct init_List{};

template<class I, class L>
struct take_List{};

template<class I, class L>
struct drop_List{};

template<class L>
struct length_List{};

//--------------------------------------------------------------------------------

template<class... XS>
struct List{};

//--------------------------------------------------------------------------------

template<>
struct List<>{

    template<class I>
    using take = List<>;

    template<class I>
    using drop = List<>;

    template<class T>
    using elem = Bool<false>;

    using null = Bool<true>;

    using length = Int<0>;

    template<class XN>
    using cons = List<XN>;

    template<class L>
    using concat = typename List_concat<List<>,L>::value;

    template<class f>
    using map = List<>;

    using reverse = List<>;

    template<class f>
    using filter = List<>;

};

//--------------------------------------------------------------------------------

template<class X, class... XS>
struct List<X,XS...>{

    using head = X;

    using tail = List<XS...>;

    using last = typename last_List<List<X,XS...>>::value;

    using init = typename init_List<List<X,XS...>>::value;

    template<class I>
    using take = typename take_List<I,List<X,XS...>>::value;

    template<class I>
    using drop = typename drop_List<I,List<X,XS...>>::value;

    using null = Bool<false>;

    using length = typename length_List<List<X,XS...>>::value;

    template<class XN>
    using cons = List<XN,X,XS...>;

    template<class L>
    using concat = typename List_concat<List<X,XS...>,L>::value;

    template<class f>
    using map = typename List<typename f::template let<X>>::template concat<typename List<XS...>::template map<f>>;

    using reverse = typename List<XS...>::reverse::template concat<List<X>>;

    template<class f>
    using filter = typename List_filter<List<X,XS...>,f>::value;

};

//--------------------------------------------------------------------------------

template<class X, class... XS>
struct take_List<Int<0>,List<X,XS...>>{
    using value = List<>;
};

template<int n>
struct take_List<Int<n>,List<>>{
    using value = List<>;
};

template<int n, class X, class... XS>
struct take_List<Int<n>,List<X,XS...>>{
    using value = typename cons::let<X>::template let<typename take_List<Int<n-1>,List<XS...>>::value>;
};

template<class X, class... XS>
struct drop_List<Int<0>,List<X,XS...>>{
    using value = List<X,XS...>;
};

template<int k>
struct drop_List<Int<k>,List<>>{
    using value = List<>;
};

template<int k, class X, class... XS>
struct drop_List<Int<k>,List<X,XS...>>{
    using value = drop_List<Int<k-1>,List<XS...>>;
};

template<class X>
struct last_List<List<X>>{
    using value = X;
};

template<class X, class... XS>
struct last_List<List<X,XS...>>{
    using value = typename last_List<List<XS...>>::value;
};

template<class X>
struct init_List<List<X>>{
    using value = List<>;
};

template<class X, class... XS>
struct init_List<List<X,XS...>>{
    using value = typename cons::let<X>::template let<typename init_List<List<XS...>>::value>;
};

template<class... XLS, class... XMS>
struct List_concat<List<XLS...>,List<XMS...>>{
    using value = List<XLS...,XMS...>;
};

template<class isFiltered, class L, class f>
struct List_filterAux{};

template<class X, class... XS, class f>
struct List_filterAux<Bool<false>,List<X,XS...>,f>{
    using value = typename List<XS...>::template filter<f>;
};

template<class X, class... XS, class f>
struct List_filterAux<Bool<true>,List<X,XS...>,f>{
    using value = typename List<X>::template concat<typename List<XS...>::template filter<f>>;
};

template<class f, class X, class... XS>
struct List_filter<List<X,XS...>,f>{
    using value = typename List_filterAux<typename f::template let<X>,List<X,XS...>,f>::value;
};

template<class L>
struct length_ListAux{
    static const int value = 0;
};

template<class X, class... XS>
struct length_ListAux<List<X,XS...>>{
    static const int value = 1+length_ListAux<List<XS...>>::value;
};

template<class X, class... XS>
struct length_List<List<X,XS...>>{
    using value = Int<length_ListAux<List<X,XS...>>::value>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<>
struct Show_c<List<>>{
    using show = List<Char<'"'>,Char<'"'>>;
};

template<class... XS>
struct Show_c<List<XS...>>{
    using show = List<Char<'"'>,XS...,Char<'"'>>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

//Hay que pasarle constexpr char var[].
template<const char* text, int i, char c>
struct toStringAux{
    using value = typename concat::let<List<Char<c>>>::template let<typename toStringAux<text,i+1,text[i+1]>::value>;
};

template<const char* text, int i>
struct toStringAux<text,i,'\0'>{
    using value = List<>;
};

template<const char* text>
using toString = typename toStringAux<text,0,text[0]>::value;

//--------------------------------------------------------------------------------

template<class L>
constexpr char fromString[] = {};

template<char... cs>
constexpr char fromString<List<Char<cs>...>>[] = {cs...,'\0'};

//--------------------------------------------------------------------------------
//********************************************************************************

}

namespace std{

    template<class S>
    struct is_base_of<pftl::List_t<S>,pftl::List<>>{
        static const bool value = true;
    };

    template<class S, class X, class... XS>
    struct is_base_of<pftl::List_t<S>,pftl::List<X,XS...>>{
        static const bool value = is_base_of<S,X>::value && is_base_of<pftl::List_t<S>,pftl::List<XS...>>::value;
    };

}



#endif // LIST_TYPE_H_INCLUDED

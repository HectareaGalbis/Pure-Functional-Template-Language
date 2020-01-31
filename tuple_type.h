#ifndef TUPLE_TYPE_H_INCLUDED
#define TUPLE_TYPE_H_INCLUDED


#include "curry.h"
#include "show_type.h"
#include "list_type.h"


namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class... TS>
struct Tuple_t{};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class... XS>
struct Tuple{};

//--------------------------------------------------------------------------------

template<class X, class Y>
using Pair = Tuple<X,Y>;

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class... XS>
struct show_Tuple{};

template<class... XS>
struct Show_c<Tuple<XS...>>{

    using show = cons::let<Char<'('>>::let<typename show_Tuple<XS...>::value>;

};

template<class X>
struct show_Tuple<X>{
    using value = typename concat::let<show::let<X>>::template let<List<Char<')'>>>;
};

template<class X, class... XS>
struct show_Tuple<X,XS...>{
    using value = typename concat::let<show::let<X>>::template let<typename cons::let<Char<','>>::let<typename show_Tuple<XS...>::value>>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}

namespace std{

template<class T, class X>
struct is_base_of<Tuple_t<T>,Tuple<X>>{
    static constexpr bool value = is_base_of<T,X>::value;
};

template<class T, class... TS, class X, class... XS>
struct is_base_of<Tuple_t<T,TS...>,Tuple<X,XS...>>{
    static constexpr bool value = is_base_of<T,X>::value && is_base_of<Tuple_t<TS...>,Tuple<XS...>>::value;
};

}


#endif // TUPLE_TYPE_H_INCLUDED

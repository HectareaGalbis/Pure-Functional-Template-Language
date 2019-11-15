#ifndef BOLEANCHURCH_H_INCLUDED
#define BOLEANCHURCH_H_INCLUDED

#include "curry.h"


namespace pftl{

//struct False;
//
//struct True{
//
//    using type = bool;
//    static const bool value = true;
//
//    template<class X, class Y>
//    using uncurry = X;
//
//    template<class... Args>
//    using let = curry<True::uncurry,2,Args...>;
//
//    using _not = False;
//
//    template<class S>
//    using _and = S;
//
//    template<class S>
//    using _or = True;
//
//};
//
//struct False{
//
//    using type = bool;
//    static const bool value = false;
//
//    template<class X, class Y>
//    using uncurry = Y;
//
//    template<class... Args>
//    using let = curry<False::uncurry,2,Args...>;
//
//    using _not = True;
//
//    template<class S>
//    using _and = False;
//
//    template<class S>
//    using _or = S;
//
//};
//
//template<bool b>
//struct B_impl{
//    using value = True;
//};
//
//template<>
//struct B_impl<false>{
//    using value = False;
//};
//
//template<bool b>
//using B = typename B_impl<b>::value;

struct not_logic{

    template<bool p>
    static const bool let = !p;

};

struct and_logicUncurry{

    template<bool p, bool q>
    static const bool value = p && q;

};

using and_logic = Curryfication<and_logicUncurry,bool(bool,bool)>;

struct or_logicUncurry{

    template<bool p, bool q>
    static const bool value = p || q;

};

using or_logic = Curryfication<or_logicUncurry,bool(bool,bool)>;


}

#endif // BOLEANCHURCH_H_INCLUDED

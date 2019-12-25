#ifndef BOOL_TYPE_H_INCLUDED
#define BOOL_TYPE_H_INCLUDED

#include "curry.h"
#include "show_type.h"
#include "eq_type.h"

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class... XS>
struct List;

template<char c>
struct Char;

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

struct Bool_t{};

//--------------------------------------------------------------------------------

struct and_logic : public Currying<and_logic,Bool_t(Bool_t,Bool_t)>{
    template<class B, class C>
    using value = typename B::template and_logic<C>;
};

struct or_logic : public Currying<or_logic,Bool_t(Bool_t,Bool_t)>{
    template<class B, class C>
    using value = typename B::template or_logic<C>;
};

struct not_logic : public Currying<not_logic,Bool_t(Bool_t)>{
    template<class B>
    using value = typename B::not_logic;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class B, class C>
struct and_logic_Bool{};

template<class B, class C>
struct or_logic_Bool{};

//--------------------------------------------------------------------------------

template<bool b>
struct Bool : public Bool_t{

    template<class B>
    using and_logic = typename and_logic_Bool<Bool<b>,B>::value;

    template<class B>
    using or_logic = typename or_logic_Bool<Bool<b>,B>::value;

    using not_logic = Bool<!b>;

};

//--------------------------------------------------------------------------------

template<bool b, bool c>
struct and_logic_Bool<Bool<b>,Bool<c>>{
    using value = Bool<b&&c>;
};

template<bool b, bool c>
struct or_logic_Bool<Bool<b>,Bool<c>>{
    using value = Bool<b||c>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

using True = Bool<true>;
using False = Bool<false>;

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class B>
struct If{
    template<class T>
    struct Then{
        template<class E>
        using Else = E;
    };
};

template<>
struct If<True>{
    template<class T>
    struct Then{
        template<class E>
        using Else = T;
    };
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class B, class C>
struct eq_Bool{};

//--------------------------------------------------------------------------------

template<bool b>
struct Eq_c<Bool<b>>{

    template<class C>
    using eq = typename eq_Bool<Bool<b>,C>::value;

};

//--------------------------------------------------------------------------------

template<bool b, bool c>
struct eq_Bool<Bool<b>,Bool<c>>{
    using value = Bool<b==c>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class B>
struct show_Bool{};

//--------------------------------------------------------------------------------

template<bool b>
struct Show_c<Bool<b>>{

    using show = typename show_Bool<Bool<b>>::value;

};

//--------------------------------------------------------------------------------

template<>
struct show_Bool<Bool<false>>{
    using value = List<Char<'F'>,Char<'a'>,Char<'l'>,Char<'s'>,Char<'e'>>;
};

template<>
struct show_Bool<Bool<true>>{
    using value = List<Char<'T'>,Char<'r'>,Char<'u'>,Char<'e'>>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}

#endif // BOOL_TYPE_H_INCLUDED

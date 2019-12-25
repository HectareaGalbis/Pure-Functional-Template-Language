#ifndef CHAR_TYPE_H_INCLUDED
#define CHAR_TYPE_H_INCLUDED

#include "curry.h"
#include "show_type.h"
#include "ord_type.h"
#include "eq_type.h"


namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<bool b>
struct Bool;

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

struct Char_t{

    using isSpace = Undefined;

    using isLower = Undefined;

    using isUpper = Undefined;

    using isAlpha = Undefined;

    using isAlphaNum = Undefined;

    using isDigit = Undefined;

    using isOctDigit = Undefined;

    using isHexDigit = Undefined;

    using toLower = Undefined;

    using toUpper = Undefined;

};

//--------------------------------------------------------------------------------

struct isSpace : public Currying<isSpace,Bool_t(Char_t)>{
    template<class C>
    using value = typename C::isSpace;
};

struct isLower : public Currying<isLower,Bool_t(Char_t)>{
    template<class C>
    using value = typename C::isLower;
};

struct isUpper : public Currying<isUpper,Bool_t(Char_t)>{
    template<class C>
    using value = typename C::isUpper;
};

struct isAlpha : public Currying<isAlpha,Bool_t(Char_t)>{
    template<class C>
    using value = typename C::isAlpha;
};

struct isAlphaNum : public Currying<isAlphaNum,Bool_t(Char_t)>{
    template<class C>
    using value = typename C::isAlphaNum;
};

struct isDigit : public Currying<isDigit,Bool_t(Char_t)>{
    template<class C>
    using value = typename C::isDigit;
};

struct isOctDigit : public Currying<isOctDigit,Bool_t(Char_t)>{
    template<class C>
    using value = typename C::isOctDigit;
};

struct isHexDigit : public Currying<isHexDigit,Bool_t(Char_t)>{
    template<class C>
    using value = typename C::isHexDigit;
};

struct toLower : public Currying<toLower,Char_t(Char_t)>{
    template<class C>
    using value = typename C::toLower;
};

struct toUpper : public Currying<toUpper,Char_t(Char_t)>{
    template<class C>
    using value = typename C::toUpper;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<char c>
struct isSpace_Char{
    using value = Bool<false>;
};

template<class B, class C>
struct toUpper_Char{};

template<class B, class C>
struct toLower_Char{};

//--------------------------------------------------------------------------------

template<char c>
struct Char : public Char_t{

    using isSpace = typename isSpace_Char<c>::value;

    using isLower = Bool<(c>='a' && c<='z')>;

    using isUpper = Bool<(c>='A' && c<='Z')>;

    using isAlpha = Bool<(c>='a' && c<='z') || (c>='A' && c<='Z')>;

    using isDigit = Bool<(c>='0' && c<='9')>;

    using isOctDigit = Bool<(c>='0' && c<='7')>;

    using isHexDigit = Bool<(c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F')>;

    using isAlphaNum = Bool<(c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z')>;

    using toUpper = typename toUpper_Char<Bool<(c>='a' && c<='z')>,Char<c>>::value;

    using toLower = typename toLower_Char<Bool<(c>='A' && c<='Z')>,Char<c>>::value;

};

//--------------------------------------------------------------------------------

template<>
struct isSpace_Char<' '>{
    using value = True;
};

template<>
struct isSpace_Char<'\t'>{
    using value = True;
};

template<>
struct isSpace_Char<'\r'>{
    using value = True;
};

template<>
struct isSpace_Char<'\n'>{
    using value = True;
};

template<>
struct isSpace_Char<'\v'>{
    using value = True;
};

template<>
struct isSpace_Char<'\f'>{
    using value = True;
};

template<char c>
struct toUpper_Char<Bool<true>,Char<c>>{
    using value = Char<(c+'A')-'a'>;
};

template<char c>
struct toUpper_Char<Bool<false>,Char<c>>{
    using value = Char<c>;
};

template<char c>
struct toLower_Char<Bool<true>,Char<c>>{
    using value = Char<(c+'a')-'A'>;
};

template<char c>
struct toLower_Char<Bool<false>,Char<c>>{
    using value = Char<c>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class C, class D>
struct eq_Char{};

//--------------------------------------------------------------------------------

template<char c>
struct Eq_c<Char<c>>{

    template<class C>
    using eq = typename eq_Char<Char<c>,C>::value;

};

//--------------------------------------------------------------------------------

template<char c, char d>
struct eq_Char<Char<c>,Char<d>>{
    using value = Bool<c==d>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<class C, class D>
struct le_Char{};

//--------------------------------------------------------------------------------

template<char c>
struct Ord_c<Char<c>>{

    template<class C>
    using le = typename le_Char<Char<c>,C>::value;

};

//--------------------------------------------------------------------------------

template<char c, char d>
struct le_Char<Char<c>,Char<d>>{
    using value = Bool<(c<=d)>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<char c>
struct Show_c<Char<c>>{

    using show = List<Char<c>>;

};

//--------------------------------------------------------------------------------
//********************************************************************************

//********************************************************************************
//--------------------------------------------------------------------------------

template<char c>
struct toNonType_impl<Char<c>>{
    static const char value = c;
};

template<char c>
struct toType_impl<c>{
    using value = Char<c>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}


#endif // CHAR_TYPE_H_INCLUDED

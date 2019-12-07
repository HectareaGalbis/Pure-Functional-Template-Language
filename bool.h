#ifndef BOLEANCHURCH_H_INCLUDED
#define BOLEANCHURCH_H_INCLUDED

#include "curry.h"
#include "eq.h"

namespace pftl{


///Clase Bool.
struct Bool_t : public Eq_t{

    using and_logic = Undefined;

    using or_logic = Undefined;

    using not_logic = Undefined;

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

struct and_logic : public Currying<and_logic,Type(Bool_t,Bool_t)>{
    template<class B, class C>
    using value = typename B::template and_logic<C>;
};

struct or_logic : public Currying<or_logic,Type(Bool_t,Bool_t)>{
    template<class B, class C>
    using value = typename B::template or_logic<C>;
};

struct not_logic : public Currying<not_logic,Type(Bool_t)>{
    template<class B>
    using value = typename B::not_logic;
};


//********************************************************************************
//--------------------------------------------------------------------------------
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//--------------------------------------------------------------------------------
//********************************************************************************

///Constructores
struct True;
struct False;

//--------------------------------------------------------------------------------

template<bool b>
struct BoolAux{
    using value = False;
};

template<>
struct BoolAux<true>{
    using value = True;
};

template<bool b>
using Bool = typename BoolAux<b>::value;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class B, class C>
struct eq_Bool{};

//--------------------------------------------------------------------------------

struct True : public Bool_t{

    template<class B>
    using and_logic = B;

    template<class B>
    using or_logic = True;

    using not_logic = False;

    //---

    template<class B>
    using eq = typename eq_Bool<True,B>::value;

};

//--------------------------------------------------------------------------------

struct False : public Bool_t{

    template<class B>
    using and_logic = False;

    template<class B>
    using or_logic = B;

    using not_logic = True;

    template<class B>
    using eq = typename eq_Bool<False,B>::value;

};

//--------------------------------------------------------------------------------

template<>
struct eq_Bool<False,False>{
    using value = True;
};

template<>
struct eq_Bool<False,True>{
    using value = False;
};

template<>
struct eq_Bool<True,False>{
    using value = False;
};

template<>
struct eq_Bool<True,True>{
    using value = True;
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

///Conversiones 'non-type' 'type'
template<bool b>
struct toTypeAux<b>{
    using value = Bool<b>;
};


template<>
struct toNonTypeAux<True>{
    static const bool value = true;
};
template<>
struct toNonTypeAux<False>{
    static const bool value = false;
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<class B>
struct If{};

template<>
struct If<True>{
    template<class X>
    struct Then{
        template<class Y>
        using Else = X;
    };
};

template<>
struct If<False>{
    template<class X>
    struct Then{
        template<class Y>
        using Else = Y;
    };
};


}

#endif // BOLEANCHURCH_H_INCLUDED

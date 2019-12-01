#ifndef BOLEANCHURCH_H_INCLUDED
#define BOLEANCHURCH_H_INCLUDED

#include "curry.h"
#include "eq.h"

namespace pftl{


struct not_logic : public Currying<not_logic,bool(bool)>{
    template<bool p>
    static const bool value = !p;
};


struct and_logic : public Currying<and_logic,bool(bool,bool)>{
    template<bool p, bool q>
    static const bool value = p && q;
};


struct or_logic : public Currying<or_logic,bool(bool,bool)>{
    template<bool p, bool q>
    static const bool value = p || q;
};


//----------------------------------------
//----------------------------------------
//----------------------------------------


///Clase Bool.
struct Bool : public Eq{

    using andB = Undefined;

    using orB = Undefined;

    using notB = Undefined;

};


struct andB : public Currying<andB,Type(Bool,Bool)>{
    template<class B, class C>
    using value = typename B::template andB<C>;
};

struct orB : public Currying<orB,Type(Bool,Bool)>{
    template<class B, class C>
    using value = typename B::template orB<C>;
};

struct notB : public Currying<notB,Type(Bool)>{
    template<class B>
    using value = typename B::notB;
};


///Constructores
struct True;
struct False;

template<class B, class C>
struct eqAux{};

template<>
struct eqAux<False,False>{
    using value = True;
};

template<>
struct eqAux<False,True>{
    using value = False;
};

template<>
struct eqAux<True,False>{
    using value = False;
};

template<>
struct eqAux<True,True>{
    using value = True;
};


struct True : public Bool{

    template<class B>
    using andB = B;

    template<class B>
    using orB = True;

    using notB = False;

    //---

    template<class B>
    using eq = typename eqAux<True,B>::value;

};

struct False : public Bool{

    template<class B>
    using andB = False;

    template<class B>
    using orB = B;

    using notB = True;

    template<class B>
    using eq = typename eqAux<False,B>::value;

};


}

#endif // BOLEANCHURCH_H_INCLUDED

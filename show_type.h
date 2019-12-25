#ifndef SHOW_TYPE_H_INCLUDED
#define SHOW_TYPE_H_INCLUDED

#include "curry.h"

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class A>
struct Show_c{

    using show = Undefined;

};

//********************************************************************************

struct Char_t;

template<class T>
struct List_t;

//--------------------------------------------------------------------------------

struct show : public Currying<show,List_t<Char_t>(Type)>{
    template<class S, class W1 = Where<Show_c,S>>
    using value = typename Show_c<S>::show;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}

#endif // SHOW_TYPE_H_INCLUDED

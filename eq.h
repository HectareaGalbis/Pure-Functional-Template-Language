#ifndef EQ_H_INCLUDED
#define EQ_H_INCLUDED

#include "curry.h"


namespace pftl{


struct Eq_t{

    template<class T>
    using eq = Undefined;

};


struct eq : public Currying<eq,Type(Eq_t,Eq_t)>{
    template<class S, class T>
    using value = typename S::template eq<T>;
};

struct ne : Currying<ne,Type(Eq_t,Eq_t)>{
    template<class S, class T>
    using value = typename S::template eq<T>::notB;   // <-- Un poco feo.
};


}


#endif // EQ_H_INCLUDED

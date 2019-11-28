#ifndef BOLEANCHURCH_H_INCLUDED
#define BOLEANCHURCH_H_INCLUDED

#include "curry.h"


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

}

#endif // BOLEANCHURCH_H_INCLUDED

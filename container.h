#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED


#include "curry.h"
#include "io.h"

namespace pftl{


struct Container{

    static const bool null = false;

    static const size_t length = 0;

    template<class L>
    using concat = Undefined;

    template<class f>
    using map = Undefined;

    using reverse = Undefined;

    template<class f>
    using filter = Undefined;

};


struct null : public Currying<null,bool(Container)>{
    template<class S>
    static const bool value = S::null;
};


struct length : public Currying<length,size_t(Container)>{
    template<class S>
    static const size_t value = S::length;
};


struct concat : public Currying<concat,Type(Container,Container)>{
    template<class L, class M>
    using value = typename L::template concat<M>;
};


struct map : public Currying<map,Type(Type,Container)>{
    template<class f, class L>
    using value = typename L::template map<f>;
};


struct reverse : public Currying<reverse,Type(Container)>{
    template<class S>
    using value = typename S::reverse;
};


struct filter : public Currying<filter,Type(Type,Container)>{
    template<class f, class L>
    using value = typename L::template filter<f>;
};


}



#endif // CONTAINER_H_INCLUDED

#ifndef FUNCTOR_TYPE_H_INCLUDED
#define FUNCTOR_TYPE_H_INCLUDED

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class T>
struct Functor_c : Class{

    template<class f>
    using fmap = Undefined;

};

//--------------------------------------------------------------------------------

struct fmap : Currying<fmap,Type(Type,Type)>{
    template<class f, class T, class W1 = Where<Functor_c,T>>
    using value = typename Functor_c<T>::template fmap<f>;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}


#endif // FUNCTOR_TYPE_H_INCLUDED

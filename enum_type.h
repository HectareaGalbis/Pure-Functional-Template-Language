#ifndef ENUM_TYPE_H_INCLUDED
#define ENUM_TYPE_H_INCLUDED


namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class A>
struct Enum_c : Class{

    using succ = Undefined;

    using pred = Undefined;

};

//********************************************************************************

struct succ : public Currying<succ,Type(Type)>{
    template<class E, class W1 = Where<Enum_c,E>>
    using value = typename Enum_c<E>::succ;
};

struct pred : public Currying<pred,Type(Type)>{
    template<class E, class W1 = Where<Enum_c,E>>
    using value = typename Enum_c<E>::pred;
};

//--------------------------------------------------------------------------------
//********************************************************************************

}


#endif // ENUM_TYPE_H_INCLUDED

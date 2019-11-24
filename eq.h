#ifndef EQ_H_INCLUDED
#define EQ_H_INCLUDED

namespace pftl{


struct Eq{

    template<class T>
    static const bool equalT = std::is_same<Eq,T>::value;

};


struct equalTUncurry{
    template<class S, class T>
    static const bool value = S::template equalT<T>;
};
using equalT = Currying<equalTUncurry,bool(Eq,Eq)>;


struct diffTUncurry{
    template<class S, class T>
    static const bool value = not S::template equalT<T>;
};
using diffT = Currying<diffTUncurry,bool(Eq,Eq)>;


}


#endif // EQ_H_INCLUDED

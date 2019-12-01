#ifndef INT_H_INCLUDED
#define INT_H_INCLUDED


namespace pftl{


struct Int : public Ord{};


template<int x>
struct I : public Int{



};


template<int x>
struct toTypeAux<x>{
    using value = I<x>;
};

template<int x>
struct toNonTypeAux<I<x>>{
    static const int value = x;
};

}



#endif // INT_H_INCLUDED

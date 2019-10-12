#ifndef PACK_H_INCLUDED
#define PACK_H_INCLUDED

template<int k, class... Args>
struct getValue{};

template<class T, class... Args>
struct getValue<0,T,Args...>{

    using value = T;

};

template<int k, class T, class... Args>
struct getValue<k,T,Args...>{

    using value = typename getValue<k-1,Args...>::value;

};


template<class... Args>
struct solve{};

template<class T, class... Args>
struct solve<T,Args...>{

    template<int k>
    using value = typename getValue<k,T,Args...>::value;

};






#endif // PACK_H_INCLUDED

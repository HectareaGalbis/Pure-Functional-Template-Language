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
struct solve{

    static const int size = 0;

};

template<class T, class... Args>
struct solve<T,Args...>{

    template<int k>
    using value = typename getValue<k,T,Args...>::value;

    static const int size = 1+solve<Args...>::size;

    using beta = T;
    using head = T;
    using tail = solve<Args...>;

};






#endif // PACK_H_INCLUDED

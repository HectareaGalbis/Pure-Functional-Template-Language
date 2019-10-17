#ifndef TUPLE_H_INCLUDED
#define TUPLE_H_INCLUDED

#include "curry.h"
#include "bool.h"

template<class X, class Y>
struct Pair{

    template<class F>
    using value = typename F::template let<X,Y>;

    template<class... Args>
    using let = typename curry<Pair::value,1,Args...>::value;

};

struct Fst{

    template<class P>
    using value = typename P::template let<True>;

    template<class... Args>
    using let = typename curry<Fst::value,1,Args...>::value;

};

struct Snd{

    template<class P>
    using value = typename P::template let<False>;

    template<class... Args>
    using let = typename curry<Snd::value,1,Args...>::value;

};

template<int k>
struct Rep{

    template<class T, class U>
    using value = typename T::template let<typename Rep<k-1>::template let<T>::template let<U>>;

    template<class... Args>
    using let = typename curry<Rep<k>::value,2,Args...>::value;

};

template<>
struct Rep<0>{

    template<class T, class U>
    using value = U;

    template<class... Args>
    using let = typename curry<Rep<0>::value,2,Args...>::value;

};

template<class... Args>
struct Tuple{};

template<class R, class S, class... Args>
struct Tuple<R,S,Args...>{

    static const int size = length<R,S,Args...>::value;

    template<class F>
    using value = typename Pair<R,typename Pair<R,S>::template let<F>>::template let<F>;

    template<class... Args2>
    using let = typename curry<Tuple<R,S,Args...>::value,1,Args2...>::value;

};

template<class R, class S, class T, class... Args>
struct Tuple<R,S,T,Args...>{

    static const int size = length<R,S,T,Args...>::value;

    template<class F>
    using value = typename Pair<R,typename Tuple<S,T,Args...>::template let<F>>::template let<F>;

    template<class... Args2>
    using let = typename curry<Tuple<R,S,T,Args...>::value,1,Args2...>::value;

};

template<int k>
struct Proy{

    template<class P>
    using value = typename Bool<k==P::size>::template let<typename Rep<k-1>::template value<Snd,P>>::template let<typename Fst::template value<typename Rep<k-1>::template value<Snd,P>>>;

    template<class... Args>
    using let = typename curry<Proy<k>::value,1,Args...>::value;

};

template<>
struct Proy<1>{

    template<class P>
    using value = Fst::let<P>;

    template<class... Args>
    using let = typename curry<Proy<1>::value,1,Args...>::value;

};

template<class F, int n>
struct Curry{

    template<class... Args>
    using value = typename F::template let<Tuple<Args...>>;

    template<class... Args>
    using let = typename curry<Proy<1>::value,n,Args...>::value;

};

template<class F, class P, int i, int n>
struct UncurryAux{

    using value = typename UncurryAux<typename F::template let<typename Proy<i>::template let<P>>,P,i+1,n>::value;

};

template<class F, class P, int n>
struct UncurryAux<F,P,n,n>{

    using value = typename F::template let<typename Proy<n>::template let<P>>;

};

template<class F, int n>
struct Uncurry{

    template<class P>
    using value = typename UncurryAux<F,P,1,n>::value;

};


#endif // TUPLE_H_INCLUDED

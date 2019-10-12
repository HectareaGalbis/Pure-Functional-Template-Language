#ifndef COND_H_INCLUDED
#define COND_H_INCLUDED



struct IfThenElse{};

template<class P, class Q, class R, class... Args>
struct solve<IfThenElse,P,Q,R,Args...>{

    template<int k>
    using value = typename solve<P,Q,R,Args...>::template value<k>;

};




#endif // COND_H_INCLUDED

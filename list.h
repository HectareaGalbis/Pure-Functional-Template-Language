#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


namespace pftl{


struct List_t : public Container{};


template<class L, class M>
struct List_concat{};


template<class L, class f>
struct List_filter{};


template<class... XS>
struct List : public List_t{

    static const bool null = true;

    static const size_t length = 0;

    template<class L>
    using concat = typename List_concat<List<>,L>::value;

    template<class f>
    using map = List<>;

    using reverse = List<>;

    template<class f>
    using filter = List<>;

};


template<class X, class... XS>
struct List<X,XS...> : public List_t{

    static const bool null = false;

    static const size_t length = 1+List<XS...>::length;

    template<class L>
    using concat = typename List_concat<List<X,XS...>,L>::value;

    template<class f>
    using map = typename List<typename f::template let<X>>::template concat<typename List<XS...>::template map<f>>;

    using reverse = typename List<XS...>::reverse::template concat<List<X>>;

    template<class f>
    using filter = typename List_filter<List<X,XS...>,f>::value;

};


template<class... XLS, class... XMS>
struct List_concat<List<XLS...>,List<XMS...>>{
    using value = List<XLS...,XMS...>;
};


template<bool isFiltered, class L, class f>
struct List_filterAux{};

template<class X, class... XS, class f>
struct List_filterAux<true,List<X,XS...>,f>{
    using value = typename List<XS...>::template filter<f>;
};

template<class X, class... XS, class f>
struct List_filterAux<false,List<X,XS...>,f>{
    using value = typename List<X>::template concat<typename List<XS...>::template filter<f>>;
};

template<class f, class X, class... XS>
struct List_filter<List<X,XS...>,f>{
    using value = typename List_filterAux<f::template let<X>,List<X,XS...>,f>::value;
};


}



#endif // LIST_H_INCLUDED

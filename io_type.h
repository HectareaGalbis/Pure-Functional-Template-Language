#ifndef IO_TYPE_H_INCLUDED
#define IO_TYPE_H_INCLUDED

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

template<class Ret>
struct IO_t{

    static Ret exe(){};

};

//--------------------------------------------------------------------------------

template<auto x>
struct Return : IO_t<decltype(x)>{
    static constexpr decltype(x) exe(){
        return x;
    }
};

//--------------------------------------------------------------------------------

template<auto f>
struct Currying_f{};

template<class Ret, class... Args, Ret (*f)(Args...)>
struct Currying_f<f> : Currying<Currying_f<f>,IO_t<Ret>(IO_t<Args>...)>{
    template<class... IOArgs>
    struct value : IO_t<Ret>{
        static constexpr Ret exe(){
            return f(IOArgs::exe()...);
        }
    };
};

template<class Ret, Ret (*f)()>
struct Currying_f<f> : IO_t<Ret>{
    static constexpr Ret exe(){
        return f();
    }
};

template<void (*f)()>
struct Currying_f<f> : IO_t<void>{
    static constexpr void exe(){
        f();
    }
};

//--------------------------------------------------------------------------------
//********************************************************************************

}

namespace std{

    template<class T>
    struct is_base_of<pftl::IO_t<pftl::Auto>,pftl::IO_t<T>>{
        static constexpr bool value = true;
    };

}

#endif // IO_TYPE_H_INCLUDED

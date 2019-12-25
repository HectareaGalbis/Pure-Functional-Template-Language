#ifndef PFTLIO_H_INCLUDED
#define PFTLIO_H_INCLUDED

#include "curry.h"
#include "char_type.h"
#include "list_type.h"
#include "io_type.h"

namespace pftl{

//********************************************************************************
//--------------------------------------------------------------------------------

struct putChar : public Currying<putChar,IO_t<void>(Char_t)>{
    template<class C>
    struct value : public IO_t<void>{
        static void exe(){
            printf("%c",toNonType<C>);
        }
    };
};


struct getChar : public IO_t<char>{
    static char exe(){
        char c;
        scanf("%c",&c);
        return c;
    }
};

struct putStr : public Currying<putStr,IO_t<void>(List_t<Char_t>)>{
    template<class L>
    struct value : public IO_t<void>{
        static void exe(){
            printf("%s",fromString<L>);
            //map::let<putChar>::let<L>::exe();
        }
    };
};

struct putStrLn : public Currying<putStrLn,IO_t<void>(List_t<Char_t>)>{
    template<class L>
    struct value : public IO_t<void>{
        static void exe(){
            printf("%s",fromString<typename concat::let<L>::template let<List<Char<'\n'>>>>);
            //map::let<putChar>::let<typename concat::let<L>::template let<List<Char<'\n'>>>>::exe();
        }
    };
};

using print = comp<putStrLn,show>;

//--------------------------------------------------------------------------------
//********************************************************************************

}

#endif // PFTLIO_H_INCLUDED

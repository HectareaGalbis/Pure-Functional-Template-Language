#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED


#include "curry.h"

namespace pftl{


struct IO{

    static void print(){};

};


struct print : Currying<print,Type(IO)>{
    template<class P>
    struct value{
        static void exe(){
            P::print();
        }
    };
};



}


#endif // IO_H_INCLUDED

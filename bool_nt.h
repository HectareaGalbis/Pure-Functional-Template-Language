#ifndef BOOL_NT_H_INCLUDED
#define BOOL_NT_H_INCLUDED


namespace pftl{


struct not_logic_nt : public Currying<not_logic_nt,bool(bool)>{
    template<bool p>
    static const bool value = !p;
};


struct and_logic_nt : public Currying<and_logic_nt,bool(bool,bool)>{
    template<bool p, bool q>
    static const bool value = p && q;
};


struct or_logic_nt : public Currying<or_logic_nt,bool(bool,bool)>{
    template<bool p, bool q>
    static const bool value = p || q;
};


}



#endif // BOOL_NT_H_INCLUDED

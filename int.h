#ifndef INT_H_INCLUDED
#define INT_H_INCLUDED

#include "curry.h"
#include "integral_nt.h"
#include "integral.h"

namespace pftl{


struct Int_t : public Integral_t{};

//********************************************************************************
//--------------------------------------------------------------------------------
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//--------------------------------------------------------------------------------
//********************************************************************************

template<class I, class J>
struct eq_Int{};

template<class I, class J>
struct le_Int{};

template<class I, class J>
struct plus_Int{};

template<class I, class J>
struct minus_Int{};

template<class I, class J>
struct mult_Int{};

template<class I, class J>
struct div_Int{};

template<class I, class J>
struct mod_Int{};

template<class I, class J>
struct and_bit_Int{};

template<class I, class J>
struct or_bit_Int{};

template<class I, class J>
struct xor_bit_Int{};

template<class I, class J>
struct shift_left_Int{};

template<class I, class J>
struct shift_right_Int{};

template<class I, class J>
struct mcd_Int{};

template<class I, class J>
struct mcm_Int{};

//--------------------------------------------------------------------------------

template<int x>
struct Int : public Int_t{

    template<class I>
    using eq = typename eq_Int<Int<x>,I>::value;

    template<class I>
    using le = typename le_Int<Int<x>,I>::value;

    template<class I>
    using plus = typename plus_Int<Int<x>,I>::value;

    template<class I>
    using minus = typename minus_Int<Int<x>,I>::value;

    template<class I>
    using mult = typename mult_Int<Int<x>,I>::value;

    template<class I>
    using div = typename div_Int<Int<x>,I>::value;

    template<class I>
    using mod = typename mod_Int<Int<x>,I>::value;

    using suc = Int<x+1>;

    using pre = Int<x-1>;

    using not_bit = Int<~x>;

    template<class I>
    using and_bit = typename and_bit_Int<Int<x>,I>::value;

    template<class I>
    using or_bit = typename or_bit_Int<Int<x>,I>::value;

    template<class I>
    using xor_bit = typename xor_bit_Int<Int<x>,I>::value;

    template<class I>
    using shift_left = typename shift_left_Int<Int<x>,I>::value;

    template<class I>
    using shift_right = typename shift_right_Int<Int<x>,I>::value;

    template<class I>
    using mcd = typename mcd_Int<Int<x>,I>::value;

    template<class I>
    using mcm = typename mcm_Int<Int<x>,I>::value;

    using signum = Int<signum_nt::let<x>>;

    using abs = Int<abs_nt::let<x>>;

    using sqrt = Int<sqrt_nt::let<x>>;

};

//--------------------------------------------------------------------------------

template<int k, int l>
struct eq_Int<Int<k>,Int<l>>{
    using value = Bool<k==l>;
};

template<int k, int l>
struct le_Int<Int<k>,Int<l>>{
    using value = Bool<k<=l>;
};

template<int k, int l>
struct plus_Int<Int<k>,Int<l>>{
    using value = Int<k+l>;
};

template<int k, int l>
struct minus_Int<Int<k>,Int<l>>{
    using value = Int<k-l>;
};

template<int k, int l>
struct mult_Int<Int<k>,Int<l>>{
    using value = Int<k*l>;
};

template<int k, int l>
struct div_Int<Int<k>,Int<l>>{
    using value = Int<k/l>;
};

template<int k, int l>
struct mod_Int<Int<k>,Int<l>>{
    using value = Int<k%l>;
};

template<int k, int l>
struct and_bit_Int<Int<k>,Int<l>>{
    using value = Int<k&l>;
};

template<int k, int l>
struct or_bit_Int<Int<k>,Int<l>>{
    using value = Int<k|l>;
};

template<int k, int l>
struct xor_bit_Int<Int<k>,Int<l>>{
    using value = Int<k^l>;
};

template<int k, int l>
struct shift_left_Int<Int<k>,Int<l>>{
    using value = Int<(k<<l)>;
};

template<int k, int l>
struct shift_right_Int<Int<k>,Int<l>>{
    using value = Int<(k>>l)>;
};

template<int k, int l>
struct mcd_Int<Int<k>,Int<l>>{
    using value = Int<mcd_nt::let<k>::template let<l>>;
};

template<int k, int l>
struct mcm_Int<Int<k>,Int<l>>{
    using value = Int<mcm_nt::let<k>::template let<l>>;
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<int x>
struct toTypeAux<x>{
    using value = Int<x>;
};

template<int x>
struct toNonTypeAux<Int<x>>{
    static const int value = x;
};

}



#endif // INT_H_INCLUDED

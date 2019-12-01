#ifndef SHOW_H_INCLUDED
#define SHOW_H_INCLUDED


namespace pftl{


struct Show{

    using show = Undefined;

};


struct show : public Currying<show,Type(Show)>{
    template<class S>
    using value = typename S::show;
};


}


#endif // SHOW_H_INCLUDED

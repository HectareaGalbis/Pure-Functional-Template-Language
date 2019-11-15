
# Pure Functional Template Language

Esta librería intenta acercarse a lenguajes funcionales puros mediante el uso de templates.

## Empezando

La librería consta de ficheros header (.h), por tanto lo único necesario es importarlas a tu proyecto.

### Requisitos

Se requiere como mínimo C++14.


## Funciones

En los lenguajes funcionales puros el elemento más importante es la función, por lo que vamos a empezar por aquí. Quien haya indagado en C++ tarde o temprano se encuentra con las meta-funciones:

```cpp
template<class X, class Y>
struct myFunction{
    using type = //...
}
```

Sin embargo son un poco engorrosas de manejar, sobre todo si queremos recibir otras funciones como parámetros e incluso retornarlas. Por esto propongo lo que he denominado (supongo que ya tendrán un nombre, pero no he encontrado nada por internet) 'meta-funciones perezosas':

```cpp
struct myFunction{
    template<class X, class Y>
    using type = //...
}
```

Ahora los parámetros se pasan tarde. ¿Qué consecuencias tiene esto? Nuestra función va a ser la clase myFunction, es decir, las funciones serán clases. Además podemos pasar como parámetros otras clases, es decir, otras funciones. Y como type es un alias de otra clase significa que estamos retornando otra función (o un tipo de dato como int).

### Ejemplo

```cpp

struct Sucesor{             // <-- Función que recibe un entero devuelve su sucesor.
    template<int k>     
    static const int value = k+1;
}

struct Cuadrado{            // <-- Función que recibe un entero y devuelve su cuadrado.
    template<int k>
    static const int value = k*k;   
}


struct Comp{                // <-- Función que recibe dos funciones y un entero resultado de F(G(k)).
    template<class F, class G, int k>
    static const int value = F::template value<G::template value<k>>;
}

int main(){

    std::cout << Comp::value<Cuandrado,Sucesor,5> << std::endl;

}

```

```
Output: 
36
```

Primero se ejecuta Sucesor::value<5> = 6, y despues se ejecuta Cuadrado::value<6> = 36.

## Funciones curryficadas

Se dice que una función está curryficada cuando puede tomar sus parámetros de uno en uno. Esto significa que al tomar un parámetro, nuestra función devuelve otra función que recibe un parámetro menos. 

### Ejemplo

```cpp

struct Max{         // <-- Funcion curryficada que devuelve el máximo de dos enteros.
    template<int m>
    struct let{
        template<int n>
        using let = m > n ? m : n;
    }
}

using Max5 = Max::let<5>;   // <-- Pasando un parámetro a Max, recibimos una nueva función.

int main(){

    static const n = 7;
    static const k = 3;

    std::cout << "El máximo entre 5 y " << n << " es: " << Max5::let<n> << std::endl;
    std::cout << "El máximo entre 5 y " << k << " es: " << Max5::let<k> << std::endl;

}

```
 
```
Output:
El máximo entre 5 y 7 es: 7
El máximo entre 5 y 3 es: 5
```

> Cuando alguien maneja meta-funciones suele usar variables como value o type para retornar los valores. Yo voy a utilizar siempre la palabra 'let' para las funcionas curryficadas, como ya se ha visto en el ejemplo anterior.

## Curryficación de funciones no curryficadas.

La función Max anterior recibía dos parámetros pero, ¿y si queremos una función curryficada con 5 parámetros? Uno ya puede ver que tendríamos unos cuantos structs anidados. 

```cpp

struct MegaFunc{
    template<class Var1>
    struct let{
        template<class Var2>
        struct let{
            template<class Var3>
            struct let{
                template<class Var4>
                struct let{
                    template<class Var5>
                    using let = //...
                }
            }
        }
    }
}

```

Esto no es viable (y duele verlo). En el fichero 'curry.h' se encuentra la clase Curryfication, que nos permite curryficar una función no curryficada, pasándole como parámetros la función no curryficada y una descripción de la función. Con un ejemplo se verá más claro.

```cpp

struct MegaFuncUncurry{                           // <-- Función no curryficada
    template<class Var1, class Var2, class Var2, class Var3, class Var4, class Var5>
    using value = //...                           // <-- Es necesario que la palabra sea 'value'.
}
             Función no curryficada         Descripción de la función
             ----------------------vvvvvv   -----------------vvvvvv
using MegaFunc = Curryfication<MegaFuncUncurry,Type(Type,Type,Type,Type,Type)>;

```

**Type** es una clase de uso especial para Curryfication. Sirve para indicar que el tipo de parámetro o de retorno es una clase. En este caso MegaFunc es una función que recibe 5 clases y devuelve una clase. Veamos otro ejemplo en el que curryficamos la función std::conditional.

```cpp

struct CondUncurry{
    template<bool b,class X, class Y>
    using value = typename std::conditional<b,X,Y>::type;
}

using Cond = Curryfication<CondUncurry,Type(bool,Type,Type)>;

```

En este caso la función 'Cond' recibe un booleano, dos clases y, devuelve otra clase. 

```cpp

int main(){

    Cond::let<true>::let<int>::let<float> varInt = 3.5;
    Cond::let<false>::let<int>::let<float> varFloat = 3.5;
    
    std::cout << "varInt tiene valor: " << varInt << std::endl;
    std::cout << "varFloat tiene valor: " << varFloat << std::endl;

}

```

```
Output:
varInt tiene valor: 3
varFloat tiene valor: 3.5
```

Aunque no es *Curry* todo lo que reluce :D . Curryfication tiene algunas limitaciones impuestas por cómo funcionan los templates de C++: Una función no curryficada debe tener los **parámetros non-type a la izquierda** y **los parámetros type a la derecha**. Pero que no cunda el pánico, podemos arreglar esto en la descripción de la función que le pasamos a Currification.

```cpp

struct myFunctionUncurry{                       // <-- No podremos curryficar la función.
    template<class X, int k, class Y, int l>    
    static const bool value = //...
}

//Compilará, pero no podremos llegar a pasarle todos los parámetros.
using myFunction = Currification<myFunctionUncurry,bool(Type,int,Type,int)>;    

```

```cpp

struct myFunctionUncurry{                       // <-- Sí podremos curryficar la función.
    template<int k, int l, class X, class Y>    // <-- Non-type (int k, int l) están en la izquierda y 
    static const bool value = //...             //     types (class X, class Y) están a la derecha.
}

//En la descripción ordenamos los parámetros como queramos.
using myFunction = Currification<myFunctionUncurry,bool(Type,int,Type,int)>;  // <-- Correcto, leerá en este orden: (X,k,Y,l).

```



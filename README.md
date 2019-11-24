
# Pure Functional Template Language

Los [templates](https://en.wikipedia.org/wiki/Template_(C%2B%2B)) son una herramienta bastante útil en C++ que nos permiten hacer cálculos en tiempo de compilación. Se usan principalmente para aritmética de tipos, [Perfect Forwarding](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c), y clases genéricas aprovechando el [SFINAE](https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error), que no es poco. Sin embargo, la algoritmia que un programador medio utilizaría en la aritmética de tipos no es compleja (porque lo complejo es usar los templates) y, crear nuevas [metafunciones](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Metafunction) rara vez se plantea. Con este proyecto intento buscar una metodología para crear nuevas metafunciones de manera más sencilla y una librería que permita realizar cálculos en tiempo de compilación más complejos.

## Situación actual

* Método para curryficar metafunciones (curry.h).
* Funciones básicas para cálculo booleano (bool.h).
* Funciones básicas para cálculo numérico (numeric.h).

## ¿Qué busco ahora?

* Cómo definir clases.
* Cómo definir métodos en las clases.
* Cómo crear funciones "polimórficas".
* Clase Ratio (Números racionales).
* Clase List (Listas de elementos de tipo integral (int,char,enum,...).
* Clase Tuple (Listas de tipos de datos o clases).
* Clase Int (Integral) (Encapsulación de elementos de tipo integral en un tipo de dato para usarlos en tuplas).

## Instalación y requisitos

* La librería consta de ficheros header (.h), por tanto lo único necesario es importarlas a tu proyecto. Todos los elementos de la librería están bajo el namespace pftl. 
* Se requiere como mínimo C++14.

## Empezando

A partir de ahora voy a ir explicando los elementos principales que he definiendo y veremos las principales clases y funciones que nos permitirán realizar cálculos medianamente complejos en tiempo de compilación. Todo el trabajo está inspirado en Haskell y en los lenguajes funcionales puros, por lo que la curryficación de funciones será el núcleo del proyecto.

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

struct sucesor{             // <-- Función que recibe un entero devuelve su sucesor.
    template<int k>     
    static const int value = k+1;
}

struct cuadrado{            // <-- Función que recibe un entero y devuelve su cuadrado.
    template<int k>
    static const int value = k*k;   
}


struct comp{                // <-- Función que recibe dos funciones y un entero y devuelve F(G(k)).
    template<class F, class G, int k>
    static const int value = F::template value<G::template value<k>>;
}

int main(){

    std::cout << comp::value<cuandrado,sucesor,5> << std::endl;

}

```

```
Output: 
36
```

Primero se ejecuta sucesor::value<5> = 6, y despues se ejecuta cuadrado::value<6> = 36.

## Funciones curryficadas

Se dice que una función está curryficada cuando puede tomar sus parámetros de uno en uno. Esto significa que al tomar un parámetro, nuestra función devuelve otra función que recibe un parámetro menos. 

### Ejemplo

```cpp

struct max{         // <-- Funcion curryficada que devuelve el máximo de dos enteros.
    template<int m>
    struct let{
        template<int n>
        using let = m > n ? m : n;
    }
}

using max5 = max::let<5>;   // <-- Pasando un parámetro a Max, recibimos una nueva función.

int main(){

    static const n = 7;
    static const k = 3;

    std::cout << "El máximo entre 5 y " << n << " es: " << max5::let<n> << std::endl;
    std::cout << "El máximo entre 5 y " << k << " es: " << max5::let<k> << std::endl;

}

```
 
```
Output:
El máximo entre 5 y 7 es: 7
El máximo entre 5 y 3 es: 5
```

> Cuando alguien maneja meta-funciones suele usar variables como value o type para retornar los valores. Yo voy a utilizar siempre la palabra 'let' para las funcionas curryficadas, como ya se ha visto en el ejemplo anterior.

## Curryficación de funciones no curryficadas

La función max anterior recibía dos parámetros pero, ¿y si queremos una función curryficada con 5 parámetros? Uno ya puede ver que tendríamos unos cuantos structs anidados. 

```cpp

struct megaFunc{
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

Esto no es viable (y duele verlo). En el fichero 'curry.h' se encuentra la clase Currying, que nos permite curryficar una función no curryficada, pasándole como parámetros la función no curryficada y una descripción de la función. Con un ejemplo se verá más claro.

```cpp
           //Función no curryficada           Descripción de la función
           //----------------------vvvvvv           vvvvvvvvvvvvv
struct megaFunc : public Currying<megaFunc,Type(Type,Type,Type,Type,Type)>{

    template<class Var1, class Var2, class Var2, class Var3, class Var4, class Var5>
    using value = //...         // <-- Es necesario que la palabra sea 'value'.
    
}
```

**Type** es una clase de uso especial para Currying. Sirve para indicar que el tipo de parámetro o de retorno es una clase. En este caso megaFunc es una función que recibe 5 clases y devuelve una clase. Veamos otro ejemplo en el que curryficamos la función std::conditional.

```cpp
struct cond : public Currying<cond,Type(bool,Type,Type)>{
    template<bool b,class X, class Y>
    using value = typename std::conditional<b,X,Y>::type;
}
```

En este caso la función 'cond' recibe un booleano, dos clases y, devuelve otra clase. 

```cpp

int main(){

    cond::let<true>::let<int>::let<float> varInt = 3.5;
    cond::let<false>::let<int>::let<float> varFloat = 3.5;
    
    std::cout << "varInt tiene valor: " << varInt << std::endl;
    std::cout << "varFloat tiene valor: " << varFloat << std::endl;

}

```

```
Output:
varInt tiene valor: 3
varFloat tiene valor: 3.5
```

Aunque no es *Curry* todo lo que reluce :D . Currying tiene algunas limitaciones impuestas por cómo funcionan los templates de C++: Una función no curryficada debe tener los **parámetros non-type a la izquierda** y **los parámetros type a la derecha**. Pero que no cunda el pánico, podemos arreglar esto en la descripción de la función que le pasamos a Currying.

```cpp

struct myFunction : public Currying<myFunction,bool(Type,int,Type,int)>{         
    template<class X, int k, class Y, int l>                    // <-- No podremos curryficar la función.
    static const bool value = //...                             // Existe type (class X) a la izquierda de non-type (int k).
}

//Compilará, pero no podremos llegar a pasarle todos los parámetros.

```

```cpp

//En la descripción ordenamos los parámetros como queramos.
                    ----------------------------------vvvvvvvvvvv
struct myFunction : public Currying<myFunction,bool(Type,int,Type,int)>{            // <-- Sí podremos curryficar la función.
    template<int k, int l, class X, class Y>    // <-- Non-type (int k, int l) están en la izquierda y 
    static const bool value = //...             //     types (class X, class Y) están a la derecha.
}

//En este caso se leerán los argumentos en el siguiente orden: X , k , Y , l .

```

## Definición de nuevas funciones

Hemos comenzado viendo que podemos curryficar funciones con struct let anidados o con la clase Currying. Entonces, ¿cuál debo usar? Literalmente, la que quieras, la que te sea más cómoda. Si no te decides, puedes seguir el siguiente procedimiento:

```cpp

// ¿Se puede obtener a partir de otra función?
using myFunctionDerived = myFunctionBase::let<Something>;


// ¿Sólo recibe un parámetro?  (¡¡¡Ojo!!!! -> No recomendada por motivos que se explicarán en apartados siguientes)
struct myFunction{              // <-- Ya está curryficada.
    template<class X>       
    using let = //...
}


// ¿Recibe más de un parámetro?
struct myFunction : public Currying<myFunction,bool(Type,char,int,Type)>;{
    template<char c, int k, class X, class Y>
    static const bool value = //...
}

```

## Meta-funciones auxiliares

En muchos casos nos encontraremos con la necesidad de crear funciones recursivas o simplemente necesitaremos utilizar especializaciones de templates para conseguir unos resultados deseados. 

> La especialización de templates recuerda bastante al encaje de patrones utilizado en lenguajes como Haskell.

Vamos a definir la función fibo, que dado un entero n, nos devuelva el número que ocupa la posición n en la sucesión de Fibonacci. Un primer intento podría ser el siguiente:

```cpp

struct fibo : public Currying<fibo,int(int)>{

    template<int n>
    static const int value = n==0 ? 0 : (n==1 ? 1 : fibo::let<n-2>+fibo::let<n-1>);

}

```

Si n es 0, retornamos 0. Si n es 1, retornamos 1. Y si n es otro número, retornamos la suma de los dos elementos anteriores de la sucesión de Fibonacci. Pero esto no compila. El error que se obtiene indica que estamos intentando usar un tipo de dato incompleto, en este caso fibo. Esto se puede entender como que al instanciar la clase fibo para un n en concreto también se instanciará para n-1 y n-2. En ningún momento estamos indicando que fibo<0> debe dejar de instanciarse, por lo que se seguirá instanciando fibo para los números negativos y así seguirá sin fin. Para evitar esto debemos usar meta-funciones auxiliares:

```cpp

template<int n>
struct fiboAux{                 // <-- Función general recursiva
    static const int value = FiboAux<n-2>::value + FiboAux<n-1>::value;
};

template<>
struct fiboAux<0>{              // <-- Especialización para n==0
    static const int value = 0;
};

template<>
struct fiboAux<1>{              // <-- Especialización para n==1
    static const int value = 1;
};

struct fibo : public Currying<fibo,int(int)>{
    template<int n>
    static const int value = fiboAux<n>::value;       // <-- Llamada a la meta-función auxiliar
};


int main(){

    std::cout << fibo::let<10> << std::endl;

    return 0;
}

```

```
Output:
55
```

## La librería 'bool.h'.

Esta librería contiene un conjunto de funciones básicas (not, and, or) para el manejo de valores booleanos. Como ya existen las palabras reservadas not, and y or en C++ se usan not_logic, and_logic y or_logic.

> A primera vista pueden parecer funciones prescindibles, pues ya tenemos símbolos que nos da C++ para estas operaciones. Sin embargo éstas serán útiles cuando veamos la clase List.

```cpp

static const bool var1 = true;
static const bool var2 = false;

int main(){

    if constexpr (and_logic::let<var1>::let<var2>){                 // <-- Ejemplo muy tonto, ya que podemos usar 'var1 && var2'.
        std::cout << "Las dos variables valen true." << std::endl;
    }
    else {
        std::cout << "Alguna variable vale false." << std::endl;
    }
    
    return 0;

}

```

```
Output:
Alguna variable vale false.
```

> La expresión 'if constexpr' comprueba valores booleanos en tiempo de compilación, por lo que funciona muy bien con las metafunciones. En este caso, la función main anterior se deduce directamente a: int main() { std::cout << "Alguna variable vale false." << std::endl; return 0;}

## La librería 'numeric.h'.

La librería 'numeric' ofrece las operaciones básica de cálculo numérico con tipos de dato integral (int,char,...). Al igual que con los booleanos estas funciones son reproducibles con símbolos que nos ofrece C++, pero serán utiles para las listas. Las operaciones básicas más importantes que ofrece esta librería son:

| 'numeric.h' | C++ |
| :-----------: | :-----------: |
| `plus` | + |
| `minus` | - |
| `mult` | * |
| `div` | / |
| `mod` | % |
| `equal` | == |
| `less` | < |
| `greater` | > |
| `lessEqual` | <= |
| `greaterEqual` | >= |
| `and_bit` | & |
| `or_bit` | \| |
| `not_bit` | ~ |
| `shift_left` | << |
| `shift_right` | >> |
| mcm | |
| mcd | |
| signum | |
| abs | |
| isqrt | |













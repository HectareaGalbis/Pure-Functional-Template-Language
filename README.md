
# Pure Functional Template Language

Los [templates](https://en.wikipedia.org/wiki/Template_(C%2B%2B)) son una herramienta bastante útil en C++ que nos permiten hacer cálculos en tiempo de compilación. Se usan principalmente para aritmética de tipos, [Perfect Forwarding](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c), y clases genéricas aprovechando el [SFINAE](https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error), que no es poco. Sin embargo, la algoritmia que un programador medio utilizaría en la aritmética de tipos no es compleja (porque lo complejo es usar los templates) y, crear nuevas [metafunciones](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Metafunction) rara vez se plantea. Con este proyecto intento buscar una metodología para crear nuevas metafunciones de manera más sencilla y una librería que permita realizar cálculos en tiempo de compilación más complejos.

## Situación actual

* Método para curryficar metafunciones (curry.h).
* Funciones básicas para cálculo booleano (bool_nt.h).
* Funciones básicas para cálculo numérico (integral_nt.h).
* Clase Vector para manejar un número variable de datos 'Non-Type'.
* Métodos 'especiales' para el paso de 'non-type' a 'type' y viceversa.
* Tipo de dato List para manejar un número variable de datos 'Type'.
* Tipo de dato Int para manejar enteros.
* Tipo de dato Bool para manejar booleanos.
* Tipo de dato Char para manejar caracteres.
* Clases Show, Eq, Ord, Num, Integral, Enum...
* Tipo de dato IO para el paso de cálculo en compilación a cálculo secuencial (incluida E/S).

## ¿Qué busco ahora?

* Una forma de unir el cálculo en compilación con el cálculo en ejecución (método exe).
* Una metodología para maximizar el cálculo en compilación y calcular lo justo y necesario en ejecución.
* Mejorar la idea de tener 3 tipos principales de clases (clases puras, clases semipuras (puras con exe), clases impuras (una clase normal de C++))
* Definición de parámetros de un programa (E/S), e hiperparámetros (parámetros precompilación, usados para generación de código).

## Instalación y requisitos

* La librería consta de ficheros header (.h), por tanto lo único necesario es importarlas a tu proyecto. Todos los elementos de la librería están bajo el namespace pftl. 
* Se requiere como mínimo C++17.

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



## La librería Non-Type.

C++ hace una distinción muy clara entre los parámetros 'non-type' y 'type', lo que hace que este proyecto haga lo mismo. En primer lugar tendremos un conjunto de funciones para el manejo de datos 'non-type' y por otro lado una librería para manejar datos Type con un funcionamiento parecido a Haskell. Por la parte 'non_type' encontramos los ficheros 

## La librería 'bool.h'.

Esta librería contiene un conjunto de funciones básicas (not, and, or) para el manejo de valores booleanos. Como ya existen las palabras reservadas not, and y or en C++ se usan not_logic, and_logic y or_logic.

| 'bool.h' | C++ |
| :-----------: | :-----------: |
| `not_logic` | ! |
| `and_logic` | && |
| `or_logic` | \|\| |

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

La librería 'numeric' ofrece las operaciones básicas de cálculo numérico con tipos de dato integral (int,char,...). Al igual que con los booleanos estas funciones son reproducibles con símbolos que nos ofrece C++, pero serán utiles para las listas. Las operaciones básicas más importantes que ofrece esta librería son:

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
| `mcm` | Mínimo común múltiplo |
| `mcd` | Máximo común divisor |
| `signum` | Signo de un número |
| `abs` | Valor absoluto |
| `isqrt` | Raíz cuadrada |

```cpp

static const unsigned int var1 = 15;
static const unsigned int var2 = 28;

using esUno = equal::let<1>;

int main(){
    
    if constexpr (esUno::let<mcd::let<var1>::let<var2>>)
        std::cout << "Los numeros " << var1 << " y " << var2 << " son comprimos. :)" << std::endl;
    else
        std::cout << "Los numeros " << var1 << " y " << var2 << " no son comprimos. :(" << std::endl;

}

```

```
Output:
Los numeros 15 y 28 son coprimos. :)
```

## La clase Vector (vector.h)

Aún no hemos definido las clases, pero me parece más adecuado dejarlo para la parte 'type' que vendrá posteriormente. Esta clase nos permite almacenar un número variable de parámetros 'non-type' **del mismo tipo** y contiene algunas funciones para manejarlas.

```cpp
using miVector = Vector<4,-10,14,5,-4,12>;                                      // <-- Vector de enteros.
using miString = Vector<'H','e','l','l','o',',',' ','w','o','r','l','d','!'>;   // <-- Vector de caracteres.
```

> Vector permite usar cualquier tipo de parámetro 'non-type', pero todos los elementos tienen que ser del mismo tipo.

Algunas funciones básicas son las siguientes:

| Vector | Qué hace |
| :-----------: | :-----------: |
| `null` | Comprueba si un vector esta vacío o no |
| `length` | Devuelve la longitud de un vector |
| `concat` | Concatena dos vectores |
| `map` | Ejecuta una función para cada elemento del vector |
| `filter` | Elimina los elementos del vector que devuelven true tras aplicarles una función |
| `reverse` | Invierte el orden de los elementos del vector |

> Podemos forzar un error de compilación para comprobar los tipos de datos deducidos por estas funciones. Usare una clase vacía llamada Display.

```cpp
template<class S>
struct Display{};       // <-- Clase vacía que usaremos para forzar un error de compilación.

using helloWorld = Vector<'H','e','l','l','o',',',' ','w','o','r','l','d','!'>;

Display<helloWorld>::value;    // <-- Error forzado.

using esEle = equal::let<'l'>;                          // <-- Función que comprueba si un caracter es la letra 'l'.
using miVector = filter::let<esEle>::let<helloWorld>;   // <-- Elimina las letras 'l' del vector. 

Display<miVector>::value;   // <-- Error forzado.

int main(){
    return 0;
}

```
```
Errores de compilación:
'value' in 'struct Display<pftl::Vector<'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!'> >' does not name a type
'value' in 'struct Display<pftl::Vector<'H', 'e', 'o', ',', ' ', 'w', 'o', 'r', 'd', '!'> >' does not name a type
```

## Clases, instancias y métodos

A partir de ahora nos metemos en el terreno de los datos 'type'. Poco a poco iremos definiendo tipos de datos básicos que nos permitirán hacer cálculos como si de otro lenguaje de programación se tratara. Hay que pensar que esto no está nada relacionado con los tipos de dato 'non-type', aunque podremos pasar de un lado a otro con los tipos más básicos (int, char, bool,...).

### Clases e instancias

Una clase viene a representar un tipo de dato y para crear una instancia de dicha clase usaremos un constructor. En la práctica una clase será una estructura de C++. 

```cpp
struct Figura{};         // <-- Clase Figura
```

Y los constructores son estructuras template que son hijas de la clase.

```cpp
template<int radio>
struct Circulo : public Figura{};       // <-- Constructor de una Figura con un argumento.

template<int alto, int ancho>
struct Rectangulo : public Figura{};    // <-- Constructor de una Figura con dos argumentos.
```

Dados estos constructores podemos crear instancias.

```cpp
using miCirculo = Circulo<5>;           // <-- Instancia de una Figura.
```

> Seguiré una norma para distinguir funciones de clases. Las funciones empiezan por minúscula mientras que las clases empiezan por mayúscula.

### Métodos de una clase

Los métodos son metafunciones que definen las clases y que cada constructor debe implementar. De esta forma conseguiremos 'polimorfismo' con funciones que manejen estos tipos de datos.

```cpp
struct Figura{
    static const int area = 0;          // <-- Definición del método area que devolvera el area de una figura. 
};


template<int radio>
struct Circulo : public Figura{
    static const int area = 3*radio*radio;          // <-- Implementación del método area.
};       

template<int alto, int ancho>
struct Rectangulo : public Figura{
    static const int area = alto*ancho;             // <-- Implementación del método area.
};
```

Para terminar necesitamos crear una función que llame al método area, que por conveniencia la llamaré igual que el método.

```cpp
struct area : public Currying<area,int(Figura)>{        // <-- Función que recibe un argumento de tipo Figura!
    template<class F>
    static const int value = F::area;
};


const int r = 5;
using circulo = Circulo<r>;

const int ancho = 2;
const int alto = 3;
using rectangulo = Rectangulo<alto,ancho>;

int main(){

    std::cout << "El circulo de radio " << r << " tiene un area aproximada de " << area::let<circulo> << " unidades" << std::endl;
    std::cout << "El rectangulo de medidas " << alto << "x" << ancho << " tiene un area de " << area::let<rectangulo> << " unidades" << std::endl;

    return 0;

}
```
```
Output:
El circulo de radio 5 tiene un area aproximada de 75 unidades
El rectangulo de medidas 3x2 tiene un area de 6 unidades
```

## Un inciso sobre la clase Currying

Ya se explicó al inicio que la clase Currying nos facilita la curryficación de metafunciones. Pero esta clase ofrece alguna cosa más. Por un lado tenemos la restricción de tipos de datos que ya se ha visto en el ejemplo anterior con la clase Figura. Y por el otro tenemos la metainformación, esto es, información sobre la función como su tipo, el tipo de retorno o el tipo del siguiente argumento.

### Restricción de tipos de datos

Hemos visto que en la clase Currying podemos especificar varios tipos de datos como entrada y el tipo de retorno de una función. Para definir los **parámetros de entrada** tenemos las siguientes tres opciones:
* **Tipos de dato 'non-type'**: Para pasar valores literales de tipo int, char, bool, ...
* **Type**: Para pasar cualquier clase.
* **Una clase**: Para pasar únicamente clases que son derivadas de la clase indicada.

```cpp
//Función que recibe como argumentos una clase derivada de Figura, un booleano, y una clase cualquiera.
struct myFunc : public Currying<myFunc,int(Figura,bool,Type)>{
    template<bool b, class F, class T>
    static const int value = //...
};
```

**Ojo**: Esto sólo se aplica para los parámetros de entrada. Para el **tipo de retorno** sólo tenemos dos opciones:

* **Tipos de dato 'non-type'**: Para retornar valores literales de tipo int, char, bool, ...
* **Type**: Para retornar cualquier clase.

```cpp
struct myFunc : public Currying<myFunc,Type(int)>{      // <-- Correcto
    template<int k>
    static const int value = //...
};

struct myFunc : public Currying<myFunc,Figura(int)>{    // <-- Error
    template<int k>
    using value = //...
};
```

### Metainformación

La clase Currying nos permite obtener información sobre cualquier función que haya sido currificada. Existen tres miembros a los que podemos acceder a partir de una función:
* **type**: Devuelve el tipo de la función. (Con el formato usado al definir los parámetros y el tipo de retorno de la función)
* **type_ret**: Devuelve el tipo de retorno de la función.
* **type_arg**: Devuelve el tipo del siguiente argumento.

```cpp
struct myFunc : public Currying<myFunc,Type(Figura,int)>{
    template<int k, class F>
    using value = //...
};

using myFuncInt = myFunc::let<Circulo<3>>;
using TypeFunc = myFuncInt::type;               // <-- TypeFunc = Type(int)
using ReturnType = myFuncInt::type_ret;         // <-- ReturnType = Type
using ArgType = myFuncInt::type_arg;            // <-- ArgType = int
```


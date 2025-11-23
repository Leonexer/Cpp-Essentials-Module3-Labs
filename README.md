# Cpp-Essentials-Module3-Labs
# Laboratorio 3.0.8

## Objetivo General

- Comprender el funcionamiento del manejo de excepciones en C++ mediante el uso de `try`, `throw` y `catch`.
- Identificar condiciones que pueden generar errores en tiempo de ejecución, como la división entre cero.
- Implementar una solución que valide la entrada del usuario y evite operaciones no permitidas.
- Mostrar mensajes claros que permitan al usuario entender el tipo de error ocurrido.


---

## Código final (Parte 3)

A continuación se muestra el código correspondiente al **laboratorio 3.0.8**, donde se implementa una excepción específica para valores no válidos en la división a realizar.
```cpp
#include <iostream>

int main(void) {
    double num = 8;
    double den = 0;

    std::cin >> den;
    try {
        if (den == 0)
        {
            throw 1;
        }
        std::cout << num / den << std::endl;
    }
    catch (int ex)
    {
        if (ex == 1)
            std::cout << "Your input is not valid, you can't divide by zero." << std::endl;
    }

    return 0;
}
```
## Output esperado

A continuación se muestran ejemplos del comportamiento del programa según la entrada proporcionada por el usuario:
### Caso 1: Entrada válida
**Entrada:**
```
2
```
**Salida:** 
```
4
```
### Caso 2: División entre cero
**Entrada:**
```
0
```
**Salida:** 
```
Your input is not valid, you can't divide by zero
```
## Conclusión de Excepciones: validación de entrada
Este laboratorio demuestra cómo el manejo de excepciones en C++ permite controlar errores comunes como la división entre cero. Gracias al uso de `throw` y `catch`, el programa evita fallos en tiempo de ejecución y proporciona un mensaje claro al usuario. Con estas técnicas se mejora la robustez del código y se garantiza un comportamiento más seguro ante entradas inválidas.

# Laboratorio 3.0.9 Excepciones: Dividir entre cero

## Objetivos
- Aplicar excepciones personalizadas en C++ derivadas de `std::exception`.
- Comparar el uso de excepciones simples del laboratorio anterior con una clase de excepción propia.
- Prevenir errores comunes como la división entre cero mediante validación y manejo adecuado de errores.
- Mejorar la claridad y robustez del código implementando mensajes de error específicos.

---

## Código en C++
A continuación se muestra el código correspondiente al **laboratorio 3.0.9**, donde se implementa una clase llamada "DivideByZeroException", la cual utilizamos para lanzar la excepción donde pueda ocurrir.

```cpp
#include <iostream>

class DivideByZeroException : public std::exception {
public:
    static const char* what() 
    {
        return "Your input is not valid, you can't divide by zero.";
    }
};

int main() {
    double numerator;
    double denominator;

    std::cout << "Enter numerator: ";
    std::cin >> numerator;
    std::cout << "Enter denominator: ";
    std::cin >> denominator;

    try {
        if (denominator == 0) {
            throw DivideByZeroException();
        }
        std::cout << "Result: " << numerator / denominator << std::endl;
    }
    catch (const DivideByZeroException& exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}
 ```
## Output esperado

### Caso 1: Entrada válida
**Entrada:**
```
Enter numerator: 10
Enter denominator: 2
```
**Salida:**
```
Result: 5
```
### Caso 2: Entrada inválida
**Entrada:**
```
Enter numerator: 7
Enter denominator: 0
```
**Salida:**
```
Your input is not valid, you can't divide by zero.`
```

## Conclusión
Este laboratorio demuestra el uso de excepciones personalizadas para manejar errores específicos, como la división entre cero. A diferencia del laboratorio anterior, aquí se emplea una clase derivada de `std::exception`, lo que proporciona una estructura más profesional y escalable para el manejo de errores. Esta técnica mejora la claridad, robustez y mantenimiento del código.
# LAB 3.1.8 — Exceptions: Input Validation

## Objetivos
- Identificar situaciones donde es necesario lanzar excepciones para garantizar un comportamiento seguro del programa.  
- Implementar bloques `try-catch` que permitan manejar errores de forma controlada.  
- Sustituir valores booleanos y parámetros de salida por excepciones estructuradas.  
- Comparar dos enfoques distintos:  
  - Validar argumentos antes de realizar la operación.  
  - Delegar la validación a una función interna que lanza la excepción.  
- Fortalecer la comprensión del manejo de excepciones en C++ siguiendo la progresión de los laboratorios anteriores.

---

## Código en C++
```cpp
#include <iostream>

class DivideByZeroException : public std::exception {
public:
    const char* what()
    {
        return "Your input is not valid, you can't divide by zero.";
    }
};

float internaldiv(float arg1, float arg2) // Código base de Cisco
{
    if (0 == arg2)
        throw DivideByZeroException();
    return arg1 / arg2;
}

float divide(float num, float den)
{
    if (den == 0) // Valida los argumentos para la excepción
        throw DivideByZeroException();
    return num / den;
}

float divide2(float num, float den) {
    try
    {
        return internaldiv(num, den); // La excepción se valida dentro de la función interna
    }
    catch (const DivideByZeroException& ex)
    {
        throw ex; // Relanza la excepción hacia el main
    }
}

int main()
{
    double numerator;
    double denominator;

    std::cout << "Enter numerator: ";
    std::cin >> numerator;
    std::cout << "Enter denominator: ";
    std::cin >> denominator;

    try {
        float result = divide(numerator, denominator);
        std::cout << "Result (divide): " << result << std::endl;
    }
    catch (const DivideByZeroException& exc)
    {
        std::cout << exc.what() << std::endl;
    }

    try {
        float result = divide2(numerator, denominator);
        std::cout << "Result (divide2): " << result << std::endl;
    }
    catch (const DivideByZeroException& exc)
    {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}

```

## Output esperado

### Caso 1: Entrada válida
**Entrada:**
```
Enter numerator: 12
Enter denominator: 3
```
**Salida:**
```
Result (divide): 4
Result (divide2): 4
```
### Caso 2: Entrada inválida
**Entrada:**
```
Enter numerator: 10
Enter denominator: 0
```
**Salida:**
```
Your input is not valid, you can't divide by zero.
Your input is not valid, you can't divide by zero.
```

## Conclusión
Este laboratorio profundiza en el manejo estructurado de excepciones, comparando dos métodos comunes: validar argumentos antes de la operación y delegar la verificación a funciones internas. Ambos enfoques funcionan correctamente, pero la validación previa es más clara y directa, mientras que la validación interna permite encapsular la lógica y reutilizar funciones. Con esta práctica, se complementa lo aprendido en los laboratorios anteriores, desarrollando programas más robustos, seguros y fáciles de depurar mediante excepciones personalizadas.
# LAB 3.1.9 — Exceptions: Catch Block

## Objetivos
- Manejar excepciones utilizando bloques `try-catch` de manera adecuada.  
- Diseñar clases de excepciones personalizadas para comunicar errores al usuario.  
- Validar parámetros numéricos y lanzar excepciones cuando sus valores no sean válidos.  
- Aplicar lo aprendido en laboratorios previos sobre excepciones, ampliando el uso de atributos y mensajes específicos en los errores.  

---

## Código en C++
```cpp
#include <iostream>

using namespace std;

// Exception class
class NegativeValuesException : public std::exception {
public:
    const char* what()
    {
        return "Your input is not valid, this parameter does not allow negative values.";
    }
};

// Functions
float square_area(float side)
{
    if (side < 0) throw NegativeValuesException();
    return side * side;
}

float rectangle_area(float side, float height)
{
    if (side < 0 || height < 0) throw NegativeValuesException();
    return side * height;
}

int main(void) {
    float side, height;

    cin >> side;
    cin >> height;

    try
    {
        float rsquare = square_area(side);
        float rrectangle = rectangle_area(side, height);
        cout << rsquare << endl;
        cout << rrectangle << endl;
    }
    catch (std::exception &exc) {
        cout << exc.what() << endl;
    }
    
    return 0;
}
```

## Output esperado

### Caso 1: Entrada válida
**Entrada:**
```
4
6
```
**Salida:**
```
16
24
```
### Caso 2: Entrada inválida
**Entrada:**
```
-5
7
```
**Salida:**
```
Your input is not valid, this parameter does not allow negative values.
```
## Conclusión

En este laboratorio se reforzó el uso de excepciones personalizadas para manejar errores comunes en funciones matemáticas básicas. Validar que los parámetros sean mayores que cero previene resultados incorrectos y asegura que el programa sea más robusto. El bloque `try-catch` permite comunicar al usuario de manera clara cuándo un valor no es válido. Este enfoque, complementado con lo aprendido en los laboratorios anteriores, mejora significativamente la calidad del código y facilita su mantenimiento.

---

# 3.1.10 - 3.1.11 Exceptions: simple checks

## Objetivos
- Implementar manejo de excepciones en clases orientadas a operaciones matemáticas y validación de límites, retomando conceptos de laboratorios anteriores.  
- Lanzar excepciones al detectar condiciones inválidas, como matrices incompatibles, tamaños incorrectos o valores fuera de límites.  
- Crear clases personalizadas que representen estructuras matemáticas (matrices) y valores restringidos (LimitedValue).  
- Utilizar bloques `try-catch` para capturar errores y comunicar claramente el problema al usuario.  
- Reforzar la importancia de validar argumentos antes de ejecutar operaciones, fortaleciendo la robustez del programa.  

---

# Parte 1 — Clase Matrix con operaciones básicas y excepciones

## Código: Operaciones con matrices
```cpp
#include <iostream>
#include <vector>
#include <string>

class MatrixException {
private:
    std::string message;
public:
    MatrixException(const std::string& msg) : message(msg) {}
    const char* what() const { return message.c_str(); }
};

class Matrix {
private:
    std::vector<std::vector<float>> data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        if (r <= 0 || c <= 0)
            throw MatrixException("Matrix dimensions must be greater than zero.");
        data.resize(r, std::vector<float>(c, 0));
    }

    void fill(float value) {
        for (auto& row : data)
            for (auto& elem : row)
                elem = value;
    }

    void addValue(float value) {
        for (auto& row : data)
            for (auto& elem : row)
                elem += value;
    }

    Matrix addMatrix(const Matrix& other) {
        if (rows != other.rows || cols != other.cols)
            throw MatrixException("Matrices must have the same size to be added.");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    void print() const {
        for (const auto& row : data) {
            for (float elem : row)
                std::cout << elem << " ";
            std::cout << std::endl;
        }
    }
};

int main() {
    try {
        Matrix m1(2, 2);
        Matrix m2(2, 2);
        Matrix m3(3, 3);

        m1.fill(1);
        m2.fill(2);
        m3.fill(5);

        std::cout << "Adding m1 + m2 (valid):\n";
        Matrix res1 = m1.addMatrix(m2);
        res1.print();

        std::cout << "\nAdding m1 + m3 (invalid):\n";
        Matrix res2 = m1.addMatrix(m3); // Genera la excepción

    }
    catch (MatrixException& e) {
        std::cout << "Matrix error: " << e.what() << std::endl;
    }

    return 0;
}
```

## Output esperado

### Caso 1: Entrada válida
**Entrada:**
```
Adding m1 + m2 (valid):
3 3 
3 3
```
**Salida:**
```
Adding m1 + m3 (invalid):
Matrix error: Matrices must have the same size to be added.
```
### Caso 2: Entrada inválida
**Entrada:**
```
-5
7
```
**Salida:**
```
Your input is not valid, this parameter does not allow negative values.
```
## Conclusión
Los laboratorios 3.1.10 y 3.1.11 permiten integrar los conceptos fundamentales del manejo de excepciones en dos contextos distintos:
1. **Álgebra de matrices:** donde se validan dimensiones, datos vacíos e incompatibilidades antes de operar;
2. **Valores con límites:** donde se controla que los valores no excedan rangos definidos.
Ambos ejercicios refuerzan la importancia de lanzar excepciones cuando ocurre una condición inválida y manejar estos errores de manera clara para el usuario mediante clases personalizadas.  
Este enfoque mejora la robustez, claridad y mantenibilidad del código, alineándose con lo aprendido en laboratorios anteriores sobre validación, clases de excepciones y propagación de errores.

# Laboratorio 3.2.16 Excepciones: file checks

## Objetivos

# LAB 3.2.16 — Exceptions: File Checks

## Objetivos

Este laboratorio tiene como propósito fortalecer el entendimiento y la práctica del manejo de excepciones en C++.  
El estudiante trabajará con situaciones reales donde una operación puede generar errores, especialmente al manipular archivos.  
A través del desarrollo de una clase para manejar matrices 2×2 y métodos para cargar y guardar datos desde archivos, el objetivo es aprender a:

- Identificar situaciones en las que una excepción debe ser arrojada.  
- Implementar excepciones personalizadas.  
- Manejar errores relacionados con archivos, como archivo inexistente o falta de permisos.  
- Re-lanzar excepciones para simular un flujo de manejo en capas superiores.  
- Utilizar bloques `try-catch` correctamente en diferentes contextos.  

Este laboratorio complementa los anteriores sobre manejo de excepciones al aplicar estos conceptos al ámbito de archivos.

---

## Código Completo

```cpp
#include <iostream>
#include <fstream> //Para el uso de archivos (files)
#include <string>

class FileException {
private:
    std::string message;
public:
    FileException(const std::string& msg) : message(msg) {}
    const char* what() const { return message.c_str(); }
};

class Matrix2x2 {
private:
    double matrix[2][2];
public:
    Matrix2x2() {
        // Inicializa con ceros por seguridad
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                matrix[i][j] = 0;
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "[Error] Cannot open file for reading: " << filename << std::endl;
            throw FileException("File not found or cannot be opened: " + filename);
        }

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (!(file >> matrix[i][j])) {
                    std::cout << "[Error] File read error: " << filename << std::endl;
                    throw FileException("Invalid matrix data format in file: " + filename);
                }
            }
        }

        file.close();
        std::cout << "Matrix successfully loaded from: " << filename << std::endl;
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "[Error] Cannot open file for writing: " << filename << std::endl;
            throw FileException("No permission or invalid path for file: " + filename);
        }

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }

        file.close();
        std::cout << "Matrix successfully saved to: " << filename << std::endl;
    }

    void print() const {
        std::cout << "Matrix contents:" << std::endl;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j)
                std::cout << matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

int main() {
    Matrix2x2 matrix;
    std::string loadFilename = "nonexistent_file.txt";  // Prueba de archivo inexistente
    std::string saveFilename = "/root/matrix.txt";       // Prueba de ruta sin permisos (La mas facil es root)

    try {
        matrix.loadFromFile(loadFilename);
    }
    catch (FileException& e) {
        std::cout << "Caught exception during load: " << e.what() << std::endl;
        throw; // re-throw para simular manejo superior
    }
    catch (...) {
        std::cout << "Unknown error while loading file." << std::endl;
    }

    try {
        matrix.saveToFile(saveFilename);
    }
    catch (FileException& e) {
        std::cout << "Caught exception during save: " << e.what() << std::endl;
        throw; // re-throw para simular manejo superior
    }
    catch (...) {
        std::cout << "Unknown error while saving file." << std::endl;
    }

    return 0;
}
```

## Muestra de output
 ```
 [Error] Cannot open file for reading: nonexistent_file.txt
Caught exception during load: File not found or cannot be opened: nonexistent_file.txt
terminate called after throwing an instance of 'FileException'
  what():  File not found or cannot be opened: nonexistent_file.txt
Aborted (core dumped)
 ```
## Conclusión
A través de este laboratorio se reforzó el uso de excepciones aplicadas a la lectura y escritura de archivos, permitiendo comprender cómo manejar fallos comunes como archivos inexistentes o falta de permisos.  
Además, se practicó la creación de excepciones personalizadas, el uso correcto de bloques `try-catch` y la técnica de re-lanzamiento (`throw;`) para simular un manejo de errores en niveles superiores.  
Al combinar este ejercicio con laboratorios previos sobre excepciones, el estudiante adquiere una visión más completa y profesional del manejo de errores en C++, un aspecto esencial para desarrollar software robusto y confiable.

# Laboratorio 3.2.17 — Excepciones: Revisar Strings

## Objetivos

Este laboratorio tiene como finalidad que el estudiante aplique el manejo de excepciones dentro de un programa que valida direcciones IP.  
A través de este ejercicio, se busca reforzar la capacidad de:

- Utilizar excepciones en situaciones reales de validación de datos.
- Lanzar excepciones desde métodos regulares y desde constructores.
- Detectar errores de formato en cadenas que representan direcciónes IPv4.
- Implementar reglas de redes para calcular la máscara correspondiente a un rango basado en potencias de 2.
- Identificar y simular múltiples escenarios incorrectos, fortaleciendo la robustez del código.

Este laboratorio continúa la línea de los anteriores, integrando validaciones, clases, excepciones personalizadas y manejo de lógica relacionada con redes.

---

## Código
```cpp
#include <iostream>
#include <string>

class InvalidIPException {
public:
    InvalidIPException(const std::string& message) : msg(message) {}
    const char* what() const { return msg.c_str(); }
private:
    std::string msg;
};

class IPAddress {
private:
    int octets[4];

    bool isValidIP(const std::string& ip) {
        int parts = 0;
        std::string temp;
        for (char c : ip) {
            if (c == '.') {
                if (temp.empty()) return false;
                int val = std::stoi(temp);
                if (val < 0 || val > 255) return false;
                temp.clear();
                parts++;
            }
            else if (isdigit(c)) {
                temp += c;
            }
            else {
                return false;
            }
        }
        if (!temp.empty()) {
            int val = std::stoi(temp);
            if (val < 0 || val > 255) return false;
            parts++;
        }
        return parts == 4;
    }

public:
    IPAddress(const std::string& ip) {
        if (!isValidIP(ip)) {
            throw InvalidIPException("Invalid IP address format: " + ip);
        }
        int idx = 0;
        std::string temp;
        for (char c : ip) {
            if (c == '.') {
                octets[idx++] = std::stoi(temp);
                temp.clear();
            }
            else {
                temp += c;
            }
        }
        octets[idx] = std::stoi(temp);
    }

    void printSubnet(int range) const {
        if (range != 1 && range != 2 && range != 4 && range != 8 && range != 16 &&
            range != 32 && range != 64 && range != 128 && range != 256) {
            throw InvalidIPException("Invalid subnet range: must be a power of 2 between 1 and 256.");
        }

        // Calcular bits sin usar <cmath>
        int bits = 0;
        int temp = range;
        while (temp > 1) {
            temp /= 2;
            bits++;
        }
        int mask = 32 - bits;

        std::cout << "IP: "
            << octets[0] << '.' << octets[1] << '.' << octets[2] << '.' << octets[3]
            << " /" << mask << std::endl;
    }
};

int main() {
    try {
        IPAddress ip1("192.168.1.10");
        ip1.printSubnet(64);

        IPAddress ip2("10.0.0.256"); // Prueba de IP inválida
        ip2.printSubnet(32);
    }
    catch (const InvalidIPException& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

    try {
        IPAddress ip3("172.16.0.5");
        ip3.printSubnet(7); // Prueba de rango inválido
    }
    catch (const InvalidIPException& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
```

## Muestra de output
```
IP: 192.168.1.10 /26
Exception: Invalid IP address format: 10.0.0.256
Exception: Invalid subnet range: must be a power of 2 between 1 and 256.
```
## Conclusión

En este laboratorio se aplicó el manejo de excepciones en un escenario práctico enfocado en la validación de direcciones IP y subnets.  
Se utilizaron excepciones tanto en el constructor como en métodos internos, lo cual permite detectar errores desde el momento en que un objeto es creado, garantizando la integridad de los datos.  
La clase implementada valida formato, valores numéricos y rangos permitidos, demostrando la importancia de un control robusto de entrada.

Este ejercicio refuerza técnicas fundamentales en programación orientada a objetos, manejo de errores y diseño de clases, además de mostrar cómo las excepciones son esenciales para evitar fallas silenciosas en programas reales.

# 3.4.12 – Excepciones: Incluir información en las excepciones

## Objetivos

El propósito de este laboratorio es reforzar el uso de excepciones dentro de programas reales, aplicando validaciones estrictas en datos críticos. En particular, se busca que el estudiante simplifique la lógica de lanzamiento de excepciones, aprenda a detectar errores desde un constructor y genere mensajes detallados que indiquen con precisión qué campo contiene un valor incorrecto. Para ello, se trabaja con un encabezado IP que incluye direcciones de origen y destino, las cuales deben validarse rigurosamente bajo el formato estándar IPv4 (cuatro octetos en el rango 0–255).

---

## Código

```
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

class InvalidIPException {
public:
    InvalidIPException(const std::string& message) : msg(message) {}
    const char* what() const { return msg.c_str(); }
private:
    std::string msg;
};

class IPHeader {
public:
    IPHeader(const std::string& IPSource, const std::string& IPDestination, const std::string& otherData)
        : IPSource(IPSource), IPDestination(IPDestination), otherData(otherData)
    {
        check(IPSource, "Source");
        check(IPDestination, "Destination");
    }

private:
    void check(const std::string& address, const std::string& type) const {
        std::stringstream parts(address);
        std::string part;
        int count = 0;

        while (std::getline(parts, part, '.')) {
            if (part.empty() || part.length() > 3) {
                throw InvalidIPException("Invalid " + type + " IP Address - wrong format.");
            }

            for (char c : part) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    throw InvalidIPException("Invalid " + type + " IP Address - only digits and dots allowed.");
                }
            }

            int value = std::stoi(part);
            if (value < 0 || value > 255) {
                throw InvalidIPException("Invalid " + type + " IP Address - number out of range (0–255).");
            }

            if (++count > 4) {
                throw InvalidIPException("Invalid " + type + " IP Address - too many parts.");
            }
        }

        if (count != 4) {
            throw InvalidIPException("Invalid " + type + " IP Address - incorrect parts count.");
        }
    }

    std::string IPSource, IPDestination, otherData;
};

int main() {
    std::string inputSourceIP;
    std::string inputDestinationIP;

    std::getline(std::cin, inputSourceIP);
    std::getline(std::cin, inputDestinationIP);

    try {
        IPHeader headerValid(inputSourceIP, inputDestinationIP, "data");
        std::cout << "Valid IP Header." << std::endl;
    }
    catch (const InvalidIPException& ex) {
        std::cout << "Invalid IP Header - " << ex.what() << std::endl;
    }

    std::getline(std::cin, inputSourceIP);
    std::getline(std::cin, inputDestinationIP);

    try {
        IPHeader headerInvalid(inputSourceIP, inputDestinationIP, "data");
        std::cout << "Valid IP Header." << std::endl;
    }
    catch (const InvalidIPException& ex) {
        std::cout << "Invalid IP Header - " << ex.what() << std::endl;
    }

    return 0;
}
```

## Muestra de Output
```
192.168.1.10
10.0.0.5
Valid IP Header.
300.2.1.5
10.0.0.5
Invalid IP Header - Invalid Source IP Address - number out of range (0–255).
```
## Conclusión

Este laboratorio permitió profundizar en la validación de datos mediante excepciones personalizadas, lo cual resulta esencial cuando se manejan estructuras como encabezados IP. Se comprobó la importancia de centralizar la lógica de verificación en un método dedicado, de forma que tanto el constructor como el resto del programa puedan apoyarse en validaciones consistentes y fáciles de mantener. Asimismo, se reforzó el uso de excepciones con mensajes detallados, facilitando al usuario o desarrollador identificar exactamente qué campo presenta un error y por qué. Esto contribuye a la creación de software más robusto, confiable y seguro.

# 3.4.13 – LAB: Excepciones – Uso en el programa
## Objetivos

El propósito de este laboratorio es fortalecer el entendimiento del uso de excepciones dentro de programas reales mediante la construcción de un modelo simplificado del juego _Torres de Hanoi_. En particular, se busca:

- Aplicar el manejo de excepciones en situaciones reales relacionadas con la lógica del programa.
- Implementar excepciones personalizadas para validar reglas específicas del problema.
- Comprender cómo detectar condiciones inválidas, tales como movimientos imposibles, torres vacías o números fuera de rango.
- Generar un seguimiento claro del estado de las torres y observe cómo las excepciones ayudan a evitar errores lógicos.

---

## Código
```
#include <iostream>
#include <stdexcept>
#include <thread> //Thread y chrono son usados para que el programa espere entre movimientos y no sea completamente instantaneo
#include <chrono>


class TorreFueraDeRangoException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: una o ambas torres no están en el rango 1–3.";
    }
};

class DiscoInvalidoException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: no se puede mover un disco más grande sobre uno más pequeño.";
    }
};

class TorreVaciaException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: la torre de origen está vacía.";
    }
};


class Nodo {
public:
    int valor;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int v) : valor(v), siguiente(nullptr), anterior(nullptr) {}
};



class Pila {
private:
    Nodo* tope;

public:
    Pila() : tope(nullptr) {}

    bool pilaVacia() const {
        return tope == nullptr;
    }

    void push(int numero) {
        Nodo* nuevo = new Nodo(numero);
        if (pilaVacia()) {
            tope = nuevo;
        }
        else {
            tope->anterior = nuevo;
            nuevo->siguiente = tope;
            tope = nuevo;
        }
    }

    int pop() {
        if (pilaVacia()) {
            throw TorreVaciaException();
        }
        int dato = tope->valor;
        Nodo* temp = tope;
        tope = tope->siguiente;
        if (tope != nullptr) {
            tope->anterior = nullptr;
        }
        delete temp;
        return dato;
    }

    int peek() const {
        if (pilaVacia()) {
            throw TorreVaciaException();
        }
        return tope->valor;
    }

    void print() const {
        Nodo* actual = tope;
        while (actual != nullptr) {
            std::cout << actual->valor << std::endl;
            actual = actual->siguiente;
        }
    }
};

// ------------ Funciones ------------

void moverDisco(Pila& origen, Pila& destino, Pila& auxiliar,
    char nombreOrig, char nombreDest, char nombreAux) {
    try {
        // Validar torres (solo deben ser A, B o C)
        if (nombreOrig < 'A' || nombreOrig > 'C' || nombreDest < 'A' || nombreDest > 'C') {
            throw TorreFueraDeRangoException();
        }

        // Intentar tomar el disco del origen
        int disco = origen.pop();

        // Si el destino no está vacío, verificar tamaño del disco
        if (!destino.pilaVacia() && disco > destino.peek()) {
            // Devolver el disco al origen y lanzar excepción
            origen.push(disco);
            throw DiscoInvalidoException();
        }

        destino.push(disco);

        system("cls"); // Cambia a "clear" si usas Linux/Mac
        std::cout << "Mover disco " << disco << " de " << nombreOrig << " a " << nombreDest << std::endl;

        std::cout << "\n====== Torre " << nombreOrig << " ========\n";
        origen.print();
        std::cout << "\n====== Torre " << nombreDest << " ========\n";
        destino.print();
        std::cout << "\n====== Torre " << nombreAux << " ========\n";
        auxiliar.print();
        std::cout << "\n=====================\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    catch (const TorreFueraDeRangoException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const DiscoInvalidoException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const TorreVaciaException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void torresDeHanoi(int n, Pila& origen, Pila& destino, Pila& auxiliar,
    char nombreOrig, char nombreDest, char nombreAux) {
    if (n == 1) {
        moverDisco(origen, destino, auxiliar, nombreOrig, nombreDest, nombreAux);
        return;
    }

    torresDeHanoi(n - 1, origen, auxiliar, destino, nombreOrig, nombreAux, nombreDest);
    moverDisco(origen, destino, auxiliar, nombreOrig, nombreDest, nombreAux);
    torresDeHanoi(n - 1, auxiliar, destino, origen, nombreAux, nombreDest, nombreOrig);
}

int main() {
    try {
        int n;
        std::cout << "Ingresa el número de discos: ";
        if (!(std::cin >> n) || n <= 0) {
            throw std::invalid_argument("Debes ingresar un número entero positivo.");
        }

        Pila torreA, torreB, torreC;

        for (int i = n; i >= 1; i--) {
            torreA.push(i);
        }

        std::cout << "\n--- Movimientos de las Torres de Hanoi ---\n";
        torresDeHanoi(n, torreA, torreC, torreB, 'A', 'C', 'B');

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error de entrada: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Excepción no controlada: " << e.what() << std::endl;
    }

    return 0;
}
```

## Output esperado
```
Ingresa el número de discos: 3

--- Movimientos de las Torres de Hanoi ---
Mover disco 1 de A a C

====== Torre A ========
3
2

====== Torre C ========
1

====== Torre B ========
(empty)

=====================

Mover disco 2 de A a B
...
(se muestran todos los movimientos)
...
Mover disco 1 de B a C

====== Torre A ========
(empty)

====== Torre C ========
3
2
1

====== Torre B ========
(empty)

=====================

```

## Conclusión

Este laboratorio permitió integrar excepciones personalizadas en un programa con lógica compleja, demostrando que el manejo adecuado de errores es fundamental para mantener la integridad de las reglas del sistema.  
Las excepciones implementadas permiten detectar movimientos inválidos, valores fuera de rango y torres vacías, lo que garantiza un funcionamiento correcto del modelo de las Torres de Hanoi. Además, el uso del seguimiento visual de los movimientos facilitó comprender el flujo del algoritmo recursivo y reforzó la importancia de validar cada operación realizada por el usuario o el programa.

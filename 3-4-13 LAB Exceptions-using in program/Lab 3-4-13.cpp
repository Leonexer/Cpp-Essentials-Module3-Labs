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

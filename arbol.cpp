#include <iostream>
#include <queue>

using namespace std;

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    #define COLOR_RED FOREGROUND_RED | FOREGROUND_INTENSITY
    #define COLOR_GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
    #define COLOR_YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
    #define COLOR_RESET FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
    void setConsoleColor(WORD color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
#else
    #define CLEAR_SCREEN "clear"
    #define COLOR_RED "\033[1;31m"
    #define COLOR_GREEN "\033[1;32m"
    #define COLOR_YELLOW "\033[1;33m"
    #define COLOR_RESET "\033[0m"
    void setConsoleColor(const string& color) {
        cout << color;
    }
#endif

class ArbolBinario {
private:
    class Nodo {
    public:
        int info;
        Nodo *izq;
        Nodo *der;
    };
    Nodo *raiz;
    void borrar(Nodo *reco);
    void imprimirPre(Nodo *reco);
    void imprimirEntre(Nodo *reco);
    void imprimirPost(Nodo *reco);
    int calcularTamanio(Nodo *reco);
    int calcularNivel(Nodo *reco);
    void imprimirArbol(Nodo* nodo, int nivel);

public:
    ArbolBinario();
    ~ArbolBinario();
    void insertar(int x);
    void imprimirPre();
    void imprimirEntre();
    void imprimirPost();
    int tamanio();
    int nivel();
    void mostrarPerOrden();
    void mostrarPostOrden();
    void mostrarEntreOrden();
    void eliminar(int x, bool &eliminado);
    void eliminarArbol();
    void imprimirArbol();
    bool estaVacio();
    int nivelNodo(int valor);
    int nivelNodo(Nodo* nodo, int valor, int nivel_actual);
};

ArbolBinario::ArbolBinario() {
    raiz = NULL;
}

ArbolBinario::~ArbolBinario() {
    borrar(raiz);
}

void ArbolBinario::borrar(Nodo *reco) {
    if (reco != NULL) {
        borrar(reco->izq);
        borrar(reco->der);
        delete reco;
    }
}

void ArbolBinario::insertar(int x) {
    Nodo *nuevo;
    nuevo = new Nodo();
    nuevo->info = x;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    if (raiz == NULL)
        raiz = nuevo;
    else {
        Nodo *anterior, *reco;
        anterior = NULL;
        reco = raiz;
        while (reco != NULL) {
            anterior = reco;
            if (x < reco->info)
                reco = reco->izq;
            else
                reco = reco->der;
        }
        if (x < anterior->info)
            anterior->izq = nuevo;
        else
            anterior->der = nuevo;
    }
}

void ArbolBinario::imprimirPre() {
    if (estaVacio()) {
        cout << "El árbol está vacío." << endl;
        return;
    }
    imprimirPre(raiz);
    cout << "\n";
}

void ArbolBinario::imprimirPre(Nodo *reco) {
    if (reco != NULL) {
        cout << reco->info << "-";
        imprimirPre(reco->izq);
        imprimirPre(reco->der);
    }
}

void ArbolBinario::imprimirEntre() {
    if (estaVacio()) {
        cout << "El árbol está vacío." << endl;
        return;
    }
    imprimirEntre(raiz);
    cout << "\n";
}

void ArbolBinario::imprimirEntre(Nodo *reco) {
    if (reco != NULL) {
        imprimirEntre(reco->izq);
        cout << reco->info << "-";
        imprimirEntre(reco->der);
    }
}

void ArbolBinario::imprimirPost() {
    if (estaVacio()) {
        cout << "El árbol está vacío." << endl;
        return;
    }
    imprimirPost(raiz);
    cout << "\n";
}

void ArbolBinario::imprimirPost(Nodo *reco) {
    if (reco != NULL) {
        imprimirPost(reco->izq);
        imprimirPost(reco->der);
        cout << reco->info << "-";
    }
}

int ArbolBinario::calcularTamanio(Nodo *reco) {
    if (reco == NULL)
        return 0;
    else
        return 1 + calcularTamanio(reco->izq) + calcularTamanio(reco->der);
}

int ArbolBinario::tamanio() {
    return calcularTamanio(raiz);
}

int ArbolBinario::calcularNivel(Nodo *reco) {
    if (reco == NULL)
        return 0;
    else {
        int izq = calcularNivel(reco->izq);
        int der = calcularNivel(reco->der);
        if (izq > der)
            return izq + 1;
        else
            return der + 1;
    }
}

int ArbolBinario::nivel() {
    return calcularNivel(raiz);
}

void ArbolBinario::mostrarPerOrden() {
    if (estaVacio()) {
        cout << "El árbol está vacío." << endl;
        return;
    }
    cout << "Impresion en perorden: ";
    imprimirPre();
}

void ArbolBinario::mostrarPostOrden() {
    if (estaVacio()) {
        cout << "El árbol está vacío." << endl;
        return;
    }
    cout << "Impresion en postorden: ";
    imprimirPost();
}

void ArbolBinario::mostrarEntreOrden() {
    if (estaVacio()) {
        cout << "El árbol está vacío." << endl;
        return;
    }
    cout << "Impresion en entreorden: ";
    imprimirEntre();
}

bool ArbolBinario::estaVacio() {
    return raiz == NULL;
}

void ArbolBinario::eliminar(int x, bool &eliminado) {
    Nodo *padre = NULL;
    Nodo *actual = raiz;
    bool encontrado = false;

    while (actual != NULL && !encontrado) {
        if (actual->info == x) {
            encontrado = true;
        } else {
            padre = actual;
            if (x > actual->info)
                actual = actual->der;
            else
                actual = actual->izq;
        }
    }

    if (!encontrado) {
        eliminado = false; // Nodo no encontrado
        return;
    }

    // Caso 1: Nodo a eliminar no tiene hijos
    if (actual->izq == NULL && actual->der == NULL) {
        if (padre != NULL) {
            if (padre->izq == actual)
                padre->izq = NULL;
            else
                padre->der = NULL;
        } else {
            raiz = NULL;
        }
        delete actual;
    }
    // Caso 2: Nodo a eliminar tiene un hijo
    else if (actual->izq == NULL || actual->der == NULL) {
        Nodo *hijo;
        if (actual->izq != NULL)
            hijo = actual->izq;
        else
            hijo = actual->der;

        if (padre != NULL) {
            if (padre->izq == actual)
                padre->izq = hijo;
            else
                padre->der = hijo;
        } else {
            raiz = hijo;
        }
        delete actual;
    }
    // Caso 3: Nodo a eliminar tiene dos hijos
    else {
        Nodo *minimoPadre = actual;
        Nodo *minimo = actual->der;
        while (minimo->izq != NULL) {
            minimoPadre = minimo;
            minimo = minimo->izq;
        }
        actual->info = minimo->info;

        if (minimoPadre == actual)
            minimoPadre->der = minimo->der;
        else
            minimoPadre->izq = minimo->der;

        delete minimo;
    }

    eliminado = true; // Nodo eliminado con éxito
}

void ArbolBinario::eliminarArbol() {
    borrar(raiz);
    raiz = NULL;
}

void ArbolBinario::imprimirArbol() {
    if (raiz == NULL) {
        cout << "El árbol está vacío." << endl;
        return;
    }

    imprimirArbol(raiz, 0);
}

void ArbolBinario::imprimirArbol(Nodo* nodo, int nivel) {
    if (nodo == NULL)
        return;

    imprimirArbol(nodo->der, nivel + 1);
    for (int i = 0; i < nivel; i++)
        cout << "    ";
    cout << nodo->info << endl;
    imprimirArbol(nodo->izq, nivel + 1);
}

int ArbolBinario::nivelNodo(int valor) {
    return nivelNodo(raiz, valor, 1);
}

int ArbolBinario::nivelNodo(Nodo* nodo, int valor, int nivel_actual) {
    if (nodo == NULL)
        return 0;
    if (nodo->info == valor)
        return nivel_actual;
    int nivel_izquierda = nivelNodo(nodo->izq, valor, nivel_actual + 1);
    if (nivel_izquierda != 0)
        return nivel_izquierda;
    return nivelNodo(nodo->der, valor, nivel_actual + 1);
}

int main() {

    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #else
        setlocale(LC_ALL, "en_US.utf8");
    #endif
    
    ArbolBinario *arbol = new ArbolBinario();
    int opcion;
    int elemento;

    do {
        cout << endl;
        setConsoleColor(COLOR_GREEN);
        cout << "Menu:\n";
        setConsoleColor(COLOR_RESET);
        cout << "1. Insertar nodo\n";
        cout << "2. Ver árbol\n";
        cout << "3. Tamaño del árbol\n";
        cout << "4. Nivel del árbol\n";
        cout << "5. Mostrar en preorden\n";
        cout << "6. Mostrar en postorden\n";
        cout << "7. Mostrar en entreorden\n";
        cout << "8. Eliminar nodo\n";
        cout << "9. Eliminar árbol\n";
        cout << "10. Buscar nivel de un nodo\n";
        setConsoleColor(COLOR_RED);
        cout << "11. Salir\n";
        setConsoleColor(COLOR_RESET);
        cout << endl;
        cout << "Ingrese la opción: ";
        cin >> opcion;
        system(CLEAR_SCREEN);

        switch (opcion) {
            case 1:
                cout << "Ingrese el elemento a insertar: ";
                cin >> elemento;
                arbol->insertar(elemento);
                break;
            case 2:
                cout << "Árbol ingresado:\n";
                arbol->imprimirArbol();
                break;
            case 3:
                cout << "El tamaño del árbol es: " << arbol->tamanio() << endl;
                break;
            case 4:
                cout << "El nivel del árbol es: " << arbol->nivel() << endl;
                break;
            case 5:
                arbol->mostrarPerOrden();
                break;
            case 6:
                arbol->mostrarPostOrden();
                break;
            case 7:
                arbol->mostrarEntreOrden();
                break;
            case 8:
                if (arbol->estaVacio()) {
                    cout << "El árbol está vacío." << endl;
                } else {
                    cout << "Ingrese el nodo a eliminar: ";
                    cin >> elemento;
                    bool eliminado;
                    arbol->eliminar(elemento, eliminado);
                    if (eliminado){
                        setConsoleColor(COLOR_GREEN);
                        cout << "Nodo " << elemento << " eliminado exitosamente.\n";
                        setConsoleColor(COLOR_RESET);
                        }
                    else
                        cout << "El nodo " << elemento << " no existe en el árbol.\n";
                }
                break;
            case 9:
                arbol->eliminarArbol();
                cout << "Árbol eliminado.\n";
                break;

            case 10:
                if (arbol->estaVacio()) {
                    cout << "El árbol está vacío." << endl;
                } else {
                    cout << "Ingrese el valor del nodo: ";
                    cin >> elemento;
                    int nivel = arbol->nivelNodo(elemento);
                    if (nivel != 0)
                        cout << "El nivel del nodo " << elemento << " es: " << nivel << endl;
                    else
                        cout << "El nodo " << elemento << " no existe en el árbol." << endl;
                }
                break;
            case 11:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }

    } while (opcion != 11);

    delete arbol;
    return 0;
}

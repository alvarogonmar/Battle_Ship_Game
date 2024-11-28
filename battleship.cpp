#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Representa el barco en el juego
class Barco
{
public:
    string tipo;                        // Tipo de Barco
    int longitud;                       // Longitud del Barco
    vector<pair<int, int>> coordenadas; // Posiciones que ocupa el Barco
    vector<pair<int, int>> impactos;    // Posiciones donde el Barco ha sido impactada
    char orientacion;                   // Orientación del Barco ('H' horizontal, 'V' vertical)

    // Inicializa un Barco con su tipo y longitud
    Barco(string tipo, int longitud) : tipo(tipo), longitud(longitud) {}

    // Establece las coordenadas del Barco basado en su posición inicial y orientación
    void establecerCoordenadas(int x, int y, char orientacion)
    {
        this->orientacion = orientacion;
        coordenadas.clear();
        for (int i = 0; i < longitud; i++)
        {
            if (orientacion == 'H')
                coordenadas.emplace_back(y, x + i);
            else
                coordenadas.emplace_back(y + i, x);
        }
    }

    // Verifica si el Barco está hundido (cuando todos sus puntos han sido impactados)
    bool estaHundido() const
    {
        return coordenadas.size() == impactos.size();
    }

    // Registra el impacto en el Barco si las coordenadas coinciden
    bool recibirImpacto(int x, int y)
    {
        for (auto &coord : coordenadas)
        {
            if (coord.first == y && coord.second == x)
            {
                impactos.emplace_back(y, x);
                return true;
            }
        }
        return false;
    }
};

// Representa el tablero de juego
class Tablero
{
public:
    int size;                  // Tamaño del tablero 10x10
    vector<vector<char>> mapa; // Matriz que representa el estado del tablero
    vector<Barco> Barcos;      // Lista de Barcos en el tablero

    // Constructor que inicializa el tablero vacío
    Tablero(int size = 10) : size(size), mapa(size, vector<char>(size, '~')) {}

    // Intenta colocar un Barco en el tablero
    bool colocarBarco(Barco Barco, int x, int y, char orientacion)
    {
        if (x < 0 || x >= size || y < 0 || y >= size)
        {
            cout << "Error: Coordenadas fuera del tablero." << endl;
            return false;
        }

        Barco.establecerCoordenadas(x, y, orientacion);
        if (!validarPosicion(Barco))
        {
            cout << "Error: Posición inválida. El Barco se superpone con otra o sale del tablero." << endl;
            return false;
        }

        Barcos.push_back(Barco);
        for (auto &coord : Barco.coordenadas)
            mapa[coord.first][coord.second] = 'B';

        cout << "Barco colocado exitosamente." << endl;
        return true;
    }

    // Valida si la posición del Barco es legal
    bool validarPosicion(const Barco &Barco) const
    {
        for (auto &coord : Barco.coordenadas)
        {
            if (coord.first < 0 || coord.first >= size || coord.second < 0 || coord.second >= size)
                return false;
            if (mapa[coord.first][coord.second] == 'B')
                return false;
        }
        return true;
    }

    // Procesa un ataque en las coordenadas dadas
    string recibirAtaque(int x, int y)
    {
        if (x < 0 || x >= size || y < 0 || y >= size)
            return "Coordenadas inválidas";

        if (mapa[y][x] == 'B')
        {
            mapa[y][x] = 'X';
            for (auto &Barco : Barcos)
            {
                if (Barco.recibirImpacto(x, y))
                {
                    if (Barco.estaHundido())
                        return "¡" + Barco.tipo + " hundido!";
                    return "¡Impacto en " + Barco.tipo + "!";
                }
            }
        }
        else if (mapa[y][x] == '~')
        {
            mapa[y][x] = 'O';
            return "Agua";
        }
        return "Posición ya atacada";
    }

    // Muestra el estado actual del tablero
    void mostrarTablero(bool ocultarBarcos = true) const
    {
        cout << "  ";
        for (int j = 0; j < size; j++)
            cout << j << " ";
        cout << endl;

        for (int i = 0; i < size; i++)
        {
            cout << i << " ";
            for (int j = 0; j < size; j++)
            {
                if (ocultarBarcos && mapa[i][j] == 'B')
                    cout << "~ ";
                else
                    cout << mapa[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Verifica si todos los Barcos en el tablero han sido hundidos
    bool todosBarcosHundidos() const
    {
        for (const auto &Barco : Barcos)
        {
            if (!Barco.estaHundido())
                return false;
        }
        return true;
    }
};

// Representa al jugador en el juego
class Jugador
{
public:
    string nombre;
    Tablero tablero;

    // Constructor: Inicializa un jugador con su nombre y tablero
    Jugador(string nombre, int size) : nombre(nombre), tablero(size) {}

    // Realiza un ataque al tablero del enemigo
    string atacar(Jugador &enemigo, int x, int y)
    {
        return enemigo.tablero.recibirAtaque(x, y);
    }
};

// Verifica como va el juego
class Referi
{
public:
    // Verifica si un jugador ha ganado (todos los Barcos del oponente están hundidos)
    static bool verificarGanador(const Jugador &jugador)
    {
        return jugador.tablero.todosBarcosHundidos();
    }
};

// Clase Juego: Controla el flujo del juego
class Juego
{
private:
    Jugador jugador1;
    Jugador jugador2;
    Jugador *turnoActual;

public:
    // Constructor: Inicializa el juego con dos jugadores
    Juego(string nombre1, string nombre2, int size = 10)
        : jugador1(nombre1, size), jugador2(nombre2, size), turnoActual(&jugador1) {}

    // Permite a un jugador colocar sus Barcos en el tablero
    void colocarBarcos(Jugador &jugador)
    {
        cout << "\n--- Colocación de Barcos para " << jugador.nombre << " ---" << endl;
        cout << "Instrucciones:" << endl;
        cout << "- Introduce las coordenadas (x y) y la orientación (H/V) para cada Barco." << endl;
        cout << "- Las coordenadas deben estar dentro del tablero (0-9)." << endl;
        cout << "- La orientación debe ser 'H' para horizontal o 'V' para vertical." << endl;
        cout << "- Los Barcos no pueden superponerse ni salir del tablero." << endl;

        vector<pair<string, int>> tiposBarcos = {
            {"Acorazado", 3},
            {"Submarino", 2},
            {"Lancha", 1}};

        for (const auto &tipoBarco : tiposBarcos)
        {
            Barco Barco(tipoBarco.first, tipoBarco.second);
            int x, y;
            char orientacion;
            do
            {
                cout << "\nColoca tu " << tipoBarco.first << " (longitud: " << tipoBarco.second << ")" << endl;
                cout << "Coordenada x: ";
                while (!(cin >> x) || x < 0 || x >= jugador.tablero.size)
                {
                    cout << "Coordenada x inválida. Intenta nuevamente: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "Coordenada y: ";
                while (!(cin >> y) || y < 0 || y >= jugador.tablero.size)
                {
                    cout << "Coordenada y inválida. Intenta nuevamente: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "Orientación (H/V): ";
                while (!(cin >> orientacion) || (orientacion != 'H' && orientacion != 'V'))
                {
                    cout << "Orientación inválida. Usa 'H' para horizontal o 'V' para vertical: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!jugador.tablero.colocarBarco(Barco, x, y, orientacion));
            jugador.tablero.mostrarTablero(false);
        }
    }

    // Ejecuta el juego principal
    void jugar()
    {
        colocarBarcos(jugador1);
        colocarBarcos(jugador2);

        cout << "\n¡Comienza la batalla!" << endl;

        while (true)
        {
            cout << "\n--- Turno de " << turnoActual->nombre << " ---" << endl;
            Jugador &enemigo = (turnoActual == &jugador1) ? jugador2 : jugador1;

            cout << "Tablero del enemigo:" << endl;
            enemigo.tablero.mostrarTablero(true);

            int x, y;
            cout << "Introduce coordenadas para atacar:" << endl;
            cout << "Coordenada x: ";
            while (!(cin >> x) || x < 0 || x >= enemigo.tablero.size)
            {
                cout << "Coordenada x inválida. Intenta nuevamente: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Coordenada y: ";
            while (!(cin >> y) || y < 0 || y >= enemigo.tablero.size)
            {
                cout << "Coordenada y inválida. Intenta nuevamente: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            string resultado = turnoActual->atacar(enemigo, x, y);
            cout << "Resultado del ataque: " << resultado << endl;

            if (Referi::verificarGanador(enemigo))
            {
                cout << "\n¡" << turnoActual->nombre << " ha ganado el juego!" << endl;
                break;
            }

            turnoActual = (turnoActual == &jugador1) ? &jugador2 : &jugador1;
        }
    }
};

// Función principal: Inicia el juego
int main()
{
    cout << "¡Bienvenido a Batalla Naval!" << endl;
    cout << "Este juego es para dos jugadores en un tablero de 10x10." << endl;

    string nombre1, nombre2;
    cout << "Introduce el nombre del Jugador 1: ";
    getline(cin, nombre1);
    cout << "Introduce el nombre del Jugador 2: ";
    getline(cin, nombre2);

    Juego juego(nombre1, nombre2, 10);
    juego.jugar();
    return 0;
}

// FOR RUN
// g++ -std=c++11 battleship.cpp -o battleship

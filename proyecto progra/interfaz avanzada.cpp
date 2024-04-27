#include <iostream>
#include <cmath>
#include <Windows.h>
#include <conio.h>

using namespace std;

const int SCREEN_HEIGHT = 200; // Altura predeterminada de la pantalla
const int SCREEN_WIDTH = 200;  // Ancho predeterminado de la pantalla

void gotoxy(int x, int y) // Modificado para mover el cursor sin imprimir nada
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void dibujarCirculo(int radio, int startX, int startY) // graficar circulo
{
    int centro = radio;
    for(int a = 0; a <= 2 * radio; a++)
    {
        for(int e = 0; e <= 2 * radio; e++)
        {
            double distancia = sqrt((a - radio) * (a - radio) + (e - radio) * (e - radio));
            if (distancia <= radio + 0.5)
            {
                int posX = (startX + e) % SCREEN_WIDTH;
                int posY = (startY + a) % SCREEN_HEIGHT;
                gotoxy(posX, posY);
                cout << "*";
            }
        }
    }
}

void dibujarCuadrado(int lado, int startX, int startY) // graficar cuadrado
{
    for (int a = 0; a < lado; ++a)
    {
        for (int e = 0; e < lado; ++e)
        {
            if (a == 0 || a == lado - 1 || e == 0 || e == lado - 1)
            {
                int posX = (startX + e * 2) % SCREEN_WIDTH;
                int posY = (startY + a) % SCREEN_HEIGHT;
                gotoxy(posX, posY);
                cout << "* ";
            }
        }
    }
}

void dibujarRectangulo(int altura, int ancho, int startX, int startY) // graficar rectangulo
{
    for (int a = 0; a < altura; a++)
    {
        for (int e = 0; e < ancho; e++)
        {
            if (a == 0 || a == altura - 1 || e == 0 || e == ancho - 1)
            {
                int posX = (startX + e * 2) % SCREEN_WIDTH;
                int posY = (startY + a) % SCREEN_HEIGHT;
                gotoxy(posX, posY);
                cout << "* ";
            }
        }
    }
}

void dibujarTriangulo(int base, int startX, int startY) // graficar triangulo
{
    int altura;
    if (base % 2 == 0)
    {
        base = base - 1;
    }
    altura = base / 2 + 1;
    for (int a = 1; a <= altura; a++)
    {
        for (int e = 0; e <= base; e++)
        {
            if (e >= altura - a + 1 && e <= altura + a - 1)
            {
                int posX = (startX + e) % SCREEN_WIDTH;
                int posY = (startY + a) % SCREEN_HEIGHT;
                gotoxy(posX, posY);
                cout << "*";
            }
        }
    }
}

int main()
{
    // Moviendo el cursor al inicio del programa
    gotoxy(0, 0);

    int tecla, x = 0, y = 0;
    int opcion, px, py;

    while (true)
    {
        system("cls");
        cout << "Presione la letra 'q' para poder mostrar el menu "<<endl;
        tecla = _getch();

        switch (tecla)
        {
            case 72: // Arriba
                y = (y - 1 + SCREEN_HEIGHT) % SCREEN_HEIGHT;
                gotoxy(x, y); // Muestra el cursor en su nueva posición
                break;
            case 75: // Izquierda
                x = (x - 1 + SCREEN_WIDTH) % SCREEN_WIDTH;
                gotoxy(x, y); // Muestra el cursor en su nueva posición
                break;
            case 80: // Abajo
                y = (y + 1) % SCREEN_HEIGHT;
                gotoxy(x, y); // Muestra el cursor en su nueva posición
                break;
            case 77: // Derecha
                x = (x + 1) % SCREEN_WIDTH;
                gotoxy(x, y); // Muestra el cursor en su nueva posición
                break;
            case 'q':
                system("cls");
                gotoxy(x, y);
                py = y;
                px = x;
                cout << "menu de comandos " << endl;
                py = y - 2;
                gotoxy(x, py);
                cout << "0. Imprime cuadrado " << endl;
                py = y - 2;
                gotoxy(x, py);
                cout << "1. Imprime Triangulo " << endl;
                py = y - 2;
                gotoxy(x, py);
                cout << "2. Imprime Circulo " << endl;
                py = y - 2;
                gotoxy(x, py);
                cout << "3. Imprime Rectangulo " << endl;
                py = y - 2;
                gotoxy(x, py);
                cout << "4. Salir " << endl;
                px = x + 20;
                gotoxy(px, y);
                cin >> opcion;
                break;
        }

        if (tecla == 'q') // menu para graficar
        {
            system("cls"); // Limpia la pantalla antes de imprimir el dibujo
            switch (opcion)
            {
                case 0:
                    {
                        int lado;
                        cout << "Ingrese un lado del cuadrado: ";
                        cin >> lado;
                        dibujarCuadrado(lado, x, y);
                        break;
                    }
                case 1:
                    {
                        int base;
                        cout << "Ingrese la base del triangulo que desea dibujar: ";
                        cin >> base;
                        dibujarTriangulo(base, x, y);
                        break;
                    }
                case 2:
                    {
                        int radio;
                        cout << "Ingrese el radio del circulo que desea dibujar: ";
                        cin >> radio;
                        dibujarCirculo(radio, x, y);
                        break;
                    }
                case 3:
                    {
                        int altura, ancho;
                        cout << "Ingrese el ancho del rectuangulo que desea dibujar: ";
                        cin >> ancho;
                        cout << "Ingrese la altura del rectuangulo que desea dibujar: ";
                        cin >> altura;
                        dibujarRectangulo(altura, ancho, x, y);
                        break;
                    }
                case 4:
                    cout << "Saliendo..." << endl;
                    return 0;
            }
            _getch(); // Espera a que se presione cualquier tecla antes de continuar
        }
    }

    return 0;
}


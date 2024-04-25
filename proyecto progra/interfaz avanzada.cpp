#include <iostream>
#include <cmath>
#include <Windows.h>
#include <conio.h>

using namespace std;

void dibujarCirculo(int radio) // graficar circulo
{
    int centro = radio;
    for(int a = 0; a <= 2 * radio; a++)
    {
        for(int e = 0; e <= 2 * radio; e++)
        {
            double distancia = sqrt((a - radio) * (a - radio) + (e - radio) * (e - radio));
            if (distancia <= radio + 0.5)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void dibujarCuadrado(int lado) // graficar cuadrado
{
    for (int a = 0; a < lado; ++a)
    {
        for (int e = 0; e < lado; ++e)
        {
            if (a == 0 || a == lado - 1 || e == 0 || e == lado - 1)
            {
                cout << "* ";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void dibujarRectangulo(int altura, int ancho) // graficar rectangulo
{
    for (int a = 0; a < altura; a++)
    {
        for (int e = 0; e < ancho; e++)
        {
            if (a == 0 || a == altura - 1 || e == 0 || e == ancho - 1)
            {
                cout << "* ";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void dibujarTriangulo(int base) // graficar triangulo
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
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void gotoxy(int x, int y, char cursor = ' ') // Modificado para imprimir un símbolo en la posición actual
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << cursor; // Imprime el símbolo en la posición actual
}

int main()
{
    int opcion, tecla, x = 0, y = 0;
    int tamx, tamy;
    cout<<"Ingrese el la altura de la pantalla que desea: "<<endl;
    cin>>tamy;
    cout<<"Ingrese el ancho de la pantalla que desea: "<<endl;
    cin>>tamx;
    while (true)
    {
        system("cls"); // Limpia la pantalla antes de imprimir el menú
        gotoxy(x, y); // Muestra el cursor en la posición actual

        tecla = _getch();

        switch (tecla)
        {
            case 72: // Arriba
                if (y > 0) y--;
                break;
            case 75: // Izquierda
                if (x > 0) x--;
                break;
            case 80: // Abajo
                if (y < tamy - 1) y++;
                break;
            case 77: // Derecha
                if (x < tamx - 1) x++;
                break;
            case 'q': // Salir del programa
                return 0;
        }

        if (tecla == 13) // Si se presiona Enter
        {
            system("cls"); // Limpia la pantalla antes de imprimir el dibujo
            switch (y)
            {
                case 0:
                    {
                        int lado;
                        cout << "Ingrese un lado del cuadrado: ";
                        cin >> lado;
                        dibujarCuadrado(lado);
                        break;
                    }
                case 1:
                    {
                        int base;
                        cout << "Ingrese la base del triangulo que desea dibujar: ";
                        cin >> base;
                        dibujarTriangulo(base);
                        break;
                    }
                case 2:
                    {
                        int radio;
                        cout << "Ingrese el radio del circulo que desea dibujar: ";
                        cin >> radio;
                        dibujarCirculo(radio);
                        break;
                    }
                case 3:
                    {
                        int altura, ancho;
                        cout << "Ingrese el ancho del rectuangulo que desea dibujar: ";
                        cin >> ancho;
                        cout << "Ingrese la altura del rectuangulo que desea dibujar: ";
                        cin >> altura;
                        dibujarRectangulo(altura, ancho);
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

#include <iostream>
using namespace std;

int main()
{
    int altura, ancho;
    cout << "Ingrese la altura de su rectangulo" << endl;
    cin >> altura;
    cout << "Ingrese el ancho de su rectangulo" << endl;
    cin >> ancho;

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
                cout << "  "; // Cambiado de "*" a "  " para el interior del rectángulo
            }
        }
        cout << endl;
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include <shlobj.h>

using namespace std;

const int SCREEN_WIDTH = 150;
const int SCREEN_HEIGHT = 50;
const int MENU_WIDTH = 50;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y)
{
    COORD cursor;
    cursor.X = x;
    cursor.Y = y;
    SetConsoleCursorPosition(hConsole, cursor);
}

void setConsoleSize(int ancho, int alto)
{
    COORD bufferSize;
    bufferSize.X = ancho;
    bufferSize.Y = alto;
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = {0, 0, ancho - 1, alto - 1};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void maximizarConsola()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

void clearLine(int y)
{
    gotoxy(0, y);
    cout << string(SCREEN_WIDTH, ' ');
    gotoxy(0, y);
}

void Menu()
{
    int menuX = SCREEN_WIDTH + 1;
    gotoxy(menuX, 0);
    cout << "Menu:";
    gotoxy(menuX, 1);
    cout << "PRESIONE LA TECLA SEGUN LA OPCION QUE DESEA USAR";
    gotoxy(menuX, 3);
    cout << "F1. TRIANGULO";
    gotoxy(menuX, 5);
    cout << "F2. CUADRADO";
    gotoxy(menuX, 7);
    cout << "F3. RECTANGULO";
    gotoxy(menuX, 9);
    cout << "F4. CIRCULO";
    gotoxy(menuX, 11);
    cout << "F5. LINEA";
    gotoxy(menuX, 13);
    cout << "F6. ROMBO";
    gotoxy(menuX, 15);
    cout << "F7. HEXAGONO";
    gotoxy(menuX, 17);
    cout << "F8. NUEVO CARACTER";
    gotoxy(menuX, 19);
    cout << "F9. LIMPIAR PANTALLA";
    gotoxy(menuX, 21);
    cout << "F10. COLOR DE CARACTER";
    gotoxy(menuX, 23);
    cout << "F12. GRABAR PANTALLA";
    gotoxy(menuX, 25);
    cout << "CTRL+A. ABRIR ARCHIVO";
    gotoxy(menuX, 27);
    cout << "ESC. Salir";
    gotoxy(menuX, 30);
    cout << "LEYENDA DE COLORES";
    gotoxy(menuX, 32);
    cout << "1:AZUL        6:AMARILLO";
    gotoxy(menuX, 34);
    cout << "2:VERDE       7:BLANCO";
    gotoxy(menuX, 36);
    cout << "3:AGUAMARINA  8:GRIS";
    gotoxy(menuX, 38);
    cout << "4:ROJO        9:AZUL CLARO";
    gotoxy(menuX, 40);
    cout << "5:PURPURA      0: NEGRO";
}

void dibujarLineaDelimitacion()
{
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        gotoxy(i, SCREEN_HEIGHT - 3);
        cout << "-";
    }
}

bool preguntarRelleno()
{
    char opcion;
    int inputY = SCREEN_HEIGHT - 1;
    gotoxy(0, inputY);
    clearLine(inputY);
    cout << "Desea dibujar con relleno? (s/n): ";
    cin >> opcion;
    clearLine(inputY);
    return (opcion == 's' || opcion == 'S');
}

void cambiarColorTexto(WORD color)
{
    SetConsoleTextAttribute(hConsole, color);
}

void mostrarMensaje(const string& mensaje, int y) {
    clearLine(y);
    gotoxy(0, y);
    cout << mensaje;
}

char preguntarOrientacion(const string& opciones)
{
    char opcion;
    int inputY = SCREEN_HEIGHT - 1;
    gotoxy(0, inputY);
    clearLine(inputY);
    cout << "Elija la orientacion (" << opciones << "): ";
    cin >> opcion;
    clearLine(inputY);
    return opcion;
}

void dibujarTriangulo(int &startX, int &startY, char cursorc, bool relleno)
{
    if (cursorc == '\0') cursorc = '*';

    int base;
    int inputY = SCREEN_HEIGHT - 2;

    mostrarMensaje("Ingrese el tamaño de la base del triángulo: ", inputY);

    while (true) {
        cin >> base;
        if (base > 0 && base <= SCREEN_WIDTH) break;
        mostrarMensaje("Valor inválido. Ingrese un tamaño válido: ", inputY);
    }

    clearLine(inputY);

    char orientacion = preguntarOrientacion("A (arriba), B (abajo), D (derecha), I (izquierda)");

    int altura = (base / 2) + 1;
    if (altura > SCREEN_HEIGHT - 3) altura = SCREEN_HEIGHT - 3;

    if (orientacion == 'A' || orientacion == 'a') {
        for (int a = 0; a < altura; a++) {
            for (int e = 0; e < base; e++) {
                if (relleno || a == altura - 1 || e == altura - a - 1 || e == altura + a - 1) {
                    if (relleno && e >= altura - a - 1 && e <= altura + a - 1) {
                        int x = (startX + e) % SCREEN_WIDTH;
                        int y = (startY + a) % (SCREEN_HEIGHT - 3);
                        if (y < SCREEN_HEIGHT - 3) {
                            gotoxy(x, y);
                            cout << cursorc;
                        }
                    } else if (!relleno) {
                        int x = (startX + e) % SCREEN_WIDTH;
                        int y = (startY + a) % (SCREEN_HEIGHT - 3);
                        if (y < SCREEN_HEIGHT - 3) {
                            gotoxy(x, y);
                            cout << cursorc;
                        }
                    }
                }
            }
        }
    } else if (orientacion == 'B' || orientacion == 'b') {
        for (int a = 0; a < altura; a++) {
            for (int e = 0; e < base; e++) {
                if (relleno || a == 0 || e == a || e == base - a - 1) {
                    if (relleno && e >= a && e <= base - a - 1) {
                        int x = (startX + e) % SCREEN_WIDTH;
                        int y = (startY + altura - a - 1) % (SCREEN_HEIGHT - 3);
                        if (y < SCREEN_HEIGHT - 3) {
                            gotoxy(x, y);
                            cout << cursorc;
                        }
                    } else if (!relleno) {
                        int x = (startX + e) % SCREEN_WIDTH;
                        int y = (startY + altura - a - 1) % (SCREEN_HEIGHT - 3);
                        if (y < SCREEN_HEIGHT - 3) {
                            gotoxy(x, y);
                            cout << cursorc;
                        }
                    }
                }
            }
        }
    } else if (orientacion == 'D' || orientacion == 'd') {
        for (int a = 0; a < base; a++) {
            for (int e = 0; e < altura; e++) {
                if (relleno || e == altura - 1 || a == altura - e - 1 || a == altura + e - 1) {
                    if (relleno && a >= altura - e - 1 && a <= altura + e - 1) {
                        int x = (startX + a) % SCREEN_WIDTH;
                        int y = (startY + e) % (SCREEN_HEIGHT - 3);
                        if (y < SCREEN_HEIGHT - 3) {
                            gotoxy(x, y);
                            cout << cursorc;
                        }
                    } else if (!relleno) {
                        int x = (startX + a) % SCREEN_WIDTH;
                        int y = (startY + e) % (SCREEN_HEIGHT - 3);
                        if (y < SCREEN_HEIGHT - 3) {
                            gotoxy(x, y);
                            cout << cursorc;
                        }
                    }
                }
            }
        }
    } else if (orientacion == 'I' || orientacion == 'i') {
        for (int a = 0; a < base; a++) {
            for (int e = 0; e < altura; e++) {
                if (relleno || e == altura - 1 || a == altura - e - 1 || a == altura + e - 1) {
                    if (relleno && a >= altura - e - 1 && a <= altura + e - 1) {
                        int x = (startX - a + SCREEN_WIDTH) % SCREEN_WIDTH;
                        int y = (startY + e) % (SCREEN_HEIGHT - 3);
                        if (y < SCREEN_HEIGHT - 3) {
                            gotoxy(x, y);
                            cout << cursorc;
                        }
                    } else if (!relleno) {
                        int x = (startX - a + SCREEN_WIDTH) % SCREEN_WIDTH;
                        int y = (startY + e) % (SCREEN_HEIGHT - 3);
                        if (y < SCREEN_HEIGHT - 3) {
                            gotoxy(x, y);
                            cout << cursorc;
                        }
                    }
                }
            }
        }
    }

    startX = (startX + base) % SCREEN_WIDTH;
    startY = (startY + altura) % (SCREEN_HEIGHT - 3);
}

void dibujarCuadrado(int &startX, int &startY, char cursorc, bool relleno)
{
    if (cursorc == '\0') cursorc = '*';

    int lado;
    int inputY = SCREEN_HEIGHT - 2;

    mostrarMensaje("Ingrese el tamaño del lado del cuadrado: ", inputY);

    while (true) {
        cin >> lado;
        if (lado > 0 && lado <= min(SCREEN_WIDTH, SCREEN_HEIGHT - 3)) break;
        mostrarMensaje("Valor inválido. Ingrese un tamaño válido: ", inputY);
    }

    clearLine(inputY);

    char orientacion = preguntarOrientacion("A (arriba), B (abajo), D (derecha), I (izquierda)");

    if (orientacion == 'A' || orientacion == 'a') {
        for (int a = 0; a < lado; ++a)
        {
            for (int e = 0; e < lado; ++e)
            {
                if (relleno || a == 0 || a == lado - 1 || e == 0 || e == lado - 1)
                {
                    int x = (startX + e) % SCREEN_WIDTH;
                    int y = (startY + a) % (SCREEN_HEIGHT - 3);
                    if (y < SCREEN_HEIGHT - 3)
                    {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    } else if (orientacion == 'B' || orientacion == 'b') {
        for (int a = 0; a < lado; ++a)
        {
            for (int e = 0; e < lado; ++e)
            {
                if (relleno || a == 0 || a == lado - 1 || e == 0 || e == lado - 1)
                {
                    int x = (startX + e) % SCREEN_WIDTH;
                    int y = (startY + lado - a - 1) % (SCREEN_HEIGHT - 3);
                    if (y < SCREEN_HEIGHT - 3)
                    {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    } else if (orientacion == 'D' || orientacion == 'd') {
        for (int a = 0; a < lado; ++a)
        {
            for (int e = 0; e < lado; ++e)
            {
                if (relleno || a == 0 || a == lado - 1 || e == 0 || e == lado - 1)
                {
                    int x = (startX + a) % SCREEN_WIDTH;
                    int y = (startY + e) % (SCREEN_HEIGHT - 3);
                    if (y < SCREEN_HEIGHT - 3)
                    {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    } else if (orientacion == 'I' || orientacion == 'i') {
        for (int a = 0; a < lado; ++a)
        {
            for (int e = 0; e < lado; ++e)
            {
                if (relleno || a == 0 || a == lado - 1 || e == 0 || e == lado - 1)
                {
                    int x = (startX - a + SCREEN_WIDTH) % SCREEN_WIDTH;
                    int y = (startY + e) % (SCREEN_HEIGHT - 3);
                    if (y < SCREEN_HEIGHT - 3)
                    {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    }

    startX = (startX + lado) % SCREEN_WIDTH;
    startY = (startY + lado) % (SCREEN_HEIGHT - 3);
}

void dibujarRectangulo(int &startX, int &startY, char cursorc, bool relleno)
{
    if (cursorc == '\0') cursorc = '*';

    int altura, ancho;
    int inputY = SCREEN_HEIGHT - 2;

    mostrarMensaje("Ingrese el tamaño de la altura del rectángulo: ", inputY);

    while (true) {
        cin >> altura;
        if (altura > 0 && altura <= SCREEN_HEIGHT - 3) break;
        mostrarMensaje("Valor inválido. Ingrese un tamaño válido: ", inputY);
    }

    clearLine(inputY);

    mostrarMensaje("Ingrese el tamaño del ancho del rectángulo: ", inputY);

    while (true) {
        cin >> ancho;
        if (ancho > 0 && ancho <= SCREEN_WIDTH) break;
        mostrarMensaje("Valor inválido. Ingrese un tamaño válido: ", inputY);
    }

    clearLine(inputY);

    char orientacion = preguntarOrientacion("A (arriba), B (abajo)");

    if (orientacion == 'A' || orientacion == 'a') {
        for (int a = 0; a < altura; a++)
        {
            for (int e = 0; e < ancho; e++)
            {
                if (relleno || a == 0 || a == altura - 1 || e == 0 || e == ancho - 1)
                {
                    int x = (startX + e) % SCREEN_WIDTH;
                    int y = (startY + a) % (SCREEN_HEIGHT - 3);
                    if (y < SCREEN_HEIGHT - 3)
                    {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    } else if (orientacion == 'B' || orientacion == 'b') {
        for (int a = 0; a < altura; a++)
        {
            for (int e = 0; e < ancho; e++)
            {
                if (relleno || a == 0 || a == altura - 1 || e == 0 || e == ancho - 1)
                {
                    int x = (startX + e) % SCREEN_WIDTH;
                    int y = (startY + altura - a - 1) % (SCREEN_HEIGHT - 3);
                    if (y < SCREEN_HEIGHT - 3)
                    {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    }

    startX = (startX + ancho) % SCREEN_WIDTH;
    startY = (startY + altura) % (SCREEN_HEIGHT - 3);
}

void dibujarCirculo(int &startX, int &startY, char cursorc, bool relleno)
{
    if (cursorc == '\0') cursorc = '*';

    int radio;
    int inputY = SCREEN_HEIGHT - 2;

    mostrarMensaje("Ingrese el radio del círculo: ", inputY);

    while (true) {
        cin >> radio;
        if (radio > 0 && radio <= min(SCREEN_WIDTH / 2, (SCREEN_HEIGHT - 3) / 2)) break;
        mostrarMensaje("Valor inválido. Ingrese un tamaño válido: ", inputY);
    }

    clearLine(inputY);

    for (int a = 0; a <= 2 * radio; a++)
    {
        for (int e = 0; e <= 2 * radio; e++)
        {
            double distancia = sqrt((a - radio) * (a - radio) + (e - radio) * (e - radio));
            if (relleno || abs(distancia - radio) < 0.5)
            {
                if (relleno && distancia <= radio)
                {
                    int x = (startX + e) % SCREEN_WIDTH;
                    int y = (startY + a) % (SCREEN_HEIGHT - 3);
                    if (y < SCREEN_HEIGHT - 3)
                    {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
                else if (!relleno)
                {
                    int x = (startX + e) % SCREEN_WIDTH;
                    int y = (startY + a) % (SCREEN_HEIGHT - 3);
                    if (y < SCREEN_HEIGHT - 3)
                    {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    }
    startX = (startX + 2 * radio) % SCREEN_WIDTH;
    startY = (startY + 2 * radio) % (SCREEN_HEIGHT - 3);
}

void dibujarLinea(int &startX, int &startY, char cursorc)
{
    if (cursorc == '\0') cursorc = '*';

    int longitud;
    int inputY = SCREEN_HEIGHT - 2;

    mostrarMensaje("Ingrese la longitud de la línea: ", inputY);

    while (true) {
        cin >> longitud;
        if (longitud > 0 && longitud <= SCREEN_WIDTH) break;
        mostrarMensaje("Valor inválido. Ingrese un tamaño válido: ", inputY);
    }

    clearLine(inputY);

    string orientacion;
    orientacion = preguntarOrientacion("A (arriba), B (abajo), D (derecha), I (izquierda)");
    if (orientacion == "A" || orientacion == "a") {
        for (int i = 0; i < longitud; ++i) {
            int x = startX;
            int y = (startY - i + SCREEN_HEIGHT - 3) % (SCREEN_HEIGHT - 3);
            gotoxy(x, y);
            cout << cursorc;
        }
    } else if (orientacion == "B" || orientacion == "b") {
        for (int i = 0; i < longitud; ++i) {
            int x = startX;
            int y = (startY + i) % (SCREEN_HEIGHT - 3);
            gotoxy(x, y);
            cout << cursorc;
        }
    } else if (orientacion == "D" || orientacion == "d") {
        for (int i = 0; i < longitud; ++i) {
            int x = (startX + i) % SCREEN_WIDTH;
            int y = startY;
            gotoxy(x, y);
            cout << cursorc;
        }
    } else if (orientacion == "I" || orientacion == "i") {
        for (int i = 0; i < longitud; ++i) {
            int x = (startX - i + SCREEN_WIDTH) % SCREEN_WIDTH;
            int y = startY;
            gotoxy(x, y);
            cout << cursorc;
        }

    }

    startX = (startX + longitud) % SCREEN_WIDTH;
}

void dibujarRombo(int &startX, int &startY, char cursorc, bool relleno)
{
    if (cursorc == '\0') cursorc = '*';

    int diagonal;
    int inputY = SCREEN_HEIGHT - 2;

    mostrarMensaje("Ingrese el tamaño de la diagonal del rombo: ", inputY);

    while (true) {
        cin >> diagonal;
        if (diagonal > 0 && diagonal <= SCREEN_WIDTH) break;
        mostrarMensaje("Valor inválido. Ingrese un tamaño válido: ", inputY);
    }

    clearLine(inputY);

    char orientacion = preguntarOrientacion("A (arriba), B (abajo)");

    int altura = diagonal / 2;

    if (orientacion == 'A' || orientacion == 'a') {
        for (int i = -altura; i <= altura; i++) {
            for (int j = -altura; j <= altura; j++) {
                if (relleno || abs(i) + abs(j) == altura) {
                    int x = (startX + j) % SCREEN_WIDTH;
                    int y = (startY + i) % (SCREEN_HEIGHT - 3);
                    if (x >= 0 && y >= 0 && y < SCREEN_HEIGHT - 3) {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    } else if (orientacion == 'B' || orientacion == 'b') {
        for (int i = -altura; i <= altura; i++) {
            for (int j = -altura; j <= altura; j++) {
                if (relleno || abs(i) + abs(j) == altura) {
                    int x = (startX + j) % SCREEN_WIDTH;
                    int y = (startY + altura - abs(i)) % (SCREEN_HEIGHT - 3);
                    if (x >= 0 && y >= 0 && y < SCREEN_HEIGHT - 3) {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    }

    startX = (startX + diagonal) % SCREEN_WIDTH;
    startY = (startY + altura) % (SCREEN_HEIGHT - 3);
}

void dibujarHexagono(int &startX, int &startY, char cursorc, bool relleno)
{
    if (cursorc == '\0') cursorc = '*';

    int lado;
    int inputY = SCREEN_HEIGHT - 2;

    mostrarMensaje("Ingrese el tamaño del lado del hexágono: ", inputY);

    while (true) {
        cin >> lado;
        if (lado > 0 && lado <= min(SCREEN_WIDTH / 2, (SCREEN_HEIGHT - 3) / 2)) break;
        mostrarMensaje("Valor inválido. Ingrese un tamaño válido: ", inputY);
    }

    clearLine(inputY);

    char orientacion = preguntarOrientacion("V (vertical), H (horizontal)");

    int altura = 2 * lado;
    int ancho = 2 * lado;
    int centroY = startY;

    if (orientacion == 'V' || orientacion == 'v') {
        for (int i = 0; i < altura; i++) {
            int fila = (i < lado) ? i : (altura - i - 1);
            int espacios = lado - fila - 1;
            for (int j = -lado + espacios + 1; j < lado - espacios; j++) {
                if (relleno || j == -lado + espacios + 1 || j == lado - espacios - 1) {
                    int x = (startX + j + lado - 1) % SCREEN_WIDTH;
                    int y = (centroY + i - lado) % (SCREEN_HEIGHT - 3);
                    if (x >= 0 && y >= 0 && y < SCREEN_HEIGHT - 3) {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    } else if (orientacion == 'H' || orientacion == 'h') {
        for (int i = 0; i < ancho; i++) {
            int columna = (i < lado) ? i : (ancho - i - 1);
            int espacios = lado - columna - 1;
            for (int j = -lado + espacios + 1; j < lado - espacios; j++) {
                if (relleno || j == -lado + espacios + 1 || j == lado - espacios - 1) {
                    int x = (startX + i) % SCREEN_WIDTH;
                    int y = (centroY + j + lado - 1) % (SCREEN_HEIGHT - 3);
                    if (x >= 0 && y >= 0 && y < SCREEN_HEIGHT - 3) {
                        gotoxy(x, y);
                        cout << cursorc;
                    }
                }
            }
        }
    }

    startX = (startX + ancho) % SCREEN_WIDTH;
    startY = (startY + altura) % (SCREEN_HEIGHT - 3);
}

void cambiarCaracter(char &cursorc)
{
    int inputY = SCREEN_HEIGHT - 2;

    gotoxy(0, inputY);
    clearLine(inputY);
    cout << "Ingrese el nuevo caracter para dibujar figuras: ";
    cin >> cursorc;
    clearLine(inputY);
}

void nuevoCaracter(int x, int y, char &cursorc)
{
    int inputY = SCREEN_HEIGHT - 2;

    gotoxy(0, inputY);
    clearLine(inputY);
    cout << "Ingrese el caracter a mostrar: ";
    cin >> cursorc;
    clearLine(inputY);
}

void limpiarPantalla()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 0xF0);
    Menu();
    dibujarLineaDelimitacion();
}

char getCharAtPosition(int x, int y)
{
    CHAR_INFO charInfo;
    COORD bufferSize = {1, 1};
    COORD bufferCoord = {0, 0};
    SMALL_RECT readRegion = {x, y, x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!ReadConsoleOutput(hConsole, &charInfo, bufferSize, bufferCoord, &readRegion))
    {
        return ' ';
    }
    return charInfo.Char.AsciiChar;
}

void configurarConsola()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 16;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void guardarPantalla()
{
    CHAR_INFO buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
    COORD bufferSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
    COORD bufferCoord = {0, 0};
    SMALL_RECT readRegion = {0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1};

    if (!ReadConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &readRegion))
    {
        cout << "Error al leer la salida de la consola." << endl;
        return;
    }

    // Obtener la ruta del escritorio
    char desktopPath[MAX_PATH];
    if (FAILED(SHGetFolderPathA(NULL, CSIDL_DESKTOP, NULL, 0, desktopPath)))
    {
        cout << "Error al obtener la ruta del escritorio." << endl;
        return;
    }
    string filePath = string(desktopPath) + "\\pantalla.txt";

    ofstream outFile(filePath.c_str());
    if (!outFile)
    {
        cout << "Error al abrir el archivo para escribir." << endl;
        return;
    }

    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            outFile << buffer[x + y * SCREEN_WIDTH].Char.AsciiChar;
        }
        outFile << endl;
    }

    outFile.close();
    cout << "Pantalla guardada en " << filePath << endl;
}

void abrirArchivo()
{
    string filePath;
    int inputY = SCREEN_HEIGHT - 2;

    mostrarMensaje("Ingrese la ruta del archivo a abrir: ", inputY);
    cin >> filePath;
    clearLine(inputY);

    ifstream inFile(filePath.c_str());
    if (!inFile)
    {
        mostrarMensaje("Error al abrir el archivo.", inputY);
        return;
    }

    string line;
    int y = 0;
    while (getline(inFile, line) && y < SCREEN_HEIGHT - 3)
    {
        gotoxy(0, y);
        cout << line.substr(0, SCREEN_WIDTH);
        y++;
    }

    inFile.close();
    mostrarMensaje("Archivo cargado correctamente.", inputY);
}

int main()
{
    configurarConsola();
    maximizarConsola();

    int x = 0, y = 0;
    int prevX = x, prevY = y;
    char cursorc = '*';

    setConsoleSize(SCREEN_WIDTH + MENU_WIDTH, SCREEN_HEIGHT);
    system("cls");
    system("color F0");
    Menu();
    dibujarLineaDelimitacion();
    gotoxy(x, y);
    cout << cursorc;

    WORD colorActual = 0xF0;

    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            gotoxy(prevX, prevY);
            if (getCharAtPosition(prevX, prevY) == cursorc)
                cout << " ";

            prevX = x;
            prevY = y;

            x--;
            if (x < 0) x = SCREEN_WIDTH - 1;

            gotoxy(x, y);
            if (getCharAtPosition(x, y) == ' ')
                cout << cursorc;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            gotoxy(prevX, prevY);
            if (getCharAtPosition(prevX, prevY) == cursorc)
                cout << " ";

            prevX = x;
            prevY = y;

            x++;
            if (x >= SCREEN_WIDTH) x = 0;

            gotoxy(x, y);
            if (getCharAtPosition(x, y) == ' ')
                cout << cursorc;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            gotoxy(prevX, prevY);
            if (getCharAtPosition(prevX, prevY) == cursorc)
                cout << " ";

            prevX = x;
            prevY = y;

            y++;
            if (y >= SCREEN_HEIGHT - 3) y = 0;

            gotoxy(x, y);
            if (getCharAtPosition(x, y) == ' ')
                cout << cursorc;
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            gotoxy(prevX, prevY);
            if (getCharAtPosition(prevX, prevY) == cursorc)
                cout << " ";

            prevX = x;
            prevY = y;

            y--;
            if (y < 0) y = SCREEN_HEIGHT - 4;

            gotoxy(x, y);
            if (getCharAtPosition(x, y) == ' ')
                cout << cursorc;
        }

        if (GetAsyncKeyState(VK_F1) & 0x8000) {cambiarColorTexto(colorActual); dibujarTriangulo(x, y, cursorc, preguntarRelleno()); Sleep(200);}
        if (GetAsyncKeyState(VK_F2) & 0x8000) {cambiarColorTexto(colorActual); dibujarCuadrado(x, y, cursorc, preguntarRelleno()); Sleep(200);}
        if (GetAsyncKeyState(VK_F3) & 0x8000) {cambiarColorTexto(colorActual); dibujarRectangulo(x, y, cursorc, preguntarRelleno()); Sleep(200);}
        if (GetAsyncKeyState(VK_F4) & 0x8000) {cambiarColorTexto(colorActual); dibujarCirculo(x, y, cursorc, preguntarRelleno()); Sleep(200);}
        if (GetAsyncKeyState(VK_F5) & 0x8000) {cambiarColorTexto(colorActual); dibujarLinea(x, y, cursorc); Sleep(200);}
        if (GetAsyncKeyState(VK_F6) & 0x8000) {cambiarColorTexto(colorActual); dibujarRombo(x, y, cursorc, preguntarRelleno()); Sleep(200);}
        if (GetAsyncKeyState(VK_F7) & 0x8000) {cambiarColorTexto(colorActual); dibujarHexagono(x, y, cursorc, preguntarRelleno()); Sleep(200);}
        if (GetAsyncKeyState(VK_F8) & 0x8000) {cambiarColorTexto(colorActual); cambiarCaracter(cursorc); Sleep(200);}
        if (GetAsyncKeyState(VK_F9) & 0x8000) limpiarPantalla();
        if (GetAsyncKeyState(VK_F10) & 0x8000)
        {
            char color;
            int inputY = SCREEN_HEIGHT - 2;

            gotoxy(0, inputY);
            clearLine(inputY);
            cout << "Ingrese el código del color del texto ( 0-9 ): ";
            cin >> color;
            clearLine(inputY);

            colorActual = 0xF0 | (isdigit(color) ? color - '0' : toupper(color) - 'A' + 10);
        }
        if (GetAsyncKeyState(VK_F12) & 0x8000) {guardarPantalla(); Sleep(200);}
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState('A') & 0x8000) {abrirArchivo(); Sleep(200);}
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;

        Sleep(100);
    }
    return 0;
}


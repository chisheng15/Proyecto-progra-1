#include <iostream>
using namespace std;

int main()
{
    int lado;
    cout<<"ingrese el tamaño de un lado del cuadrado"<<endl;
    cin>>lado;
     for (int a=0; a<lado;++a)
        {
        for (int e=0; e<lado;++e)
            {
            if (a==0||a==lado-1||e==0||e==lado-1)
            {
                cout<< "* ";
            }
            else
            {
                cout << "* ";
            }

            }
        cout<<endl;
        }
return 0;
}

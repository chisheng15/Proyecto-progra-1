#include <iostream>

using namespace std;

int main()
{
    int base,altura;
    cout<<"ingrese la base del triagulo que desea dibujar"<<endl;
    cin>>base;
    if (base % 2 == 0)
    {
        base=base-1;
    }
    altura=base/2+1;

    for (int a=1; a<=altura; a++)
    {
        for (int e=0;e<=base;e++)
        {
            if(e>=altura-a+1 && e<=altura+a-1)
                {
                cout<<"*";
                }
            else
                {
                cout<<" ";
                }
        }
        cout<<endl;
    }
    return 0;
}

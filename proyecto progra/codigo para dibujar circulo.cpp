#include <iostream>
#include <cmath>
using namespace std;

int main()
{
int radio,centro;
cout<<"Ingrese su radio"<<endl;
cin>>radio;
centro=radio;
for(int a=0; a<=2*radio; a++)
    {
    for(int e=0; e<=2 * radio; e++)
        {
        double distancia =sqrt((a-radio)*(a-radio)+(e-radio)*(e-radio));
        if (distancia<=radio+0.05)
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

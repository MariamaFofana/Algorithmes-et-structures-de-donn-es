#include <iostream>
using namespace std;
// un algorithme pour calculer l'aire de l'intersection de deux intervalles
int main(){
    int a1, b1, a2, b2, resultat;
    cin>> a1 >> b1>> a2>> b2;
    resultat=b1-a2;
    if (resultat<0){
        cout<< 0<<"\r\n";
    }else{
        cout<<resultat<<"\r\n";
    }
     if (a2>a1 || b2>b1){
        cout<< b1-a2<<"\r\n";
    }else if(a2<a1 || b2<b1){
        cout<<b2-a2<<"\r\n";
    }else if(a2>a1 || b2<b1){
        cout<<b2-a2<<"\r\n";
    }
     return 0;
}
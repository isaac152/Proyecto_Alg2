#include <iostream>
#include "base64.cpp"
using namespace std;

int main(){
    string a=base64_encode("alg204008",true);
    cout<<a<<endl;
    cout<<base64_decode(a,true)<<endl;
    return 0;
}
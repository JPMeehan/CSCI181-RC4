#include <iostream>
#include <cmath>
#include <array>

using namespace std;

void subA(uint32_t x, uint32_t y, bool a[]);// outputs array of length x w/ bin rep of y
uint32_t subB(bool a[], uint8_t l);// takes array and outputs the integer whose binary representation is the array
void rc4(uint32_t n, uint32_t l, uint32_t k[], bool out[]);

int main()
{
    uint32_t n=8, l=28;
    uint32_t u=(1 << n);
    uint32_t k[u];
    bool a[80] = {1, 0, 1, 1, 1, 0, 0, 1 , 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1};
    for (int i=0; i<10; i++){
        bool b[8];
        for (int j=0; j<8;j++)
            b[j] = a[i*8+j];
            k[i] = subB(b, 8);
    }
    for (int i=10; i<u; i++){
        k[i] = k[i-10];
    }
//    uint32_t k[u] = {3,1,4,1,5,3,1,4};
    u = n*l;
    bool out[u];
    for (uint32_t i=0; i<u;i++)
        out[i] = 0;
    rc4(n,l,k,out);
    for (int i=0; i<u;i++)
        cout << out[i];
    cout << endl;
    bool c[u]  = {1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0};
    for (uint32_t i=0; i<(n*l); i++){
        if (out[i] != c[i])
            cout << 1;
        else
            cout << 0;
    }
    cout << endl;
    return 0;
}

/*
j = 0
for i=0 to 2^n-1
    s[i] = i
for i=0 to 2^n-1
    j=j+s[i]+k[i] mod 2^n
    swap(s[i],s[j])
i=0,j=0
// generating l random n bit strings
for r=0 to l-1
    i = i+1 mod 2^n
    j = j + s[i] mod 2^n
    t = s[i] + s[j] mod 2^n
    KS[r] = s[t]
Then convert KS[0] to KS[l-1] into the key stream
*/

void rc4(uint32_t n, uint32_t l, uint32_t k[], bool out[]){
    uint32_t i=0, j = 0, u = (1 << n);
    uint32_t s[u];
//    cout << u << endl;
    for (i = 0; i<u; i++){
        s[i] = i;
    }
    for (i = 0; i<u; i++){
        j = j + s[i] + k[i];
        while (j>=u)
            j-=u;
        swap(s[i],s[j]);
    }
//    for (i=0; i<u;i++)
//        cout << s[i];
//    cout << endl;
    i = 0, j = 0;
    uint32_t r,t;
    uint32_t KS[l];
    for (r = 0; r<l;r++){
        i = ++i % u;
        j = (j + s[i]) % u;
        swap(s[i],s[j]);
        t = (s[i] + s[j]) % u;
        KS[r] = s[t];
//        for (i=0; i<u;i++)
//            cout << s[i];
//        cout << endl;
    }

//    for (r=0; r<l;r++)
//        cout << KS[r];
//    cout << endl;
    r=0;
    for (i = 0; i<l; i++){
        r = KS[i];
        bool a[n];
        subA(n, r, a);
        for (j = 0; j<n; j++){
//            cout << a[j] << ' ' << j + i*n << endl;
            out[j + i*n] = a[j];
        }
        //cout << i << endl;
    }
    return;
}

void subA(uint32_t x, uint32_t y, bool a[]){// outputs array of length x w/ bin rep of y
    if ((1 << x) < y){
        cout << "y is too large to fit in the array" << endl;
        return;
    }
    uint32_t i=0,j=0;
    for (i = 0; i<x; i++){
        j = 1 << (x-i-1);
        if (j <= y){
            y-=j;
            a[i] = 1;
        }
        else
            a[i] = 0;
    }
    return;
}
uint32_t subB(bool a[], uint8_t l){// takes array and outputs the integer whose binary representation is the array
    uint32_t out=0;
    for (int i = 0; i < l; ++i){
        if (a[i] == true){
//            cout << (1 << (l-i-1)) << endl;
            out += (1 << (l-i-1));
        }
    }
    return out;
}

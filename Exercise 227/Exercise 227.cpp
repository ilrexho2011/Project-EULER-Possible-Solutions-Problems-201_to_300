#include<iostream>

const int N = 100;

using namespace std;

void put(int i, const char* s){
        if (!i) return;
        if (i == -1){
                put(1, s);
                return;
        }
        if (i == -2){
                put(2, s);
                return;
        }
        if (i == N/2 + 1){
                put(N/2-1, s);
                return;
        }
        if (i == N/2 + 2){
                put(N/2 - 2, s);
                return;
        }

        cout << s << i;
}

void gen(){
        cout << "var('";
        for (int i = 1; i < N/2; i++)
                cout << "t" << i << ", ";
        cout << "t" << N/2 << "');\n";

        cout << "eq=[";
        for (int i = 1; i <= N/2; i++){
                cout << "1/2*t" << i << " == 1";
                put(i-1, " + 8/36*t");
                put(i+1, " + 8/36*t");
                put(i-2, " + 1/36*t");
                put(i+2, " + 1/36*t");
                if (i != N/2) cout <<", ";
        }
        cout << "]\nsolve(eq";
        for (int i = 1; i <= N/2; i++)
                cout << ", t" << i;
        cout << ")\n";
}


int main(){
        gen();
}
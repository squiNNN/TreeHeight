#include<bits/stdc++.h>
using namespace std;
#define MAX 1000000

int main(){
    srand(std::time(nullptr));
    string filename[] = {"Test01.txt","Test02.txt","Test03.txt","Test04.txt","Test05.txt","Test06.txt","Test07.txt","Test08.txt","Test09.txt","Test10.txt"};


    for (int i = 0; i < 10; i++){
        ofstream gene(filename[i]);
        for(int i = 0; i < MAX; i++){
            double random_number = double(rand()) + static_cast<double>(rand()) / RAND_MAX;
            gene << setprecision(2) << fixed << random_number <<'\n';
        }

        // for (int i = 0; i < 1000000; i++) {
        //     int randomNum = rand(); // Generate random integer between 0 and 999
        //     gene << randomNum << '\n';
        // }

        gene.close();
    }

    for (int i = 0; i < 1000000; i++) {
        int randomNum = rand(); // Generate random integer between 0 and 999
        
    }
}
#include <iostream>
#include <vector>

void print(std::vector <int> a){
    std::cout << "[";
    for(std::size_t i = 0; i < a.size(); i++){
        if(i == a.size() - 1){
            std::cout << a[i] << "]";
        } else{
            std::cout << a[i] << ", ";
        }
    }

    std::cout << std::endl;
}

int main(){
    //std::vector <int> pole = {1, 2, 3};

    /*
    for(int i = 0; i < pole.size(); i++){
        std::cout << pole[i];
    }
    

    for(int a : pole){
        std::cout << a;
    }
    */
   std::vector <int> a = {1, 2, 3, 4, 5};
   print(a);
}
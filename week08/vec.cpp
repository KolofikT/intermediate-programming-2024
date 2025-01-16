#include <iostream>
#include <vector>

void print(std::vector<int> data) {
    if (data.size() == 0) {
        std::cout << "[]";
        return;
    }

    std::cout << "[ ";
    for (std::size_t i = 0; i < data.size() - 1; i++) {
        std::cout << data[i] << ", ";
    }

    std::cout << data.back() << " ]" << std::endl;
}

void print2(std::vector<std::vector<int>> vec){
    std::cout << "{" << std::endl;

    for(std::vector<int> a : vec){
        std::cout << " ";
        print(a);
        std::cout << std::endl;
    }

    std::cout << "}" << std::endl;
}


int suma(std::vector<int> data){
    int sumsum = 0;
    for(int e : data){
        sumsum += e;
    }
    return sumsum;
}

std::vector<int> sum(std::vector<std::vector<int>> vec) {
    // {{0, 1}, {2}, {}} -> {1, 2, 0}
    std::vector<int> data;
    for(std::vector<int> a : vec){
        data.push_back(suma(a));
    }
    //std::cout << data << std::endl;
    return data;
}

int multiple(std::vector<int> data){
    int multi = 1;
    for(int e : data){
        multi *= e;
    }
    return multi;
}


std::vector<int> product(std::vector<std::vector<int>> vec) {
    // {{0, 1}, {2}, {}} -> {0, 2, 1}
    std::vector<int> data;
    for(std::vector<int> a : vec){
        data.push_back(multiple(a));
    }
    return data;
}


std::vector<int> concat(std::vector<std::vector<int>> vec) {
    // {{0, 1}, {2}, {}} -> {0, 1, 2}
        std::vector<int> data;
    for(std::vector<int> a : vec){
        for(int b : a){
        data.push_back(b);
        }
    }
    return data;
}



std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> vec) {
    // {
    //   {0, 1, 2},
    //   {3, 4, 5},
    //   {6, 7, 8},
    // } -> {
    //   {0, 3, 6},
    //   {1, 4, 7},
    //   {2, 5, 8},
    // }
    std::vector<std::vector<int>> data;
    data.resize(vec.size());
    for(std::vector<int> a : vec){
        for(std::size_t i = 0; i < a.size(); i++){
            
        }
    }
    
    return data;
}



int main(){
    std::vector<std::vector<int>> a {{0, 1}, {2}};
    std::vector<int> b {1, 6, 9, 13, 8};
    std::vector<std::vector<int>> c = {{0, 1}, {2}, {}};
    std::vector<std::vector<int>> d = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8} };
    print(b);
    print2(a);
    print(sum(c));
    print(product(c));
    print(concat(c));
    print2(transpose(d));
}
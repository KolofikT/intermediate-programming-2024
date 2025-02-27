#include <iostream>
#include <string>
#include <vector>

int sum(int a, int b) {
    return a + b;
}

std::string sum(std::string a, std::string b) {
    return a + b;
}

int sum(std::vector<int> xs) {
    int suma = 0;
    for(int e : xs){
       suma += e; 
    }
    return suma;
}

std::string sum(std::vector<std::string> xs) {
    std::string suma;
    for(std::string a : xs){
        suma += a;
    }
    return suma;
}

int mul(int a, int b) {
    return a * b;
}

std::string mul(int a, std::string b) {
    std::string multi;
    for(int i = 0; i < a; i++){
        multi += b;
    }
    return multi;
}

int main() {
    std::cout << "sum(3, 4): " << sum(3, 4) << "\n"; // 7
    std::cout << R"(sum("Hello, ", "World!"): )" << sum("Hello, ", "World!") << "\n"; // Hello, World!
    std::cout << "sum({1, 2, 3, 4, 5}): " << sum(std::vector<int>{1, 2, 3, 4, 5}) << "\n"; // 15
    std::cout << R"(sum({"abc", "def", "ghi"}): )" << sum(std::vector<std::string>{"abc", "def", "ghi"}) << "\n"; // abcdefghi

    std::cout << "mul(3, 5): " << mul(3, 5) << "\n"; // 15
    std::cout << R"(mul(3, "Hi"): )" << mul(3, "Hi") << "\n"; // HiHiHi

    return 0;
}


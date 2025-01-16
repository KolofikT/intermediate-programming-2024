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

    std::cout << data.back() << " ]";
}


/*
 * Napište funkci merge, která vezme dvě vzestupně seřazená pole a spojí je do jednoho
 * vzestupně seřazeného seznamu
 * */
std::vector<int> merge(std::vector<int> a, std::vector<int> b) {
    std::vector<int> vector;
    int size = a.size() + b.size();
    int av = 0;
    int bv = 0;
    //std::cout << size;
    for(int i = 0; i < size; i++){
        if (a[av] <= b[bv]){
            vector.push_back(a[av]);
            av++;
        } else {
            vector.push_back(b[bv]);
            bv++;
        }
    }
    return vector;
}

/* Napište funkci histogram, která dostane pole čísel z rozsahu [0-100), a vrátí nové pole takové, že
 * na i-té pozici nového seznamu bude uložen počet výskytů čísla i ve vstupním poli.
 */
std::vector<int> histogram(std::vector<int> data) {
    int size = data.size();
    std::vector<int> vector;
    int count = 0;
    for(int i = 0; i < size; i++){
        for(int f = 0; f < size; f++){
            if(data[f] == i){
                count++;
            }
        }
        vector.push_back(count);
        count = 0;
    }
    return vector;
}

// Napište (čistou) funkci, která simuluje jeden krok výpočtu
// jednorozměrného buněčného automatu (cellular automaton). My se
// omezíme na «binární» (buňky nabývají hodnot 0 a 1) «jednorozměrný»
// automat s «konečným stavem»: stav takového automatu je seznam
// jedniček a nul, například:
//
//   ┌───┬───┬───┬───┬───┬───┬───┐
//   │ 0 │ 1 │ 1 │ 1 │ 0 │ 0 │ 1 │
//   └───┴───┴───┴───┴───┴───┴───┘
//
// Protože obecný automat tohoto typu je stále relativně složitý,
// budeme implementovat automat s fixní sadou pravidel:
//
// │‹old[i - 1]›│‹old[i]›│‹old[i + 1]›│‹new[i]›│
// ├┄┄┄┄┄┄┄┄┄┄┄┄┼┄┄┄┄┄┄┄┄┼┄┄┄┄┄┄┄┄┄┄┄┄│┄┄┄┄┄┄┄┄│
// │     0      │    0   │      1     │    1   │
// │     1      │    0   │      0     │    1   │
// │     1      │    0   │      1     │    1   │
// │     1      │    1   │      0     │    0   │
// │     1      │    1   │      1     │    0   │
//
// Pravidla určují, jakou hodnotu bude mít buňka v následujícím
// stavu, v závislosti na několika okolních buňkách stavu nynějšího
// (konkrétní indexy viz tabulka). Neexistuje-li pro danou vstupní
// kombinaci pravidlo, do nového stavu přepíšeme stávající hodnotu
// buňky. Na krajích stavu interpretujeme chybějící políčko vždy
// jako nulu.
//
// Výpočet s touto sadou pravidel tedy funguje takto:
//
//   ┌───┬───┬───┬───┬───┬───┐ 001 → 1 ┌───┬───┬───┬───┬───┬───┐
//   │░0░│░1░│ 1 │ 0 │ 0 │ 1 │────────▶│░1 │   │   │   │   │   │
//   └───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
//   ┌───┬───┬───┬───┬───┬───┐ 011 → ? ┌───┬───┬───┬───┬───┬───┐
//   │░0░│░1░│░1░│ 0 │ 0 │ 1 │────────▶│ 1 │░1 │   │   │   │   │
//   └───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
//   ┌───┬───┬───┬───┬───┬───┐ 110 → 0 ┌───┬───┬───┬───┬───┬───┐
//   │ 0 │░1░│░1░│░0░│ 0 │ 1 │────────▶│ 1 │ 1 │░0░│   │   │   │
//   └───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
//   ┌───┬───┬───┬───┬───┬───┐ 100 → 1 ┌───┬───┬───┬───┬───┬───┐
//   │ 0 │ 1 │░1░│░0░│░0░│ 1 │────────▶│ 1 │ 1 │ 0 │░1░│   │   │
//   └───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
//   ┌───┬───┬───┬───┬───┬───┐ 001 → 1 ┌───┬───┬───┬───┬───┬───┐
//   │ 0 │ 1 │ 1 │░0░│░0░│░1░│────────▶│ 1 │ 1 │ 0 │ 1 │░1░│   │
//   └───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
//   ┌───┬───┬───┬───┬───┬───┐ 010 → ? ┌───┬───┬───┬───┬───┬───┐
//   │ 0 │ 1 │ 1 │ 0 │░0░│░1░│────────▶│ 1 │ 1 │ 0 │ 1 │ 1 │░1░│
//   └───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
//
// Na vstupu dostanete stav (konfiguraci) ‹state›, výstupem funkce je
// nový seznam, který obsahuje stav vzniklý aplikací výše uvedených
// pravidel na ‹state›.

std::vector<bool> cellular_step(std::vector<bool> input) {
    return input;
}

int main() {
    std::vector<int> vec1 = { 1, 9, 4, 8, 4, 0, 9, 2, 3, 5, 6 };
    std::vector<int> asc1 = { 0, 2, 4, 7, 8 };
    std::vector<int> asc2 = { 1, 3, 5, 6, 7, 9 };
    std::vector<int> vec2 = { 43, 93, 76, 49, 11,  7, 70, 20, 43, 36,
                              73, 47, 77, 48, 91, 46, 31, 78, 63, 61,
                               7, 88, 42, 62, 84, 29, 61, 28, 18, 41,
                              93, 90, 13, 27, 19, 50, 61, 73, 55, 64,
                              45, 75, 28, 64, 51, 49, 44, 64, 60, 29,
                              53, 86, 81, 50, 31, 14, 69, 92, 23, 88,
                              15, 21, 54, 33, 15, 31, 77, 43, 21, 13,
                              45, 95,  3, 13, 28, 44, 21, 27, 13, 55,
                               8, 13, 19, 95, 78, 43, 91, 89, 54, 73,
                              32, 81, 27, 94, 73, 73, 97, 70, 68, 27,
                              53, 61, 92, 24, 49, 66, 82, 55, 49, 13,
                              92, 64, 92, 88, 91, 32, 17, 71, 26, 61,
                              93, 59, 89, 87, 42, 77, 17, 60,  7, 49,
                              22, 36,  6, 51, 86, 35, 87, 37, 53, 77,
                               1,  7, 24, 93, 38, 40, 44, 75, 16,  6,
                              76, 20, 91, 89, 72, 94, 24, 95,  5, 26,
                              47, 88,  2, 40, 42, 72, 74, 33,  8,  6,
                              64,  2, 24, 64, 66,  8, 84, 68, 17, 91,
                              77, 10, 51, 84, 20, 55, 82,  4, 36, 32,
                               0, 36, 60, 98, 16, 83, 12, 72,  5, 45,
                               1, 27, 34, 67, 71, 98, 49, 46, 36, 79,
                              91, 10,  2, 34, 80, 80, 17, 98,  9, 42,
                              87, 62,  4,  3, 91, 22, 45, 60, 77, 63,
                              24, 61, 79, 27, 23, 51, 45, 20, 89, 64,
                               0, 40, 14, 81, 34, 44,  7, 25, 49, 79,
                              22, 50, 52,  2, 22, 58, 77, 62, 73, 19,
                              24, 74, 38, 32, 54, 74, 30, 27, 71, 52,
                              63, 28,  4, 64, 49, 12, 87, 41, 38, 15,
                               1, 98, 10, 67,  2, 76, 63, 48, 32, 20,
                               3, 23, 41, 14, 67, 98, 95, 66, 86, 90 };
    std::cout << "merge(asc1, asc2): ";
    print(merge(asc1, asc2));
    std::cout << std::endl;

    std::cout << "histogram(vec2): ";
    print(histogram(vec2));
    std::cout << std::endl;
}

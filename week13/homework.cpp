#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <tuple>
#include <cassert>

// Konstanty pro typ záznamu
bool ENTRY = true;
bool LEAVE = false;

// V tomto příkladu budeme pracovat se systémem docházky jedné
// fiktivní firmy. Při příchodu do práce si musí každý zaměstnanec
// pípnout kartičkou u vchodu a zaznamenat tak svůj příchod. Při
// odchodu zase stejně musí zaznamenat, že z práce odešel.
//
// Čidlo u dveří pak do firemního systému zaznamená data o docházce
// zaměstnance. Každý záznam je trojice obsahující kód zaměstnance,
// časovou známku a typ záznamu - příchod nebo odchod.
//
// Bohužel, někteří zaměstnanci zapomínají zaznamenávat svou
// docházku. Vaším úkolem je napsat čistou funkci
// `employees_with_missing_records`, která projde seznam záznamů, a
// vrátí množinu obsahující kódy těch zaměstnanců, pro které existuje
// v seznamu nějaká nesrovnalost – buď z práce odešli, aniž by do ní
// přišli, nebo přišli do práce vícekrát bez záznamu oodchodu.
// Seznam záznamů začíná vsituaci, kdy žádný zaměstnanec vpráci není.
// Můžete počítat stím, že seznam je seřazený podle času od
// nejstaršího záznamu po nejnovější.

std::set<std::string> employees_with_missing_records(std::vector<std::tuple<std::string, int, bool>> records) {
    return {};
}

void main_test() {
    std::string id1 = "abc00001";
    std::string id2 = "xyz00002";
    std::string id3 = "hjkl0003";

    std::tuple<std::string, int, bool> e1 = {id1, 100, ENTRY};
    std::tuple<std::string, int, bool> e2 = {id2, 110, ENTRY};
    std::tuple<std::string, int, bool> e3 = {id3, 140, ENTRY};
    std::tuple<std::string, int, bool> e4 = {id1, 200, ENTRY};
    std::tuple<std::string, int, bool> e5 = {id1, 300, ENTRY};

    std::tuple<std::string, int, bool> l1 = {id1, 150, LEAVE};
    std::tuple<std::string, int, bool> l2 = {id2, 160, LEAVE};
    std::tuple<std::string, int, bool> l3 = {id3, 210, LEAVE};
    std::tuple<std::string, int, bool> l4 = {id1, 250, LEAVE};
    std::tuple<std::string, int, bool> l5 = {id2, 270, LEAVE};

    // no missing records
    std::set<std::string> m1 = employees_with_missing_records({});
    assert(m1.empty());

    std::set<std::string> m2 = employees_with_missing_records({e1, l1});
    assert(m2.empty());

    std::set<std::string> m3 = employees_with_missing_records({e1, e2, l1, l2, e4});
    assert(m3.empty());

    std::set<std::string> m4 = employees_with_missing_records({e1, e3, l1, e4, l3, l4});
    assert(m4.empty());

    // missing records
    std::set<std::string> m5 = employees_with_missing_records({e1, l1, e4, e5});
    assert(m5.size() == 1);
    assert(m5.count(id1));

    std::set<std::string> m6 = employees_with_missing_records({e1, e2, l1, l2, l5});
    assert(m6.size() == 1);
    assert(m6.count(id2));

    std::set<std::string> m7 = employees_with_missing_records({e1, e4, l5});
    assert(m7.size() == 2);
    assert(m7.count(id1));
    assert(m7.count(id2));
}

int main() {
    main_test();
    std::cout << "Všechny testy proběhly úspěšně.\n";
    return 0;
}
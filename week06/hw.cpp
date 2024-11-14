#include <cassert>
#include <iostream>
#include <cmath>
// TODO: doplťe co potřebujete


// Implementujte funkci ‹power_digit_sum›, která vrátí „speciální“
// ciferný součet čísla ‹number›, který se od běžného ciferného
// součtu liší tím, že každou cifru před přičtením umocníme na číslo
// její pozice. Pozice číslujeme zleva, přičemž první má číslo 1.
// Vstupem funkce ‹power_digit_sum› bude libovolné nezáporné celé
// číslo, na výstupu se očekává celé číslo. Výpočet budeme provádět
// v číselné soustavě se základem 7.
// Příklad: Číslo ⟦1234⟧ zapíšeme v sedmičkové soustavě jako
// ⟦(3412)₇⟧ – skutečně, ⟦3⋅7³ + 4⋅7² + 1⋅7¹ + 2⋅7⁰ = 1029 + 196 + 7
// + 2 = 1234⟧.  Proto ‹power_digit_sum(1234)› získáme jako ⟦3¹ + 4²
// + 1³ + 2⁴ = 36⟧.


int power_digit_sum(int number){

    int power = 0;
    int position = 0;
    int number7 = 0;
    while(number > 0){
        int remainder = number % 7;
        number = number/7;
        number7 = remainder * pow(10, power) + number7;
        //result = pow(number7, position) + result;
        power++;
        position++;
    }

    int digits = 0;
    float random_number = number7;
    while(number7 >= 1){
        number7 = number7/10;
        digits++;
        random_number = random_number/10;
    }
    
    int result = 0;
    int single_digit = 0;
    int deleted = 0;
    int power2 = 1;
    for(int i = 0; i < digits; i++){
        random_number = random_number*10;
        single_digit = floor(random_number);
        int result_number = single_digit - deleted*10;
        result = result + pow(result_number, power2);
        power2++;
        deleted = single_digit;
    }
    std::cout << std::endl;
    std::cout << "Speciální ciferný počet je " << result << std::endl;
    std::cout << std::endl;
    return 0;
}


// Napište funkci, která najde celé číslo ‹x›, které leží mezi
// hodnotami ‹low› a ‹high› (včetně), a pro které vrátí funkce ‹poly›
// maximální hodnotu (tzn. libovolné ⟦x⟧ takové, že pro všechny ⟦x'⟧
// platí ⟦f(x) ≥ f(x')⟧, kde ⟦f⟧ je funkce, kterou počítá podprogram
// ‹poly›).


int poly(int x) {
    return 10 + 30 * x - 15 * x * x * x + x * x * x * x * x;
}


int function(int LOW, int HIGH){
    int max_x = LOW;
    int x = LOW;
    int f = poly(LOW);
    int f_new;
    for(int i = LOW; i <= HIGH; i++){
        f_new = poly(i);
        x++;
        if(f_new >= f){
            max_x = i;
            f = f_new;
        }
    }
    std::cout << std::endl;
    std::cout << "Maximální hodnota pro x je " << max_x << std::endl;
    std::cout << std::endl;
    return 0;
}


// Napište funkci, která zjistí, kolik bude pracovních dnů v roce
// ‹year›. Dny v týdnu mají hodnoty 0–6 počínaje pondělím s hodnotou 0.
// Předpokládejte, že ‹year› je větší než 1600.
// České státní svátky jsou:
//
// │  datum │ svátek                                         │
// ├┄┄┄┄┄┄▻┼◅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄│
// │   1.1. │ Den obnovy samostatného českého státu          │
// │      — │ Velký pátek                                    │
// │      — │ Velikonoční pondělí                            │
// │   1.5. │ Svátek práce                                   │
// │   8.5. │ Den vítězství                                  │
// │   5.7. │ Den slovanských věrozvěstů Cyrila a Metoděje   │
// │   6.7. │ Den upálení mistra Jana Husa                   │
// │  28.9. │ Den české státnosti                            │
// │ 28.10. │ Den vzniku samostatného československého státu │
// │ 17.11. │ Den boje za svobodu a demokracii               │
// │ 24.12. │ Štědrý den                                     │
// │ 25.12. │ 1. svátek vánoční                              │
// │ 26.12. │ 2. svátek vánoční                              │
// Přestupné roky: v některých letech se na konec února přidává 29.
// den. Jsou to roky, které jsou dělitelné čtyřmi, s výjimkou těch,
// které jsou zároveň dělitelné 100 a nedělitelné 400.
// Čistou funkci ‹first_day› můžete použít k tomu, abyste zjistili,
// na který den v týdnu padne 1. leden daného roku. Např.
// ‹first_day(2001)› vrátí nulu, protože rok 2001 začínal pondělím.


int first_day_in_year(int year) {
    assert(year >= 1601);
    int years = year - 1601;
    int offset = years + years / 4 - years / 100 + years / 400;
    int day = offset % 7;
    std::cout << day << std::endl;
    return day;

}


int calendar(int year){
    assert(year >= 1601);

    bool leap_year = false;

    int days = 365;
    int first_day = first_day_in_year(year);//5,6 víkend
    int weeks = days / 7;

    int last_whole_week_end = (first_day + 364) % 7;
    int last_day_in_year = last_whole_week_end;
    int day_x = 0;

    int Easter = 2;
    int day_1_1 = first_day;
    int day_1_5 = (first_day + 120) % 7;
    int day_8_5 = (first_day + 127) % 7;
    int day_5_7 = (first_day + 185) % 7;
    int day_6_7 = (first_day + 186) % 7;
    int day_28_9 = (first_day + 270) % 7;
    int day_28_10 = (first_day + 300) % 7;
    int day_17_11 = (first_day + 320) % 7;
    int day_24_12 = (first_day + 357) % 7;
    int day_25_12 = (first_day + 358) % 7;
    int day_26_12 = (first_day + 359) % 7;

    if((year % 4 == 0 && year % 100 > 0) || year % 400 == 0){
        leap_year = true;
        
        days = 366;

        day_1_5 = (first_day + 121) % 7;
        day_8_5 = (first_day + 128) % 7;
        day_5_7 = (first_day + 186) % 7;
        day_6_7 = (first_day + 187) % 7;
        day_28_9 = (first_day + 271) % 7;
        day_28_10 = (first_day + 301) % 7;
        day_17_11 = (first_day + 321) % 7;
        day_24_12 = (first_day + 358) % 7;
        day_25_12 = (first_day + 359) % 7;
        day_26_12 = (first_day + 360) % 7;
        
        last_day_in_year = last_whole_week_end + 2;
    }

    if(last_day_in_year == 5){
        day_x = 1;
    }

    if(last_day_in_year == 6){
        day_x = 1;
        if(leap_year == true){
            day_x = 2;    
        }
    }

    int weekend_days = weeks * 2 + day_x;
    int free_work_days = Easter;

    if(day_1_1 < 5){free_work_days++;}
    if(day_1_5 < 5){free_work_days++;}
    if(day_8_5 < 5){free_work_days++;}
    if(day_5_7 < 5){free_work_days++;}
    if(day_6_7 < 5){free_work_days++;}
    if(day_28_9 < 5){free_work_days++;}
    if(day_28_10 < 5){free_work_days++;}
    if(day_17_11 < 5){free_work_days++;}
    if(day_24_12 < 5){free_work_days++;}
    if(day_25_12 < 5){free_work_days++;}
    if(day_26_12 < 5){free_work_days++;}

    std::cout << std::endl;
    std::cout << "KALENDÁŘ ROKU:            " << year << std::endl;
    std::cout << std::endl;
    std::cout << "Přestupný rok:            " << leap_year << std::endl;
    std::cout << "Počet dní:                " << days << std::endl;
    std::cout << "Počet víkendových dní:    " << weekend_days << std::endl;
    std::cout << "Počet volných dní:        " << free_work_days << std::endl;
    
    int work_days = days - weekend_days - free_work_days;

    std::cout << "Počet pracovních dní:     " << work_days << std::endl;
    std::cout << std::endl;

    return 0;
}


int main(){

    power_digit_sum(1234);

    function(-1, 4);

    calendar(2024);


    //first_day_in_year(2001);
}
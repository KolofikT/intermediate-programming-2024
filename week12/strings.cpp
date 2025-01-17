#include <iostream>
#include <string>
#include <vector>
#include <cassert>

void showoff() {
    std::string s1 = "Hello";
    std::string s2 = "World!";

    std::string s3 = s1 + " " + s2;

    std::cout << s3 << std::endl; // Hello World!
    std::cout << s3.size() << std::endl; // 12

    std::string s4 = s3.substr(2, 7);
    std::cout << s4 << std::endl; // llo Wor

    std::string num = std::to_string(10);
    std::cout << num << std::endl; // 10
    int parsed = std::stoi(num);
    std::cout << parsed + 2 << std::endl; // 12

    char znak = s1[0];
    std::cout << znak << std::endl; // H

    std::string multi_line_not_really =
        "Ahoj,"
        "tento dopis vám píšu,"
        "abych vám ukázal,"
        "jak se dá řetězec napsat na více řádků";

    std::cout << multi_line_not_really << std::endl;
    // Ahoj,tento test vám píšu,abych vám ukázal,jak se dá řetězec napsat na více řádků

    std::string escaped_string = 
        "Ahoj,\n"
        "tento dopis vám píšu,\n"
        "abych vám ukázal,\n"
        "jak se dá řetězec napsat na více řádků";

/*
Ahoj,
tento dopis vám píšu,
abych vám ukázal,
jak se dá řetězec napsat na více řádků
*/

    std::string raw_string =
        R"( Tohle je raw string\n\n\n
            ve kterém se věci ne-escapují\n\n
        i)";

    std::cout << raw_string << std::endl;
/*
Tohle je raw string\n\n\n
            ve kterém se věci ne-escapují\n\n
        i

*/

    std::string raw_string2 =
        R"abcd()() Tohle je raw string\n\n\n
            ve kterém se věci ne-escapují\n\n
        i())abcd";
}

/* Napište funkci line_count, která spočítá kolik řádků má řetězec předaný
 * argumentem text. Řádky jsou odděleny znakem '\n' */
int line_count(std::string text) {
    int lines = 1;
    for(int i = 0; i < text.size(); i++){
        char znak = text[i];
        if(znak == '\n'){
            lines++;
        }
    }
    return lines;
}

/* Napište funkci word_count, která spočítá kolik slov má řetězec předaný
 * argumentem text. */
int word_count(std::string text) {
    int words = 1;
    for(int i = 0; i < text.size(); i++){
        char space = text[i];
        if(space == ' ' || space == '\n'){
            words++;
        }
    }
    return words;
}

/* Napište funkci paragraph_count, která spočítá kolik odstavců má řetězec předaný
 * argumentem text. */
int paragraph_count(std::string text) {
    int odstavec = 1;
    for(int i = 0; i < text.size(); i++){
        char free_line = text[i];
        if(free_line == '\n' && text[i+1] == '\n'){
            odstavec++;
        }
    }
    return odstavec;
}

/* Napište funkci lines, která rozdělí řetezec předaný v argumentu text na jednotlivé řádky.
 */
std::vector<std::string> lines(std::string text) {
    std::vector<std::string> string;
    int first_znak = 0;
    int last_znak = 0;
    for(int i = 0; i < text.size(); i++){
        char znak = text[i];
        if(znak == '\n' ){
            last_znak = i - first_znak;
            std::string a = text.substr(first_znak, last_znak);
            string.push_back(a);
            first_znak = i + 1;
        }
    }
    string.push_back(text.substr(first_znak));
    return {string};
}
//aaaaaa/n/naaa
/* Napište funkci words, která rozdělí řetezec předaný v argumentu text na jednotlivá slova. */
std::vector<std::string> words(std::string text) {
    std::vector<std::string> string;
    int first_znak = 0;
    int last_znak = 0;
    for(int i = 0; i < text.size(); i++){
        char znak = text[i];
        if(znak == '\n' || znak == ' '){
            if(text[i-1] != '\n'){
                last_znak = i - first_znak;
                std::string a = text.substr(first_znak, last_znak);
                string.push_back(a);
            }
            first_znak = i + 1;    
        }
    }
    string.push_back(text.substr(first_znak));
    return {string};
}

/* Napište funkci paragraphs, která rozdělí řetezec předaný v argumentu text na jednotlivé odstavce. */
std::vector<std::string> paragraphs(std::string text) {
    std::vector<std::string> string;
    int first_znak = 0;
    int last_znak = 0;
    for(int i = 0; i < text.size(); i++){
        char znak = text[i];
        if(znak == '\n' && text[i-1] == '\n'){
            last_znak = i - first_znak - 1;
            std::string a = text.substr(first_znak, last_znak);
            string.push_back(a);
            first_znak = i + 1;    
        }
    }
    string.push_back(text.substr(first_znak));
    return {string};
}

/* Naimplementujte funkci check_brackets,
 * která zkontroluje jestli je text předaný v argumentu text validní
 * Text je validní pokud každá otevírací závorka '(' má náležitou uzavírací závorku ')' */
bool check_brackets(std::string text) {
    int open_bracket = 0;
    int closed_bracket = 0;
    bool valid = false;
    for(int i = 0; i < text.size(); i++){
        char znak = text[i];
        if(znak == '('){
            open_bracket++;
        }
        if(znak == ')'){
            closed_bracket++;
        }
    }
    if(open_bracket == closed_bracket){
        valid = true;
    }
    return valid;
}

int main() {
    std::cout << "Testing showoff:" << std::endl;
    showoff();
    std::cout << std::endl;

    // Common test text
    std::string testText = R"(This is the first line.
And here is the second line.

This is a new paragraph. It has multiple lines.
Another line in the same paragraph.

Final paragraph. Short and sweet.)";

    // Test line_count
    assert(line_count(testText) == 7); // Total lines in testText
    std::cout << "line_count passed!" << std::endl;

    // Test word_count
    assert(word_count(testText) == 33); // Total words in testText
    std::cout << "word_count passed!" << std::endl;

    // Test paragraph_count
    assert(paragraph_count(testText) == 3); // Total paragraphs in testText
    std::cout << "paragraph_count passed!" << std::endl;

    // Test lines function
    std::vector<std::string> expectedLines = {
        "This is the first line.",
        "And here is the second line.",
        "",
        "This is a new paragraph. It has multiple lines.",
        "Another line in the same paragraph.",
        "",
        "Final paragraph. Short and sweet."
    };
    assert(lines(testText) == expectedLines);
    std::cout << "lines passed!" << std::endl;

    // Test words function
    std::vector<std::string> expectedWords = {
        "This", "is", "the", "first", "line.",
        "And", "here", "is", "the", "second", "line.",
        "This", "is", "a", "new", "paragraph.", "It", "has", "multiple", "lines.",
        "Another", "line", "in", "the", "same", "paragraph.",
        "Final", "paragraph.", "Short", "and", "sweet."
    };
    assert(words(testText) == expectedWords);
    std::cout << "words passed!" << std::endl;

    // Test paragraphs function
    std::vector<std::string> expectedParagraphs = {
        "This is the first line.\nAnd here is the second line.",
        "This is a new paragraph. It has multiple lines.\nAnother line in the same paragraph.",
        "Final paragraph. Short and sweet."
    };
    assert(paragraphs(testText) == expectedParagraphs);
    std::cout << "paragraphs passed!" << std::endl;

    // Test check_brackets
    std::string bracketsTest = "(This is a (valid) test)";
    assert(check_brackets(bracketsTest) == true);

    bracketsTest = "(This is not (valid)";
    assert(check_brackets(bracketsTest) == false);

    bracketsTest = "This is also invalid)";
    assert(check_brackets(bracketsTest) == false);

    std::cout << "check_brackets passed!" << std::endl;

    std::cout << "All tests passed!" << std::endl;

    return 0;
}

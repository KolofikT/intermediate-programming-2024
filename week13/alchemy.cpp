#include <cassert>
#include <iostream>
#include <string>
#include <set>
#include <map>

using Element = std::string;

bool can_make_recipe(std::set<Element> required, std::set<Element> known){
    for(Element elem: required){
        if(!known.contains(elem)){
            return false;
        }
    }

    return true;

}

bool can_make(std::string goal,
              std::set<std::string> start,
              std::map<std::set<std::string>, std::string> recipes) {
    
    

    int made = 1;

    while (made > 0){

        if(start.contains(goal)){
            return true;
        }

        made = 0;
    
        for(auto [recipe, result] : recipes){

            if(start.contains(result)){
                continue;
            }

            if(can_make_recipe(recipe, start)){
                start.insert(result);
                made++;
            }
        }
    }

    return false;

}


void run_tests() 
{
    {
        std::set<std::string> start = {"water", "salt", "sugar"};
        std::map<std::set<std::string>, std::string> recipes;
        assert(can_make("water", start, recipes) == true);  
        assert(can_make("salt", start, recipes) == true);  
        assert(can_make("sugar", start, recipes) == true);  
    }
    {
        std::set<std::string> start = {"water", "salt"};
        std::map<std::set<std::string>, std::string> recipes;
        recipes[{ "salt", "water" }] = "saltwater";
        assert(can_make("saltwater", start, recipes) == true);
        assert(can_make("sugar", start, recipes) == false);
    }
    {
        std::set<std::string> start = {"water", "salt", "air"};
        std::map<std::set<std::string>, std::string> recipes;
        recipes[{ "water", "salt" }] = "brine";
        recipes[{ "brine", "air" }] = "saltedAir";
        assert(can_make("saltedAir", start, recipes) == true);
        assert(can_make("fire", start, recipes) == false);
    }
    {
        std::set<std::string> start = {"a", "b", "c", "d"};
        std::map<std::set<std::string>, std::string> recipes;
        recipes[{ "a", "b", "c" }] = "x";
        recipes[{ "x", "d" }] = "y";
        assert(can_make("y", start, recipes) == true);
    }
    {
        std::set<std::string> start = {"flour", "water", "yeast"};
        std::map<std::set<std::string>, std::string> recipes;
        recipes[{ "flour", "water" }] = "dough";
        recipes[{ "dough", "yeast" }] = "bread";
        recipes[{ "bread", "dough" }] = "superBread";
        assert(can_make("bread", start, recipes) == true);
    }
    {
        std::set<std::string> start = {"iron", "carbon"};
        std::map<std::set<std::string>, std::string> recipes;
        recipes[{ "iron", "carbon" }] = "steel";
        assert(can_make("diamond", start, recipes) == false);
    }

    {
        std::set<std::string> start = {"hydrogen", "oxygen"};
        std::map<std::set<std::string>, std::string> recipes;

        // Recipe with 0 ingredients (produces a constant)
        recipes[{ }] = "pureWater";  // No ingredients, pure water is just made
        // Recipe with 1 ingredient
        recipes[{ "hydrogen" }] = "hydrogenGas";
        recipes[{ "oxygen" }] = "oxygenGas";
        // Recipe with 2 ingredients
        recipes[{ "hydrogen", "oxygen" }] = "water";

        // Test if the pureWater can be made directly with no ingredients
        assert(can_make("pureWater", start, recipes) == true);
        // Test if hydrogenGas can be made from hydrogen
        assert(can_make("hydrogenGas", start, recipes) == true);
        // Test if oxygenGas can be made from oxygen
        assert(can_make("oxygenGas", start, recipes) == true);
        // Test if water can be made from hydrogen and oxygen
        assert(can_make("water", start, recipes) == true);

        // Test if an impossible goal that requires a recipe we don't have is handled
        assert(can_make("carbonDioxide", start, recipes) == false);
    }
    {
        std::set<std::string> start = {"hydrogen", "oxygen", "carbon", "nitrogen"};
        std::map<std::set<std::string>, std::string> recipes;

        recipes[{ "hydrogen", "oxygen" }] = "water";
        recipes[{ "carbon", "oxygen" }] = "carbonDioxide";
        recipes[{ "water", "carbonDioxide" }] = "carbonicAcid";
        recipes[{ "carbonicAcid", "oxygen" }] = "carbonicAcidGas";
        recipes[{ "carbonicAcid", "nitrogen" }] = "ammoniumCarbonate";
        recipes[{ "ammoniumCarbonate", "water" }] = "ammoniumHydroxide";

        assert(can_make("ammoniumHydroxide", start, recipes) == true);
        assert(can_make("carbonicAcidGas", start, recipes) == true);
        assert(can_make("sulfuricAcid", start, recipes) == false);
    }

    // Complex test with multiple intermediate steps to produce a final compound
    {
        std::set<std::string> start = {"water", "sodium", "chlorine", "ammonia"};
        std::map<std::set<std::string>, std::string> recipes;

        recipes[{ "water", "sodium" }] = "sodiumHydroxide";
        recipes[{ "sodiumHydroxide", "chlorine" }] = "sodiumChloride";
        recipes[{ "sodiumChloride", "ammonia" }] = "ammoniumChloride";
        recipes[{ "ammoniumChloride", "water" }] = "ammoniumHydroxide";

        assert(can_make("ammoniumHydroxide", start, recipes) == true);
        assert(can_make("sodiumChloride", start, recipes) == true);
        assert(can_make("chlorine", start, recipes) == true);
        assert(can_make("water", start, recipes) == true);
    }

    // Test with a very long sequence of steps (complex chain reaction)
    {
        std::set<std::string> start = {"hydrogen", "oxygen"};
        std::map<std::set<std::string>, std::string> recipes;

        recipes[{ "hydrogen", "oxygen" }] = "water";
        recipes[{ "water", "hydrogen" }] = "hydrogenPeroxide";
        recipes[{ "hydrogenPeroxide", "oxygen" }] = "oxygenGas";
        recipes[{ "oxygen", "water" }] = "ozone";
        recipes[{ "ozone", "hydrogenPeroxide" }] = "oxygenatedWater";

        assert(can_make("oxygenatedWater", start, recipes) == true);
        assert(can_make("oxygenGas", start, recipes) == true);
        assert(can_make("ozone", start, recipes) == true);
        assert(can_make("hydrogenPeroxide", start, recipes) == true);
        assert(can_make("water", start, recipes) == true);
        assert(can_make("carbonDioxide", start, recipes) == false);
    }

    // Test with more than two ingredients in a recipe and multipath recipe
    {
        std::set<std::string> start = {"hydrogen", "oxygen", "carbon", "nitrogen"};
        std::map<std::set<std::string>, std::string> recipes;

        recipes[{ "hydrogen", "oxygen", "carbon" }] = "carbonHydride";
        recipes[{ "carbon", "hydrogen", "nitrogen" }] = "hydrogenNitride";
        recipes[{ "carbonHydride", "oxygen" }] = "carbonDioxide";
        recipes[{ "hydrogenNitride", "oxygen" }] = "nitrousOxide";

        assert(can_make("carbonDioxide", start, recipes) == true);
        assert(can_make("nitrousOxide", start, recipes) == true);
        assert(can_make("carbonHydride", start, recipes) == true);
        assert(can_make("carbon", start, recipes) == true);  // Cannot directly make carbon
    }
    std::cout << "All tests passed!\n";
}

int main()
{
    run_tests();
    return 0;
}
#include <iostream>
#include "yaml-cpp/yaml.h"

using namespace std;

int main(int argc,char** argv)
{
    try{
        YAML::Node config = YAML::LoadFile("../config.yaml");
        for (auto it : config["skills"]) {
            YAML::Node test2 = YAML::Load(it.second.as<string>());
            cout << " Type: " << test2.Type() << endl; //< 2
            cout << it.first.as<string>() << ":" << it.second.as<string>() << endl;
        }

        for (YAML::const_iterator it = config.begin(); it != config.end(); it++)
        {
            cout << it->first.as<string>() << endl;
        }
        system("pause");
    }catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
    return 0;

}


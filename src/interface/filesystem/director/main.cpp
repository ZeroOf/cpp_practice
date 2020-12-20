//
// Created by god on 2021/4/4.
//

#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
int main()
{
    fs::create_directories("sandbox/a/b");
    std::ofstream("sandbox/file1.txt");
    std::ofstream("sandbox/file2.txt");
    for(auto& p: fs::directory_iterator("sandbox"))
        std::cout << p.path() << '\n';
    fs::remove_all("sandbox");
    try {
        for(auto& p: fs::directory_iterator("sandbox")){
            std::cout << p.path() << '\n';
        }
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
    }
}
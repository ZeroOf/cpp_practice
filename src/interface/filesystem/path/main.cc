#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

int main() {
    fs::path p1 = "/usr//lib//sendmail.cf"; // portable format
    fs::path p2 = "C:\\users\\abcdef\\AppData\\Local\\Temp\\"; // native format
    fs::path p3 = u8"D:/猫.txt"; // wide string
    fs::path p4 = "/usr/lib//sendmail.cf"; // portable format


    std::cout << "p1 = " << p1.make_preferred() << '\n'
              << "p2 = " << p2.make_preferred() << '\n'
              << "p3 = " << p3.make_preferred() << '\n';
    cout << boolalpha << (p1 == p4) << endl;
}
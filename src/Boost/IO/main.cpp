#include <boost/io/ios_state.hpp>
#include <iostream>

void new_hex_my_byte(std::ostream &os, char byte) {
    boost::io::ios_flags_saver ifs(os);
    os << std::hex << static_cast<unsigned>(byte);
}

int main() {
    // ...
    {
        boost::io::ios_all_saver ias(std::cout);
        new_hex_my_byte(std::cout, 'A');
    }
    // ...
    {
        boost::io::ios_all_saver ias(std::cerr);
        new_hex_my_byte(std::cerr, 'b');
        ias.restore();
        new_hex_my_byte(std::cerr, 'C');
    }
    // ...
}

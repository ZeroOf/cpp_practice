
#include <iostream>
#include <openssl/rand.h>

int main() {
    unsigned char buf[17] = {0};
    RAND_bytes(buf, 16);
    std::string rand = reinterpret_cast<const char *>(buf);

    std::cout << rand << std::endl;
}

#include <iostream>
#include "DebugSetting.h"

int main() {
    try {
        DebugSetting ds;
        ds.file_ = "setting.log";
        ds.level_ = 2;
        ds.modules_ = {
                "a", "b"
        };
        ds.save("debug_settings_out.xml");
//        ds.load("debug_settings.xml");
        std::cout << "Success\n";
    }
    catch (std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    return 0;
}

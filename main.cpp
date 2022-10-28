#include <iostream>

#include "BBCodeParser.h"


#include <string>

using std::string;

int main(int argc, char *argv[]) {



  string str =
            "[b]\n[u]\n"
            "I'm alive!\n"
            "test\n"
            "[b]another bold[/b]\n"
            "[img]pic.png[/img]\n"
            "[/u]\n[/b]";

    BBCodeParser t(str);


    std::cout << t.render() << std::endl;



    return 0;
}

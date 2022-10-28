#include <iostream>

#include "BBCodeParser.h"


#include <iostream>
#include <iterator>
#include <string>

using std::string;

int main(int argc, char *argv[]) {



    std::istreambuf_iterator<char> begin(std::cin), end;
    std::string str(begin, end);

    BBCodeParser t(str);


    std::cout << t.render() << std::endl;



    return 0;
}

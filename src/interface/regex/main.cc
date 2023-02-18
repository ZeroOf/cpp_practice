//
// Created by god on 2021/4/11.
//

#include <iostream>
#include <string>
#include <regex>

void match()
{
    std::string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
    // 在 C++ 中 \ 会被作为字符串内的转义符，为使 \. 作为正则表达式传递进去生效，需要对 \ 进行二次转义，从而有 \\.
    std::regex txt_regex("[a-z]+\\.txt");
    for (const auto& fname: fnames)
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << std::endl;
}

void search()
{
    std::string parse = "hello world \r\n\r\n\r\n";
    std::regex search(".*\\r\\n\\r\\n");
    std::smatch result;
    std::cout << std::boolalpha << std::regex_search(parse, result, search) << std::endl;
    std::cout << result.size() << result.begin()->str().size() << std::endl;
}

int main()
{
    match();
    search();
}
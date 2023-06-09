#include <windows.h>
#include <locale.h>
#include <vector>
#include <iostream>


template <typename T>
void move_vector(std::vector<T>& left, std::vector<T>& right)
{
    right = std::move(left);
}
 
 
int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
  
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;

    move_vector(one, two);

    for (const auto &ex : two)
    {
        std::cout << ex<<" ";
    }

    return 0;
}
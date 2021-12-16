#include <iostream>

#include <cstdio>
#include <cctype>

using namespace std;

int countWords(const char *str)
{
    bool state = true;
    int num = 0;
    while (*str)
    {
        if (std::isspace(*str))
        {
            state= true;
        }
        else if (state)
        {
            num++;
            state = false;
        }
        ++str;
    }
    return num;
}
int main(int argc, char** argv){
    if (argc > 1) {
        printf("Number of words: %d", countWords(argv[1]));
    }
    else {
        cout << "String not ended" << endl;
    }
    return 0;
}
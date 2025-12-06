#include <fstream>
#include <iostream>
#include <list>

int main()
{
    std::fstream fs;
    fs.open("data.txt", std::fstream::in);

    std::list<std::string> turns;
    while (!fs.eof())
    {
        std::string item;
        fs >> item;
        turns.push_back(item);
    }

    int last = 50;
    int position = 50;
    int count = 0;

    for (auto it = turns.begin(); it != turns.end(); ++it)
    {
        if ((*it).size() == 0)
            continue;
        int mod = 1;
        if ((*it)[0] == 'L')
            mod = -1;
        int mov = atoi((*it).substr(1).c_str()) * mod;

        if (mov > 0)
        {
            while (mov / 100 > 0)
            {
                std::cout << "!!!" << std::endl;
                ++count;
                mov -= 100;
            }
        }
        else if (mov < 0)
        {
            while (mov / 100 < 0)
            {
                std::cout << "!!!" << std::endl;
                ++count;
                mov += 100;
            }
        }

        position += mov;
        if (position < 0)
        {
            position = 100 + position;
            if (last != 0)
                ++count;
            std::cout << *it << " " << mov << " " << position << " !!! " << last << std::endl;
        }
        else if (position > 99)
        {
            position = position % 100;
            ++count;
            std::cout << *it << " " << mov << " " << position << " !!!" << std::endl;
        }
        else if (position == 0)
        {
            ++count;
            std::cout << *it << " " << mov << " " << position << " !!!" << std::endl;
        }
        else
        {
            std::cout << *it << " " << mov << " " << position << std::endl;
        }


        last = position;
    }

    std::cout << "Answer: " << count << std::endl;

    return 0;
}

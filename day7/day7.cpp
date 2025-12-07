#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

void printManifold(const std::vector<std::vector<long long>>& manifold)
{
    for (auto it = manifold.begin(); it != manifold.end(); ++it)
    {
        for (auto jt = (*it).begin(); jt != (*it).end(); ++jt)
            std::cout << " " << *jt;
        std::cout << std::endl;
    }
}

int main()
{
    std::fstream fs;
    fs.open("data.txt", std::fstream::in);

    std::list<std::string> manifold_text;
    std::string line;
    size_t lineLength = 0;
    while (std::getline(fs, line))
    {
        if (line.size() > 0)
        {
            manifold_text.push_back(line);
            if (line.size() > lineLength)
                lineLength = line.size();
        }
    }

    std::vector<std::vector<long long>> manifold(manifold_text.size(), std::vector<long long>(manifold_text.front().size()));
    size_t row = 0;
    for (auto it = manifold_text.begin(); it != manifold_text.end(); ++it)
    {
        for (size_t i = 0; i < lineLength; ++i)
        {
            long long ch = 0;
            switch ((*it).substr(i, 1).c_str()[0])
            {
            case 'S': ch = -1; break;
            case '.': ch = 0; break;
            case '^': ch = -2; break;
            }
            manifold[row][i] = ch;
        }
        ++row;
    }

    printManifold(manifold);

    int splitCount = 0;
    for (size_t row = 1; row < manifold.size(); ++row)
    {
        for (size_t column = 0; column < manifold[row].size(); ++column)
        {
            long long ch = manifold[row][column];
            switch (ch)
            {
            case -2: // ^
                if (manifold[row - 1][column] > 0)
                {
                    ++splitCount;
                    manifold[row][column - 1] += manifold[row - 1][column];
                    manifold[row][column + 1] += manifold[row - 1][column];
                }
                break;
            case 0: // .
                if (manifold[row - 1][column] == -2)
                    manifold[row][column] = 0;
                else if (manifold[row - 1][column] == -1)
                    manifold[row][column] = 1;
                else
                    manifold[row][column] = manifold[row - 1][column];
                break;
            case -1: // S
                break;
            case 1: // |
            default:
                if (manifold[row - 1][column] >= 0)
                    manifold[row][column] += manifold[row - 1][column];
                break;
            }
        }
    }

    long long timelineCount = 0;
    for (size_t i = 0; i < lineLength; ++i)
        timelineCount += manifold[manifold.size() - 1][i];

    printManifold(manifold);

    std::cout << "Answer1: " << splitCount << std::endl;
    std::cout << "Answer2: " << timelineCount << std::endl;

    return 0;
}

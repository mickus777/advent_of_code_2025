#include <fstream>
#include <iostream>
#include <list>
#include <vector>

int main()
{
    std::fstream fs;
    fs.open("data.txt", std::fstream::in);

    std::list<std::string> bank_texts;
    while (!fs.eof())
    {
        std::string item;
        fs >> item;
        if (item.size() > 0)
            bank_texts.push_back(item);
    }

    size_t size = bank_texts.front().size();

    std::list<std::vector<int>> banks;

    for (auto bank_text = bank_texts.begin(); bank_text != bank_texts.end(); ++bank_text)
    {
        std::string text = *bank_text;
        std::vector<int> bank(size);
        size_t i = 0;
        for (size_t i = 0; i < size; ++i)
            bank[i] = atoi(text.substr(i, 1).c_str());
        banks.push_back(bank);
    }

    size_t limit = 12;

    long long totalJoltage = 0;
    for (auto bank = banks.begin(); bank != banks.end(); ++bank)
    {
        long long bankJoltage = 0;
        size_t lastIndex = 0;
        for (size_t i = 0; i < limit; ++i)
        {
            long long largestValue = (*bank)[lastIndex];
            for (size_t j = lastIndex + 1; j < size - limit + i + 1; ++j)
            {
                if ((*bank)[j] > largestValue)
                {
                    lastIndex = j;
                    largestValue = (*bank)[j];
                }
            }
            bankJoltage = bankJoltage * 10 + largestValue;
            lastIndex += 1;
        }
        totalJoltage += bankJoltage;
    }

    std::cout << "Answer: " << totalJoltage << std::endl;

    return 0;
}

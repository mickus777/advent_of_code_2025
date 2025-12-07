#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

long long add(long long i1, int i2)
{
    return i1 + i2;
}

long long multiply(long long i1, int i2)
{
    return i1 * i2;
}

typedef long long Op(long long i1, int i2);

long long applyOperators(std::vector<Op*>& operators, std::vector<std::vector<int>>& operands, size_t index)
{
    std::vector<int> specialOperands(operands.size(), 0);
    for (size_t i = 0; i < operands.size(); ++i)
        specialOperands[i] = operands[i][index];



    long long result = operands[0][index];
    for (size_t i = 1; i < operands.size(); ++i)
    {
        Op* op = operators[index];
        result = op(result, operands[i][index]);
    }
    return result;
}

int main()
{
    std::fstream fs;
    fs.open("data.txt", std::fstream::in);

    std::list<std::string> homework_text;
    std::string line;
    size_t lineLength = 0;
    while (std::getline(fs, line))
    {
        if (line.size() > 0)
        {
            homework_text.push_back(line);
            if (line.size() > lineLength)
                lineLength = line.size();
        }
    }

    long long sum = 0;
    std::list<int> numbers;
    char op;
    for (size_t i = 0; i < lineLength; ++i)
    {
        int number = 0;
        for (auto homeworkLine = homework_text.begin(); homeworkLine != homework_text.end(); ++homeworkLine)
        {
            if (i >= (*homeworkLine).size())
                continue;
            std::string ch = (*homeworkLine).substr(i, 1);
            if (ch == "+" || ch == "*")
                op = ch.c_str()[0];
            else if (ch != " ")
                number = number * 10 + atoi(ch.c_str());
        }

        if (number == 0)
        {
            auto it = numbers.begin();
            long long value = *it;
            for (++it; it != numbers.end(); ++it)
            {
                if (op == '+')
                    value += *it;
                else
                    value *= *it;
            }
            numbers.clear();
            sum += value;
        }
        else
        {
            numbers.push_back(number);
        }
    }
    auto it = numbers.begin();
    long long value = *it;
    for (++it; it != numbers.end(); ++it)
    {
        if (op == '+')
            value += *it;
        else
            value *= *it;
    }
    sum += value;

    std::cout << "Answer: " << sum << std::endl;

    return 0;
}

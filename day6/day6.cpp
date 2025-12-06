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
    while (std::getline(fs, line))
    {
        if (line.size() > 0)
            homework_text.push_back(line);
    }

    std::list<std::list<std::string>> tokens;
    for (auto homework_row = homework_text.begin(); homework_row != homework_text.end(); ++homework_row)
    {
        if ((*homework_row).size() == 0)
            continue;

        std::list<std::string> token_row;
        std::stringstream stream(*homework_row);
        while (!stream.eof())
        {
            std::string token;
            stream >> token;
            if (token.size() > 0)
                token_row.push_back(token);
        }
        tokens.push_back(token_row);
    }

    std::vector<std::vector<int>> operands(tokens.size() - 1, std::vector<int>(tokens.front().size(), 0));
    size_t row = 0;
    for (auto token_row = tokens.begin(); token_row != --tokens.end(); ++token_row)
    {
        size_t item = 0;
        for (auto token = (*token_row).begin(); token != (*token_row).end(); ++token)
        {
            operands[row][item] = atoi((*token).c_str());

            ++item;
        }
        ++row;
    }
    std::vector<Op*> operators(tokens.front().size());
    size_t item = 0;
    for (auto operator_item = tokens.back().begin(); operator_item != tokens.back().end(); ++operator_item)
    {
        operators[item] = (*operator_item == "+" ? add : multiply);
        ++item;
    }

    long long sum = 0;
    for (size_t i = 0; i < operators.size(); ++i)
    {
        long long value = applyOperators(operators, operands, i);
        sum += value;
    }

    std::cout << "Answer: " << sum << std::endl;

    return 0;
}

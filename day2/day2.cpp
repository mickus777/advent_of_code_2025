#include <fstream>
#include <iostream>
#include <list>
#include <sstream>

struct Range
{
    long long start;
    long long end;

    Range(long long s, long long e) : start(s), end(e) {}

    std::string print()
    {
        std::stringstream stream;
        stream << start << "-" << end;
        return stream.str();
    }
};

bool is_invalid(long long value)
{
    std::list<int> digits;
    while (value > 0)
    {
        int digit = value % 10;
        value /= 10;
        digits.push_back(digit);
    }

    if (digits.size() % 2 > 0)
        return false;

    size_t midpoint = digits.size() / 2;

    auto first = digits.begin();
    auto second = digits.begin();
    for (size_t i = 0; i < midpoint; ++i)
        ++second;

    while (second != digits.end())
    {
        if (*first != *second)
            return false;
        ++first;
        ++second;
    }

    return true;
}

int main()
{
    std::fstream fs;
    fs.open("data.txt", std::fstream::in);

    std::string ranges_text;
    fs >> ranges_text;

    std::list<Range> ranges;
    size_t last_pos = 0;
    for (size_t pos = ranges_text.find(','); pos != -1; pos = ranges_text.find(',', pos + 1))
    {
        std::string range_text = ranges_text.substr(last_pos, pos - last_pos);
        size_t dash_point = range_text.find('-');

        long long start = atoll(range_text.substr(0, dash_point).c_str());
        long long end = atoll(range_text.substr(dash_point + 1).c_str());

        ranges.push_back(Range(start, end));

        last_pos = pos + 1;
    }
    std::string range_text = ranges_text.substr(last_pos);
    size_t dash_point = range_text.find('-');

    long long start = atoll(range_text.substr(0, dash_point).c_str());
    long long end = atoll(range_text.substr(dash_point + 1).c_str());

    ranges.push_back(Range(start, end));


    long long sum_of_invalids = 0;
    for (auto it = ranges.begin(); it != ranges.end(); ++it)
    {
        for (long long i = (*it).start; i <= (*it).end; ++i)
        {
            if (is_invalid(i))
            {
                sum_of_invalids += i;
                std::cout << i << " " << sum_of_invalids << std::endl;
            }
        }
    }

    std::cout << "Answer: " << sum_of_invalids << std::endl;

    return 0;
}

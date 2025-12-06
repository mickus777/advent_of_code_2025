#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

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
    std::list<int> digit_list;
    while (value > 0)
    {
        int digit = value % 10;
        value /= 10;
        digit_list.push_back(digit);
    }
    digit_list.reverse();

    std::vector<int> digits(digit_list.size());
    size_t index = 0;
    for (auto it = digit_list.begin(); it != digit_list.end(); ++it)
    {
        digits[index] = *it;
        ++index;
    }

    for (size_t len = 1; len <= digits.size() / 2; ++len)
    {
        if (digits.size() % len != 0)
            continue;

        bool same_segments = true;
        for (size_t i = 0; i < len; ++i)
        {
            bool same_digit_at_interval = true;
            int digit = digits[i];
            for (size_t j = i + len; j < digits.size(); j += len)
            {
                if (digit != digits[j])
                {
                    same_digit_at_interval = false;
                    break;
                }
            }
            if (!same_digit_at_interval)
            {
                same_segments = false;
                break;
            }
        }
        if (same_segments)
            return true;
    }

    return false;
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

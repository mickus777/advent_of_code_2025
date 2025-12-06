#include <fstream>
#include <iostream>
#include <list>
#include <vector>

struct Range
{
    long long start;
    long long end;

    Range(long long s, long long e) : start(s), end(e) {}
};

bool compareRanges(const Range& r1, const Range& r2)
{
    return r1.start < r2.start;
}

int main()
{
    std::fstream fs;
    fs.open("data.txt", std::fstream::in);

    std::list<std::string> registry_text;
    while (!fs.eof())
    {
        std::string item;
        fs >> item;
        if (item.size() > 0)
            registry_text.push_back(item);
    }

    std::list<Range> ranges;
    std::list<long long> ingredients;

    for (auto it = registry_text.begin(); it != registry_text.end(); ++it)
    {
        size_t dashIndex = (*it).find('-');
        if (dashIndex != -1)
        {
            long long start = atoll((*it).substr(0, dashIndex).c_str());
            long long end = atoll((*it).substr(dashIndex + 1).c_str());
            ranges.push_back(Range(start, end));
        }
        else
        {
            ingredients.push_back(atoll((*it).c_str()));
        }
    }
    ranges.sort(compareRanges);
    ingredients.sort();

    std::list<Range> mergedRanges;
    Range currentRange = ranges.front();
    ranges.pop_front();

    while (ranges.size() > 0)
    {
        Range range = ranges.front();
        ranges.pop_front();
        if (range.start <= currentRange.end)
        {
            if (range.end > currentRange.end)
                currentRange.end = range.end;
        }
        else
        {
            mergedRanges.push_back(currentRange);
            currentRange = range;
        }
    }
    mergedRanges.push_back(currentRange);

    int freshCount = 0;
    auto rangeIt = mergedRanges.begin();
    for (auto ingredient = ingredients.begin(); ingredient != ingredients.end(); ++ingredient)
    {
        while (rangeIt != mergedRanges.end())
        {
            if (*ingredient < (*rangeIt).start)
            {
                break;
            }
            else if (*ingredient <= (*rangeIt).end)
            {
                ++freshCount;
                break;
            }
            else
            {
                ++rangeIt;
            }
        }
    }

    long long totalFreshCount = 0;
    for (auto range = mergedRanges.begin(); range != mergedRanges.end(); ++range)
        totalFreshCount += (*range).end - (*range).start + 1;

    std::cout << "Answer 1: " << freshCount << std::endl;
    std::cout << "Answer 2: " << totalFreshCount << std::endl;

    return 0;
}

#include <fstream>
#include <iostream>
#include <list>
#include <math.h>
#include <sstream>
#include <vector>

struct JunctionBox
{
    int x;
    int y;
    int z;

    size_t setIndex;

    JunctionBox() : x(0), y(0), z(0), setIndex(0) {}
    JunctionBox(int nx, int ny, int nz) : x(nx), y(ny), z(nz), setIndex(0) {}
};

JunctionBox read(const std::string& text)
{
    size_t comma1 = text.find(',');
    size_t comma2 = text.find(',', comma1 + 1);

    return JunctionBox(atoi(text.substr(0, comma1).c_str()), atoi(text.substr(comma1 + 1, comma2 - comma1 - 1).c_str()), atoi(text.substr(comma2 + 1).c_str()));
}

double distance(const JunctionBox& jb1, const JunctionBox& jb2)
{
    double x = jb1.x - jb2.x;
    double y = jb1.y - jb2.y;
    double z = jb1.z - jb2.z;

    return sqrt(x * x + y * y + z * z);
}

int main()
{
    std::fstream fs;
    fs.open("data.txt", std::fstream::in);

    std::list<std::string> junctionBoxes_text;
    std::string line;
    size_t lineLength = 0;
    while (std::getline(fs, line))
    {
        if (line.size() > 0)
        {
            junctionBoxes_text.push_back(line);
            if (line.size() > lineLength)
                lineLength = line.size();
        }
    }

    std::vector<JunctionBox> junctionBoxes(junctionBoxes_text.size());
    size_t i = 0;
    for (auto it = junctionBoxes_text.begin(); it != junctionBoxes_text.end(); ++it)
    {
        junctionBoxes[i] = read(*it);
        ++i;
    }

    std::vector<std::vector<double>> distances(junctionBoxes.size(), std::vector<double>(junctionBoxes.size(), 0));
    for (size_t i = 0; i < junctionBoxes.size(); ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            distances[i][j] = distance(junctionBoxes[i], junctionBoxes[j]);
        }
    }

    long long xMultiple = 0;
    size_t setIndex = 1;
    for (size_t count = 0; count < 100000000000; ++count)
    {
        size_t jbi = 0;
        size_t jbj = 0;
        double shortestDistance = 100000000000;
        for (size_t i = 0; i < junctionBoxes.size(); ++i)
        {
            for (size_t j = 0; j < i; ++j)
            {
                if (junctionBoxes[i].setIndex != 0 && junctionBoxes[j].setIndex && junctionBoxes[i].setIndex == junctionBoxes[j].setIndex)
                    continue;

                if (distances[i][j] < shortestDistance)
                {
                    jbi = i;
                    jbj = j;
                    shortestDistance = distances[i][j];
                }
            }
        }

        if (shortestDistance == 100000000000)
        {
            break;
        }

        distances[jbi][jbj] = 100000000000;

        if (junctionBoxes[jbi].setIndex > 0)
        {
            if (junctionBoxes[jbj].setIndex > 0)
            {
                if (junctionBoxes[jbi].setIndex != junctionBoxes[jbj].setIndex)
                {
                    size_t oldIndex = junctionBoxes[jbj].setIndex;
                    for (size_t k = 0; k < junctionBoxes.size(); ++k)
                        if (junctionBoxes[k].setIndex == oldIndex)
                            junctionBoxes[k].setIndex = junctionBoxes[jbi].setIndex;
                }
            }
            else
            {
                junctionBoxes[jbj].setIndex = junctionBoxes[jbi].setIndex;
            }
        }
        else if (junctionBoxes[jbj].setIndex > 0)
        {
            junctionBoxes[jbi].setIndex = junctionBoxes[jbj].setIndex;
        }
        else
        {
            junctionBoxes[jbi].setIndex = setIndex;
            junctionBoxes[jbj].setIndex = setIndex;
            ++setIndex;
        }

        xMultiple = junctionBoxes[jbi].x * junctionBoxes[jbj].x;
    }
    /*
    std::list<int> setSizes;
    for (size_t i = 1; i < setIndex; ++i)
    {
        int size = 0;
        for (size_t j = 0; j < junctionBoxes.size(); ++j)
            if (junctionBoxes[j].setIndex == i)
                ++size;
        setSizes.push_back(size);
    }
    setSizes.sort();
    setSizes.reverse();

    long long result = 1;
    for (size_t i = 0; i < 3; ++i)
    {
        int item = setSizes.front();
        setSizes.pop_front();
        result *= item;
    }
    */
    std::cout << "Answer: " << xMultiple << std::endl;

    return 0;
}

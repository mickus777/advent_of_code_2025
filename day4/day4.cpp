#include <fstream>
#include <iostream>
#include <list>
#include <vector>

enum FloorState
{
    Empty,
    Free,
    Roll
};

enum Direction
{
    N, NE, E, SE, S, SW, W, NW
};

FloorState charToState(char ch)
{
    switch (ch)
    {
    case '.': return Empty;
    case '@': return Roll;
    default: throw 0;
    }
}

char stateToChar(FloorState state)
{
    switch (state)
    {
    case Empty: return '.';
    case Free: return 'X';
    case Roll: return '@';
    default: throw 0;
    }
}

FloorState stateAt(Direction dir, size_t x, size_t y, size_t width, size_t height, std::vector<std::vector<FloorState>>& floorplan)
{
    switch (dir)
    {
    case N: return (y > 0) ? floorplan[x][y - 1] : Empty;
    case NE: return (y > 0) && (x < width - 1) ? floorplan[x + 1][y - 1] : Empty;
    case E: return (x < width - 1) ? floorplan[x + 1][y] : Empty;
    case SE: return (y < height - 1) && (x < width - 1) ? floorplan[x + 1][y + 1] : Empty;
    case S: return (y < height - 1) ? floorplan[x][y + 1] : Empty;
    case SW: return (y < height - 1) && (x > 0) ? floorplan[x - 1][y + 1] : Empty;
    case W: return (x > 0) ? floorplan[x - 1][y] : Empty;
    case NW: return (y > 0) && (x > 0) ? floorplan[x - 1][y - 1] : Empty;
    default: throw 0;
    }
}

void printFloorplan(std::vector<std::vector<FloorState>>& floorplan, size_t height, size_t width)
{
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            std::cout << stateToChar(floorplan[x][y]);
        }
        std::cout << std::endl;
    }
}

void clearAllFreeSpace(std::vector<std::vector<FloorState>>& floorplan, size_t height, size_t width)
{
    for (size_t x = 0; x < width; ++x)
        for (size_t y = 0; y < height; ++y)
            if (floorplan[x][y] == Free)
                floorplan[x][y] = Empty;
}

int main()
{
    std::fstream fs;
    fs.open("data.txt", std::fstream::in);

    std::list<std::string> floorplan_text;
    while (!fs.eof())
    {
        std::string item;
        fs >> item;
        if (item.size() > 0)
            floorplan_text.push_back(item);
    }

    size_t height = floorplan_text.size();
    size_t width = floorplan_text.front().size();

    std::vector<std::vector<FloorState>> floorplan(width, std::vector<FloorState>(height, Empty));

    size_t y = 0;
    for (auto row_text = floorplan_text.begin(); row_text != floorplan_text.end(); ++row_text)
    {
        std::string row = *row_text;
        for (size_t x = 0; x < width; ++x)
            floorplan[x][y] = charToState(row.c_str()[x]);
        ++y;
    }


    int count = 0;
    int lastCount = 0;
    do
    {
        std::cout << std::endl;
        printFloorplan(floorplan, height, width);

        lastCount = count;
        for (size_t x = 0; x < width; ++x)
        {
            for (size_t y = 0; y < height; ++y)
            {
                if (Roll != floorplan[x][y])
                    continue;

                int neighbors = 0;
                if (!(Empty == stateAt(N, x, y, width, height, floorplan)))
                    ++neighbors;
                if (!(Empty == stateAt(NE, x, y, width, height, floorplan)))
                    ++neighbors;
                if (!(Empty == stateAt(E, x, y, width, height, floorplan)))
                    ++neighbors;
                if (!(Empty == stateAt(SE, x, y, width, height, floorplan)))
                    ++neighbors;
                if (!(Empty == stateAt(S, x, y, width, height, floorplan)))
                    ++neighbors;
                if (!(Empty == stateAt(SW, x, y, width, height, floorplan)))
                    ++neighbors;
                if (!(Empty == stateAt(W, x, y, width, height, floorplan)))
                    ++neighbors;
                if (!(Empty == stateAt(NW, x, y, width, height, floorplan)))
                    ++neighbors;
                if (neighbors < 4)
                {
                    floorplan[x][y] = Free;
                    ++count;
                }
            }
        }

        clearAllFreeSpace(floorplan, height, width);
    }
    while (count != lastCount);

    std::cout << std::endl;
    printFloorplan(floorplan, height, width);

    std::cout << "Answer: " << count << std::endl;

    return 0;
}

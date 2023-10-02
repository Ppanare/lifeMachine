#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <fstream>


std::vector<int>coord_x;
std::vector<int>coord_y;
bool stopIt = false;
bool stopIt2 = false;

int readRowsFromFile()
{
    std::string buffer;
    std::ifstream output("fieldInit.txt");
    std::getline(output,buffer,' ');
    int rows{};
    rows = std::stoi(buffer);
    //std::cout<<rows;
    output.close();
    return rows;
}

int readColsFromFile()
{
    std::string buffer;
    std::ifstream output("fieldInit.txt");
    std::getline(output,buffer,' ');
    std::getline(output,buffer,' ');
    int cols{};
    cols = std::stoi(buffer);
    //std::cout<<rows;
    output.close();
    return cols;
}

int rows = 0;
int cols = 0;
int generation = 0;

void printGrid(const std::vector<std::vector<bool>>& grid)
{
    int liveCells = 0;
    int dead{};
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols;++j)
        {
            if(grid[i][j])
            {
            std::cout<<"*";
            liveCells++;
            dead = liveCells;
            }
            else
                std::cout<<"_";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Alive cells - >"<<liveCells<<std::endl;
    std::cout<<"Generation - >"<<generation<<std::endl;
    if(dead == 0)
    {
        std::cout<<"ALL CELLS ARE DEAD"<<std::endl;
        stopIt = true;
    }

}

void updateGrid(std::vector<std::vector<bool>>& grid)
{
    std::vector<std::vector<bool>> newGrid(rows,std::vector<bool>(cols,false));
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            int neighbors = 0;
            for(int dx = -1; dx <=1; ++dx)
            {
                for(int dy = -1; dy <= 1; ++dy)
                {
                    if(dx == 0 && dy ==0)
                        continue;
                    int ni = i + dx;
                    int nj = j + dy;
                    if(ni >=0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj])
                        neighbors++;
                }
            }
            if(grid[i][j])
            {
                if(neighbors == 2 || neighbors == 3)
                    newGrid[i][j] = true;
            }
            else
            {
                if(neighbors == 3)
                newGrid[i][j] = true;

            }
            if(newGrid == grid)
            {
                stopIt2 = true;
            }

        }

    }
    grid = newGrid;
}

bool checkAliveCells(std::vector<std::vector<bool>>& grid)
{
    bool check = false;
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            if (grid[i][j] == false) check = false; else check = true;
        }
    }
    return check;
}

void readCellFromFile()
{
    std::ifstream openFile("fieldInit.txt");
    int number{};
    int count = 0;
    while(openFile >> number)
    {
        if(count % 2 == 0)
        {
            coord_x.push_back(number);
        }
        else
        {
            coord_y.push_back(number);
        }
        count++;
    }
    openFile.close();
    coord_x.erase(coord_x.begin());
    coord_y.erase(coord_y.begin());
    openFile.close();
}


void go()
{
    rows = readRowsFromFile();
    cols = readColsFromFile();
    std::vector<std::vector<bool>> grid(rows,std::vector<bool>(cols,false));
    for(int i = 0 ; i < coord_x.size(); ++i)
    {
        grid[coord_x[i]][coord_y[i]] = true;
    }
    for(int cycle = 0;; ++ cycle)
    {
        ++generation;
        std::system("clear");
        printGrid(grid);
        updateGrid(grid);
        if(stopIt == true)
            {
                break;
            }
        if(stopIt2 == true)
            {
             break;
            }
        usleep(2000000);
    }
        if(stopIt2 == true)
        {
            std::system("clear");
            printGrid(grid);
            usleep(2000000);
            generation++;
            std::system("clear");
            printGrid(grid);
            std::cout<<"The world stignized\n";
        }
        if(stopIt == true)
        {
            std::system("clear");
            printGrid(grid);
            usleep(2000000);
            generation--;
            std::system("clear");
            printGrid(grid);
            std::cout<<"The world stignized\n";
        }

}
int main()
{
    readCellFromFile();
    go();
}

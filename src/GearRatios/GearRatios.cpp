#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool IsAdjacentToSymbol(const int Row, const int Column, const std::vector<std::pair<int,int>> SymbolCoordinates);

int GetMissingEnginePart()
{
    std::string SchematicPath = "Content/EngineSchematic.txt";
    std::ifstream File(SchematicPath);
    std::vector<std::pair<int,int>> SymbolCoordinates;

    if(!File.is_open())
    {
        std::cout << "Cannot open the file: " << SchematicPath << std::endl;
        return 0;
    }

    std::string Line;
    std::vector<std::vector<char>> Grid;

    //Parse the file and get symbol coordinates
    while(std::getline(File, Line))
    {
        std::vector<char> Row(Line.begin(), Line.end());
        Grid.push_back(Row);

        //Cache engine part indicator coordinates
        for(int i = 0; i < Line.length(); i++)
        {
            if(Line[i] != '.' && !std::isdigit(Line[i]))
            {
                SymbolCoordinates.push_back(std::make_pair(Grid.size() - 1, i));
            }
        }
    }

    int AdjacentsSum = 0;
    // Iterate and find the adjacent numbers
    for(int i = 0; i < Grid.size(); i++)
    {
        std::vector<int> Adjacents;
        std::string BuiltNumber;
        bool bIsBuildingNumber = false;
        bool bIsAdjacent = false;
        
        for (int j = 0; j < Grid[i].size(); j++)
        {
            char& c = Grid[i][j];
            if(std::isdigit(c))
            {
                bIsBuildingNumber = true;
                BuiltNumber += c;
                if(IsAdjacentToSymbol(i, j, SymbolCoordinates))
                {
                    bIsAdjacent = true;
                }
            }
            else
            {
                if(bIsBuildingNumber && bIsAdjacent)
                {
                    AdjacentsSum += std::stoi(BuiltNumber);
                }

                //Cleanup for next number
                bIsBuildingNumber = false;
                bIsAdjacent = false;
                BuiltNumber.clear();
            }
        }
    }    

    std::cout << AdjacentsSum << std::endl;
    return AdjacentsSum;
}

bool IsAdjacentToSymbol(const int Row, const int Column, const std::vector<std::pair<int,int>> SymbolCoordinates)
{
    for(std::pair<int,int> Coordinates : SymbolCoordinates)
    {
        int SymbolRow = Coordinates.first;
        int SymbolColumn = Coordinates.second;
        bool isAdjacent = (std::abs(Row - SymbolRow) <= 1.0f && std::abs(Column-SymbolColumn) <= 1.0f);

        if(isAdjacent)
        {
            return true;
        }
    }
    return false;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

struct ColorGroup 
{
    std::vector<std::pair<std::string, int>> Colors;
};

struct Game
{
    Game(int InIndex, std::vector<ColorGroup> InGroups) : Index(InIndex), Groups(std::move(InGroups)) {}

    int Index;
    std::vector<ColorGroup> Groups;
};

void ProcessGame()
{
    const std::string FilePath = "Content/GamesRecord.txt";
    std::ifstream File(FilePath);
    
    if (!File)
    {
        std::cerr << "Failed to open file: " << FilePath << std::endl;
        return;
    }
    
    std::map<std::string, int> Inventory = { {"red", 12}, { "green", 13}, { "blue", 14}};

    std::string Line;
    std::vector<Game> Games;

    while (std::getline(File, Line)) 
    {
        std::istringstream LineStream(Line);
        std::string Word;

        // Parse game index
        LineStream >> Word; // "Game"
        int GameIndex;
        LineStream >> GameIndex; // "1:"

        std::string GroupStrings;
        std::getline(LineStream, GroupStrings, ':');
        std::getline(LineStream, GroupStrings);

        std::istringstream GroupStream(GroupStrings);
        std::string GroupString;
        std::vector<ColorGroup> Groups; 
        while (std::getline(GroupStream, GroupString, ';'))
        {
            ColorGroup Group;
            std::istringstream ElementStream(GroupString);
            std::string ElementString;
            while (std::getline(ElementStream, ElementString, ','))
            {
                std::istringstream ElementPairStream(ElementString);
                int Count;
                std::string Color;
                ElementPairStream >> Count >> Color;
                Group.Colors.emplace_back(Color, Count);
            }
            Groups.push_back(Group);
        }
        Games.emplace_back(GameIndex, Groups);
    }

    int PossibleSum = 0;

    for (const auto& game : Games)
    {
        bool IsGamePossible = true;
        for (const auto& group : game.Groups)
        {
            for (const auto& color : group.Colors)
            {
                auto Data = Inventory.find(color.first);
                if (Data != Inventory.end())
                {
                    std::string Status = (color.second <= Data->second) ? " - Possible" : " - Impossible";
                    std::cout << color.first << ": " << color.second << " - out of: " << Data->second << Status << std::endl;
                    if (color.second > Data->second)
                    {
                        IsGamePossible = false;
                        break;
                    }
                }
            }
            if (!IsGamePossible)
            {
                break;
            }
        }
        if (IsGamePossible)
        {
            PossibleSum += game.Index;
        }
        std::cout << "-------------------" << std::endl;
    }
    std::cout << "Possible game indexes sum: " << PossibleSum << std::endl;
}

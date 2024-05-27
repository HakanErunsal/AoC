#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> WordToNumber = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
};

int ContainsWrittenNumber(const std::string Input)
{
    if(Input.length() < 3)
    {
        return -1;
    }

    for(const auto Pair : WordToNumber)
    {
        if(Input.find(Pair.first) != std::string::npos)
        {
            return Pair.second;
        }
    }
    
    return -1;
}

void DecryptDocument() {
    // Open the text file from the Content folder
    int DecryptedValue = 0;

    std::string FilePath = "Content/CalibrationDocument.txt";
    std::ifstream File(FilePath);

    // Check if the file was successfully opened
    if (!File.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    // Read and print each line of the file
    std::string Line;
    int LineIndex = 0;
    while (getline(File, Line)) {
        int FirstDigit = 0, LastDigit = 0;
        std::string WordToNumber;

        for (char Character : Line)
        {
            WordToNumber.push_back(Character);
            if(ContainsWrittenNumber(WordToNumber) != -1)
            {
                
            }

            if(std::isdigit(Character))
            {
                WordToNumber.clear();
                if(FirstDigit == 0)
                    FirstDigit = Character - '0';
                LastDigit = Character - '0';
            }

        }
        
        int DecryptedLineValue = FirstDigit*10 + LastDigit;
        //std::cout << "Line " << LineIndex << ": " << DecryptedLineValue << "\n";
        
        DecryptedValue += DecryptedLineValue;
        LineIndex++;
    }

    std::cout << "Decrypted Value: " << DecryptedValue << std::endl;

    File.close();
}
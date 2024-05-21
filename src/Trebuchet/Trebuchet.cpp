#include <iostream>
#include <fstream>
#include <string>

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
        
        for (char Character : Line)
        {
            if(std::isdigit(Character))
            {
                if(FirstDigit == 0)
                    FirstDigit = Character - '0';
                LastDigit = Character - '0';
            }

        }
        
        int DecryptedLineValue = FirstDigit*10 + LastDigit;
        std::cout << "Line " << LineIndex << ": " << DecryptedLineValue << "\n";
        
        DecryptedValue += DecryptedLineValue;
        LineIndex++;
    }

    std::cout << "Decrypted Value: " << DecryptedValue << std::endl;

    File.close();
}
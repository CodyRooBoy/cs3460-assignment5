#include "WordTree.hpp"

int main()
{
    auto wordTree = readDictionary("dictionary.txt");

    std::string input;
    std::string currentWord;
    int consoleHeight = rlutil::trows();
    std::uint8_t maxPredictions = consoleHeight - 5;

    rlutil::cls();
    rlutil::locate(1, 1);

    while (true)
    {
        char key = rlutil::getkey();
        if (key == rlutil::KEY_BACKSPACE && !input.empty())
        {
            input.pop_back();
            if (!currentWord.empty())
            {
                currentWord.pop_back();
            }
            else
            {
                size_t lastSpace = input.find_last_of(" ");
                currentWord = (lastSpace == std::string::npos) ? input : input.substr(lastSpace + 1);
            }
        }
        else if (std::isalpha(key))
        {
            input += key;
            currentWord += key;
        }
        else if (key == ' ' || key == '\n')
        {
            input += key;
            currentWord.clear();
        }
        else
        {
            continue;
        }

        rlutil::cls();
        rlutil::locate(1, 1);
        std::cout << input;

        if (!currentWord.empty())
        {
            auto predictions = wordTree->predict(currentWord, maxPredictions);

            rlutil::locate(1, 3);
            std::cout << "--- prediction ---";
            int line = 4;
            for (const auto& prediction : predictions)
            {
                rlutil::locate(1, line++);
                std::cout << prediction;
            }
        }
    }

    return 0;
}
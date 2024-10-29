#include "WordTree.hpp"

void WordTree::add(std::string word)
{
    if (word.empty() || !std::all_of(word.begin(), word.end(), ::isalpha))
    {
        return;
    }

    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    auto node = root;

    for (char c : word)
    {
        int index = c - 'a';
        if (!node->children[index])
        {
            node->children[index] = std::make_shared<TreeNode>();
        }
        node = node->children[index];
    }

    node->endOfWord = true;
}

bool WordTree::find(std::string word)
{
    if (word.empty() || !std::all_of(word.begin(), word.end(), ::isalpha))
    {
        return false;
    }

    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    auto node = root;

    for (char c : word)
    {
        int index = c - 'a';
        if (!node->children[index])
        {
            return false;
        }
        node = node->children[index];
    }

    return node->endOfWord;
}

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::vector<std::string> result;

    if (partial.empty() || !std::all_of(partial.begin(), partial.end(), ::isalpha))
    {
        return result;
    }
    std::transform(partial.begin(), partial.end(), partial.begin(), ::tolower);
    auto node = root;

    for (char c : partial)
    {
        int index = c - 'a';
        if (!node->children[index])
        {
            return result;
        }
        node = node->children[index];
    }

    std::queue<std::pair<std::shared_ptr<TreeNode>, std::string>> q;
    q.emplace(node, partial);

    while (!q.empty() && result.size() < howMany)
    {
        auto [currentNode, currentPrefix] = q.front();
        q.pop();

        if (currentNode->endOfWord && currentPrefix != partial)
        {
            result.push_back(currentPrefix);
        }

        for (size_t i = 0; i < 26; i++)
        {
            if (currentNode->children[i])
            {
                q.emplace(currentNode->children[i], currentPrefix + char(i + 'a'));
            }
        }
    }

    return result;
}

std::size_t WordTree::size()
{
    return countWords(root);
}

std::size_t WordTree::countWords(std::shared_ptr<TreeNode> node)
{
    std::size_t count = 0;
    if (node == NULL)
    {
        return count;
    }

    if (node->endOfWord)
    {
        count++;
    }

    for (size_t i = 0; i < 26; i++)
    {
        count += countWords(node->children[i]);
    }

    return count;
}

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c)
                        {
                            return std::isalpha(c);
                        }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c)
                           {
                               return static_cast<char>(std::tolower(c));
                           });
            wordTree->add(word);
        }
    }

    return wordTree;
}
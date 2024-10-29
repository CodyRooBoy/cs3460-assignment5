#pragma once

#include "rlutil.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

class TreeNode
{
  public:
    bool endOfWord;
    std::array<std::shared_ptr<TreeNode>, 26> children;

    TreeNode()
    {
        endOfWord = false;
    }
};

class WordTree
{
  private:
    std::shared_ptr<TreeNode> root;

    std::size_t countWords(std::shared_ptr<TreeNode> node);

  public:
    WordTree()
    {
        root = std::make_shared<TreeNode>();
    }

    void add(std::string word);

    bool find(std::string word);

    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);

    std::size_t size();
};

std::shared_ptr<WordTree> readDictionary(std::string filename);
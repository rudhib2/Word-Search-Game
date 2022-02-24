#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);
  WordLocation LookingForWordH(const std::vector<std::vector<char>>& puzzle,
                               std::string word);
  WordLocation LookingForWordV(const std::vector<std::vector<char>>& puzzle,
                               std::string word);
  WordLocation LookingForWordR(const std::vector<std::vector<char>>& puzzle,
                               std::string word);
  WordLocation LookingForWordL(const std::vector<std::vector<char>>& puzzle,
                               std::string word);

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};

#endif
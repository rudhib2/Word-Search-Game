#include "WordSearchSolver.hpp"

#include <cassert>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "CharPositions.hpp"
#include "WordLocation.hpp"

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle),
    puzzle_height_(puzzle.size()),
    puzzle_width_(puzzle.at(0).size()) {}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  // searhes for word in puzzle_
  // if word found, non empty WordLocation object is returned
  // if word not found after checking CheckDirection return WordLocation{};
  WordLocation a = WordLocation{};
  // WordLocation b;
  // WordLocation c;
  // WordLocation d;
  WordLocation toreturn;
  a = FindWord(word, CheckDirection::kHorizontal);
  if (!(a.word.empty())) {
    std::cout << a.word << std::endl;
    toreturn = a;
  }
  // std::cout << "here" << std::endl;
  a = FindWord(word, CheckDirection::kVertical);
  // std::cout << "here" << std::endl;
  if (!(a.word.empty())) {
    toreturn = a;
    std::cout << a.word << std::endl;
  }
  a = FindWord(word, CheckDirection::kLeftDiag);
  if (!(a.word.empty())) {
    toreturn = a;
    std::cout << a.word << std::endl;
  }
  a = FindWord(word, CheckDirection::kRightDiag);
  if (!(a.word.empty())) {
    toreturn = a;
    std::cout << a.word << std::endl;
  }
  return toreturn;
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  WordLocation x = WordLocation{};
  if (direction == CheckDirection::kHorizontal) {
    x = LookingForWordH(puzzle_, word);
    std::cout << x.word << std::endl;
  } else if (direction == CheckDirection::kVertical) {
    x = LookingForWordV(puzzle_, word);
  } else if (direction == CheckDirection::kRightDiag) {
    x = LookingForWordR(puzzle_, word);
  } else if (direction == CheckDirection::kLeftDiag) {
    x = LookingForWordL(puzzle_, word);
  }
  return x;
}

WordLocation WordSearchSolver::LookingForWordH(
    const std::vector<std::vector<char>>& puzzle, std::string word) {
  WordLocation a = WordLocation{};
  std::vector<CharPositions> v;

  for (size_t row = 0; row < puzzle_height_; ++row) {
    for (size_t col = 0; col < puzzle_width_; ++col) {
      for (size_t i = 0; i < word.length(); ++i) {
        if (LocationInBounds(row, col + i)) {
          if (puzzle.at(row).at(col + i) == word.at(i)) {
            CharPositions p = CharPositions{};
            p.character = word.at(i);
            p.row = row;
            p.col = col + i;
            v.push_back(p);
            if (v.size() == word.length()) {
              a.char_positions = v;
              a.word = word;
            }
          } else {
            v.clear();
          }
        }
      }
    }
  }
  return a;
}

WordLocation WordSearchSolver::LookingForWordV(
    const std::vector<std::vector<char>>& puzzle, std::string word) {
  WordLocation a = WordLocation{};
  std::vector<CharPositions> v;

  for (size_t row = 0; row < puzzle_height_; ++row) {
    for (size_t col = 0; col < puzzle_width_; ++col) {
      for (size_t i = 0; i < word.length(); ++i) {
        if (LocationInBounds(row + i, col)) {
          if (puzzle.at(row + i).at(col) == word.at(i)) {
            CharPositions p = CharPositions{};
            p.character = word.at(i);
            p.row = row + i;
            p.col = col;
            v.push_back(p);
            if (v.size() == word.length()) {
              a.char_positions = v;
              a.word = word;
            }
          } else {
            v.clear();
          }
        } else {
          v.clear();
        }
      }
    }
  }
  return a;
}

// WordLocation WordSearchSolver::LookingForWordV(
//     const std::vector<std::vector<char>>& puzzle, std::string word) {
//   WordLocation a = WordLocation{};
//   std::vector<CharPositions> v;
//   std::cout << a.word << std::endl;
//   for (size_t row = 0; row < puzzle_height_; ++row) {
//     for (size_t col = 0; col < puzzle_width_; ++col) {
//       for (size_t i = 0; i < word.length(); ++i) {
//         if (LocationInBounds(row + i, col)) {
//           if (puzzle.at(row + i).at(col) == word.at(i)) {
//             CharPositions p = CharPositions{};
//             p.character = word.at(i);
//             p.row = row + i;
//             p.col = col;
//             v.push_back(p);
//             if (v.size() == word.length()) {
//               a.word = word;
//               a.char_positions = v;
//             }
//           } else {
//             v.clear();
//           }
//         }
//       }
//     }
//   }
//   std::cout << a.word << std::endl;
//   return a;
// }

WordLocation WordSearchSolver::LookingForWordR(
    const std::vector<std::vector<char>>& puzzle, std::string word) {
  WordLocation a = WordLocation{};

  std::vector<CharPositions> v;
  for (size_t row = 0; row < puzzle_height_; ++row) {
    for (size_t col = 0; col < puzzle_width_; ++col) {
      for (size_t i = 0; i < word.length(); ++i) {
        if (LocationInBounds(row + i, col + i)) {
          if (puzzle.at(row + i).at(col + i) == word.at(i)) {
            CharPositions p = CharPositions{};
            p.character = word.at(i);
            p.row = row + i;
            p.col = col + i;
            v.push_back(p);
            if (v.size() == word.length()) {
              a.char_positions = v;
              a.word = word;
            }
          } else {
            v.clear();
          }
        }
      }
    }
  }

  return a;
}

WordLocation WordSearchSolver::LookingForWordL(
    const std::vector<std::vector<char>>& puzzle, std::string word) {
  WordLocation a = WordLocation{};

  std::vector<CharPositions> v;
  for (size_t row = 0; row < puzzle_height_; ++row) {
    for (size_t col = 0; col < puzzle_width_; ++col) {
      for (size_t i = 0; i < word.length(); ++i) {
        if (LocationInBounds(row + i, col - i)) {
          if (puzzle.at(row + i).at(col - i) == word.at(i)) {
            CharPositions p = CharPositions{};
            p.character = word.at(i);
            p.row = row + i;
            p.col = col - i;
            v.push_back(p);
            if (v.size() == word.length()) {
              a.word = word;
              a.char_positions = v;
            }
          } else {
            v.clear();
          }
        }
      }
    }
  }

  return a;
}

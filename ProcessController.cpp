//
//  STLWordProcessor.cpp
//  assignment6
//
//  Created by rick gessner on 11/12/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "ProcessController.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>

namespace ECE17 {

    std::string columnPad(std::string str, int column_width) {
      if(str.length() < column_width) str = str + std::string(column_width - str.length(), ' ');
      return str;
    }

    bool isPunct(char aChar) {
      static std::string punct(".;?!:,'-()");
      return std::string::npos != punct.find(aChar);
    }

    void removePunct(std::string &str) {
      std::string str_orig = str;
      str.clear();

      for(char c: str_orig) {
        if(!isPunct(c)) str.push_back(c);
      }
    }

    ProcessController::ProcessController() {
      //don't forget to initialze your data members...
    }

    ProcessController::ProcessController(const ProcessController &aCopy) {
      //ocf requirement
    }

    ProcessController::~ProcessController() {
      //dont forget me!
    }

    ProcessController &ProcessController::operator=(const ProcessController &aCopy) {
      return *this;
    }

    //This drives your statistical functions...
    void ProcessController::showStatistics(std::string &anInput, std::ostream &anOutput) {

      anOutput << "\nWord Counts: \n";
      showWordUsage(anInput, anOutput);
      anOutput << "\nWord Pairs: \n";
      showWordPairs(anInput, anOutput);
    }

    void ProcessController::showWordUsage(std::string &anInput, std::ostream &anOutput) {
      std::list<std::string> word_col;
      std::list<int> count_col;

      calcWordUsage(word_col, count_col, anInput);
      printTable("Word", "Count", word_col, count_col, anOutput);
    }

    void ProcessController::showWordPairs(std::string &anInput, std::ostream &anOutput) {
      std::list<std::string> word_pairs_col;
      std::list<int> count_col;

      calcWordPairs(word_pairs_col, count_col, anInput);
      printTable("Word Pairs", "Count", word_pairs_col, count_col, anOutput);
    }

    void ProcessController::printTable(std::string col1_label, std::string col2_label,
                                       std::list<std::string> &col1, std::list<int> &col2,
                                       std::ostream &anOutput) {
      std::cout << "| " << columnPad(col1_label, 30);
      std::cout << "| " << columnPad(col2_label, 10) << " |" << std::endl;
      std::cout << std::string(46, '-') << std::endl;

      std::list<std::string>::iterator col1_it = col1.begin();
      std::list<int>::iterator col2_it = col2.begin();

      while(col1_it != col1.end() && col2_it != col2.end()) {
        std::cout << "| "  << columnPad(*col1_it++, 30);
        std::cout << "| " << columnPad(std::to_string(*col2_it++), 10) << " |" << std::endl;
      }
    }

    void ProcessController::calcWordUsage(std::list<std::string> &word_col, std::list<int> &count_col,
                                          std::string &anInput) {
      word_col.clear();
      count_col.clear();
      std::vector<std::string> wordUse;
      std::vector<int> wordCount;
      std::vector<std::string>::iterator word_it = wordUse.begin();
      //std::vector<int>::iterator count_it = wordCount.begin();
      int index = 0;
      std::string word;
      std::istringstream s(anInput);

      while (s >> word) {
          removePunct(word);
          word_it = std::find(wordUse.begin(), wordUse.end(), word);
          if (word_it == wordUse.end()) {
              wordUse.push_back(word);
              wordCount.push_back(1);
          } else {
              index = word_it - wordUse.begin();
              wordCount[index]++;
          }
      }
      std::copy(wordUse.begin(), wordUse.end(), std::back_inserter(word_col));
      std::copy(wordCount.begin(), wordCount.end(), std::back_inserter(count_col));
    }

    void ProcessController::calcWordPairs(std::list<std::string> &word_pairs_col, std::list<int> &count_col,
                                          std::string &anInput) {
      word_pairs_col.clear();
      count_col.clear();
      std::vector<std::string> wordUse;
      std::vector<int> wordCount;
      std::vector<std::string>::iterator word_it = wordUse.begin();
      int index = 0;
      std::string word1, word2, phrase;
      std::istringstream s(anInput);
      s >> word1;

      while (s >> word2) {
          phrase.clear();
          phrase.append(word1);
          phrase.append(" " + word2);
          word_it = std::find(wordUse.begin(), wordUse.end(), phrase);
          if (word_it == wordUse.end()) {
              wordUse.push_back(phrase);
              wordCount.push_back(1);
          } else {
              index = word_it - wordUse.begin();
              wordCount[index]++;
          }
          word1 = word2;
      }

      std::copy(wordUse.begin(), wordUse.end(), std::back_inserter(word_pairs_col));
      std::copy(wordCount.begin(), wordCount.end(), std::back_inserter(count_col));
    }

    //output your compressed version input the anOutput stream...
    bool ProcessController::compress(std::string &anInput, std::ostream &anOutput) {
      //STUDENT: implement this method...
      anOutput << anInput;
      return true;
    }

    //de-compress given string back to original form, and write it out to anOutput...
    bool ProcessController::decompress(std::string &aBuffer, std::ostream &anOutput) {
      //STUDENT: implement this method...
      anOutput << aBuffer;
      return true;
    }

}

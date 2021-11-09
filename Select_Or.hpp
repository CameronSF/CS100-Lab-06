#ifndef __SELECT_OR_HPP__
#define __SELECT_OR_HPP__

#include <cstring>
#include <string>
#include "select.hpp"
#include <iostream>
#include <vector>


class Select_Or : public Select
{
private:
  std::vector<int> combined;

public:
     Select_Or(Select* one, Select* two) 
    {
      choice1 = one;
      choice2 = two;
      choice1->set_parent(this);
      choice2->set_parent(this);
      std::vector<int> vector1 = choice1->select();
      std::vector<int> vector2 = choice2->select();
      for (unsigned int i = 0; i < vector1.size(); i++)
      {
        combined.push_back(vector1.at(i));
      }
      for (unsigned int i = 0; i < vector2.size(); i++)
      {
        combined.push_back(vector2.at(i));
      }
      sheet_size = choice1->get_sheet_size();
    }

    virtual ~Select_Or(){
      if (parentPtr == nullptr)
      {
        erase(this);
      }
    }

    
    bool select(const Spreadsheet* sheet, int row) const
    {
      
    }

    std::vector<int> select() const 
    {
      return combined;
    }
};
#endif

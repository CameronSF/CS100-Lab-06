#ifndef __SELECT_NOT_HPP__
#define __SELECT_NOT_HPP__

#include <cstring>
#include <string>
#include "select.hpp"
#include <iostream>
#include <vector>


class Select_Not : public Select
{
private:
  std::vector<int> combined;

public:
     Select_Not(Select* one) 
    {
      choice1 = one;
      choice1->set_parent(this);
      std::vector<int> vector1 = choice1->select();
      std::vector<int> vectorAll;
      for (unsigned int k = 0; k < choice1->get_sheet_size(); k++)
      {
        vectorAll.push_back(k);
      }

      for (unsigned int i = 0; i < vectorAll.size(); i++)
      {
        for (unsigned int j = 0; j < vector1.size(); j++)
        {
          if (vectorAll.at(i) != vector1.at(j))
          {
            combined.push_back(vectorAll.at(i));
          }
        }
      }
      
    }

    virtual ~Select_Not(){ 
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




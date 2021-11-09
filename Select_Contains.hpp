#ifndef __SELECT_CONTAINS_HPP__
#define __SELECT_CONTAINS_HPP__

#include <cstring>
#include <string>
#include "select.hpp"
#include <iostream>
#include <vector>


class Select_Contains: public Select_Column
{

private:
  Spreadsheet* current_sheet;

  std::string data;


public:

    Select_Contains(Spreadsheet* sheet, std::string column_name, std::string data_get):Select_Column(sheet, column_name)
    {
      current_sheet = sheet;

      data = data_get;
      sheet_size = sheet->get_data().size();
    }

    virtual ~Select_Contains()
    {

    };
    

    std::vector<int> select() const
    {
      std::vector<int> rows;
      for (unsigned int i = 0; i < current_sheet->get_data().size(); i++)
      {
        if(Select_Column::select(current_sheet, i))
        {
          rows.push_back(i);
        }
      }
      return rows; 
    }

    bool select(const std::string& s) const   
    {
      if(s.find(data) != std::string::npos) 
      {
        return true;
      }
      return false;
    }
   
};
#endif

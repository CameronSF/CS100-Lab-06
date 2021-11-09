#include "spreadsheet.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>
using namespace std;

Spreadsheet::~Spreadsheet()
{
    delete select;
}

void Spreadsheet::set_selection(Select* new_select)
{
    delete select;
    select = new_select;
}

void Spreadsheet::clear()
{
    column_names.clear();
    data.clear();
    delete select;
    select = nullptr;
}

void Spreadsheet::set_column_names(const std::vector<std::string>& names)
{
    column_names=names;
}

void Spreadsheet::add_row(const std::vector<std::string>& row_data)
{
    data.push_back(row_data);
}

int Spreadsheet::get_column_by_name(const std::string& name) const
{
    for(int i=0; i<column_names.size(); i++)
        if(column_names.at(i) == name)
            return i;
    return -1;
}

void Spreadsheet::print_selection(std::ostream& out) const
{
  
  if (select == nullptr)
  {
    std::vector<std::string> current_row;
    for (unsigned int i = 0; i < data.size(); i++)
    {
      current_row = data.at(i);
      for (unsigned int j = 0; j < current_row.size(); j++)
      {
        out << current_row.at(j) << " ";
      }
      out << endl;
    }
  }
  else
  {
    std::vector<int> rowSelect = select->select();
    if (rowSelect.size() == 0) 
    {
      out << "";
      return;
    }
    else
    {
      std::vector<std::string> output;
      for (unsigned int j = 0; j < rowSelect.size(); j++){
        output = data.at(rowSelect.at(j));
        for (unsigned int i = 0; i < output.size(); i++)
        {
          out << output.at(i) << " ";  
        }
        out << endl;
      }
    }
  }
  
  return;
}

std::vector<std::vector<std::string>> Spreadsheet::get_data() const
{
  return data;
}

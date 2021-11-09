#include "spreadsheet.hpp"
#include "select.hpp"
#include "Select_Contains.hpp"
#include "Select_Not.hpp"
#include "Select_Or.hpp"
#include "Select_And.hpp"
#include "gtest/gtest.h"
#include <string>
#include <sstream>
using namespace std;

TEST(TestSelect_Contains, TestingContains)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HiveMind","Teemo","15"});
  sheet.add_row({"Soul","Ashe","20"});
  sheet.add_row({"TheJoker","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  std::stringstream s;
  sheet.set_selection(new Select_Contains(&sheet, "Username", "Joke"));
  sheet.print_selection(s);
  EXPECT_EQ("TheJoker Twisted Fate 21 \nJokesOnYou Jinx 30 \n", s.str());
  sheet.set_selection(new Select_Contains(&sheet, "Level", "21"));
  sheet.print_selection(s);
  EXPECT_EQ("TheJoker Twisted Fate 21 \nMindlessMachine Blitzcrank 21 \n", s.str());
}

TEST(TestSelect_Contains, TestingEmpty)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HiveMind","Teemo","15"});
  sheet.add_row({"Soul","Ashe","20"});
  sheet.add_row({"TheJoker","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  std::stringstream s;
  sheet.set_selection(new Select_Contains(&sheet, "Username", ""));
  sheet.print_selection(s);
  EXPECT_EQ("", s.str());
}

TEST(TestSelect_Contains, TestingNoColumn)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HiveMind","Teemo","15"});
  sheet.add_row({"Soul","Ashe","20"});
  sheet.add_row({"TheJoker","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  std::stringstream s;
  sheet.set_selection(new Select_Contains(&sheet, "Age", "21"));
  sheet.print_selection(s);
  EXPECT_EQ("\n", s.str());
}

TEST(TestSelect_Contains, TestingMultipleColumns)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Name", "Name", "Level"});
  sheet.add_row({"HiveMind","Teemo","15"});
  sheet.add_row({"Soul","Ashe","20"});
  sheet.add_row({"TheJoker","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  std::stringstream s;
  sheet.set_selection(new Select_Contains(&sheet, "Name", "Soul"));
  sheet.print_selection(s);
  EXPECT_EQ("Soul Ashe 20 \n", s.str());
}

TEST(TestSelect_Contains, TestingUpperCase)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HIVEMIND","Teemo","15"});
  sheet.add_row({"soul","Ashe","20"});
  sheet.add_row({"THEJOKER","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  std::stringstream s;
  sheet.set_selection(new Select_Contains(&sheet, "Username", "Joke"));
  sheet.print_selection(s);
  EXPECT_EQ("JokesOnYou Jinx 30 \n", s.str());
}

TEST(TestSelect_Contains, TestingPartial)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HIVEMIND","Teemo","15"});
  sheet.add_row({"soul","Ashe","20"});
  sheet.add_row({"TheJok","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  std::stringstream s;
  sheet.set_selection(new Select_Contains(&sheet, "Username", "Joke"));
  sheet.print_selection(s);
  EXPECT_EQ("JokesOnYou Jinx 30 \n", s.str());
}

TEST(TestSelect_Contains, TestingSelectFunction)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HiveMind","Teemo","15"});
  sheet.add_row({"Soul","Ashe","20"});
  sheet.add_row({"TheJoker","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  Select* test = new Select_Contains(&sheet, "Username", "Joke");
  vector<int> test_vector = {2,3};
  EXPECT_EQ(test_vector, test->select());
}


TEST(TestSelect_And, TestingAnd)
{
  Spreadsheet sheet;

  sheet.set_column_names({"First_name", "Class", "Element"});
  sheet.add_row({"Zavala","Titan","Arc"});
  sheet.add_row({"Cayde", "Hunter", "Solar"});
  sheet.add_row({"Ikora", "Warlock", "Void"});
  sheet.add_row({"Shaxx", "Titan", "Arc"});
  sheet.add_row({"Osiris", "Warlock", "Solar"});
  std::stringstream s;
  sheet.set_selection(new Select_And(new Select_Contains(&sheet, "Class", "Warlock"), new Select_Contains(&sheet, "Element", "Solar")));
  sheet.print_selection(s);
  EXPECT_EQ("Osiris Warlock Solar \n", s.str());
} 

TEST(TestSelect_And, TestingAndOr)
{
  Spreadsheet sheet;

  sheet.set_column_names({"First_name", "Class", "Element"});
  sheet.add_row({"Zavala","Titan","Arc"});
  sheet.add_row({"Cayde", "Hunter", "Solar"});
  sheet.add_row({"Ikora", "Warlock", "Void"});
  sheet.add_row({"Shaxx", "Titan", "Arc"});
  sheet.add_row({"Osiris", "Warlock", "Solar"});
  std::stringstream s;
  sheet.set_selection(new Select_And(new Select_Contains(&sheet, "Class", "Warlock"), new Select_Or(new Select_Contains(&sheet, "First_name", "Ikora"), new Select_Contains(&sheet, "First_name", "Zavala")));
  sheet.print_selection(s);
  EXPECT_EQ("Ikora Warlock Void \n", s.str());
} 

TEST(TestSelect_And, TestingAndSelect)
{
  sheet.set_column_names({"First_name", "Class", "Element"});
  sheet.add_row({"Zavala","Titan","Arc"});
  sheet.add_row({"Cayde", "Hunter", "Solar"});
  sheet.add_row({"Ikora", "Warlock", "Void"});
  sheet.add_row({"Shaxx", "Titan", "Arc"});
  sheet.add_row({"Osiris", "Warlock", "Solar"});

  Select* test = new Select_And(new Select_Contains(&sheet, "Class", "Warlock"), new Select_Contains(&sheet, "Element", "Solar")));

  vector<int> test_vector = {4};
  EXPECT_EQ(test_vector, test->select());
}


TEST(TestSelect_Not, TestingNot)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HiveMind","Teemo","15"});
  sheet.add_row({"Soul","Ashe","20"});
  sheet.add_row({"TheJoker","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  std::stringstream s;
  sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Champion", "Teemo")));
  sheet.print_selection(s);
  EXPECT_EQ("Soul Ashe 20 \nTheJoker Twisted Fate 21 \nJokesOnYou Jinx 30 \nMindlessMachine Blitzcrank 21 \n", s.str());
} 

TEST(TestSelect_Not, TestingNotSelect)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HiveMind","Teemo","15"});
  sheet.add_row({"Soul","Ashe","20"});
  sheet.add_row({"TheJoker","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});

  Select* test = new Select_Not(new Select_Contains(&sheet, "Champion", "Teemo")));
  vector<int> test_vector = {1,2,3,4};
  EXPECT_EQ(test_vector, test->select());
}


TEST(TestSelect_Or, TestingOr)
{
  Spreadsheet sheet;

  sheet.set_column_names({"First_name", "Class", "Element"});
  sheet.add_row({"Zavala","Titan","Arc"});
  sheet.add_row({"Cayde", "Hunter", "Solar"});
  sheet.add_row({"Ikora", "Warlock", "Void"});
  sheet.add_row({"Shaxx", "Titan", "Arc"});
  sheet.add_row({"Osiris", "Warlock", "Solar"});

  std::stringstream s;
  sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Class", "Titan"), new Select_Contains(&sheet, "First_name", "Ikora"));
  sheet.print_selection(s);
  EXPECT_EQ("Zavala Titan Arc \nIkora Warlock Void \nShaxx Titan Arc \n", s.str());
} 

TEST(TestSelect_Not_And, TestNotAnd)
{
  Spreadsheet sheet;

  sheet.set_column_names({"Username", "Champion", "Level"});
  sheet.add_row({"HiveMind","Teemo","15"});
  sheet.add_row({"Soul","Ashe","20"});
  sheet.add_row({"TheJoker","Twisted Fate","21"});
  sheet.add_row({"JokesOnYou","Jinx","30"});
  sheet.add_row({"MindlessMachine","Blitzcrank","21"});
  sheet.add_row({"MindYourBussiness", "Blitzcrnank", "21"});

  std::stringstream s;
  sheet.set_selection(new Select_Not(new Select_And(new Select_Contains(&sheet, "Username", "Mind"), new Select_Contains(&sheet, "Champion", "Blitzcrank"))));
  sheet.print_selection(s);
  EXPECT_EQ("HiveMind Teemo 15 \nSoul Ashe 20 \nTheJoker Twisted Fate 21 \nJokesOnYou Jinx 30 \n", s.str());
} 

TEST(TestSelect_Not_Or, TestNotOr)
{
  Spreadsheet sheet;

  sheet.set_column_names({"First_name", "Class", "Element"});
  sheet.add_row({"Zavala","Titan","Arc"});
  sheet.add_row({"Cayde", "Hunter", "Solar"});
  sheet.add_row({"Ikora", "Warlock", "Void"});
  sheet.add_row({"Shaxx", "Titan", "Arc"});
  sheet.add_row({"Osiris", "Warlock", "Solar"});
  std::stringstream s;
  sheet.set_selection(new Select_Not(new Select_Or(new Select_Contains(&sheet, "Class", "Warlock"), new Select_Contains(&sheet, "Element", "Solar")));
  sheet.print_selection(s);
  EXPECT_EQ("Zavala Titan Arc \nShaxx Titan Arc \n", s.str());
}

TEST(TestSelect_Or, TestingOrSelect)
{
  sheet.set_column_names({"First_name", "Class", "Element"});
  sheet.add_row({"Zavala","Titan","Arc"});
  sheet.add_row({"Cayde", "Hunter", "Solar"});
  sheet.add_row({"Ikora", "Warlock", "Void"});
  sheet.add_row({"Shaxx", "Titan", "Arc"});
  sheet.add_row({"Osiris", "Warlock", "Solar"});

  Select* test = new Select_Or(new Select_Contains(&sheet, "Class", "Warlock"), new Select_Contains(&sheet, "Element", "Solar")));

  vector<int> test_vector = {1, 2, 4};
  EXPECT_EQ(test_vector, test->select());
}


TEST(TestSelect_And_Not_Or, TestAndNotOr)
{
  Spreadsheet sheet;

  sheet.set_column_names({"First_name", "Class", "Element"});
  sheet.add_row({"Zavala","Titan","Arc"});
  sheet.add_row({"Cayde", "Hunter", "Solar"});
  sheet.add_row({"Ikora", "Warlock", "Void"});
  sheet.add_row({"Shaxx", "Titan", "Arc"});
  sheet.add_row({"Osiris", "Warlock", "Solar"});
  sheet.add_row({})
  
  std::stringstream s;
  sheet.set_selection(new Select_And(new Select_Not(new Select_Contains(&sheet, "First_name", "Shaxx"), new Select_Or(new Select_Contains(&sheet, "Element", "Solar"), new Select_Contains(&sheet, "Element", "Void")));
  sheet.print_selection(s);
  EXPECT_EQ("Cayde Hunter Solar \nIkora Warlock Void \nOsiris Warlock Solar \n", s.str());
} 


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

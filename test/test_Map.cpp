
#include <fstream>
#include <../gtest/gtest.h>
#include "TMap.h"

TEST(TSortMap, can_create_sortmap)
{
  TSortMap<int, double> sm(10);
  ASSERT_NO_THROW(sm);
}

TEST(TSortMap, can_add_elem)
{
  TSortMap<int, double> e;
  e.Add(2, 2);
  e.Add(1, 1);
  e.Add(3, 3);
  ofstream fout("output.txt");
  fout << e;
  fout.close();
  ifstream fin("output.txt");
  string s;
  string sum;
  while (getline(fin, s))
  {
    sum += s;
  }
  string exps = "1: 1 2: 2 3: 3 ";
  EXPECT_EQ(exps, sum);
}

TEST(TSortMap, can_find_elem)
{
  TSortMap<int, double> e;
  e.Add(2, 2);
  e.Add(1, 1);
  e.Add(3, 3);
  vector<double> v;
  v.push_back(e.Find(1));
  v.push_back(e.Find(3));
  v.push_back(e.Find(2));
  vector<double> expv;
  expv.push_back(1);
  expv.push_back(3);
  expv.push_back(2);
  EXPECT_EQ(expv, v);
}

TEST(TSortMap, can_index_elem)
{
  TSortMap<int, double> e;
  e.Add(2, 2);
  e.Add(1, 1);
  e.Add(3, 3);
  vector<double> v;
  v.push_back(e[1]);
  v.push_back(e[3]);
  v.push_back(e[2]);
  vector<double> expv;
  expv.push_back(1);
  expv.push_back(3);
  expv.push_back(2);
  EXPECT_EQ(expv, v);
}

TEST(TSortMap, can_delete_elem)
{
  TSortMap<int, double> e;
  e.Add(1, 1);
  e.Add(2, 2);
  e.Add(3, 3);
  e.Delete(2);
  ofstream fout("output.txt");
  fout << e;
  fout.close();
  ifstream fin("output.txt");
  string s;
  string sum;
  while (getline(fin, s))
  {
    sum += s;
  }
  string exps = "1: 1 3: 3 ";
  EXPECT_EQ(exps, sum);
}

TEST(TSortMap, can_iter_elem)
{
  TSortMap<int, double> e;
  e.Add(1, 1);
  e.Add(2, 2);
  e.Add(3, 3);
  TIterSortMap<int, double> iter = e.GetBegin();
  iter.GoNext();
  iter.GoNext();
  EXPECT_EQ(3, iter.Get().GetVal());
}
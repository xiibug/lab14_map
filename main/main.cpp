#include <iostream>
#include "Table.h"

int main()
{
  ofstream fout("output.txt");
  TSortMap<int, double> sm;
  sm.Add(5, 5);
  sm.Add(4, 4);
  sm.Add(11, 11);
  sm.Add(10, 10);
  sm.Add(12, 12);
  sm.Add(7, 7);
  sm.Add(6, 6);
  sm.Add(8, 8);
  fout << sm;
  fout.close();
  ifstream fin("output.txt");
  string s;
  string sum;
  while (getline(fin, s))
  {
    sum += s;
  }
  cout << sum;
  fin.close();
}
#pragma once
#include <fstream>
#include <iostream>

using namespace std;


void inputData(string path)
{
   fstream fin(path);
   int arr[5];
   for (int i = 0; i < 5; i++)
   {
      int el = 0;
      fin >> el;
      arr[i] = el;
   }
   for (int value : arr)
      cout << value << " ";
}
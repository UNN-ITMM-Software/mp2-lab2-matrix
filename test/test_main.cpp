#include <gtest.h>
#include "Triangular_matrix.h"
#include "Lent_matrix.h"
#include "Vector.h"
using namespace std;

int main(int argc, char **argv)
{

  ///*TLentDynamicMatrix<int> g(6, 3);
  //g[0][0] = 4; g[0][1] = 8; g[0][2] = 9; g[0][3] = 6;
  //g[1][0] = 7; g[1][1] = 8; g[1][2] = 6; g[1][3] = 5; g[1][4] = 4;
  //g[2][0] = 1; g[2][1] = 2; g[2][2] = 3; g[2][3] = 4; g[2][4] = 5; g[2][5] = 6;
  //g[3][0] = 7; g[3][1] = 6; g[3][2] = 8; g[3][3] = 3; g[3][4] = 2;
  //g[4][0] = 3; g[4][1] = 7; g[4][2] = 2; g[4][3] = 1;*/


  //TLentDynamicMatrix<int> g(5, 3);
  //g[0][0] = 4; g[0][1] = 8; g[0][2] = 9; 
  //g[1][0] = 7; g[1][1] = 8; g[1][2] = 6; g[1][3] = 5; 
  //g[2][0] = 1; g[2][1] = 2; g[2][2] = 3; g[2][3] = 4; g[2][4] = 5; 
  //g[3][0] = 7; g[3][1] = 6; g[3][2] = 8; g[3][3] = 3; 
  //g[4][0] = 3; g[4][1] = 7; g[4][2] = 2; 

  ///*for (int i = 0; i < 5; i++)
  //{
  //  cout << g[i] << "\n";
  //}*/

  ///*cout << endl << "Vvedite\n";
  //TLentDynamicMatrix<int> x(4, 2);
  //cin >> x;
  //cout << endl << "Vvod zakonchen";*/
  ///*x[0][0] = 2; x[0][1] = 5; x[0][2] = 8;
  //x[1][0] = 1; x[1][1] = 4; x[1][2] = 7; x[1][3] = 10;
  //x[2][0] = 3; x[2][1] = 6; x[2][2] = 9;*/

  ///*for (int i = 0; i < 3; i++)
  //{
  //  cout << x[i] << "\n";
  //}*/
  ///*cout << c[0][0] << "\n";
  //cout << c[1][0] << "\t" << c[1][1] << "\n";
  //cout << c[2][0] << "\t" << c[2][1] << "\t" << c[2][2] << "\n";*/
  //return 0;

  //int n = 3;
  //TDynamicVector<int> a(n);
  //for (int i = 0; i < n; i++)
  //{
  //  a[i] = i + 1;
  //}
  //TDynamicVector<int> b = a;

  //TDynamicVector<int> c;

  //c = a + b;

  //std::cout << c;

  //for (auto i = c.begin(); i != c.end(); ++i)
  //{
  //  std::cout << *i;
  //}

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <gtest.h>
#include "tTriangularMatrix.h"
#include "tBandMatrix.h"
#include "tVector.h"
#include "tMatrix.h"

using namespace std;

int main(int argc, char **argv)
{
  TBandDynamicMatrix<int> g(6, 3);
  g[0][0] = 1;  g[0][1] = 2;  g[0][2] = 3;  g[0][3] = 4;
  g[1][0] = 5;  g[1][1] = 6;  g[1][2] = 7;  g[1][3] = 8;  g[1][4] = 9;
  g[2][0] = 10; g[2][1] = 11; g[2][2] = 12; g[2][3] = 13; g[2][4] = 14; g[2][5] = 15;
  g[3][0] = 16; g[3][1] = 17; g[3][2] = 18; g[3][3] = 19; g[3][4] = 20;
  g[4][0] = 21; g[4][1] = 22; g[4][2] = 23; g[4][3] = 24;

  int n = 10;
  TDynamicVector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = i + 1;

  TDynamicVector<int> b = (a * 10);

  TDynamicVector<int> c;
  c = b - a;

  cout << "Vector b - a = \n";
  for (auto i = c.begin(); i != c.end(); i++)
    cout << *i << ' ';
  cout << endl;

  TDynamicMatrix<int> matrix1(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      matrix1[i][j] = i + j * 3 + 1;

  cout << "Matrix1 =: \n" << matrix1;

  TDynamicMatrix<int> matrix2(matrix1), result(n);
  cout << "\nMatrix2 =: \n" << matrix2;

  result = matrix2 * matrix1;
  cout << "\nMatrix mat2 * mat1 =: \n" << result;

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

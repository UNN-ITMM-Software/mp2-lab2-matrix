#include <gtest.h>
#include <cstdlib> // ��� ������ � �������� system()
using namespace std;

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int returnable = RUN_ALL_TESTS();
  system("pause"); // ������� �������� ������
  return returnable;
}

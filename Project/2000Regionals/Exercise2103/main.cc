#include <iostream>

struct piece
{
   bool isSpecial;
   int position;
};

int main(int argc, char** argv)
{
   int r, w;
   piece[12] redPieces;
   piece[12] whitePieces;

   while (std::cin >> r >> w && r != 0 && w != 0)
   {
      for (int i = 0; i < r; ++i)
      {
         int val;
         std::cin >> val;
      }
   }

   return 0;
}
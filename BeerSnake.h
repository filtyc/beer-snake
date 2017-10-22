#pragma once

#include <QWidget>
#include <QImage>
#include <array>


class BeerSnake : public QWidget {

public:
   BeerSnake(QWidget *parent = 0);
protected:
   void paintEvent(QPaintEvent *);
private:
   static const int ITEM_SIDE = 30;
   static const int ITEMS_HORIZONTALLY = 20;
   static const int ITEMS_VERTICALLY = 20;
   static const int BOARD_WIDTH = ITEM_SIDE * ITEMS_HORIZONTALLY;
   static const int BOARD_HIGHT = ITEM_SIDE * ITEMS_VERTICALLY;
   static const int MAX_LENGTH = ITEMS_HORIZONTALLY * ITEMS_VERTICALLY;

   int length;
   std::array<int, MAX_LENGTH> snakeXs;
   std::array<int, MAX_LENGTH> snakeYs;

   QImage head;
   QImage body;
   QImage beer;

   void loadImages();
   void startGame();

};

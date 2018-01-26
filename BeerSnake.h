#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QImage>
#include <QTimer>
#include <array>

class BeerSnake : public QWidget {

public:
   BeerSnake(QWidget *parent = 0);
protected:
   void paintEvent(QPaintEvent *);
   void keyPressEvent(QKeyEvent *);
private:
   static const int ITEM_SIDE = 30;
   static const int ITEMS_HORIZONTALLY = 16;
   static const int ITEMS_VERTICALLY = 20;
   static const int BOARD_WIDTH = ITEM_SIDE * ITEMS_HORIZONTALLY;
   static const int BOARD_HIGHT = ITEM_SIDE * ITEMS_VERTICALLY;
   static const int MAX_LENGTH = ITEMS_HORIZONTALLY * ITEMS_VERTICALLY;
   static const int INITIAL_LENGHT = 1;
   static const int INITIAL_INTERVAL = 200;
   static const int FINAL_INTERVAL = 100;
   static const int INTERVAL_DELTA = 2;
   static const int LAST_X = (ITEMS_HORIZONTALLY - 1) * ITEM_SIDE;
   static const int LAST_Y = (ITEMS_VERTICALLY - 1) * ITEM_SIDE;

   enum Direction {Up, Right, Down, Left};

   int length;
   std::array<int, MAX_LENGTH> snakeXs;
   std::array<int, MAX_LENGTH> snakeYs;
   int direction;
   int newDirection;
   int beerX;
   int beerY;
   bool gameOver;

   int &headX = snakeXs.at(0);
   int &headY = snakeYs.at(0);

   QImage head;
   QImage body;
   QImage beer;

   QTimer *timer;

   void onTimeOut();
   void loadImages();
   void startGame();
   void changeDirection();
   void move();
   void placeBeer();
   void drinkBeer();
   void checkCollision();
};

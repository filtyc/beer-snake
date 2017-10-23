#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QImage>
#include <array>


class BeerSnake : public QWidget {

public:
   BeerSnake(QWidget *parent = 0);
protected:
   void paintEvent(QPaintEvent *);
   void timerEvent(QTimerEvent *);
   void keyPressEvent(QKeyEvent *);
private:
   static const int ITEM_SIDE = 30;
   static const int ITEMS_HORIZONTALLY = 16;
   static const int ITEMS_VERTICALLY = 20;
   static const int BOARD_WIDTH = ITEM_SIDE * ITEMS_HORIZONTALLY;
   static const int BOARD_HIGHT = ITEM_SIDE * ITEMS_VERTICALLY;
   static const int MAX_LENGTH = ITEMS_HORIZONTALLY * ITEMS_VERTICALLY;
   static const int INITIAL_STEP_TIME = 200;
   static const int FINAL_STEP_TIME = 100;
   static const int STEP_TIME_INCREMENT = 2;
   enum Direction {Up, Right, Down, Left};

   int length;
   int stepTime;
   std::array<int, MAX_LENGTH> snakeXs;
   std::array<int, MAX_LENGTH> snakeYs;
   int direction;
   int newDirection;
   int beerX;
   int beerY;
   bool gameOver;
   int timerID;

   QImage head;
   QImage body;
   QImage beer;

   void loadImages();
   void startGame();
   void changeDirection();
   void move();
   void placeBeer();
   void drinkBeer();
   void checkCollision();

};

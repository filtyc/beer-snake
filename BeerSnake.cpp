#include <BeerSnake.h>
#include <QPainter>

BeerSnake::BeerSnake(QWidget *parent) : QWidget(parent) {
   setStyleSheet("background-color:white;");
   resize(BOARD_WIDTH, BOARD_HIGHT);
   loadImages();
   startGame();
}

void BeerSnake::loadImages() {
   head.load("images/head.png");
   body.load("images/body.png");
   beer.load("images/beer.png");
}

void BeerSnake::startGame() {
   length = 2;
   direction = BeerSnake::UP;
   newDirection = BeerSnake::UP;
   snakeXs.at(0) = (ITEMS_HORIZONTALLY/2-1)*ITEM_SIDE;
   snakeYs.at(0) = (ITEMS_VERTICALLY/2-1)*ITEM_SIDE;
   snakeXs.at(1) = snakeXs.at(0);
   snakeYs.at(1) = snakeYs.at(0) + ITEM_SIDE;
   startTimer(STEP_TIME);
}

void BeerSnake::paintEvent(QPaintEvent *e) {
   Q_UNUSED(e);

   QPainter painter(this);

   painter.drawImage(snakeXs.at(0), snakeYs.at(0), head);

   for (int piece = 1; piece < length; piece++) {
      painter.drawImage(snakeXs.at(piece), snakeYs.at(piece), body);
   }
}

void BeerSnake::timerEvent(QTimerEvent *e) {
   Q_UNUSED(e);
   changeDirection();
   move();
   repaint();
}

void BeerSnake::keyPressEvent(QKeyEvent *e) {
   int key = e->key();
   switch(key) {
      case Qt::Key_Up: {
         newDirection = BeerSnake::UP;
         break;
      }
      case Qt::Key_Right: {
         newDirection = BeerSnake::RIGHT;
         break;
      }
      case Qt::Key_Down: {
         newDirection = BeerSnake::DOWN;
         break;
      }
      case Qt::Key_Left: {
         newDirection = BeerSnake::LEFT;
      }
      default: {
         break;
      }
   }
}

void BeerSnake::move() {
   for (int piece = (length - 1); piece > 0; piece--) {
      snakeXs.at(piece) = snakeXs.at(piece - 1);
      snakeYs.at(piece) = snakeYs.at(piece - 1);
   }

   switch(direction) {
      case BeerSnake::UP: {
         if (snakeYs.at(0) == 0){
            snakeYs.at(0) = (ITEMS_VERTICALLY - 1) * ITEM_SIDE;
         }
         else {
            snakeYs.at(0) -= ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::RIGHT: {
         if (snakeXs.at(0) == (ITEMS_HORIZONTALLY - 1) * ITEM_SIDE) {
            snakeXs.at(0) = 0;
         }
         else {
            snakeXs.at(0) += ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::DOWN: {
         if (snakeYs.at(0) == (ITEMS_VERTICALLY - 1) * ITEM_SIDE) {
            snakeYs.at(0) = 0;
         }
         else {
            snakeYs.at(0) += ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::LEFT: {
         if (snakeXs.at(0) == 0) {
            snakeXs.at(0) = (ITEMS_HORIZONTALLY - 1) * ITEM_SIDE;
         }
         else {
            snakeXs.at(0) -= ITEM_SIDE;
         }
      }
   }
}

void BeerSnake::changeDirection() {
   if (direction != newDirection) {
      switch(newDirection) {
         case BeerSnake::UP: {
            if (direction != BeerSnake::DOWN) {
               direction = newDirection;
            }
            break;
         }
         case BeerSnake::RIGHT: {
            if (direction != BeerSnake::LEFT) {
               direction = newDirection;
            }
            break;
         }
         case BeerSnake::DOWN: {
            if (direction != BeerSnake::UP) {
               direction = newDirection;
            }
            break;
         }
         case BeerSnake::LEFT: {
            if (direction != BeerSnake::RIGHT) {
               direction = newDirection;
            }
            break;
         }
      }
   }
}

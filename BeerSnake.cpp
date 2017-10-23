#include <BeerSnake.h>
#include <QPainter>
#include <QTime>
#include <QApplication>

BeerSnake::BeerSnake(QWidget *parent) : QWidget(parent) {
   setStyleSheet("background-color:white;");
   resize(BOARD_WIDTH, BOARD_HIGHT);
   setFixedSize(size());
   loadImages();
   startGame();
}

void BeerSnake::loadImages() {
   head.load("images/head.png");
   body.load("images/body.png");
   beer.load("images/beer.png");
}

void BeerSnake::startGame() {
   gameOver = false;
   length = 2;
   stepTime = INITIAL_STEP_TIME;
   direction = BeerSnake::Up;
   newDirection = BeerSnake::Up;
   snakeXs.at(0) = (ITEMS_HORIZONTALLY/2-1)*ITEM_SIDE;
   snakeYs.at(0) = (ITEMS_VERTICALLY/2-1)*ITEM_SIDE;
   snakeXs.at(1) = snakeXs.at(0);
   snakeYs.at(1) = snakeYs.at(0) + ITEM_SIDE;
   placeBeer();
   timerID = startTimer(stepTime);
}

void BeerSnake::paintEvent(QPaintEvent *e) {
   Q_UNUSED(e);

   QPainter painter(this);

   if (!gameOver) {
      painter.drawImage(snakeXs.at(0), snakeYs.at(0), head);

      for (int piece = 1; piece < length; piece++) {
         painter.drawImage(snakeXs.at(piece), snakeYs.at(piece), body);
      }

      painter.drawImage(beerX, beerY, beer);
   }
   else {
      killTimer(timerID);
      QString message;
      message.setNum(length - 2);
      message.append(" beers was 1 too many...");
      QFont font("Courier", 17, QFont::DemiBold);
      QFontMetrics fm(font);
      int textWidth = fm.width(message);
      painter.setFont(font);
      int h = height();
      int w = width();
      painter.translate(QPoint(w/ 2, h/2));
      painter.drawText(-textWidth/2, 0, message);
   }

}

void BeerSnake::timerEvent(QTimerEvent *e) {
   Q_UNUSED(e);
   checkCollision();
   changeDirection();
   drinkBeer();
   move();
   repaint();
}

void BeerSnake::keyPressEvent(QKeyEvent *e) {
   int key = e->key();
   switch(key) {
      case Qt::Key_Up: {
         newDirection = BeerSnake::Up;
         break;
      }
      case Qt::Key_Right: {
         newDirection = BeerSnake::Right;
         break;
      }
      case Qt::Key_Down: {
         newDirection = BeerSnake::Down;
         break;
      }
      case Qt::Key_Left: {
         newDirection = BeerSnake::Left;
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
      case BeerSnake::Up: {
         if (snakeYs.at(0) == 0){
            snakeYs.at(0) = (ITEMS_VERTICALLY - 1) * ITEM_SIDE;
         }
         else {
            snakeYs.at(0) -= ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::Right: {
         if (snakeXs.at(0) == (ITEMS_HORIZONTALLY - 1) * ITEM_SIDE) {
            snakeXs.at(0) = 0;
         }
         else {
            snakeXs.at(0) += ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::Down: {
         if (snakeYs.at(0) == (ITEMS_VERTICALLY - 1) * ITEM_SIDE) {
            snakeYs.at(0) = 0;
         }
         else {
            snakeYs.at(0) += ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::Left: {
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
         case BeerSnake::Up: {
            if (direction != BeerSnake::Down) {
               direction = newDirection;
            }
            break;
         }
         case BeerSnake::Right: {
            if (direction != BeerSnake::Left) {
               direction = newDirection;
            }
            break;
         }
         case BeerSnake::Down: {
            if (direction != BeerSnake::Up) {
               direction = newDirection;
            }
            break;
         }
         case BeerSnake::Left: {
            if (direction != BeerSnake::Right) {
               direction = newDirection;
            }
            break;
         }
      }
   }
}

void BeerSnake::placeBeer() {
   QTime time = QTime::currentTime();
   qsrand((uint)time.msec());
   int r = qrand() % (ITEMS_HORIZONTALLY - 1);
   beerX = r * ITEM_SIDE;
   r = qrand() % (ITEMS_VERTICALLY - 1);
   beerY = r * ITEM_SIDE;
   bool onSnake = false;
   for (int piece = 0; piece < length; piece++) {
      if (beerX == snakeXs.at(piece) && beerY == snakeYs.at(piece)) {
         onSnake = true;
      }
   }
   if (onSnake) {
      placeBeer();
   }
}

void BeerSnake::drinkBeer() {
   if (beerX == snakeXs.at(0) && beerY == snakeYs.at(0)) {
      ++length;
      placeBeer();
      if (stepTime > FINAL_STEP_TIME) {
         stepTime -= STEP_TIME_INCREMENT;
         killTimer(timerID);
         timerID = startTimer(stepTime);
      }
   }
}

void BeerSnake::checkCollision() {
   for (int piece = 1; piece < length; piece++) {
      if (snakeXs.at(0) == snakeXs.at(piece) &&
         snakeYs.at(0) == snakeYs.at(piece)) {
         gameOver = true;
      }
   }
}

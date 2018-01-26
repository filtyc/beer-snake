#include <BeerSnake.h>
#include <QPainter>
#include <QApplication>
#include <QDateTime>

BeerSnake::BeerSnake(QWidget *parent) : QWidget(parent) {
   setStyleSheet("background-color:white;");
   resize(BOARD_WIDTH, BOARD_HIGHT);
   setFixedSize(size());
   loadImages();
   startGame();
}

void BeerSnake::loadImages() {
   head.load(":/images/head.png");
   body.load(":/images/body.png");
   beer.load(":/images/beer.png");
}

void BeerSnake::startGame() {
   gameOver = false;
   length = INITIAL_LENGHT;
   direction = BeerSnake::Up;
   newDirection = BeerSnake::Up;
   headX = (ITEMS_HORIZONTALLY/2-1)*ITEM_SIDE;
   headY = (ITEMS_VERTICALLY/2-1)*ITEM_SIDE;
   placeBeer();
   timer = new QTimer(this);
   timer->setInterval(INITIAL_INTERVAL);
   connect(timer, &QTimer::timeout, this, &BeerSnake::onTimeOut);
   timer->start();
}

void BeerSnake::paintEvent(QPaintEvent *e) {
   Q_UNUSED(e);

   QPainter painter(this);

   if (!gameOver) {
      painter.drawImage(headX, headY, head);

      for (int piece = 1; piece < length; piece++) {
         painter.drawImage(snakeXs.at(piece), snakeYs.at(piece), body);
      }

      painter.drawImage(beerX, beerY, beer);
   }
   else {
      timer->stop();
      QString message;
      message.setNum(length - INITIAL_LENGHT);
      message.append(" beers was 1 too many...");
      QFont font("Courier", 17, QFont::DemiBold);
      QFontMetrics fm(font);
      int textWidth = fm.width(message);
      painter.setFont(font);
      painter.translate(QPoint(BOARD_WIDTH/ 2, BOARD_HIGHT/2));
      painter.drawText(-textWidth/2, 0, message);
   }

}

void BeerSnake::onTimeOut() {
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
         break;
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
         if (headY == 0){
            headY = LAST_Y;
         }
         else {
            headY -= ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::Right: {
         if (headX == LAST_X) {
            headX = 0;
         }
         else {
            headX += ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::Down: {
         if (headY == LAST_Y) {
            headY = 0;
         }
         else {
            headY += ITEM_SIDE;
         }
         break;
      }
      case BeerSnake::Left: {
         if (headX == 0) {
            headX = LAST_X;
         }
         else {
            headX -= ITEM_SIDE;
         }
         break;
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
   qsrand(QDateTime::currentMSecsSinceEpoch());
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
   if (beerX == headX && beerY == headY) {
      ++length;
      placeBeer();
      if (timer->interval() > FINAL_INTERVAL) {
         timer->setInterval(timer->interval() - INTERVAL_DELTA);
      }
   }
}

void BeerSnake::checkCollision() {
   for (int piece = 1; piece < length; piece++) {
      if (headX == snakeXs.at(piece) &&
         headY == snakeYs.at(piece)) {
         gameOver = true;
      }
   }
}

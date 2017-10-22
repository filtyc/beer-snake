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
   snakeXs.at(0) = (ITEMS_HORIZONTALLY/2-1)*ITEM_SIDE;
   snakeYs.at(0) = (ITEMS_VERTICALLY/2-1)*ITEM_SIDE;
   snakeXs.at(1) = snakeXs.at(0);
   snakeYs.at(1) = snakeYs.at(0) + ITEM_SIDE;
}

void BeerSnake::paintEvent(QPaintEvent *e) {
   Q_UNUSED(e);

   QPainter painter(this);

   painter.drawImage(snakeXs.at(0), snakeYs.at(0), head);

   for (int piece = 1; piece < length; piece++) {
      painter.drawImage(snakeXs.at(piece), snakeYs.at(piece), body);
   }
}

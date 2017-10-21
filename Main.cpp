#include <QApplication>
#include <BeerSnake.h>

int main(int argc, char *argv[]) {
   QApplication app(argc, argv);

   BeerSnake game;
   game.show();

   return app.exec();
}

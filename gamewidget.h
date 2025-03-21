#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "gameboard.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(GameBoard *board, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void showGameOverDialog();

private:
    GameBoard *gameBoard;
};

#endif // GAMEWIDGET_H

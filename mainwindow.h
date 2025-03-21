#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "gameboard.h"
#include "gamewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onNewGame();
    void updateBoard();
    void handleGameOver();

private:
    Ui::MainWindow *ui;
    GameBoard *game;
    GameWidget *gameWidget;  // Теперь создаём `GameWidget` вручную
    QVBoxLayout *layout;    // Лэйаут для размещения `GameWidget`

    QPushButton *btnUp;
    QPushButton *btnDown;
    QPushButton *btnLeft;
    QPushButton *btnRight;
    QPushButton *btnNewGame;

    void setupControls(); // Метод для инициализации кнопок
};

#endif // MAINWINDOW_H

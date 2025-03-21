#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QPair>
#include <QRandomGenerator>
#include <QDebug>
#include <QPoint>

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard(QObject *parent = nullptr);

    void newGame(); // Запуск новой игры
    const QVector<QVector<int>>& getGrid() const { return grid; }

public slots:
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();


signals:
    void boardUpdated();
    void gameOver();

private:
    QVector<QVector<int>> grid;
    int m_score;

    bool slideAndMergeRow(QVector<int>& row);
    void generateTile();
    bool isGameOver() const;
    bool canMove();
    bool canSlideAndMergeRow(const QVector<int>& row);
};

#endif // GAMEBOARD_H

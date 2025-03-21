#include "gamewidget.h"
#include <QPainter>
#include <QFont>

GameWidget::GameWidget(GameBoard *board, QWidget *parent)
    : QWidget(parent), gameBoard(board)
{
    setMinimumSize(400, 400);
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (!gameBoard) {
        qWarning() << "Ошибка: GameBoard отсутствует!";
        return;
    }

    try {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int gridSize = 4;
        int cellWidth = width() / gridSize;
        int cellHeight = height() / gridSize;
        const QVector<QVector<int>>& grid = gameBoard->getGrid();

        QFont font = painter.font();
        font.setPointSize(20);
        painter.setFont(font);

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                QRect rect(j * cellWidth, i * cellHeight, cellWidth, cellHeight);
                painter.setPen(Qt::black);
                painter.setBrush(Qt::lightGray);
                painter.drawRect(rect);

                int value = grid[i][j];
                if (value != 0)
                    painter.drawText(rect, Qt::AlignCenter, QString::number(value));
            }
        }
    } catch (const std::exception &e) {
        qWarning() << "Ошибка в paintEvent:" << e.what();
    }
}

void GameWidget::showGameOverDialog()
{
    // Блокируем ввод
    setEnabled(false);

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        tr("Игра окончена"),
        tr("Ходов больше нет! Начать новую игру?"),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        if (gameBoard) {
            gameBoard->newGame(); // Вызываем newGame() у GameBoard
            update(); // Перерисовываем игровое поле
        }
    }

    // Разблокируем ввод
    setEnabled(true);
}

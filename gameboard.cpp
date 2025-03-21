#include "gameboard.h"
#include <algorithm>

GameBoard::GameBoard(QObject *parent) : QObject(parent), m_score(0)
{
    newGame();
}

void GameBoard::newGame()
{
    grid = QVector<QVector<int>>(4, QVector<int>(4, 0));
    m_score = 0;
    generateTile();
    generateTile();
}

void GameBoard::generateTile()
{
    QVector<QPoint> emptyCells;

    // Находим все пустые клетки на поле
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j] == 0) {
                emptyCells.append(QPoint(i, j));
            }
        }
    }

    // Если нет пустых клеток, не генерируем плитку
    if (emptyCells.isEmpty()) {
        return;
    }

    // Выбираем случайную пустую клетку
    int index = rand() % emptyCells.size();
    QPoint randomEmptyCell = emptyCells[index];

    // Генерируем плитку 2 (или 4 с определенной вероятностью)
    grid[randomEmptyCell.x()][randomEmptyCell.y()] = (rand() % 10 == 0) ? 4 : 2;

    qDebug() << "Генерация плитки в позиции" << randomEmptyCell;

    emit boardUpdated();
}

bool GameBoard::canMove()
{
    // Проверка движения по строкам (влево и вправо)
    for (int i = 0; i < 4; i++) {
        // Проверяем, можно ли сдвигать или объединять плитки в строке при движении влево
        if (canSlideAndMergeRow(grid[i])) {
            return true;
        }
    }

    // Проверка движения по столбцам (вверх и вниз)
    for (int col = 0; col < 4; col++) {
        QVector<int> column;
        for (int row = 0; row < 4; row++) {
            column.append(grid[row][col]);
        }

        // Проверяем, можно ли сдвигать или объединять плитки в столбце при движении вверх
        if (canSlideAndMergeRow(column)) {
            return true;
        }
    }

    // Если ни одно движение не возможно, возвращаем false
    return false;
}

bool GameBoard::canSlideAndMergeRow(const QVector<int>& row)
{
    // Проверяем, можно ли сдвигать или объединять плитки в ряду
    QVector<int> compactedRow;

    // Сжимаем ряд
    for (int num : row) {
        if (num != 0) {
            compactedRow.append(num);
        }
    }

    // Если ряд пуст или его можно объединить, возвращаем true
    if (compactedRow.size() < 4) {
        return true;
    }

    // Проверяем возможность объединения плиток
    for (int i = 0; i < compactedRow.size() - 1; i++) {
        if (compactedRow[i] == compactedRow[i + 1]) {
            return true; // Можно объединить плитки
        }
    }

    return false; // Нет возможности сдвига или объединения
}

bool GameBoard::slideAndMergeRow(QVector<int>& row)
{
    // Проверка корректного размера ряда
    if (row.size() != 4) {
        qWarning() << "Ошибка: некорректный размер ряда!" << row;
        return false;
    }

    bool changed = false;
    QVector<int> compactedRow;

    // 1. "Сжимаем" ряд: убираем нули и оставляем только ненулевые плитки
    for (int num : row) {
        if (num != 0) {
            compactedRow.append(num);
        }
    }

    // Если после сжатия ряд пуст, изменений не произошло
    if (compactedRow.isEmpty()) {
        return false;
    }

    // 2. Объединение соседних плиток
    // Проходим по сжатому ряду и объединяем, если соседние элементы равны.
    // При объединении элемент удваивается, добавляется к счёту, а следующий удаляется.
    for (int i = 0; i < compactedRow.size() - 1; i++) {
        if (compactedRow[i] == compactedRow[i + 1]) {
            compactedRow[i] *= 2;         // Удваиваем значение плитки
            m_score += compactedRow[i];     // Добавляем к счёту
            compactedRow.removeAt(i + 1);   // Удаляем объединённую плитку
            changed = true;
        }
    }

    // 3. Заполнение ряда нулями до полного размера (4 элемента)
    while (compactedRow.size() < 4) {
        compactedRow.append(0);
    }

    // 4. Если итоговый ряд отличается от исходного, перезаписываем его
    if (row != compactedRow) {
        row = compactedRow;
        changed = true;
    }

    qDebug() << "Сдвиг и объединение завершены успешно.";
    return changed;
}

bool GameBoard::moveLeft()
{
    if (!canMove()) return false; // Проверка возможности движения

    bool changed = false;
    for (int i = 0; i < 4; i++) {
        if (slideAndMergeRow(grid[i])) {
            changed = true;
        }
    }

    if (changed) {
        generateTile();
        emit boardUpdated();
        if (isGameOver()) emit gameOver();
    }
    return changed;  // Возвращаем, произошло ли движение
}

bool GameBoard::moveRight()
{
    if (!canMove()) return false; // Проверка возможности движения

    bool changed = false;
    for (int i = 0; i < 4; i++) {
        QVector<int> row = grid[i];
        std::reverse(row.begin(), row.end());
        if (slideAndMergeRow(row)) {
            std::reverse(row.begin(), row.end());
            grid[i] = row;
            changed = true;
        }
    }

    if (changed) {
        generateTile();
        emit boardUpdated();
        if (isGameOver()) emit gameOver();
    }
    return changed;  // Возвращаем, произошло ли движение
}

bool GameBoard::moveUp()
{
    if (!canMove()) return false; // Проверка возможности движения

    bool changed = false;
    for (int col = 0; col < 4; col++) {
        QVector<int> column;
        for (int row = 0; row < 4; row++)
            column.append(grid[row][col]);

        if (slideAndMergeRow(column)) {
            for (int row = 0; row < 4; row++)
                grid[row][col] = column[row];
            changed = true;
        }
    }

    if (changed) {
        generateTile();
        emit boardUpdated();
        if (isGameOver()) emit gameOver();
    }
    return changed;  // Возвращаем, произошло ли движение
}

bool GameBoard::moveDown()
{
    if (!canMove()) return false; // Проверка возможности движения

    bool changed = false;
    for (int col = 0; col < 4; col++) {
        QVector<int> column;
        for (int row = 0; row < 4; row++)
            column.append(grid[row][col]);

        std::reverse(column.begin(), column.end());
        if (slideAndMergeRow(column)) {
            std::reverse(column.begin(), column.end());
            for (int row = 0; row < 4; row++)
                grid[row][col] = column[row];
            changed = true;
        }
    }

    if (changed) {
        generateTile();
        emit boardUpdated();
        if (isGameOver()) emit gameOver();
    }
    return changed;  // Возвращаем, произошло ли движение
}

bool GameBoard::isGameOver() const
{
    // Можно вызывать этот метод для проверки состояния
    return !const_cast<GameBoard*>(this)->canMove();

}

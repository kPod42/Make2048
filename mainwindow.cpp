#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание логики игры
    game = new GameBoard(this);
    gameWidget = new GameWidget(game, this);

    // Устанавливаем размер окна
    setMinimumSize(400, 500);
    setMaximumSize(600, 700);

    // Инициализация элементов управления
    setupControls();

    // Устанавливаем фокус для корректного ввода с клавиатуры
    this->setFocusPolicy(Qt::StrongFocus);

    // Соединяем сигналы с слотами
    connect(game, &GameBoard::boardUpdated, this, &MainWindow::updateBoard);
    connect(game, &GameBoard::gameOver, this, &MainWindow::handleGameOver);
    connect(ui->newGameButton, &QPushButton::clicked, this, &MainWindow::onNewGame);

    updateBoard();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onNewGame() {
    game->newGame();
    updateBoard();
}

void MainWindow::updateBoard() {
//    ui->scoreLabel->setText(QString::number(game->m_score()));
    gameWidget->update();  // Обновляем вручную созданный виджет
}

void MainWindow::handleGameOver() {
    QMessageBox::information(this, "Game Over", "Нет доступных ходов. Игра окончена!");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!game) {
        qWarning() << "Ошибка: объект GameBoard отсутствует!";
        return;
    }

    bool moved = false;
    switch (event->key()) {
    case Qt::Key_Left:  moved = game->moveLeft();  break;
    case Qt::Key_Right: moved = game->moveRight(); break;
    case Qt::Key_Up:    moved = game->moveUp();    break;
    case Qt::Key_Down:  moved = game->moveDown();  break;
    }

    if (moved)
        updateBoard();
}

void MainWindow::setupControls()
{
    // Создаём кнопки управления
    btnUp = new QPushButton("▲");
    btnDown = new QPushButton("▼");
    btnLeft = new QPushButton("◄");
    btnRight = new QPushButton("►");
    btnNewGame = new QPushButton("Новая игра");

    // Устанавливаем размеры кнопок
    btnUp->setFixedSize(50, 50);
    btnDown->setFixedSize(50, 50);
    btnLeft->setFixedSize(50, 50);
    btnRight->setFixedSize(50, 50);
    btnNewGame->setFixedSize(100, 40);

    // Крестовина управления
    QGridLayout *controlLayout = new QGridLayout;
    controlLayout->addWidget(btnUp, 0, 1);
    controlLayout->addWidget(btnLeft, 1, 0);
    controlLayout->addWidget(btnDown, 1, 1);
    controlLayout->addWidget(btnRight, 1, 2);

    // Обертка для крестовины
    QWidget *controlsWidget = new QWidget();
    controlsWidget->setLayout(controlLayout);

    // Верхняя панель (кнопка "Новая игра")
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addStretch();
    topLayout->addWidget(btnNewGame);
    topLayout->setContentsMargins(10, 10, 10, 10); // Отступы

    // Нижняя панель (управление)
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(controlsWidget);
    bottomLayout->setContentsMargins(10, 10, 10, 10);

    // Основной макет окна
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(topLayout);  // Верхний ряд с кнопкой "Новая игра"
    layout->addWidget(gameWidget, 1, Qt::AlignCenter);  // Игровое поле по центру
    layout->addLayout(bottomLayout); // Нижний ряд с кнопками управления

    // Создание центрального виджета
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Подключение кнопок к игровым действиям
    connect(btnUp, &QPushButton::clicked, this, [=](){
        game->moveUp(); updateBoard(); this->setFocus();
    });
    connect(btnDown, &QPushButton::clicked, this, [=](){
        game->moveDown(); updateBoard(); this->setFocus();
    });
    connect(btnLeft, &QPushButton::clicked, this, [=](){
        game->moveLeft(); updateBoard(); this->setFocus();
    });
    connect(btnRight, &QPushButton::clicked, this, [=](){
        game->moveRight(); updateBoard(); this->setFocus();
    });
    connect(btnNewGame, &QPushButton::clicked, this, &MainWindow::onNewGame);
}

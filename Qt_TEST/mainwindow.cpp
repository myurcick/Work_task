#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , generator(new Generator)
    , queue(new Q)
    , consumer(new Consumer)
{
    ui->setupUi(this);

    // Move workers to threads
    generator->moveToThread(&genThread);
    queue->moveToThread(&queueThread);
    consumer->moveToThread(&consThread);

    genThread.start();
    queueThread.start();
    consThread.start();

    // generator connections
    connect(&prodTimer, &QTimer::timeout, generator, &Generator::tick);
    connect(generator, &Generator::numberProduced, queue, &Q::push);
    connect(generator, &Generator::numberProduced, this, &MainWindow::onProduced);

    // Queue connections
    connect(queue, &Q::queueUpdated, this, &MainWindow::onQueue);
    connect(queue, &Q::popped, consumer, &Consumer::onPopped);

    // Consumer connections
    connect(&consTimer, &QTimer::timeout, consumer, &Consumer::onTick);
    connect(consumer, &Consumer::requestPop, queue, &Q::pop);
    connect(consumer, &Consumer::consumed, this, &MainWindow::onConsumed);

    // UI refresh
    uiTimer.setInterval(300);
    connect(&uiTimer, &QTimer::timeout, this, &MainWindow::refreshUI);
    uiTimer.start();

    // Buttons
    connect(ui->btnGen, &QPushButton::clicked, this, &MainWindow::onGeneratorToggle);
    connect(ui->btnCons, &QPushButton::clicked, this, &MainWindow::onConsumerToggle);

    prodTimer.setInterval(100); // Set generator frequency
    consTimer.setInterval(200); // Set third thread(Consumer) frequency
}

MainWindow::~MainWindow()
{
    genThread.quit(); genThread.wait();
    queueThread.quit(); queueThread.wait();
    consThread.quit(); consThread.wait();
    delete ui;
}

void MainWindow::onGeneratorToggle()
{
    if (!prodRunning) {
        generator->start();
        prodTimer.start();
        ui->btnGen->setText("Stop generator");
    } else {
        generator->stop();
        prodTimer.stop();
        ui->btnGen->setText("Start generator");
    }
    prodRunning = !prodRunning;
}//start/stop number generator

void MainWindow::onConsumerToggle()
{
    if (!consRunning) {
        consumer->start();
        consTimer.start();
        ui->btnCons->setText("Stop Consumer");
    } else {
        consumer->stop();
        consTimer.stop();
        ui->btnCons->setText("Start Consumer");
    }
    consRunning = !consRunning;
}
//start/stop cons

void MainWindow::onProduced(int v)
{
    prodList.append(v);
    if (prodList.size() > 50) prodList.removeFirst();// If in list more than 50 numbers, oldest one will be removed, I did this to make the display look nicer.
}

void MainWindow::onQueue(QQueue<int> q)
{
    queueList = q.toList();
}

void MainWindow::onConsumed(int v)
{
    consList.append(v);
    if (consList.size() > 50) consList.removeFirst();// same as in prodlist
}

void MainWindow::refreshUI()
{
    ui->listGen->clear();
    for (int v : prodList) ui->listGen->addItem(QString::number(v));

    ui->listQ->clear();
    for (int v : queueList) ui->listQ->addItem(QString::number(v));

    ui->listCuns->clear();
    for (int v : consList) ui->listCuns->addItem(QString::number(v));
}

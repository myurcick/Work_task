#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// ------------------- Producer -------------------
// This class generates numbers incrementally. It can be started/stopped via slots.
// Emits signal `numberProduced(int)` each time a number is generated.
class Generator : public QObject {
    Q_OBJECT
public:
    Generator() : m_running(false), m_value(0) {}

public slots:
    void start() { m_running = true; }
    void stop()  { m_running = false; }
    void tick() {
        if (m_running) emit numberProduced(++m_value);
    }

signals:
    void numberProduced(int);

private:
    bool m_running;
    int m_value;
};
// Manages a FIFO queue with a maximum of 20 numbers.
// Thread-safe push/pop operations. Emits signals when queue changes.

class Q : public QObject {
    Q_OBJECT
public slots:
    void push(int v) {
        if(m_queue.size() >= 20) m_queue.dequeue();
        m_queue.enqueue(v);
        emit queueUpdated(m_queue);
    }
    void pop() {
        if(!m_queue.isEmpty()) {
            int v = m_queue.dequeue();
            emit queueUpdated(m_queue);
            emit popped(v);
        }
    }
signals:
    void queueUpdated(QQueue<int>);
    void popped(int);
private:
    QQueue<int> m_queue;
};

// This class requests numbers from the queue at regular intervals.
// Emits `consumed(int)` signal when a number is received.
class Consumer : public QObject {
    Q_OBJECT
public:
    Consumer() : m_running(false) {}

public slots:
    void start() { m_running = true; }
    void stop()  { m_running = false; }
    void onTick() {
        if (m_running) emit requestPop();
    }
    void onPopped(int v) { emit consumed(v); }

signals:
    void requestPop();
    void consumed(int);

private:
    bool m_running;
};

// ------------------- MainWindow -------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGeneratorToggle();             // Slot for Start/Stop Generator button
    void onConsumerToggle();             // Slot for Start/Stop Consumer button
    void onProduced(int v);              // Slot to receive generated numbers
    void onQueue(QQueue<int> q);         // Slot to receive current queue contents
    void onConsumed(int v);              // Slot to receive consumed numbers
    void refreshUI();

private:
    Ui::MainWindow *ui;

    QThread genThread, queueThread, consThread;
    Generator *generator;                  // Generator object
    Q *queue;                  // QueueWorker object
    Consumer *consumer;                  // Consumer object

    QList<int> prodList, consList;
    QList<int> queueList;

    QTimer uiTimer, prodTimer, consTimer;

    bool prodRunning = false;
    bool consRunning = false;
};

#endif // MAINWINDOW_H

#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>
#include <QDebug>
#include <unistd.h>

class TestThread : public QThread
{
    Q_OBJECT
public:
    explicit TestThread(QObject *parent = 0);
    void stop();
    int m_stopFlag = false;

private:
    void run();

signals:
    void ThreadEnd();

};
#endif // TESTTHREAD_H

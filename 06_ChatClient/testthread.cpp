#include "testthread.h"

TestThread::TestThread(QObject *parent) :
    QThread(parent)
{

}

void TestThread::run()
{
    while(!m_stopFlag)
    {
        emit ThreadEnd();
        sleep(1);
    }
}

void TestThread::stop()
{
    m_stopFlag = true;
}

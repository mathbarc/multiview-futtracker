#ifndef INCLUDESYNCSTACK_HPP
#define INCLUDESYNCSTACK_HPP

#include <QObject>

class SyncStack : public QObject
{
        Q_OBJECT
    public:
        explicit SyncStack(QObject *parent = 0);

    signals:

    public slots:
};

#endif // INCLUDESYNCSTACK_HPP
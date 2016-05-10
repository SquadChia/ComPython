#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H
#include <QObject>
#include "compy.h"

class keyEnterReceiver : public QObject
{
    Q_OBJECT
public:
    keyEnterReceiver(COMPy * py);
protected:
    bool eventFilter(QObject* obj, QEvent* event);

private:

    COMPy * p_Py;
};
#endif // KEYENTERRECEIVER_H

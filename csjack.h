#ifndef CSJACK_H
#define CSJACK_H

#include <QMainWindow>
#include <channel.h>

namespace Ui {
class CSJack;
}

class CSJack : public QMainWindow
{
    Q_OBJECT

    Channel * ch;

public:
    explicit CSJack(QWidget *parent = 0);
    ~CSJack();
    void ConnectControls(Channel * c);

private:
    Ui::CSJack *ui;
};

#endif // CSJACK_H

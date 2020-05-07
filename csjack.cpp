#include "csjack.h"
#include "ui_csjack.h"

CSJack::CSJack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSJack)
{
    ui->setupUi(this);
}

CSJack::~CSJack()
{
    delete ui;
}

void CSJack::ConnectControls(Channel *c){
    ch = c;
    connect(ui->pulseToggle, SIGNAL(toggled(bool)), ch, SLOT(setPulse(bool)));
    connect(ui->sawToggle, SIGNAL(toggled(bool)), ch, SLOT(setSaw(bool)));
    connect(ui->sineLevel, SIGNAL(valueChanged(int)), ch, SLOT(setSineLevel(int)));
    connect(ui->pulseWidth, SIGNAL(valueChanged(int)), ch, SLOT(setPulseWidth(int)));
    connect(ui->filterCutoff, SIGNAL(valueChanged(int)), ch, SLOT(setFilterCutoff(int)));
    connect(ui->filterResonance, SIGNAL(valueChanged(int)), ch, SLOT(setFilterResonance(int)));
}

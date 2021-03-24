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

void CSJack::ConnectControls(Channel *c, Channel *c2){
    ch = c;
    connect(ui->pulseToggle, SIGNAL(toggled(bool)), ch, SLOT(setPulse(bool)));
    connect(ui->sawToggle, SIGNAL(toggled(bool)), ch, SLOT(setSaw(bool)));
    connect(ui->sineLevel, SIGNAL(valueChanged(int)), ch, SLOT(setSineLevel(int)));
    connect(ui->pulseWidth, SIGNAL(valueChanged(int)), ch, SLOT(setPulseWidth(int)));
    connect(ui->lpf_cutoff, SIGNAL(valueChanged(int)), ch, SLOT(setLPFCutoff(int)));
    connect(ui->lpf_resonance, SIGNAL(valueChanged(int)), ch, SLOT(setLPFResonance(int)));
    connect(ui->hpf_cutoff, SIGNAL(valueChanged(int)), ch, SLOT(setHPFCutoff(int)));
    connect(ui->hpf_resonance, SIGNAL(valueChanged(int)), ch, SLOT(setHPFResonance(int)));
    //connect(ui->hpf_resonance, SIGNAL(valueChanged(int)), ui->hpf_c_label, SLOT(setNum(int)));

    connect(ui->pulseToggle_2, SIGNAL(toggled(bool)), c2, SLOT(setPulse(bool)));
    connect(ui->sawToggle_2, SIGNAL(toggled(bool)), c2, SLOT(setSaw(bool)));
    connect(ui->sineLevel_2, SIGNAL(valueChanged(int)), c2, SLOT(setSineLevel(int)));
    connect(ui->pulseWidth_2, SIGNAL(valueChanged(int)), c2, SLOT(setPulseWidth(int)));
    connect(ui->lpf_cutoff_2, SIGNAL(valueChanged(int)), c2, SLOT(setLPFCutoff(int)));
    connect(ui->lpf_resonance_2, SIGNAL(valueChanged(int)), c2, SLOT(setLPFResonance(int)));
    connect(ui->hpf_cutoff_2, SIGNAL(valueChanged(int)), c2, SLOT(setHPFCutoff(int)));
    connect(ui->hpf_resonance_2, SIGNAL(valueChanged(int)), c2, SLOT(setHPFResonance(int)));
    connect(ui->detune, SIGNAL(valueChanged(int)), c2, SLOT(setDetune(int)));
    connect(c2, SIGNAL(detuneSet(QString)), ui->detune_value, SLOT(setText(QString)));
    ui->hpf_cutoff->setValue(0);
}

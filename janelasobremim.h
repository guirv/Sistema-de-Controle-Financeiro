#ifndef JANELASOBREMIM_H
#define JANELASOBREMIM_H

#include <QDialog>

namespace Ui {
class JanelaSobreMim;
}

// Janela de dialogo que exibe informacoes sobre o desenvolvedor
class JanelaSobreMim : public QDialog
{
    Q_OBJECT

public:

    // Construtor e destrutor da janela
    explicit JanelaSobreMim(QWidget *parent = nullptr);
    ~JanelaSobreMim();

private:

    // Ponteiro para os elementos da interface grafica
    Ui::JanelaSobreMim *ui;
};

#endif

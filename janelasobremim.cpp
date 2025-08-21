#include "janelasobremim.h"
#include "ui_janelasobremim.h"
#include <QPixmap>

// Construtor da janela "Sobre Mim"
JanelaSobreMim::JanelaSobreMim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaSobreMim)
{
    ui->setupUi(this);

    // Carrega a foto a partir dos recursos da aplicacao e a exibe no label
    QPixmap foto(":/imagens/minha_foto.jpg");
    ui->label_foto->setPixmap(foto);
}

// Destrutor da janela
JanelaSobreMim::~JanelaSobreMim()
{
    delete ui;
}

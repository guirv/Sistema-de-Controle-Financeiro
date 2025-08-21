#include "janelasenha.h"
#include "ui_janelasenha.h"

// Construtor da janela de senha
JanelaSenha::JanelaSenha(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaSenha)
{
    ui->setupUi(this);
}

// Destrutor da janela
JanelaSenha::~JanelaSenha()
{
    delete ui;
}

// Retorna o texto digitado no campo de senha
QString JanelaSenha::getSenha() const
{
    return ui->input_senha->text();
}

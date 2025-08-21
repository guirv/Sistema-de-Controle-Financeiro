#ifndef JANELASENHA_H
#define JANELASENHA_H

#include <QDialog>

namespace Ui {
class JanelaSenha;
}

// Janela de dialogo simples para solicitar a senha de um usuario
class JanelaSenha : public QDialog
{
    Q_OBJECT

public:

    // Construtor e destrutor da janela
    explicit JanelaSenha(QWidget *parent = nullptr);
    ~JanelaSenha();

    // Retorna a senha digitada pelo usuario no campo de texto
    QString getSenha() const;

private:

    // Ponteiro para os elementos da interface grafica
    Ui::JanelaSenha *ui;
};

#endif

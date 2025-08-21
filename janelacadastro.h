#ifndef JANELACADASTRO_H
#define JANELACADASTRO_H

#include "user.h"
#include <QDialog>

namespace Ui {
class JanelaCadastro;
}

// Janela de dialogo para o cadastro de um novo usuario
class JanelaCadastro : public QDialog {

    Q_OBJECT

public:

    // Construtor e destrutor da janela
    explicit JanelaCadastro(QWidget *parent = nullptr);
    ~JanelaCadastro();

    // Retorna o ponteiro para o usuario criado apos o cadastro
    User* getUser() const;

public slots:

    // Processa os dados do formulario quando o usuario clica em "OK"
    void accept();

private slots:

    // Habilita ou desabilita os campos de senha com base na checkbox
    void on_check_conta_privada_stateChanged(int arg1);

private:

    // Ponteiro para os elementos da interface grafica (gerenciado pelo Qt)
    Ui::JanelaCadastro *ui;

    // Ponteiro para o objeto User que sera criado
    User* m_user;
};

#endif

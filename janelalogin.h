#ifndef JANELALOGIN_H
#define JANELALOGIN_H

#include <QDialog>
#include "perfis.h"
#include "user.h"

namespace Ui {
class JanelaLogin;
}

// Janela de dialogo para o login do usuario ou para o registro
class JanelaLogin : public QDialog
{
    Q_OBJECT

public:

    // Construtor que recebe o gerenciador de perfis
    explicit JanelaLogin(Perfis* gerenciador, QWidget *parent = nullptr);

    // Destrutor da janela
    ~JanelaLogin();

    // Processa a tentativa de login quando o usuario clica em "OK"
    void accept();

    // Retorna o ponteiro para o usuario que efetuou o login com sucesso
    User* getUsuarioLogado() const;

private slots:

    // Abre a janela de cadastro de um novo perfil
    void on_btn_registrarse_clicked();

    // Abre a janela com informacoes sobre o desenvolvedor
    void on_btn_sobremim_clicked();

private:

    // Ponteiro para os elementos da interface grafica
    Ui::JanelaLogin *ui;

    // Ponteiro para o gerenciador que contem a lista de todos os perfis
    Perfis* m_lista;

    // Ponteiro para o usuario que realizou o login
    User* m_usuarioLogado;
};

#endif

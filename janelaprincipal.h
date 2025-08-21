#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QMainWindow>
#include "user.h"

// Declaracoes antecipadas de classes Qt para otimizar a compilacao
class QProgressBar;
class QLabel;

namespace Ui {
class JanelaPrincipal;
}

// A janela principal da aplicacao, que exibe o dashboard financeiro
class JanelaPrincipal : public QMainWindow
{
    Q_OBJECT

public:

    // Construtor que recebe o usuario logado para exibir seus dados
    explicit JanelaPrincipal(User* user, QWidget *parent = nullptr);

    // Destrutor da janela
    ~JanelaPrincipal();

private slots:

    // Acoes do usuario
    void on_actionNova_Despesa_triggered();
    void on_btn_limpar_despesas_clicked();

    // Funcoes de atualizacao da interface
    void atualizarTabelaDespesas();
    void atualizarDashboard();

private:

    // Ponteiro para os elementos da interface grafica
    Ui::JanelaPrincipal *ui;

    // Ponteiro para o objeto do usuario logado
    User* m_usuario;
};

#endif

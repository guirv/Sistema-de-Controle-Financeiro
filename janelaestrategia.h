#ifndef JANELAESTRATEGIA_H
#define JANELAESTRATEGIA_H

#include <QDialog>
#include "user.h"

namespace Ui {
class JanelaEstrategia;
}

// Janela para o usuario escolher ou criar sua estrategia financeira
class JanelaEstrategia : public QDialog
{
    Q_OBJECT

public:

    // Construtor que recebe o usuario logado
    explicit JanelaEstrategia(User* usuario, QWidget *parent = nullptr);

    // Destrutor da janela
    ~JanelaEstrategia();

private slots:

    // Exibe o grafico da estrategia conservadora
    void on_btn_detalhes_conservadora_clicked();

    // Exibe o grafico da estrategia moderada
    void on_btn_detalhes_moderada_clicked();

    // Exibe o grafico da estrategia agressiva
    void on_btn_detalhes_agressiva_clicked();

    // Abre a janela para criar uma estrategia personalizada
    void on_btn_criar_personalizada_clicked();

    // Salva a estrategia escolhida pelo usuario
    void on_btn_salvar_clicked();

private:

    // Ponteiro para os elementos da interface grafica
    Ui::JanelaEstrategia *ui;

    // Ponteiro para o objeto do usuario logado
    User* m_usuario;

    // Imagens para exibir os detalhes de cada estrategia
    QPixmap m_pix_conservadora;
    QPixmap m_pix_moderada;
    QPixmap m_pix_agressiva;

    // Armazena a estrategia personalizada caso o usuario a crie
    Estrategia m_estrategia_personalizada;

    // Flag para indicar se uma estrategia personalizada foi criada
    bool m_personalizada_criada;
};

#endif

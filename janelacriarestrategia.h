#ifndef JANELACRIARESTRATEGIA_H
#define JANELACRIARESTRATEGIA_H

#include <QDialog>
#include "estrategia.h"

namespace Ui {
class JanelaCriarEstrategia;
}

// Janela de dialogo para criar uma estrategia de gastos personalizada
class JanelaCriarEstrategia : public QDialog
{
    Q_OBJECT

public:

    // Construtor que recebe a renda do usuario para calculos
    explicit JanelaCriarEstrategia(double renda_usuario, QWidget *parent = nullptr);

    // Destrutor da janela
    ~JanelaCriarEstrategia();

    // Retorna a estrategia personalizada criada pelo usuario
    Estrategia getEstrategiaPersonalizada() const;

private slots:

    // Atualiza os valores e a barra de progresso total em tempo real
    void atualizarTotal();

    // Salva a estrategia personalizada quando o botao e clicado
    void on_bnt_salvar_personalizada_clicked();

private:

    // Ponteiro para os elementos da interface grafica
    Ui::JanelaCriarEstrategia *ui;

    // Objeto que armazena a estrategia sendo criada
    Estrategia m_estrategia;

    // Renda mensal do usuario, usada como base para os calculos
    double m_renda_usuario;
};

#endif

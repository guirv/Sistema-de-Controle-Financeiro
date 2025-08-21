#ifndef JANELANOVADESPESA_H
#define JANELANOVADESPESA_H

#include <QDialog>
#include "despesa.h"

namespace Ui {
class JanelaNovaDespesa;
}

// Janela de dialogo para registrar uma nova despesa ou investimento
class JanelaNovaDespesa : public QDialog
{
    Q_OBJECT

public:

    // Construtor e destrutor da janela
    explicit JanelaNovaDespesa(QWidget *parent = nullptr);
    ~JanelaNovaDespesa();

    // Retorna o objeto Despesa criado apos o preenchimento do formulario
    Despesa getDespesa() const;

public slots:

    // Valida e processa os dados do formulario quando o usuario clica em "OK"
    void accept();

private:

    // Ponteiro para os elementos da interface grafica
    Ui::JanelaNovaDespesa *ui;

    // Objeto que armazena a despesa sendo criada
    Despesa m_despesa;
};

#endif

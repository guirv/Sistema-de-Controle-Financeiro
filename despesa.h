#ifndef DESPESA_H
#define DESPESA_H

#include "lancamento.h"

using namespace std;

// Representa uma despesa unica, herdando de Lancamento
class Despesa : public Lancamento {

private:

    // Categoria em que a despesa se enquadra
    string m_categoria;

public:

    // Construtor para inicializar uma nova despesa
    Despesa(double valor, const string& desc, const QDate& data, const string& cat) :
        Lancamento(valor, desc, data),
        m_categoria(cat)
    {
    }

    // Retorna a categoria da despesa
    string getCategoria() const {
        return m_categoria;
    }
};

#endif

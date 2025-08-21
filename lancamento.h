#ifndef LANCAMENTO_H
#define LANCAMENTO_H

#include <string>
#include <QDate>

using namespace std;

// Classe base que representa um lancamento financeiro generico
class Lancamento {

protected:

    // Atributos basicos de qualquer lancamento
    double m_valor;
    string m_descricao;
    QDate m_data;

public:

    // Construtor para inicializar os dados do lancamento
    Lancamento(double valor, const string& desc, const QDate& data) :
        m_valor(valor),
        m_descricao(desc),
        m_data(data)
    {
    }

    // Destrutor virtual para permitir polimorfismo
    virtual ~Lancamento() = default;

    // Retorna o valor monetario do lancamento
    double getValor() const {
        return m_valor;
    }

    // Retorna a descricao do lancamento
    string getDescricao() const {
        return m_descricao;
    }

    // Retorna a data em que o lancamento foi feito
    QDate getData() const {
        return m_data;
    }
};

#endif

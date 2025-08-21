#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <QDate>
#include "estrategia.h"
#include "despesa.h"

using namespace std;

// Representa o usuario da aplicacao e todos os seus dados
class User {

private:

    // Atributos do perfil do usuario
    string m_username;
    string m_nome;
    double m_saldo_inicial;
    double m_renda_mensal;
    bool m_conta_privada;
    string m_senha;
    QDate m_data_nascimento;
    int m_dia_pagamento;
    bool m_estrategia_definida;

    // Composicao de objetos
    Estrategia m_estrategia_atual;
    vector<Despesa> m_despesas;

public:

    // Construtor principal para criar um novo usuario
    User(const string& user, const string& nome, double saldo, double renda);

    // --- Setters ---
    void setNickname(const string& user) { m_username = user; }
    void setNome(const string& nome) { m_nome = nome; }
    void setSaldoInicial(double saldo) { m_saldo_inicial = saldo; }
    void setRendaMensal(double renda) { m_renda_mensal = renda; }
    void setContaPrivada(bool ehPrivada) { m_conta_privada = ehPrivada; }
    void setSenha(const string& senha) { m_senha = senha; }
    void setDataNascimento(const QDate& data) { m_data_nascimento = data; }
    void setDiaPagamento(int dia) { m_dia_pagamento = dia; }
    void setEstrategia(const Estrategia& estrategia) { m_estrategia_atual = estrategia; }
    void setEstrategiaDefinida(bool definida);

    // Getters
    string getUsername() const { return m_username; }
    string getNome() const { return m_nome; }
    double getSaldoInicial() const { return m_saldo_inicial; }
    double getRendaMensal() const { return m_renda_mensal; }
    bool isContaPrivada() const { return m_conta_privada; }
    string getSenha() const { return m_senha; }
    QDate getDataNascimento() const { return m_data_nascimento; }
    int getDiaPagamento() const { return m_dia_pagamento; }
    Estrategia getEstrategia() const { return m_estrategia_atual; }
    const vector<Despesa>& getDespesas() const;

    // Outras Funcoes

    // Verifica se e o primeiro login do usuario (se a estrategia ja foi definida)
    bool primeiro_login() const;

    // Adiciona uma nova despesa ao historico do usuario
    void adicionarDespesa(const Despesa& despesa);

    // Salva todos os dados do usuario em um arquivo .user
    bool salvarDados() const;

    // Limpa todo o historico de despesas do usuario
    void limparDespesas();
};

#endif

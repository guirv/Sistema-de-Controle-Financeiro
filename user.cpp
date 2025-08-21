#include "user.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <map>

using namespace std;

// Construtor que inicializa os principais atributos do usuario
User::User(const string& user, const string& nome, double saldo, double renda) :
    m_username(user),
    m_nome(nome),
    m_saldo_inicial(saldo),
    m_renda_mensal(renda),
    m_conta_privada(false),
    m_senha(""),
    m_data_nascimento(QDate::currentDate()),
    m_dia_pagamento(1),
    m_estrategia_atual(),
    m_estrategia_definida(false)
{
}

// Salva todos os dados do objeto User em um arquivo de texto
bool User::salvarDados() const
{
    // Garante que o diretorio "perfis" existe, criando-o se necessario
    if (!QDir("perfis").exists()) {
        QDir().mkdir("perfis");
    }

    // Abre o arquivo correspondente ao username para escrita
    QString nomeArquivo = "perfis/" + QString::fromStdString(m_username) + ".user";
    QFile arquivo(nomeArquivo);
    if (!arquivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&arquivo);

    // Escreve os dados do perfil no formato "chave=valor"
    out << "nome=" << QString::fromStdString(m_nome) << "\n";
    out << "renda=" << m_renda_mensal << "\n";
    out << "saldo=" << m_saldo_inicial << "\n";
    out << "data_nascimento=" << m_data_nascimento.toString("yyyy-MM-dd") << "\n";
    out << "dia_pagamento=" << m_dia_pagamento << "\n";
    out << "conta_privada=" << (m_conta_privada ? "true" : "false") << "\n";
    out << "senha=" << QString::fromStdString(m_senha) << "\n";
    out << "estrategia_definida=" << (m_estrategia_definida ? "true" : "false") << "\n";
    out << "estrategia=" << QString::fromStdString(m_estrategia_atual.getNome()) << "\n";

    // Se a estrategia for personalizada, salva suas metas especificas
    if (m_estrategia_atual.getNome() == "Personalizada") {
        QString metas_string = "";
        map<string, double> metas = m_estrategia_atual.getMetas();
        for (auto const& [categoria, percentual] : metas) {
            metas_string += QString::fromStdString(categoria) + ":" + QString::number(percentual) + ";";
        }
        if (!metas_string.isEmpty()) {
            metas_string.chop(1); // Remove o ultimo ";"
        }
        out << "estrategia_metas=" << metas_string << "\n";
    }

    // Escreve cada despesa registrada em uma nova linha
    for (const Despesa& despesa : m_despesas) {
        out << "despesa="
            << despesa.getData().toString("yyyy-MM-dd") << ";"
            << QString::fromStdString(despesa.getDescricao()) << ";"
            << QString::fromStdString(despesa.getCategoria()) << ";"
            << QString::number(despesa.getValor()) << "\n";
    }

    // Fecha o arquivo e retorna sucesso
    arquivo.close();
    return true;
}

// Adiciona uma nova despesa a lista do usuario
void User::adicionarDespesa(const Despesa& despesa)
{
    m_despesas.push_back(despesa);
}

// Retorna uma referencia constante para o vetor de despesas
const vector<Despesa>& User::getDespesas() const
{
    return m_despesas;
}

// Verifica se a estrategia ja foi definida
bool User::primeiro_login() const
{
    return !m_estrategia_definida;
}

// Define o status da estrategia (se ja foi definida ou nao)
void User::setEstrategiaDefinida(bool definida)
{
    m_estrategia_definida = definida;
}

// Apaga todas as despesas da lista
void User::limparDespesas()
{
    m_despesas.clear();
}

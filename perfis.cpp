#include "perfis.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

using namespace std;

// Construtor padrao
Perfis::Perfis()
{
}

// Destrutor que libera a memoria de todos os objetos User armazenados
Perfis::~Perfis()
{
    for (User* perfil : m_perfis) {
        delete perfil;
    }
    m_perfis.clear();
}

// Carrega todos os perfis de usuario salvos na pasta "perfis"
void Perfis::carregarPerfis()
{
    // Limpa a lista atual para evitar duplicatas ao recarregar
    for (User* perfil : m_perfis) {
        delete perfil;
    }
    m_perfis.clear();

    // Procura pelo diretorio "perfis"
    QDir diretorio("perfis");
    if (!diretorio.exists()) {
        return;
    }

    // Lista todos os arquivos com a extensao .user
    QStringList arquivos = diretorio.entryList(QStringList() << "*.user", QDir::Files);

    // Itera sobre cada arquivo de perfil encontrado
    foreach (const QString &nomeArquivo, arquivos) {
        QFile arquivo(diretorio.filePath(nomeArquivo));
        if (!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        // Extrai o nome de usuario do nome do arquivo
        QTextStream in(&arquivo);
        string nickname = nomeArquivo.section('.', 0, 0).toStdString();

        // Variaveis temporarias para armazenar os dados lidos do arquivo
        string nome, senha, nome_estrategia;
        QString metas_string;
        double renda = 0, saldo = 0;
        QDate dataNascimento;
        int diaPagamento = 1;
        bool contaPrivada = false;
        bool estrategiaDefinida = false;
        vector<Despesa> despesas_carregadas;

        // Le o arquivo linha por linha
        while (!in.atEnd()) {
            QString linha = in.readLine();
            QStringList partes = linha.split('=');
            if (partes.size() < 2) continue;

            // Separa a linha em chave e valor (ex: "nome=Joao")
            QString chave = partes[0].trimmed();
            QString valor = partes.sliced(1).join("=").trimmed();

            // Atribui o valor a variavel correspondente com base na chave
            if (chave == "nome") nome = valor.toStdString();
            else if (chave == "renda") renda = valor.toDouble();
            else if (chave == "saldo") saldo = valor.toDouble();
            else if (chave == "data_nascimento") dataNascimento = QDate::fromString(valor, "yyyy-MM-dd");
            else if (chave == "dia_pagamento") diaPagamento = valor.toInt();
            else if (chave == "conta_privada") contaPrivada = (valor == "true");
            else if (chave == "senha") senha = valor.toStdString();
            else if (chave == "estrategia_definida") estrategiaDefinida = (valor == "true");
            else if (chave == "estrategia") nome_estrategia = valor.toStdString();
            else if (chave == "estrategia_metas") metas_string = valor;
            else if (chave == "despesa") {
                // Processa a linha de despesa, que tem um formato proprio
                QStringList dados_despesa = valor.split(';');
                if (dados_despesa.size() == 4) {
                    QDate data = QDate::fromString(dados_despesa[0], "yyyy-MM-dd");
                    string desc = dados_despesa[1].toStdString();
                    string cat = dados_despesa[2].toStdString();
                    double val = dados_despesa[3].toDouble();
                    despesas_carregadas.push_back(Despesa(val, desc, data, cat));
                }
            }
        }
        arquivo.close();

        // Cria o objeto User com os dados carregados
        User* novoUsuario = new User(nickname, nome, saldo, renda);
        novoUsuario->setDataNascimento(dataNascimento);
        novoUsuario->setDiaPagamento(diaPagamento);
        novoUsuario->setContaPrivada(contaPrivada);
        novoUsuario->setSenha(senha);
        novoUsuario->setEstrategiaDefinida(estrategiaDefinida);

        // Reconstrutor a estrategia do usuario
        if (nome_estrategia == "Personalizada") {
            Estrategia est_custom("Personalizada");
            QStringList pares_metas = metas_string.split(';');
            foreach (const QString &par, pares_metas) {
                if(par.isEmpty()) continue;
                QStringList item_meta = par.split(':');
                if (item_meta.size() == 2) {
                    est_custom.definirMeta(item_meta[0].toStdString(), item_meta[1].toDouble());
                }
            }
            novoUsuario->setEstrategia(est_custom);
        } else if (nome_estrategia == "Conservadora") {
            novoUsuario->setEstrategia(Estrategia::criarEstrategiaConservadora());
        } else if (nome_estrategia == "Moderada") {
            novoUsuario->setEstrategia(Estrategia::criarEstrategiaModerada());
        } else if (nome_estrategia == "Agressiva") {
            novoUsuario->setEstrategia(Estrategia::criarEstrategiaAgressiva());
        }

        // Adiciona as despesas carregadas ao usuario
        for (const Despesa& d : despesas_carregadas) {
            novoUsuario->adicionarDespesa(d);
        }

        // Adiciona o usuario totalmente reconstruido a lista
        m_perfis.push_back(novoUsuario);
    }
}

// Adiciona um novo perfil a lista de perfis em memoria
void Perfis::adicionarPerfil(User* perfil)
{
    if (perfil) {
        m_perfis.push_back(perfil);
    }
}

// Retorna um ponteiro para um usuario com base no seu nome de usuario
User* Perfis::getByUsername(const string& username)
{
    for (User* perfil : m_perfis) {
        if (perfil->getUsername() == username) {
            return perfil;
        }
    }
    return nullptr;
}

// Retorna uma lista de strings com todos os nomes de usuario
QStringList Perfis::getListaUsernames() const
{
    QStringList usernames;
    for (const User* perfil : m_perfis) {
        usernames.append(QString::fromStdString(perfil->getUsername()));
    }
    return usernames;
}

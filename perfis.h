#ifndef PERFIS_H
#define PERFIS_H

#include "user.h"
#include <vector>
#include <QStringList>
#include <string>

using namespace std;

// Gerencia a colecao de todos os perfis de usuario da aplicacao
class Perfis {

private:

    // Vetor de ponteiros que armazena todos os perfis carregados
    vector<User*> m_perfis;

public:

    // Construtor e destrutor da classe
    Perfis();
    ~Perfis();

    // Carrega todos os perfis de usuario a partir dos arquivos .user
    void carregarPerfis();

    // Adiciona um novo perfil de usuario a lista em memoria
    void adicionarPerfil(User* perfil);

    // Busca e retorna um usuario pelo seu nome de usuario (username)
    User* getByUsername(const string& username);

    // Retorna uma lista com os nomes de todos os usuarios cadastrados
    QStringList getListaUsernames() const;
};

#endif

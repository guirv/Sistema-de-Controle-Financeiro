#include "estrategia.h"

using namespace std;

// Construtor padrao
Estrategia::Estrategia() : m_nome("Nenhuma")
{
}

// Construtor que define um nome para a estrategia
Estrategia::Estrategia(const string& nome) : m_nome(nome)
{
}

// Busca e retorna o percentual da meta para uma categoria especifica
double Estrategia::getMetaParaCategoria(const string& categoria) const {
    auto it = m_metas.find(categoria);
    if (it != m_metas.end()) {
        return it->second;
    }
    return 0.0;
}

// Estrategias Pre-definidas

// Cria uma estrategia com foco em bem-estar e gastos essenciais
Estrategia Estrategia::criarEstrategiaConservadora() {
    Estrategia est("Conservadora");
    est.definirMeta("Moradia",         0.30); // 30%
    est.definirMeta("Alimentação",     0.15); // 15%
    est.definirMeta("Transporte",      0.10); // 10%
    est.definirMeta("Saúde",           0.10); // 10%
    est.definirMeta("Educação",        0.10); // 10%
    est.definirMeta("Desejos e Lazer", 0.15); // 15%
    est.definirMeta("Investimentos",   0.10); // 10%
    return est;
}

// Cria uma estrategia com foco balanceado entre gastos e investimentos
Estrategia Estrategia::criarEstrategiaModerada() {
    Estrategia est("Moderada");
    est.definirMeta("Moradia",         0.30); // 30%
    est.definirMeta("Alimentação",     0.10); // 10%
    est.definirMeta("Transporte",      0.10); // 10%
    est.definirMeta("Saúde",           0.10); // 10%
    est.definirMeta("Educação",        0.10); // 10%
    est.definirMeta("Desejos e Lazer", 0.10); // 10%
    est.definirMeta("Investimentos",   0.20); // 20%
    return est;
}

// Cria uma estrategia com foco agressivo em investimentos
Estrategia Estrategia::criarEstrategiaAgressiva() {
    Estrategia est("Agressiva");
    est.definirMeta("Moradia",         0.25); // 25%
    est.definirMeta("Alimentação",     0.10); // 10%
    est.definirMeta("Transporte",      0.10); // 10%
    est.definirMeta("Saúde",           0.10); // 10%
    est.definirMeta("Educação",        0.08); //  8%
    est.definirMeta("Desejos e Lazer", 0.07); //  7%
    est.definirMeta("Investimentos",   0.30); // 30%
    return est;
}

// Cria uma estrategia vazia para ser preenchida pelo usuario
Estrategia Estrategia::criarEstrategiaPersonalizada(const string& nome) {
    Estrategia est(nome);
    return est;
}

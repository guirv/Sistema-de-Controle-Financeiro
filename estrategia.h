#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include <string>
#include <map>

using namespace std;

// Define uma estrategia financeira com metas de gastos por categoria
class Estrategia {

private:

    // Nome da estrategia (ex: "Conservadora")
    string m_nome;

    // Mapa que associa uma categoria a um percentual de gasto
    map<string, double> m_metas;

public:

    // Construtores
    Estrategia();
    Estrategia(const string& nome);

    // Define o percentual de uma meta para uma determinada categoria
    void definirMeta(const string& categoria, double percentual) {
        m_metas[categoria] = percentual;
    }

    // Retorna o nome da estrategia
    string getNome() const {
        return m_nome;
    }

    // Retorna o percentual da meta para uma categoria especifica
    double getMetaParaCategoria(const string& categoria) const;

    // Retorna o mapa completo de metas
    map<string, double> getMetas() const {
        return m_metas;
    }

    // Metodos estaticos para criar estrategias pre-definidas
    static Estrategia criarEstrategiaConservadora();
    static Estrategia criarEstrategiaModerada();
    static Estrategia criarEstrategiaAgressiva();
    static Estrategia criarEstrategiaPersonalizada(const string& nome);
};

#endif

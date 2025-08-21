#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"
#include "janelanovadespesa.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QProgressBar>
#include <QLabel>
#include <QGridLayout>
#include <map>
#include <tuple>
#include <QHeaderView>

using namespace std;

// Construtor da janela principal
JanelaPrincipal::JanelaPrincipal(User* user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JanelaPrincipal),
    m_usuario(user)
{
    ui->setupUi(this);

    // Atualiza a interface com os dados do usuario assim que a janela e criada
    if (m_usuario) {
        atualizarTabelaDespesas();
        atualizarDashboard();
    }
}

// Destrutor da janela
JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
}

// Abre a janela para adicionar uma nova despesa
void JanelaPrincipal::on_actionNova_Despesa_triggered()
{
    if (!m_usuario) return;

    // Cria e exibe a janela de nova despesa
    JanelaNovaDespesa dialog_nova_despesa(this);
    if (dialog_nova_despesa.exec() == QDialog::Accepted) {
        // Se o usuario confirmar, adiciona a despesa e atualiza a interface
        Despesa novaDespesa = dialog_nova_despesa.getDespesa();
        m_usuario->adicionarDespesa(novaDespesa);
        m_usuario->salvarDados();
        atualizarTabelaDespesas();
        atualizarDashboard();
    }
}

// Limpa todas as despesas registradas pelo usuario
void JanelaPrincipal::on_btn_limpar_despesas_clicked()
{
    if (!m_usuario) return;

    // Exibe uma mensagem de confirmacao antes de apagar os dados
    QMessageBox::StandardButton resposta = QMessageBox::question(this, "Confirmar Ação",
                                                                 "Você tem certeza que deseja REINICIAR os registros? Esta ação não pode ser desfeita.",
                                                                 QMessageBox::Yes | QMessageBox::No);

    // Se o usuario confirmar, limpa os dados e atualiza a interface
    if (resposta == QMessageBox::Yes) {
        m_usuario->limparDespesas();
        m_usuario->salvarDados();
        atualizarTabelaDespesas();
        atualizarDashboard();
        QMessageBox::information(this, "Sucesso", "Todas os registros foram removidos.");
    }
}

// Atualiza a tabela com a lista de despesas
void JanelaPrincipal::atualizarTabelaDespesas()
{
    if (!m_usuario) return;

    // Limpa a tabela antes de preencher novamente
    ui->tabela_despesas->setRowCount(0);
    double total_despesas = 0.0;
    const vector<Despesa>& despesas = m_usuario->getDespesas();

    // Itera sobre cada despesa do usuario para adicionar uma linha na tabela
    for (const Despesa& despesa : despesas) {
        total_despesas += despesa.getValor();
        int linha_atual = ui->tabela_despesas->rowCount();
        ui->tabela_despesas->insertRow(linha_atual);

        // Cria os itens para cada celula da linha
        QTableWidgetItem *itemData = new QTableWidgetItem(despesa.getData().toString("dd/MM/yyyy"));
        QTableWidgetItem *itemDesc = new QTableWidgetItem(QString::fromStdString(despesa.getDescricao()));
        QTableWidgetItem *itemCat = new QTableWidgetItem(QString::fromStdString(despesa.getCategoria()));
        QTableWidgetItem *itemValor = new QTableWidgetItem(QString::number(despesa.getValor(), 'f', 2));

        // Centraliza o texto em todas as celulas
        itemData->setTextAlignment(Qt::AlignCenter);
        itemDesc->setTextAlignment(Qt::AlignCenter);
        itemCat->setTextAlignment(Qt::AlignCenter);
        itemValor->setTextAlignment(Qt::AlignCenter);

        // Adiciona os itens na tabela
        ui->tabela_despesas->setItem(linha_atual, 0, itemData);
        ui->tabela_despesas->setItem(linha_atual, 1, itemDesc);
        ui->tabela_despesas->setItem(linha_atual, 2, itemCat);
        ui->tabela_despesas->setItem(linha_atual, 3, itemValor);
    }

    // Atualiza o label com o valor total das despesas
    ui->label_total_despesas->setText(QString("TOTAL: R$ %1").arg(QString::asprintf("%.2f", total_despesas)));
}

// Atualiza todos os componentes visuais do dashboard
void JanelaPrincipal::atualizarDashboard()
{
    if (!m_usuario) return;

    // Calculo dos totais de gastos
    map<string, double> gastos_por_categoria;
    for (const Despesa& despesa : m_usuario->getDespesas()) {
        gastos_por_categoria[despesa.getCategoria()] += despesa.getValor();
    }

    double renda = m_usuario->getRendaMensal();

    double total_gasto_despesas = 0;
    for(auto const& [categoria, valor] : gastos_por_categoria){
        total_gasto_despesas += valor;
    }
    double sobra = renda - total_gasto_despesas;

    // Atualizacao do painel "Resumo do Mes"
    ui->label_resumo_renda->setText(QString("Entrou: <b>R$ %1</b>").arg(QString::asprintf("%.2f", renda)));
    ui->label_resumo_gasto->setText(QString("Saiu: <b style='color:red;'>R$ %1</b>").arg(QString::asprintf("%.2f", total_gasto_despesas)));
    if (sobra >= 0) {
        ui->label_resumo_sobra->setText(QString("Saldo Mensal: <b style='color:green;'>R$ %1</b>").arg(QString::asprintf("%.2f", sobra)));
    } else {
        ui->label_resumo_sobra->setText(QString("Saldo Mensal: <b style='color:red;'>R$ %1</b>").arg(QString::asprintf("%.2f", sobra)));
    }

    //  Atualizacao do painel "Resumo do Perfil"
    QDate data_nascimento = m_usuario->getDataNascimento();
    int idade = QDate::currentDate().year() - data_nascimento.year();
    if (QDate::currentDate().month() < data_nascimento.month() || (QDate::currentDate().month() == data_nascimento.month() && QDate::currentDate().day() < data_nascimento.day())) {
        idade--;
    }
    ui->label_perfil_nome->setText(QString("Usuário: <b>%1</b>").arg(QString::fromStdString(m_usuario->getNome())));
    ui->label_perfil_idade->setText(QString("Idade: <b>%1 anos</b>").arg(idade));
    ui->label_perfil_estrategia->setText(QString("Estratégia: <b>%1</b>").arg(QString::fromStdString(m_usuario->getEstrategia().getNome())));


    // Atualizacao das barras de progresso das metas
    Estrategia estrategia_atual = m_usuario->getEstrategia();
    vector<tuple<QString, QProgressBar*, QLabel*>> widgets_metas = {
        {"Moradia", ui->progress_moradia_3, ui->label_valor_moradia_3},
        {"Alimentação", ui->progress_alimentacao_3, ui->label_valor_alimentacao_3},
        {"Transporte", ui->progress_transporte_3, ui->label_valor_transporte_3},
        {"Saúde", ui->progress_saude_3, ui->label_valor_saude_3},
        {"Educação", ui->progress_educacao_3, ui->label_valor_educacao_3},
        {"Desejos e Lazer", ui->progress_desejos_3, ui->label_valor_desejos_3},
        {"Investimentos", ui->progress_sobra_3, ui->label_valor_sobra_3}
    };

    // Itera sobre cada meta para atualizar a barra de progresso correspondente
    for (const auto& meta_info : widgets_metas) {
        QString categoria_qs = get<0>(meta_info);
        QProgressBar* pbar = get<1>(meta_info);
        QLabel* label_valor = get<2>(meta_info);

        if (!pbar || !label_valor) continue;

        string categoria_std = categoria_qs.toStdString();

        // Calcula os valores da meta e do gasto atual
        double gasto_atual = gastos_por_categoria[categoria_std];
        double meta_valor = renda * estrategia_atual.getMetaParaCategoria(categoria_std);
        int progresso_percentual = (meta_valor > 0) ? (gasto_atual / meta_valor) * 100 : 0;

        // Atualiza os textos e o valor da barra de progresso
        label_valor->setText(QString::asprintf("R$ %.2f / R$ %.2f", gasto_atual, meta_valor));
        pbar->setFormat(QString::number(progresso_percentual) + "%");
        pbar->setValue(progresso_percentual > 100 ? 100 : progresso_percentual);

        // Define a cor da barra de acordo com a categoria e o percentual
        if (categoria_std == "Investimentos") {
            // Logica de cores para a meta de investimentos
            if (progresso_percentual > 100) {
                pbar->setStyleSheet("QProgressBar::chunk { background-color: #2196F3; }"); // Azul
            } else if (progresso_percentual == 100) {
                pbar->setStyleSheet("QProgressBar::chunk { background-color: #4CAF50; }"); // Verde
            } else {
                pbar->setStyleSheet("QProgressBar::chunk { background-color: #FFC107; }"); // Amarelo
            }
        } else {
            // Logica de cores para as metas de gastos
            if (progresso_percentual > 100) {
                pbar->setStyleSheet("QProgressBar::chunk { background-color: #F44336; }"); // Vermelho
            } else if (progresso_percentual == 100) {
                pbar->setStyleSheet("QProgressBar::chunk { background-color: #FFC107; }"); // Amarelo
            } else {
                pbar->setStyleSheet("QProgressBar::chunk { background-color: #4CAF50; }"); // Verde
            }
        }
    }
}

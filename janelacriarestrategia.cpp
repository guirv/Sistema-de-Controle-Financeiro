#include "janelacriarestrategia.h"
#include "ui_janelacriarestrategia.h"
#include <QMessageBox>

// Construtor da janela de criacao de estrategia
JanelaCriarEstrategia::JanelaCriarEstrategia(double renda_usuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaCriarEstrategia),
    m_renda_usuario(renda_usuario)
{
    ui->setupUi(this);

    // Conecta o sinal de mudanca de valor de cada slider ao metodo de atualizacao
    connect(ui->slider_moradia, &QSlider::valueChanged, this, &JanelaCriarEstrategia::atualizarTotal);
    connect(ui->slider_alimentacao, &QSlider::valueChanged, this, &JanelaCriarEstrategia::atualizarTotal);
    connect(ui->slider_transporte, &QSlider::valueChanged, this, &JanelaCriarEstrategia::atualizarTotal);
    connect(ui->slider_saude, &QSlider::valueChanged, this, &JanelaCriarEstrategia::atualizarTotal);
    connect(ui->slider_educacao, &QSlider::valueChanged, this, &JanelaCriarEstrategia::atualizarTotal);
    connect(ui->slider_desejos, &QSlider::valueChanged, this, &JanelaCriarEstrategia::atualizarTotal);
    connect(ui->slider_sobra, &QSlider::valueChanged, this, &JanelaCriarEstrategia::atualizarTotal);

    // Realiza uma atualizacao inicial para exibir os valores corretos
    atualizarTotal();
}

// Destrutor da janela
JanelaCriarEstrategia::~JanelaCriarEstrategia()
{
    delete ui;
}

// Atualiza todos os campos da tela em tempo real conforme os sliders sao movidos
void JanelaCriarEstrategia::atualizarTotal() {
    // Atualiza os labels que exibem os percentuais
    ui->valor_moradia->setText(QString::number(ui->slider_moradia->value()) + " %");
    ui->valor_alimentacao->setText(QString::number(ui->slider_alimentacao->value()) + " %");
    ui->valor_transporte->setText(QString::number(ui->slider_transporte->value()) + " %");
    ui->valor_saude->setText(QString::number(ui->slider_saude->value()) + " %");
    ui->valor_educacao->setText(QString::number(ui->slider_educacao->value()) + " %");
    ui->valor_desejos->setText(QString::number(ui->slider_desejos->value()) + " %");
    ui->valor_sobra->setText(QString::number(ui->slider_sobra->value()) + " %");

    // Calcula e exibe o valor em Reais (R$) para cada categoria
    double valor_moradia_reais = (ui->slider_moradia->value() / 100.0) * m_renda_usuario;
    ui->valor_reais_moradia->setText("<b>R$ " + QString::number(valor_moradia_reais, 'f', 2) + "</b>");

    double valor_alimentacao_reais = (ui->slider_alimentacao->value() / 100.0) * m_renda_usuario;
    ui->valor_reais_alimentacao->setText("<b>R$ " + QString::number(valor_alimentacao_reais, 'f', 2) + "</b>");

    double valor_transporte_reais = (ui->slider_transporte->value() / 100.0) * m_renda_usuario;
    ui->valor_reais_transporte->setText("<b>R$ " + QString::number(valor_transporte_reais, 'f', 2) + "</b>");

    double valor_saude_reais = (ui->slider_saude->value() / 100.0) * m_renda_usuario;
    ui->valor_reais_saude->setText("<b>R$ " + QString::number(valor_saude_reais, 'f', 2) + "</b>");

    double valor_educacao_reais = (ui->slider_educacao->value() / 100.0) * m_renda_usuario;
    ui->valor_reais_educacao->setText("<b>R$ " + QString::number(valor_educacao_reais, 'f', 2) + "</b>");

    double valor_desejos_reais = (ui->slider_desejos->value() / 100.0) * m_renda_usuario;
    ui->valor_reais_desejos->setText("<b>R$ " + QString::number(valor_desejos_reais, 'f', 2) + "</b>");

    double valor_sobra_reais = (ui->slider_sobra->value() / 100.0) * m_renda_usuario;
    ui->valor_reais_sobra->setText("<b>R$ " + QString::number(valor_sobra_reais, 'f', 2) + "</b>");

    // Soma os percentuais e atualiza a barra de progresso total
    int total = ui->slider_moradia->value() + ui->slider_alimentacao->value() +
                ui->slider_transporte->value() + ui->slider_saude->value() +
                ui->slider_educacao->value() + ui->slider_desejos->value() +
                ui->slider_sobra->value();

    ui->progressBar_total->setValue(total);

    // Muda a cor da barra de progresso para indicar o status
    if (total == 100) {
        ui->progressBar_total->setStyleSheet("QProgressBar::chunk { background-color: #4CAF50; }");
    } else if (total > 100) {
        ui->progressBar_total->setStyleSheet("QProgressBar::chunk { background-color: #F44336; }");
    }
}

// Valida e salva a estrategia personalizada
void JanelaCriarEstrategia::on_bnt_salvar_personalizada_clicked()
{
    // Valida se a soma dos percentuais e exatamente 100%
    int total = ui->slider_moradia->value() + ui->slider_alimentacao->value() +
                ui->slider_transporte->value() + ui->slider_saude->value() +
                ui->slider_educacao->value() + ui->slider_desejos->value() +
                ui->slider_sobra->value();

    if (total != 100) {
        QMessageBox::warning(this, "Erro de Validação", "A soma dos percentuais para todas as categorias deve ser exatamente 100%.");
        return;
    }

    // Cria o objeto Estrategia e define as metas com base nos sliders
    m_estrategia = Estrategia("Personalizada");
    m_estrategia.definirMeta("Moradia", ui->slider_moradia->value() / 100.0);
    m_estrategia.definirMeta("Alimentação", ui->slider_alimentacao->value() / 100.0);
    m_estrategia.definirMeta("Transporte", ui->slider_transporte->value() / 100.0);
    m_estrategia.definirMeta("Saúde", ui->slider_saude->value() / 100.0);
    m_estrategia.definirMeta("Educação", ui->slider_educacao->value() / 100.0);
    m_estrategia.definirMeta("Desejos e Lazer", ui->slider_desejos->value() / 100.0);
    m_estrategia.definirMeta("Investimentos", ui->slider_sobra->value() / 100.0);

    // Fecha a janela com sucesso
    QDialog::accept();
}

// Retorna o objeto da estrategia criada
Estrategia JanelaCriarEstrategia::getEstrategiaPersonalizada() const
{
    return m_estrategia;
}

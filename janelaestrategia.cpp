#include "janelaestrategia.h"
#include "ui_janelaestrategia.h"
#include "janelacriarestrategia.h"
#include <QPixmap>
#include <QMessageBox>
#include <QButtonGroup>

// Construtor da janela de selecao de estrategia
JanelaEstrategia::JanelaEstrategia(User* usuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaEstrategia),
    m_usuario(usuario),
    m_personalizada_criada(false)
{
    ui->setupUi(this);

    // Carrega as imagens dos graficos de estrategia a partir dos recursos
    m_pix_conservadora.load(":/imagens/CONSERVADORA.png");
    m_pix_moderada.load(":/imagens/MODERADA.png");
    m_pix_agressiva.load(":/imagens/AGRESSIVA.png");

    // Limpa o display de grafico ao iniciar
    ui->label_display_grafico->clear();

    // Agrupa os radio buttons para garantir que apenas um seja selecionado por vez
    QButtonGroup* grupo_estrategias = new QButtonGroup(this);
    grupo_estrategias->addButton(ui->radio_conservadora);
    grupo_estrategias->addButton(ui->radio_moderada);
    grupo_estrategias->addButton(ui->radio_agressiva);
    grupo_estrategias->setExclusive(true);
}

// Destrutor da janela
JanelaEstrategia::~JanelaEstrategia()
{
    delete ui;
}

// Exibe o grafico da estrategia conservadora
void JanelaEstrategia::on_btn_detalhes_conservadora_clicked()
{
    ui->label_display_grafico->setPixmap(m_pix_conservadora.scaled(710, 425, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// Exibe o grafico da estrategia moderada
void JanelaEstrategia::on_btn_detalhes_moderada_clicked()
{
    ui->label_display_grafico->setPixmap(m_pix_moderada.scaled(710, 425, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// Exibe o grafico da estrategia agressiva
void JanelaEstrategia::on_btn_detalhes_agressiva_clicked()
{
    ui->label_display_grafico->setPixmap(m_pix_agressiva.scaled(710, 425, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// Abre a janela para o usuario criar uma estrategia personalizada
void JanelaEstrategia::on_btn_criar_personalizada_clicked()
{
    if (!m_usuario) return;

    // Desmarca as outras opcoes para focar na criacao da personalizada
    ui->radio_conservadora->setChecked(false);
    ui->radio_moderada->setChecked(false);
    ui->radio_agressiva->setChecked(false);

    // Cria e abre a janela de criacao
    JanelaCriarEstrategia janela_criar(m_usuario->getRendaMensal(), this);
    if (janela_criar.exec() == QDialog::Accepted) {
        // Se o usuario salvou, obtem a estrategia criada
        m_estrategia_personalizada = janela_criar.getEstrategiaPersonalizada();
        m_personalizada_criada = true;

        // Desabilita as opcoes pre-definidas para evitar confusao
        ui->radio_conservadora->setEnabled(false);
        ui->radio_moderada->setEnabled(false);
        ui->radio_agressiva->setEnabled(false);

        QMessageBox::information(this, "Sucesso", "Estratégia personalizada criada! Clique em 'Salvar e Continuar' para aplicá-la.");
    }
}

// Salva a estrategia selecionada ou criada no perfil do usuario
void JanelaEstrategia::on_btn_salvar_clicked()
{
    Estrategia estrategia_escolhida;
    bool opcao_valida_selecionada = false;

    // Verifica qual opcao foi selecionada
    if (ui->radio_conservadora->isChecked()) {
        estrategia_escolhida = Estrategia::criarEstrategiaConservadora();
        opcao_valida_selecionada = true;
    } else if (ui->radio_moderada->isChecked()) {
        estrategia_escolhida = Estrategia::criarEstrategiaModerada();
        opcao_valida_selecionada = true;
    } else if (ui->radio_agressiva->isChecked()) {
        estrategia_escolhida = Estrategia::criarEstrategiaAgressiva();
        opcao_valida_selecionada = true;
    } else if (m_personalizada_criada) {
        estrategia_escolhida = m_estrategia_personalizada;
        opcao_valida_selecionada = true;
    }

    // Valida se o usuario fez uma escolha
    if (!opcao_valida_selecionada) {
        QMessageBox::warning(this, "Seleção Necessária", "Por favor, selecione uma das três estratégias ou crie uma personalizada.");
        return;
    }

    // Salva a estrategia no perfil do usuario e fecha a janela
    if (m_usuario) {
        m_usuario->setEstrategia(estrategia_escolhida);
        m_usuario->setEstrategiaDefinida(true);

        if (m_usuario->salvarDados()) {
            QMessageBox::information(this, "Sucesso", "Estratégia definida e salva com sucesso!");
            accept();
        } else {
            QMessageBox::warning(this, "Erro", "Não foi possível salvar a sua escolha de estratégia.");
        }
    }
}

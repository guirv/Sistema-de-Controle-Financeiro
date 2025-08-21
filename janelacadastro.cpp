#include "janelacadastro.h"
#include "ui_janelacadastro.h"
#include <QMessageBox>
#include <QRegularExpression>

using namespace std;

// Construtor da janela de cadastro
JanelaCadastro::JanelaCadastro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaCadastro),
    m_user(nullptr)
{
    ui->setupUi(this);

    // Inicia os campos de senha como desabilitados
    ui->label_senha->setEnabled(false);
    ui->input_senha->setEnabled(false);
    ui->label_confirmar_senha->setEnabled(false);
    ui->input_confirmar_senha->setEnabled(false);
}

// Destrutor da janela
JanelaCadastro::~JanelaCadastro()
{
    delete ui;
}

// Controla a visibilidade dos campos de senha com base na checkbox
void JanelaCadastro::on_check_conta_privada_stateChanged(int arg1)
{
    bool habilitar = (arg1 == Qt::Checked);

    ui->label_senha->setEnabled(habilitar);
    ui->input_senha->setEnabled(habilitar);
    ui->label_confirmar_senha->setEnabled(habilitar);
    ui->input_confirmar_senha->setEnabled(habilitar);

    // Limpa os campos de senha se a opcao for desmarcada
    if (!habilitar) {
        ui->input_senha->clear();
        ui->input_confirmar_senha->clear();
    }
}

// Retorna o usuario criado
User* JanelaCadastro::getUser() const
{
    return m_user;
}

// Metodo chamado ao clicar "OK", realiza a validacao e criacao do usuario
void JanelaCadastro::accept()
{
    // Coleta de dados do formulario
    QString nickname = ui->input_username->text().trimmed();
    QString nome = ui->input_nome_completo->text().trimmed();
    QString rendaStr = ui->input_renda_mensal->text().trimmed();
    QString saldoStr = ui->input_saldo_inicial->text().trimmed();
    bool contaPrivada = ui->check_conta_privada->isChecked();
    QString senha = ui->input_senha->text();
    QString confirmarSenha = ui->input_confirmar_senha->text();
    QDate dataNascimento = ui->input_data_nascimento->date();
    int diaPagamento = ui->input_dia_pagamento->value();

    // Validacao dos campos

    // Valida se todos os campos obrigatorios foram preenchidos
    if (nickname.isEmpty() || nome.isEmpty() || rendaStr.isEmpty() || saldoStr.isEmpty()) {
        QMessageBox::warning(this, "Erro de Validação", "Todos os campos são obrigatórios!");
        return;
    }

    // Valida se o nome contem apenas letras e espacos
    static QRegularExpression regexNome("^[a-zA-Z\\s]+$");
    if (!regexNome.match(nome).hasMatch()) {
        QMessageBox::warning(this, "Erro de Validação", "O campo 'Nome Completo' deve conter apenas letras e espaços!");
        return;
    }

    // Valida se a renda e o saldo sao numeros validos
    static QRegularExpression regexNumero("^[0-9]+([.,][0-9]{1,2})?$");
    if (!regexNumero.match(rendaStr).hasMatch() || !regexNumero.match(saldoStr).hasMatch()) {
        QMessageBox::warning(this, "Erro de Validação", "Os campos 'Renda' e 'Saldo' devem conter apenas números válidos.");
        return;
    }

    // Valida a senha caso a conta seja privada
    if (contaPrivada) {
        if (senha.length() < 4) {
            QMessageBox::warning(this, "Erro de Validação", "A senha deve ter no mínimo 4 caracteres.");
            return;
        }
        if (senha != confirmarSenha) {
            QMessageBox::warning(this, "Erro de Validação", "As senhas não são idênticas.");
            return;
        }
    }

    // Valida se a data de nascimento nao e uma data futura
    if (dataNascimento > QDate::currentDate()) {
        QMessageBox::warning(this, "Erro de Validação", "A data de nascimento não pode ser uma data futura.");
        return;
    }

    // Criacao do objeto User

    // Converte os valores de renda e saldo para double
    double renda = rendaStr.replace(",", ".").toDouble();
    double saldo = saldoStr.replace(",", ".").toDouble();

    // Cria a instancia do novo usuario
    m_user = new User(nickname.toStdString(), nome.toStdString(), saldo, renda);
    m_user->setDataNascimento(dataNascimento);
    m_user->setDiaPagamento(diaPagamento);

    // Define os dados da conta privada, se aplicavel
    if (contaPrivada) {
        m_user->setContaPrivada(true);
        m_user->setSenha(senha.toStdString());
    }

    // Fecha a janela com sucesso se todas as validacoes passaram
    QDialog::accept();
}

#include "janelanovadespesa.h"
#include "ui_janelanovadespesa.h"
#include <QMessageBox>

using namespace std;

// Construtor da janela de nova despesa
JanelaNovaDespesa::JanelaNovaDespesa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaNovaDespesa),
    // Inicializa uma despesa "vazia" para garantir que o objeto e valido
    m_despesa(0, "", QDate::currentDate(), "")
{
    ui->setupUi(this);

    // Define a data do formulario como a data atual por padrao
    ui->input_data->setDate(QDate::currentDate());

    // Define a lista de categorias disponiveis
    QStringList categorias = {
        "Moradia", "Alimentação", "Transporte", "Saúde", "Educação",
        "Desejos e Lazer", "Investimentos", "Outros"
    };

    // Adiciona as categorias ao menu suspenso (ComboBox)
    ui->combo_categoria->addItems(categorias);
}

// Destrutor da janela
JanelaNovaDespesa::~JanelaNovaDespesa()
{
    delete ui;
}

// Metodo chamado ao clicar "OK", valida os dados e cria o objeto Despesa
void JanelaNovaDespesa::accept()
{
    // Coleta os dados preenchidos nos campos do formulario
    QString descricao = ui->input_descricao->text().trimmed();
    QString valorStr = ui->input_valor->text().trimmed();
    QDate data = ui->input_data->date();
    QString categoria = ui->combo_categoria->currentText();

    // Valida os dados para garantir que sao consistentes
    bool conversaoOk;
    double valor = valorStr.replace(",", ".").toDouble(&conversaoOk);

    if (descricao.isEmpty() || !conversaoOk || valor <= 0) {
        QMessageBox::warning(this, "Erro de Validação", "Por favor, preencha a descrição e um valor numérico válido e positivo.");
        return; // Impede o fechamento da janela se a validacao falhar
    }

    // Cria o objeto Despesa com os dados validados
    m_despesa = Despesa(valor, descricao.toStdString(), data, categoria.toStdString());

    // Chama o metodo original para fechar a janela com sucesso
    QDialog::accept();
}

// Retorna a despesa que foi criada na janela
Despesa JanelaNovaDespesa::getDespesa() const
{
    return m_despesa;
}

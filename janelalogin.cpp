#include "janelalogin.h"
#include "ui_janelalogin.h"
#include "janelacadastro.h"
#include "perfis.h"
#include "janelasenha.h"
#include "janelasobremim.h"
#include <QMessageBox>

using namespace std;

// Construtor da janela de login
JanelaLogin::JanelaLogin(Perfis* gerenciador, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaLogin),
    m_lista(gerenciador),
    m_usuarioLogado(nullptr)
{
    ui->setupUi(this);
}

// Destrutor da janela
JanelaLogin::~JanelaLogin()
{
    delete ui;
}

// Abre a janela de cadastro quando o botao "Registrar-se" e clicado
void JanelaLogin::on_btn_registrarse_clicked()
{
    JanelaCadastro janela_cadastro(this);

    // Executa a janela de cadastro e espera o usuario interagir com ela
    if (janela_cadastro.exec() == QDialog::Accepted) {
        User* novoUsuario = janela_cadastro.getUser();

        // Se o usuario foi criado e o gerenciador de perfis existe
        if (novoUsuario && m_lista) {
            // Tenta salvar os dados do novo usuario em arquivo
            if (novoUsuario->salvarDados()) {
                QMessageBox::information(this, "Sucesso!", "Perfil cadastrado com sucesso!");
                m_lista->adicionarPerfil(novoUsuario);
            } else {
                QMessageBox::warning(this, "Erro de Arquivo", "Não foi possível salvar o perfil do usuário.");
                delete novoUsuario; // Libera a memoria se o salvamento falhar
            }
        }
    }
}

// Tenta realizar o login quando o usuario clica em "OK"
void JanelaLogin::accept()
{
    string username = ui->input_username->text().toStdString();

    // Valida se o campo de username foi preenchido
    if (username.empty()) {
        QMessageBox::warning(this, "Erro", "Por favor, informe um username!");
        return;
    }

    // Procura o usuario na lista de perfis carregados
    User* usuario = m_lista->getByUsername(username);

    // Valida se o usuario foi encontrado
    if (!usuario) {
        QMessageBox::warning(this, "Erro", "Este perfil não está cadastrado! REGISTRE-SE!");
        return;
    }

    // Se a conta for privada, solicita a senha
    if (usuario->isContaPrivada()) {
        JanelaSenha janela_senha(this);
        if (janela_senha.exec() == QDialog::Accepted) {
            string senha_digitada = janela_senha.getSenha().toStdString();

            // Verifica se a senha digitada esta correta
            if (usuario->getSenha() == senha_digitada) {
                m_usuarioLogado = usuario;
                QMessageBox::information(this, "Login", "Login bem-sucedido!");
                QDialog::accept(); // Fecha a janela com sucesso
            } else {
                QMessageBox::warning(this, "Erro", "Senha incorreta. TENTE NOVAMENTE!");
                return;
            }
        } else {
            // Se o usuario cancelar a janela de senha, o login e abortado
            return;
        }
    } else {
        // Se a conta for publica, o login e direto
        m_usuarioLogado = usuario;
        QMessageBox::information(this, "Login", "Login bem-sucedido!");
        QDialog::accept();
    }
}

// Retorna o ponteiro para o usuario que fez o login
User* JanelaLogin::getUsuarioLogado() const
{
    return m_usuarioLogado;
}

// Abre a janela "Sobre Mim"
void JanelaLogin::on_btn_sobremim_clicked()
{
    JanelaSobreMim janela_sobremim(this);
    janela_sobremim.exec();
}

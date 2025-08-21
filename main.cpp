#include "janelalogin.h"
#include "janelaprincipal.h"
#include "janelaestrategia.h"
#include "perfis.h"
#include <QApplication>

// Funcao principal, ponto de entrada da aplicacao
int main(int argc, char *argv[])
{
    // Inicializa a aplicacao Qt
    QApplication a(argc, argv);

    // Cria o gerenciador de perfis e carrega os dados salvos
    Perfis gerenciador;
    gerenciador.carregarPerfis();

    // Cria e exibe a janela de login
    JanelaLogin janelaLogin(&gerenciador);

    // Se o login for bem-sucedido (usuario clicou "OK" e foi validado)
    if (janelaLogin.exec() == QDialog::Accepted)
    {
        // Obtem o ponteiro para o usuario que fez o login
        User* usuarioLogado = janelaLogin.getUsuarioLogado();
        if (!usuarioLogado) return -1; // Encerra se o usuario for invalido

        // Se for o primeiro login do usuario, abre a janela para definir a estrategia
        if (usuarioLogado->primeiro_login())
        {
            JanelaEstrategia janela_est(usuarioLogado);
            if (janela_est.exec() != QDialog::Accepted) {
                return 0; // Encerra se o usuario fechar a janela de estrategia
            }
        }

        // Cria e exibe a janela principal da aplicacao
        JanelaPrincipal janelaPrincipal(usuarioLogado);
        janelaPrincipal.show();

        // Inicia o loop de eventos da aplicacao
        return a.exec();
    }
    else
    {
        // Se o usuario fechar a janela de login, a aplicacao encerra
        return 0;
    }
}

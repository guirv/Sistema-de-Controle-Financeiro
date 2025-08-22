# Sistema de Controle Financeiro Pessoal 
![C++](https://img.shields.io/badge/C%2B%2B-BACKEND-blue.svg)
![Qt](https://img.shields.io/badge/Qt-FRONTEND-green.svg)
![Status](https://img.shields.io/badge/Status-Finished-brightgreen?style=flat-square)

Um sistema desktop intuitivo e personalizável para gerenciamento de finanças pessoais, desenvolvido em C++ com o framework Qt. Permite que os usuários cadastrem seus perfis, definam estratégias e monitorem seus gastos em tempo real através de um dashboard interativo.

## ✨ Funcionalidades Principais

* **👤 Sistema de Login / Registro :** Crie e gerencie múltiplos perfis de usuário, que podem ser protegidos por senha.
  
* **🎯 Estratégias Financeiras:** Escolha entre três estratégias de orçamento pré-definidas (Conservadora, Moderada e Agressiva) ou crie uma 100% personalizada que atenda suas demandas mensais.
  
* **💸 Lançamento de Despesas:** Informe novas despesas e investimentos de forma simples, categorizando cada lançamento (Moradia, Alimentação, Saúde, etc), incluindo uma breve descrição

* **📊 Dashboard Interativo:** A tela principal oferece uma visão geral do mês, informando o valor total das despesas, saldo disponível e barras de progresso que indicam o quanto já foi gasto em relação à meta definida para cada categoria
  
* **🧾 Extrato Detalhado:** Consulte um extrato completo com o histórico de todas as despesas lançadas (incluindo investimentos), organizadas em uma tabela clara e detalhada.
  
* **💾 Persistência de Dados:** Todas as informações de perfil, estratégias e despesas são salvas em arquivos locais, para que seus dados nunca sejam perdidos ao fechar o programa.

## 🛠️ Tecnologias Utilizadas

* **Linguagem de Programação:** C++
* **Framework de Interface Gráfica:** Qt Creator
* **Build:** CMake

## 📷 Capturas de Tela

### ✏️ Estabelecimento de Estratégia Personalizada
![Tela de Login](https://github.com/user-attachments/assets/9cc18e08-d602-4c99-a103-35ffe8e1b235)
- Interface em que o usuário estabelece uma estratégia financeira personalizada, definindo metas de gasto para cada categoria conforme a respectiva necessidade.
### 📊 Dashboard Principal
![Dashboard](https://github.com/user-attachments/assets/cbf384c6-89ef-49c5-837f-0c8ed27d695f)
- Visão geral das finanças mensais: exibe o total de despesas, saldo disponível e barras de progresso indicando o quanto já foi gasto em cada categoria, de maneira comparativa com a meta estabelecida.
### 🧾 Extrato de Lançamentos
![Extrato](https://github.com/user-attachments/assets/619ee62d-6e1b-4827-8182-3e2110b953f7)
- Tabela detalhada com o histórico de todas as despesas e investimentos cadastrados, permitindo acompanhar cada transação de forma clara e organizada.

## 🚀 Como Compilar e Executar o Projeto

### 📋 Pré-requisitos

Antes de começar, verifique se você possui os seguintes componentes instalados no sistema:

- **Compilador C++**  
  - Linux/macOS: GCC ou Clang  
  - Windows: MinGW ou MSVC (Visual Studio)  

- **Qt Framework (>= 6.x)**  
  - Inclui `qmake`, `Qt Designer` e as bibliotecas gráficas.  
  - Baixe em: [https://www.qt.io/download](https://www.qt.io/download)  

- **CMake (>= 3.15)**  
  - Usado para configurar e gerar a build do projeto.  
  - Baixe em: [https://cmake.org/download/](https://cmake.org/download/)  

⚠️ **Importante:** Certifique-se de que o **Qt** e o **CMake** estejam configurados no `PATH` do sistema para serem reconhecidos no terminal.  

---

### 💻 Passo a Passo de Compilação

1. **Clone o repositório**
   ```bash
   git clone https://github.com/guirv/Sistema-de-Controle-Financeiro.git
   ```

2. **Entre no diretório do projeto**
   ```bash
   cd Sistema-de-Controle-Financeiro
   ```

3. **Crie um diretório para a build**
   ```bash
   mkdir build && cd build
   ```

4. **Configure o projeto com o CMake**  
   - Se o Qt estiver no PATH:
     ```bash
     cmake ..
     ```
   - Caso contrário, especifique o caminho para o `Qt6_DIR`, por exemplo:
     ```bash
     cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.5.0/msvc2019_64/lib/cmake/Qt6"
     ```

5. **Compile o projeto**
   ```bash
   cmake --build .
   ```
   - Alternativamente, em Linux/macOS:
     ```bash
     make
     ```

6. **Execute a aplicação**
   - O executável será gerado dentro do diretório `build`.  
   - Exemplos:
     ```bash
     ./SistemaFinanceiro    # Linux/macOS
     SistemaFinanceiro.exe  # Windows
     ```

---

### 🔧 Observações Importantes

- No **Windows**, se aparecer erro de DLL ao executar o `.exe`, utilize o **windeployqt** (incluso no Qt) para copiar as dependências necessárias para a pasta do executável:  
  ```bash
  windeployqt SistemaFinanceiro.exe
  ```

- No **Linux**, pode ser necessário instalar pacotes adicionais:  
  ```bash
  sudo apt-get install qt6-base-dev cmake g++
  ```

- Você pode abrir o projeto diretamente no **Qt Creator** sem usar CMake manualmente. Basta:  
  1. Abrir o Qt Creator  
  2. Selecionar *Open Project*  
  3. Escolher o arquivo `CMakeLists.txt`

---

## 🧭 Roadmap / Melhorias Futuras

- [ ] Implementar autenticação com **armazenamento seguro de credenciais** (usuários e senhas criptografadas)  
- [ ] Migrar a persistência de dados para um **banco de dados relacional** (ex: SQLite, MySQL)
- [ ] Implementar funcionalidade que permita o usuário alterar dados de seu perfil (ex: estratégia financeira, salário, privacidade)
- [ ] Adicionar **suporte a múltiplas moedas** (ex: USD, EUR)  

---

## 🙋 Autor

Desenvolvido por [Guilherme Rodrigues Viaro] - Trabalho Final (Tema Livre) - Linguagem de Programação II - UFSC

---


# 🐾 Guia do Usuário - Sistema de Agendamento Veterinário

Bem-vindo ao Sistema de Agendamento Veterinário! Este sistema foi desenvolvido para facilitar o gerenciamento de clientes, pets e consultas veterinárias.

## 📌 Índice

1. Introdução
2. Instalação
     - Pré-requisitos
     - Passo a Passo de Instalação
3. Login
4. Tela de Consultas Gerais
5. Cadastro de Cliente
6. Cadastro de Pet
7. Pesquisar
8. Alterar Dados ou Apagar Dados
      - Tutor
      - Pet
9. Agendamento
10. Remarcação
11. Cancelar Consulta
12. Consultas do Dia
## 📖 Introdução

O Sistema de Agendamento Veterinário permite gerenciar informações de clientes e pets, agendar consultas e acompanhar atendimentos diários.


## ⚙️ Instalação

### Pré-requisitos 

Certifique-se de que seu computador atende aos seguintes requisitos:

- Sistema Operacional: Windows, macOS ou Linux.
- Espaço em Disco: Aproximadamente 10 GB para instalação do Qt e dependências.

###  Passo a Passo de Instalação

1. Baixar o Qt 6.8

- Acesse o site oficial do Qt: <https://www.qt.io/download.>
- Faça o download do Qt Online Installer para a sua plataforma.


2. Instalar o Qt com MinGW


- Execute o instalador baixado.
- Durante a instalação:
  - Escolha a versão Qt 6.8.
  - Marque a opção Desenvolvimento para Computador.
  -Certifique-se de incluir:
    - Bibliotecas Qt (Desktop).
    - MinGW Toolchain.
    - Ferramentas adicionais como qmake (incluído automaticamente com o Qt Desktop).
- Conclua a instalação.


3. Configurar o Ambiente (Windows)


- Adicione o caminho do MinGW ao PATH do sistema:
  1. Vá até Configurações do Sistema → Sistema → Configurações Avançadas do Sistema.
  2. Clique em Variáveis de Ambiente.
  3. Em Path, adicione o diretório bin do MinGW (geralmente algo como C:\Qt\Tools\mingw1120_64\bin).


4. Clonar o repositório:

   - Abra um terminal ou prompt de comando e execute:
   - ` git clone https://github.com/brenoafsa/VeterinaryScheduleSystem.git `

5. Abrir o Projeto no Qt Creator

- Inicie o Qt Creator.
- Vá em File → Open File or Project.
- Selecione o arquivo .pro do projeto (usado pelo qmake).

6. Configurar o Kit de Compilação

- No Qt Creator, vá para a aba Projects.
- Certifique-se de que o kit de compilação está configurado para Desktop (Qt 6.8 com MinGW).

7- Compilar o Projeto

- No menu superior, clique em Build → Build Project.
- Certifique-se de que o projeto compila sem erros.

8. Executar o Sistema

- Após a compilação, clique em Run (ou pressione Ctrl+R) para iniciar a aplicação.

### Observações
- Caso enfrente problemas na instalação ou configuração, consulte a [documentação oficial do Qt](https://doc.qt.io/qtcreator/).
- Certifique-se de que as dependências de seu projeto estão configuradas corretamente no arquivo .pro.


## 🏠 Login

Ao iniciar a aplicação, você será direcionado para a tela de login, onde deverá informar o login e senha descritos abaixo. Após validação bem-sucedida, você terá acesso ao sistema.

  - Login -> admin
    - Senha -> 12345

-  Login -> user
    - Senha -> password123
      
![image](https://github.com/user-attachments/assets/7ea5569f-82fc-4255-a359-3fda84d69b9d)


##  📋  Consultas Gerais

Depois de realizar o login, você será redirecionado para a tela de Consultas Gerais. Nessa tela, é possível visualizar todas as consultas, organizadas por meses e dias.

![image](https://github.com/user-attachments/assets/ff07cd58-8d8c-4730-b3d4-b37d39e02c19)

## 👤 Cadastro de Cliente

Para cadastrar um novo cliente:

- Acesse "Cadastro".
- Preencha os campos obrigatórios: Nome, CPF(apenas números), Email, Endereço e Telefone.
- Clique no botão "Cadastrar" para salvar as informações.


![image](https://github.com/user-attachments/assets/60cf81c9-f811-478f-86b6-09049f77f12b)

## 🐶 Cadastro de Pet
Para registrar um pet:

- Acesse "Cadastro Pet".
- Preencha os campos: Nome, Espécie, CPF do Tutor(apenas números), Raça, Idade e Cor.
- Clique em "Cadastrar" para salvar o pet.

  > Atenção! O cadastro do Pet só pode ser realizado caso o tutor seja cadastrado, pois utilizamos o CPF do mesmo.

![image](https://github.com/user-attachments/assets/59944f9a-d109-4ba0-a111-3cc5857bcd53)

## 🔍 Pesquisar
Para encontrar informações de clientes e pets:

- Vá até "Pesquisar".
- Digite o CPF do tutor no campo de busca.
- Clique em "Pesquisar" para visualizar os dados.

![image](https://github.com/user-attachments/assets/fe14649d-2d55-4d26-8053-9c40d3993432)


## ✏️ Alterar Dados ou Apagar Dados
Para modificar informações ou apagar de clientes e pets:

- Aperte o botão "Alterar" nas abas de "Cadastro Pet/Tutor".

- Tutor:
  - Alterar:
    - Preencha os dados obrigatórios: Nome do Tutor, CPF(apenas números).
    - Altere oque precisa (email, endereço ou telefone).
    - Aperte em Alterar.

      > Atenção, em casos de Alterações em nome do tutor ou CPF do mesmo, Apagar tutor e Cadastrar novamente.

  - Apagar:
    - Preencha os dados obrigatórios: Nome do Tutor, CPF(apenas números), Email, Endereço e Telefone.
    - Aperte em Apagar.
    
      > Atenção ao preenchimento correto de todos os campos, pois é com isto que identificamos o tutor para conseguir apagar.

  - Listar:
    - Para casos de confirmação de alteração ou de apagamento, poderia verificar no Botão listar, ele lista tutores disponíveis no banco de dados.

![image](https://github.com/user-attachments/assets/0b2fce3b-3413-48d2-846d-03d68f1afcb6)






    
- Pet:
  - Alterar:
    - Preencha os dados obrigatórios: Nome do Pet, CPF do Tutor(apenas números).
    - Altere oque precisa (Espécie, Raça, Idade e/ou Cor).
    - Aperte em Alterar.

      > Atenção, em casos de Alterações em nome do Pet, Apagar Pet e Cadastrar novamente.

  - Apagar:
    - Preencha os dados obrigatórios: Nome do Pet, Espécie, CPF do Tutor(apenas números), Raça, Idade e Cor.
    - Aperte em Apagar.
    
      > Atenção ao preenchimento correto de todos os campos, pois é com isto que identificamos o Pet para conseguir apagar.

  - Listar:
    - Para casos de confirmação de alteração ou de apagamento, poderia verificar no Botão listar, ele lista tutores disponíveis no banco de dados.

      


![image](https://github.com/user-attachments/assets/bebce981-58d4-43e0-bb72-cb6111c38ffe)



## 📅 Agendamento
Para marcar uma consulta:

- Vá até "Agendamento".
- Preencha os dados obrigatórios: Nome do Pet, CPF do Tutor(apenas números), Data, Hora e Veterinário Responsável.
- Clique em "Cadastrar" para confirmar.

  > Atenção! O Agendamento de consulta só pode ser realizado caso o tutor seja cadastrado e o nome do pet esteja disponível no CPF do mesmo.



![image](https://github.com/user-attachments/assets/4b603419-c3e0-49b5-b924-fc65af598cec)

## 📅 Remarcação
Para Remarcar uma consulta:

- Vá até "Remarcação".
- Preencha os dados obrigatórios: Nome do Pet, CPF do Tutor(apenas números), Data, Hora e Veterinário Responsável.
- Clique em "Alterar" para confirmar.

  > Atenção ao preenchimento correto do Nome do Pet, CPF do tutor(apenas números e Veterinário Responsável. Na remarcação você mudará apenas Horário e/ou Data.


![image](https://github.com/user-attachments/assets/8661aa8c-7f21-4620-8947-5e2a3280a87a)


## 📅 Cancelar Consulta
Para Cancelar uma consulta:

- Vá até "Cancelar Consulta".
- Preencha os dados obrigatórios: Nome do Pet, CPF do Tutor(apenas números), Data, Hora e Veterinário Responsável.
- Clique em "Apagar" para confirmar.

  > Atenção ao preenchimento correto de todos os campos, pois é com isto que identificamos a consulta.

![image](https://github.com/user-attachments/assets/3c32c217-1aa5-4881-92b7-9ececbe86d8e)


## 📋 Consultas do Dia
Para visualizar as consultas agendadas para o dia:

- Acesse "Consulta".
- A lista de atendimentos será exibida automaticamente.

> Na campo de pesquisar, poderá pesquisar pelo nome do animalzinho ou pelo CPF do Tutor(apenas números).

![image](https://github.com/user-attachments/assets/3af348d8-02d5-4425-898d-6484643d1e40)


## 👥 Equipe

- Camily Vitoria Saraiva
- Maria Letícia Figuerôa
- Breno Augusto Ferreira

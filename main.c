#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define maxescolas 5
#define maxusers 200
#define maxtransacao 5000

typedef struct{
    int id,campus;
    char nome[50],abreviatura[15],localidade[20];
} escolas;

typedef struct{
    int id,idEscola,nif;
    float saldo;
    char nome[50],tipo[20],email[40];
} users;

typedef struct{
    int ano,mes,dia,hora,min,seg;
} dataehora;

typedef struct{
    int id,idUser;
    float valorTransacao;
    char tipo;
    dataehora datahora;
} transacoes;


bool menuPrincipal(bool);
bool funcaoswitch(char, bool);
void menuEscola(void);
void menuUtilizador(void);
void menuTransacoes(void);
void menuEstatisticas(void);
void lerEscolas(void);
void gravarEscolas(void);
int verificacaoMaximoEscola(void);
void gravarUtilizador(void);
int mostrarEscolaIDs(void);
int verificacaoMaximoUtilizador(void);
void lerUtilizador(void);
void editarUtilizador(void);
int mostrarUsersIDs(void);
void dadosParaEditar (int, users[],int);
void gravarTransacao(void);
int datahoraAutomatico(void);
int verificacaoMaximaTransacao(void);
int mostrarUtilizadores(void);
void gravarTransacaoContinuacao(transacoes [],users[]);
void gravarTransacaoFicheiro(users[],transacoes[]);
void lerTransacao(void);
void estatisticasFaturadoEscola(float*[]);
void CalcularvaloresEscolas(transacoes[],users[],float[],int);
void mostrarValoresEscola(float[]);
void estatisticaPercentagemTransacao(void);
void transacaoPagamentoTipoUser(void);
int inserirdatas(int*,int*,int*,int*,int*,int*,int*,int*);
int verificarDatas(int,int,int,int,int,int,int,int);
char menuEscolherTipoUser(void);
float encontrardatas(users[],transacoes[],int,char,float,int);
int comparardatas(int,int,int,int,int,int,int,int,transacoes[],int);


int main(){
    bool sair=false;
    while(sair==false)
    {
        system("cls");
        sair = menuPrincipal(sair);        // FAZ A ESCRITA DO MENU PRINCIPAL
    }
    return 0;
}

bool menuPrincipal(bool sair){
    char opcao;
    float valores[maxescolas]={0,0,0,0,0};
    estatisticasFaturadoEscola(&valores);
    printf("\n\n\n------ MENU ------");
    printf("\nPrima a opcao que pretende utilizar!\n\n\n1 - Escolas\n2 - Utilizadores\n3 - Transacoes\n4 - Estatisticas\n0 - Sair\n\nOpcao - ");// FALTA COLOCAR LINHAS REFERENTES A DADOS DE FICHEIROS;
    scanf(" %c",&opcao);
    sair = funcaoswitch(opcao,sair);
    return sair;
}

bool funcaoswitch(char opcao, bool sair){
    switch (opcao){
        case '1':
            menuEscola();
        break;
        case '2':
            menuUtilizador();
        break;
        case '3':
            menuTransacoes();
        break;
        case '4':
            menuEstatisticas();
        break;
        case '0':
            sair = true;
        break;
        default:
            printf("Introduza uma opcao valida...");
            system("pause");
    }
    return sair;
 }

void menuEscola(void){
    char opcao;
    system("cls");
    printf("\nQue acao pretende realizar?\n\n\n 1 - Consultar Escolas\n 2 - Registar nova Escolas (Apenas possivel se o numero de escolas for inferior a 5!)\n 0 - Voltar ao menu anterior\n\n\nOpcao - ");
    scanf(" %c",&opcao);
    switch(opcao){
        case '1':
            lerEscolas();
            system("pause");
        break;
        case '2':
            gravarEscolas();
            system("pause");
        break;
        case '0':
            return 0;
        break;
        default:
            printf("Introduza uma opcao valida!");
            getchar();
    }
}

void menuUtilizador(void){
    char opcao;
    system("cls");
    printf("Que acao pretende realizar?\n\n\n 1 - Consultar utilizadores\n 2 - Editar um utilizador existente\n 3 - Registar novo utilizador (Apenas possivel se o numero de utilizadores for inferior a 200!)\n 0 - Voltar ao menu anterior\n\n\nOpcao - ");
    scanf(" %c",&opcao);
    switch (opcao)
    {
        case '1':
            lerUtilizador();
            break;
        case '2':
            editarUtilizador();
            break;
        case '3':
            system("cls");
            gravarUtilizador();
            break;
        case '0':
            return 0;
            break;
        default:
            printf("Introduza uma opcao valida!");
            system("pause");
    }
}

void menuTransacoes(void){
    char opcao;
    system("cls");
    printf("Que acao pretende realizar?\n\n\n 1 - Registar transacao\n 2 - Consultar transacao\n 0 - Voltar ao menu anterior\n\n\n Opcao - ");
    scanf(" %c",&opcao);
    switch(opcao)
    {
        case '1':
            system("cls");
            gravarTransacao();
        break;
        case '2':
            system("cls");
            lerTransacao();
        break;
        case '0':
            return 0;
        break;
        default:
            printf("Introduza uma opcao valida!");
            system("pause");
    }
}

void menuEstatisticas(void){
    char opcao;
    system("cls");
    printf("Que acao pretende realizar?\n\n\n 1 - Percentagem de transacao por escola\n 2 - Total transacao por tipo de user entre datas\n 0 - Voltar ao menu anterior\n\n\n Opcao - ");
    scanf(" %c",&opcao);
    switch(opcao)
    {
        case '1':
            system("cls");
            estatisticaPercentagemTransacao();
            system("pause");
        break;
        case '2':
            system("cls");
            transacaoPagamentoTipoUser();
            system("pause");
        break;
        case '0':
            return 0;
        break;
        default:
            printf("Introduza uma opcao valida!");
            system("pause");
    }
}

void lerEscolas(void){
    int i;
    escolas escola[maxescolas];
    FILE *ficheiroEscolas;
    system("cls");
    for(i=0;i<maxescolas;i++){
        escola[i].id=0;
    }
    ficheiroEscolas = fopen("escolas.dat","rb");
    if(ficheiroEscolas == NULL)
        printf("\nErro! Ficheiro nao existe!\n");
    fread(escola,sizeof(escolas),5,ficheiroEscolas);
    for(i=0;i<5;i++){
        if (escola[i].id!=0){
            printf("\nID: %i\nCampus %i\n",escola[i].id,escola[i].campus);
            puts(escola[i].nome);
            puts(escola[i].abreviatura);
            puts(escola[i].localidade);
        }
    }
    fclose(ficheiroEscolas);
}

void gravarEscolas(void){
    escolas escola[1];
    FILE*ficheiroEscolas;
    int idatual=0;
    system("cls");
    idatual = verificacaoMaximoEscola();
    if (idatual <= 4){       // se maior que 4 é porque já existem 5 escolas
        escola[0].id= idatual+1;
        printf("Numero do Campus: ");
        scanf("%i",&escola[0].campus);
        printf("Nome: ");
        fflush(stdin);
        gets(escola[0].nome);
        printf("Abreviatura: ");
        fflush(stdin);
        gets(escola[0].abreviatura);
        printf("Localidade: ");
        fflush(stdin);
        gets(escola[0].localidade);
        ficheiroEscolas= fopen("Escolas.dat","ab");
        fwrite(escola,sizeof(escolas),1,ficheiroEscolas);
        fclose(ficheiroEscolas);
    } else printf("Ja existem 5 escolas registadas...\n");
}

int verificacaoMaximoEscola(void){
    int contador=0,i;
    escolas escola[maxescolas];
    FILE *ficheiroEscolas;
    for(i=0;i<5;i++){
        escola[i].id=0;
    }
    ficheiroEscolas = fopen("escolas.dat","rb");
    fread(escola,sizeof(escolas),5,ficheiroEscolas);
    while(escola[contador].id!=0&&contador<5)
        contador++;
    return contador;
}

void gravarUtilizador(void){
    users user[1];
    int idatual=0,escola=0;
    FILE*ficheiroUsers;
    idatual = verificacaoMaximoUtilizador();
    if (idatual <= 199){ // se maior que 199 é porque já existem 200 users
        user[0].id = idatual+1;
        escola = mostrarEscolaIDs();
        user[0].idEscola = escola;
        printf("NIF: ");
        scanf("%i",&user[0].nif);
        printf("Nome: ");
        fflush(stdin);
        gets(user[0].nome);
        printf("Tipo(Estudante,Docente,Funcionario): ");
        fflush(stdin);
        gets(user[0].tipo);
        printf("Email: ");
        fflush(stdin);
        gets(user[0].email);
        ficheiroUsers= fopen("Users.dat","ab");
        fwrite(user,sizeof(users),1,ficheiroUsers);
        fclose(ficheiroUsers);
    } else printf("Já existem 200 alunos");
}

int mostrarEscolaIDs(void){
    int i,id, sair =0;
    escolas escola[maxescolas];
    FILE *ficheiroEscolas;
    for(i=0;i<maxescolas;i++){
        escola[i].id=0;
    }
    ficheiroEscolas = fopen("Escolas.dat","rb");
    if(ficheiroEscolas == NULL)
        printf("\nErro! Ficheiro nao existe!\n");
    fread(escola,sizeof(escolas),maxescolas,ficheiroEscolas);
    for(i=0;i<5;i++){
        if (escola[i].id!=0){
            printf("\nID: %i\n%s\n",escola[i].id,escola[i].nome);
        }
    }
    fclose(ficheiroEscolas);
    while (sair==0){
        printf("\nIndique o id da escola ao qual pretende adicionar o utilizador: ");
        scanf("%i",&id);
            for (i=0;i<maxescolas;i++)
                if (id == escola[i].id&& id != 0) sair=1;
    }
    return id;
}

int verificacaoMaximoUtilizador(void){
    int contador=0,i;
    users user[maxusers];
    FILE *ficheiroUser;
    for(i=0;i<maxusers;i++){
        user[i].id=0;
    }
    ficheiroUser = fopen("users.dat","rb");
    fread(user,sizeof(users),maxusers,ficheiroUser);
    fclose(ficheiroUser);
    while(user[contador].id!=0)
        contador++;
    return contador;
}

void lerUtilizador(void){
    int i;
    users user[maxusers];
    FILE *ficheiroUsers;
    system("cls");
     for(i=0;i<maxusers;i++){
        user[i].id=0;
    }
    ficheiroUsers= fopen("Users.dat","rb");
    if(ficheiroUsers == NULL)
        printf("\nErro! Ficheiro nao existe!\n");
    fread(user,sizeof(users),maxusers,ficheiroUsers);
    for(i=0;i<maxusers;i++){
        if (user[i].id!=0){
            printf("\nID: %i\nID Escola: %i\nNIF: %i\nSaldo: %.2f\n",user[i].id,user[i].idEscola,user[i].nif,user[i].saldo);
            puts(user[i].tipo);
            puts(user[i].nome);
            puts(user[i].email);
        }
    }
    system("pause");
    fclose(ficheiroUsers);
}

void editarUtilizador (void){
    users user[maxusers];
    int idatual=0, usermax=0;
    FILE *ficheiroUsers;
    system("cls");
    idatual = mostrarUsersIDs() - 1;
    usermax = verificacaoMaximoUtilizador();
    if (idatual != -1){         // se for -1 o utilizador selecionou o 0 e pretende cancelar
        ficheiroUsers=fopen("Users.dat","rb");
        fread(user,sizeof(users),maxusers,ficheiroUsers);
        fclose(ficheiroUsers);
        dadosParaEditar(idatual, user, usermax);
    }
}

int mostrarUsersIDs(void){
    int i,id, sair =0;
    users user[maxusers];
    FILE *ficheiroUsers;
    for(i=0;i<maxusers;i++){
        user[i].id=0;
    }
    ficheiroUsers = fopen("Users.dat","rb");
    if(ficheiroUsers == NULL)
        printf("\nErro! Ficheiro nao existe!\n");
    fread(user,sizeof(users),maxusers,ficheiroUsers);
    for(i=0;i<maxusers;i++){
        if (user[i].id!=0){
            printf("\nID: %i\n%s\n%s\n",user[i].id,user[i].nome,user[i].email);
        }
    }
    fclose(ficheiroUsers);
    while (sair==0){
        printf("\nIndique o id do utilizador que pretende editar (0 para cancelar): ");
        scanf("%i",&id);
            for (i=0;i<maxusers;i++)
                if (id == user[i].id) sair=1;
    }
    return id;
}

void dadosParaEditar (int idatual, users user[],int usermax){
    FILE *ficheiroUsers;
    printf("\nDigite os novos dados do utilizador:\n\nNIF:");
    scanf("%i",&user[idatual].nif);
    printf("Nome: ");
    fflush(stdin);
    gets(user[idatual].nome);
    printf("Tipo(Estudante,Docente,Funcionario): ");
    fflush(stdin);
    gets(user[idatual].tipo);
    printf("Email: ");
    fflush(stdin);
    gets(user[idatual].email);
    ficheiroUsers= fopen("Users.dat","wb");
    fwrite(user,sizeof(users),usermax,ficheiroUsers);
    fclose(ficheiroUsers);
    printf("\nUtilizador alterado!\n");
    system("pause");
}

void gravarTransacao(void){
    FILE *ficheiroTransacoes, *ficheiroUsers;
    transacoes transacao[1];
    users user[maxusers];
    int idatual=0,idUser=0;
    struct tm* datahora;
    datahora = datahoraAutomatico();
    idatual=verificacaoMaximaTransacao();
    if (idatual<=4999){   // se maior que 4999 é porque já existem 5000 transacoes
        idUser = mostrarUtilizadores();        //recebe o id do utilizador que vai fazer a transacao
        if (idUser != 0){
            transacao[0].id = idatual+1;
            transacao[0].idUser = idUser;
            transacao[0].datahora.ano= datahora->tm_year+1900;  // +1900 porque a funcao apenas começa a contar a partir de 1900
            transacao[0].datahora.mes= datahora->tm_mon+1;      // +1 porque o mes vai de 0-11
            transacao[0].datahora.dia= datahora->tm_mday;
            transacao[0].datahora.hora= datahora->tm_hour;
            transacao[0].datahora.min= datahora->tm_min;
            transacao[0].datahora.seg= datahora->tm_sec;
            ficheiroUsers= fopen("Users.dat","rb");
            fread(user,sizeof(users),maxusers,ficheiroUsers);
            fclose(ficheiroUsers);
            gravarTransacaoContinuacao(transacao,user);
        }
    } else printf("Já existem 5000 transacoes");
}

int datahoraAutomatico(void){
    time_t tempo;
    struct tm * estruturaDataHora;
    time(&tempo);
    estruturaDataHora = localtime(&tempo);
    return estruturaDataHora;
}

int verificacaoMaximaTransacao(void){
    int contador=0,i;
    transacoes transacao[maxtransacao];
    FILE *ficheiroTransacoes;
    for(i=0;i<maxtransacao;i++){
        transacao[i].id=0;
    }
    ficheiroTransacoes = fopen("Transacoes.dat","rb");
    fread(transacao,sizeof(transacoes),maxtransacao,ficheiroTransacoes);
    fclose(ficheiroTransacoes);
    while(transacao[contador].id!=0)
        contador++;
    return contador;
}

int mostrarUtilizadores(void){
    int i,id, sair =0;
    users user[maxusers];
    FILE *ficheiroUsers;
    for(i=0;i<maxusers;i++){
        user[i].id=0;
    }
    ficheiroUsers = fopen("Users.dat","rb");
    if(ficheiroUsers == NULL)
        printf("\nErro! Ficheiro nao existe!\n");
    fread(user,sizeof(users),maxusers,ficheiroUsers);
    for(i=0;i<maxusers;i++){
        if (user[i].id!=0){
            printf("\nID: %i\n%s\n%s\nSaldo: %.2f\n",user[i].id,user[i].nome,user[i].email,user[i].saldo);
        }
    }
    fclose(ficheiroUsers);
    while (sair==0){
        printf("\nIndique o id do aluno ao qual pretende adicionar o transacao (0 para sair): ");
        scanf("%i",&id);
            for (i=0;i<maxusers;i++)
                if (id == user[i].id) sair=1;
    }
    return id;
}

void gravarTransacaoContinuacao(transacoes transacao[],users user[]){
    bool sairwhile = false,sairwhile2=false;
    int usermax=0;
    while (sairwhile==false){
        printf("Indique o tipo de transacao ([C]arregamento/[P]agamento): ");
        fflush(stdin);
        scanf(" %c",&transacao[0].tipo);
        if (transacao[0].tipo == 'C'|| transacao[0].tipo == 'P'&&user[transacao[0].idUser-1].saldo || transacao[0].tipo == 'c' || transacao[0].tipo=='p'&&user[transacao[0].idUser-1].saldo)
            sairwhile=true;
        else printf("Caracter errado, ou o utilizador nao tem saldo!\n");
    }
    while (sairwhile2==false){
        printf("Indique o valor da transacao (escreva o numero com '.' se necessario): ");
        scanf("%f",&transacao[0].valorTransacao);       // SE P OU p E SE O VALOR FOR MAIOR DO QUE O DO SALDO ATUAL
        if((transacao[0].tipo=='p'&&user[transacao[0].idUser-1].saldo>=transacao[0].valorTransacao)||(transacao[0].tipo == 'P'&&user[transacao[0].idUser-1].saldo>=transacao[0].valorTransacao)){
            sairwhile2=true;
            user[transacao[0].idUser-1].saldo= user[transacao[0].idUser-1].saldo - transacao[0].valorTransacao;
        }
        else if (transacao[0].tipo=='C'|| transacao[0].tipo == 'c'){
                user[transacao[0].idUser-1].saldo= user[transacao[0].idUser-1].saldo + transacao[0].valorTransacao;
                sairwhile2=true;
            } else printf("Saldo disponivel inferior ao pagamento efetuado.\n");
    }
    gravarTransacaoFicheiro(user,transacao);
}

void gravarTransacaoFicheiro(users user[], transacoes transacao[]){
    int usermax=0;
    FILE *ficheiroTransacoes, *ficheiroUsers;
    ficheiroTransacoes= fopen("Transacoes.dat","ab");
    fwrite(transacao,sizeof(transacoes),1,ficheiroTransacoes);
    fclose(ficheiroTransacoes);
    usermax = verificacaoMaximoUtilizador();
    ficheiroUsers= fopen("Users.dat","wb");
    fwrite(user,sizeof(users),usermax,ficheiroUsers);
    fclose(ficheiroUsers);
}

void lerTransacao(void){
    int i;
    transacoes transacao[maxtransacao];
    FILE *ficheiroTransacao;
     for(i=0;i<maxtransacao;i++){
        transacao[i].id=0;
    }
    ficheiroTransacao= fopen("Transacoes.dat","rb");
    if(ficheiroTransacao == NULL)
        printf("\nErro! Ficheiro nao existe!\n");
    fread(transacao,sizeof(transacoes),maxtransacao,ficheiroTransacao);
    for(i=0;i<maxtransacao;i++){
        if (transacao[i].id!=0){
            printf("\nID: %i\nID Utilizador: %i\nTipo da transacao:%c\n",transacao[i].id,transacao[i].idUser,transacao[i].tipo);

            printf("Valor:%.2f\nData da transacao: %i-%i-%i\nHora da transacao: %i:%i:%i\n",transacao[i].valorTransacao,transacao[i].datahora.dia,transacao[i].datahora.mes,transacao[i].datahora.ano,transacao[i].datahora.hora,transacao[i].datahora.min,transacao[i].datahora.seg);
        }
    }
    system("pause");
    fclose(ficheiroTransacao);
}

void estatisticasFaturadoEscola(float* valor[]){
    int idatual=0,contador=0;
    float valortotal;
    FILE *ficheiroTransacoes, *ficheiroUsers;
    transacoes transacao[maxtransacao];
    users user[maxusers];
    idatual=verificacaoMaximaTransacao();
    ficheiroTransacoes=fopen("Transacoes.dat","rb");
    fread(transacao,sizeof(transacoes),maxtransacao,ficheiroTransacoes);
    fclose(ficheiroTransacoes);
    ficheiroUsers= fopen("Users.dat","rb");
    fread(user,sizeof(users),maxusers,ficheiroUsers);
    fclose(ficheiroUsers);
    for (int i=0;i<=idatual;i++){
        if(transacao[i].tipo=='P'||transacao[i].tipo=='p'){
            CalcularvaloresEscolas(transacao, user,valor,i);
            contador++;
        }
    }
    if (idatual!= 0&&contador>0)
        mostrarValoresEscola(valor);
}

void CalcularvaloresEscolas(transacoes transacao[], users user[], float valor[],int i){
    int idUser=0,idEscola=0;
    idUser=transacao[i].idUser;
    idEscola=user[idUser-1].idEscola;
    switch(idEscola){
        case 1:
            valor[0]=transacao[i].valorTransacao + valor[0];
        break;
        case 2:
            valor[1]=transacao[i].valorTransacao + valor[1];
        break;
        case 3:
            valor[2]=transacao[i].valorTransacao + valor[2];
        break;
        case 4:
            valor[3]=transacao[i].valorTransacao + valor[3];
        break;
        case 5:
            valor[4]=transacao[i].valorTransacao + valor[4];
        break;
    }
}

void mostrarValoresEscola (float valor[]){
    escolas escola[maxescolas];
    int idatual=0;
    FILE *ficheiroEscolas;
    ficheiroEscolas = fopen("escolas.dat","rb");
    fread(escola,sizeof(escolas),5,ficheiroEscolas);
    fclose(ficheiroEscolas);
    idatual=verificacaoMaximoEscola();
    printf("------ Faturacao por escola ------\n");
    for (int i=0;i<=idatual-1;i++){
        printf("\n%s: %.2f\n",escola[i].nome,valor[i]);
    }
}

void estatisticaPercentagemTransacao(void){
    float valortotal, valoresEscola[maxescolas]={0,0,0,0,0},percentagemEscola;
    int idatual=0;
    FILE *ficheiroEscolas;
    escolas escola[maxescolas];
    ficheiroEscolas = fopen("escolas.dat","rb");
    fread(escola,sizeof(escolas),5,ficheiroEscolas);
    fclose(ficheiroEscolas);
    idatual=verificacaoMaximoEscola();
    estatisticasFaturadoEscola(&valoresEscola);
    valortotal=valoresEscola[0]+valoresEscola[1]+valoresEscola[2]+valoresEscola[3]+valoresEscola[4];
    printf("\n\n\n------ Percentagens ------\n");
    for (int i=0;i<=idatual-1;i++){
        percentagemEscola=valoresEscola[i]*100/valortotal;
        printf("\n%s: %.2f%%\n",escola[i].nome,percentagemEscola);
    }
}

void transacaoPagamentoTipoUser(void){
    int idatual=0,erro,anoMaior,anoMenor,mesMaior,mesMenor,diaMaior,diaMenor,horaMaior,horaMenor,errodatas;
    float valortotal=0;
    char opcaoUser;
    FILE *ficheiroTransacoes, *ficheiroUsers;
    transacoes transacao[maxtransacao];
    users user[maxusers];
    idatual=verificacaoMaximaTransacao();
    ficheiroTransacoes=fopen("Transacoes.dat","rb");
    fread(transacao,sizeof(transacoes),maxtransacao,ficheiroTransacoes);
    fclose(ficheiroTransacoes);
    ficheiroUsers= fopen("Users.dat","rb");
    fread(user,sizeof(users),maxusers,ficheiroUsers);
    fclose(ficheiroUsers);
    erro = inserirdatas(&anoMaior,&anoMenor,&mesMaior,&mesMenor,&diaMaior,&diaMenor,&horaMaior,&horaMenor);
    if (erro == 0){
        opcaoUser=menuEscolherTipoUser();
        for (int i=0;i<=idatual;i++){
            if(transacao[i].tipo=='P'||transacao[i].tipo=='p'){
                errodatas=comparardatas(anoMaior,anoMenor,mesMaior,mesMenor,diaMaior,diaMenor,horaMaior,horaMenor,transacao,i);
                valortotal=encontrardatas(user,transacao,i,opcaoUser,valortotal,errodatas);
            }
        }
        printf("VALOR TOTAL: %.2f\n",valortotal);
    }
}

int inserirdatas(int* anoMaior,int* anoMenor,int* mesMaior,int* mesMenor,int* diaMaior,int* diaMenor,int* horaMaior,int* horaMenor){
    int erro=0;
    printf("Quais as datas que pretende inserir?\n\n--- Mais Antiga ---\nAno: ");
    scanf("%i",&*anoMenor);
    printf("Mes: ");
    scanf("%i",&*mesMenor);
    printf("Dia: ");
    scanf("%i",&*diaMenor);
    printf("Hora: ");
    scanf("%i",&*horaMenor);
    printf("\n\n--- Mais Recente ---\nAno: ");
    scanf("%i",&*anoMaior);
    printf("Mes: ");
    scanf("%i",&*mesMaior);
    printf("Dia: ");
    scanf("%i",&*diaMaior);
    printf("Hora: ");
    scanf("%i",&*horaMaior);
    erro=verificarDatas(*anoMaior,*mesMaior,*diaMaior,*horaMaior,*anoMenor,*mesMenor,*diaMenor,*horaMenor);
    return erro;
}

int verificarDatas(int anoMaior,int mesMaior,int diaMaior, int horaMaior,int anoMenor,int mesMenor,int diaMenor, int horaMenor){
    int erro=0;
    if (anoMaior<anoMenor){
        erro=1;
        printf("Datas inseridas de forma incorreta.");
    }else
        if (anoMaior==anoMenor)
            if(mesMaior<mesMenor){
                printf("Datas inseridas de forma incorreta.");
                erro=1;
            }else
                if (mesMaior==mesMenor)
                    if(diaMaior<diaMenor){
                        erro=1;
                        printf("Datas inseridas de forma incorreta.");
                    }else
                        if(diaMaior==diaMenor)
                            if (horaMaior<horaMenor){
                                printf("Datas inseridas de forma incorreta.");
                                erro=1;
                            }
    return erro;
}

char menuEscolherTipoUser(void){
    bool sair=false;
    char opcao;
    while(sair==false){
        printf("\nDe qual de tipo de utilizador pretende ver as transacoes?");
        printf("\n\n(F)uncionario");
        printf("\n(E)studante");
        printf("\n(D)ocente");
        printf("\nOpcao:");
        scanf(" %c",&opcao);
        if (opcao=='F'||opcao=='f'){
            sair=true;
            opcao='f';
        }
        if (opcao=='E'||opcao=='e'){
            sair=true;
            opcao='e';
        }
        if (opcao=='D'||opcao=='d'){
            sair=true;
            opcao='d';
        }
    }
    return opcao;
}

float encontrardatas(users user[], transacoes transacao[],int i,char opcaoUser,float valortotal,int erro){
    int idUser=0;
    idUser=transacao[i].idUser;
    if (user[idUser-1].tipo[0]=='F'||user[idUser-1].tipo[0]=='f'){
            user[idUser-1].tipo[0]='f';
        }
    if (user[idUser-1].tipo[0]=='E'||user[idUser-1].tipo[0]=='e'){
        user[idUser-1].tipo[0]='e';
    }
    if (user[idUser-1].tipo[0]=='D'||user[idUser-1].tipo[0]=='d'){
        user[idUser-1].tipo[0]='d';
    }
    if (erro == 0){
        if (user[idUser-1].tipo[0]==opcaoUser){
            valortotal=valortotal+transacao[i].valorTransacao;
        }
    }
    return valortotal;
}

int comparardatas(int anoMaior,int anoMenor,int mesMaior,int mesMenor,int diaMaior,int diaMenor,int horaMaior,int horaMenor,transacoes transacao[],int i){
    int erro=0;
    if (anoMaior<transacao[i].datahora.ano)erro=1;
    else if(anoMaior==transacao[i].datahora.ano)
            if(mesMaior<transacao[i].datahora.mes)erro=1;
            else if(mesMaior==transacao[i].datahora.mes)
                    if(diaMaior<transacao[i].datahora.dia)erro=1;
                    else if(diaMaior==transacao[i].datahora.dia)
                            if(horaMaior<transacao[i].datahora.hora)erro=1;
    if(anoMenor>transacao[i].datahora.ano)erro=1;
    else if(anoMenor==transacao[i].datahora.ano)
            if (mesMenor>transacao[i].datahora.mes)erro=1;
            else if (mesMenor==transacao[i].datahora.mes)
                    if (diaMenor>transacao[i].datahora.dia)erro=1;
                    else if(diaMenor==transacao[i].datahora.dia)
                            if (horaMenor>transacao[i].datahora.hora)erro=1;
    return erro;
}

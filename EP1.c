/*
INTEGRANTES DA EQUIPE:
ANA LIDIA LISBOA
GABRIEL FELICIANO
LETICIA SAMPAIO
MARINA BRASIL
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.00000001 // isso é igual a 10 elevado a -8

typedef struct
{
    int tamMatriz; // NUMERO DE LINHAS E VARIAVEIS
    double **matrizRecebida;
} MatrizGS;

// Funcao auxiliares
void trocas(double *a, double *b);

// Declaracao das funcoes a serem utilizadas na main
void conversao(double num);
void equacaoAlgebrica();
void teoremaLagrange(double n, double an, double *coeficientes, double *limites, int contadorLimites);
void metodoNewton(double *limites, int grauEquacao, double *coeficientes);
void sistemaLinear();

int main()
{
    char comando = 0;
    double num_conv = 0.0;

    // Imprime o menu com as opcoes de funcoes ate ser selecionado "F - Finalizar"
    do
    {
        printf("\n\n==== MENU ====\n");
        printf("'C' - Conversao\n'S' - Sistema Linear\n'E' - Equacao Algebrica\n'F' - Finalizar\n");
        printf("Digite a opcao desejada: ");
        scanf(" %c%*[^\n]", &comando); // recebe o comando e limpa o buffer

        switch (comando)
        {
        case 'C':
            printf("insira o numero decimal para conversao: ");
            scanf("%lf", &num_conv);
            conversao(num_conv);
            break;

        case 'S':
            sistemaLinear();
            break;

        case 'E':
            equacaoAlgebrica();
            break;

        case 'F':
            printf("Voce escolheu finalizar a aplicacao.");
            break;

        default:
            printf("Opcao invalida, tente novamente.");
            break;
        }
    } while (comando != 'F');
} // Finalizando a Main

// Implementacao das funcoes declaradas no inicio

void conversao(double num)
{
    // --------------------------- CONVERSAO BINARIA --------------------------------//

    // vetor para salvar o numero binario
    int numBinarioInt[32];  // parte inteira do numero binario
    int numBinarioFrac[32]; // parte fracionaria do numero binario

    char isSigned = 0; // variavel que armazena a informacao do sinal do input

    // testa se o input é negativo, salva a informação e manipula o valor para conversao
    if (num < 0.0)
    {
        isSigned = 1;
        num = -num;
    }

    // separa o input recebido na parte inteira (n) e fracionaria (m)
    int n = (int)num;
    double m = num - n;

    // conversao da parte inteira
    int i = 0; // armazena qtd de casas da parte inteira
    while (n > 0)
    {
        numBinarioInt[i] = n % 2; // salva resto da divisao por 2
        n = n / 2;                // salva o resultado inteiro da divisao por 2
        i++;                      // aumenta contador para impressao ao final
    };

    // imprime a parte inteira em ordem inversa
    printf("Binario: ");
    if (isSigned)
        printf("-"); // imprime o sinal negativo se a variavel isSigned for true
    for (int j = i - 1; j >= 0; j--)
        printf("%d", numBinarioInt[j]); // imprime cada digito salvo no vetor

    // testa se existe parte fracionaria antes de fazer a conversao
    int k = 0; // armazena qtd de casas da parte fracionaria
    if (m)
    {
        // conversao da parte fracionaria
        while (m > 0)
        {
            numBinarioFrac[k] = (int)(m *= 2); // salva a parte inteira da multiplicacao
            m = m - (int)m;                    // salva somente a parte fracionaria apos multiplicacao
            k++;                               // aumenta contador para impressao ao final
        };
        // imprime a parte fracionaria em ordem direta
        printf(".");
        for (int l = 0; l < k && l < 20; l++)
            printf("%d", numBinarioFrac[l]); // imprime cada digito salvo no vetor
    };

    // -------------------------- CONVERSAO OCTAL -----------------------------------//

    // vetor para salvar o numero octal
    int numOctalInt[32];  // parte inteira do numero octal
    int numOctalFrac[32]; // parte fracionaria do numero octal

    double div_int = ceil(i / 3.0);  // encontra quantos conjuntos de 3 existem no inteiro
    double div_frac = ceil(k / 3.0); // encontra quantos conjuntos de 3 existem na fracao

    // separa o input recebido na parte inteira (n) e fracionaria (m)
    n = (int)num;
    m = num - n;

    // pega o valor inteiro de tres em tres e converte em octal
    int j = 0; // armazena qtd de casas da parte inteira
    while (n)
    {
        numOctalInt[j++] = (n & 0b111); // salva a informação de 3 bits significativos do inteiro
        n >>= 3;                        // desloca a parte inteira em 3 posicoes
    }

    // imprime a parte inteira em ordem inversa
    printf("\nOctal: ");
    if (isSigned)
        printf("-"); // imprime o sinal negativo se a variavel isSigned for true
    for (j = div_int - 1; j >= 0; j--)
        printf("%d", numOctalInt[j]); // imprime cada digito salvo no vetor

    j = 0; // armazena qtd de casas da parte fracionaria
    // inicia conversao da parte fracionaria se m nao for 0 e tiver ate 20 casas fracionarias
    while (m && j < 20)
    {
        m *= 8;                     // multiplica fracionario por 8 para transformar temporariamente em inteiro
        numOctalFrac[j++] = (int)m; // salva parte "inteira" da conversao
        m = m - (int)m;             // salva a parte fracionaria restante para conversao
    }

    // imprime a parte fracionaria em ordem direta
    printf(".");
    for (j = 0; j < div_frac; j++)
        printf("%d", numOctalFrac[j]); // imprime cada digito salvo no vetor

    // ----------------------- CONVERSAO HEXADECIMAL --------------------------------//

    // vetor para salvar o numero octal
    int numHexaInt[32];  // parte inteira do numero hexadecimal
    int numHexaFrac[32]; // parte fracionaria do numero hexadecimal

    div_int = ceil(i / 4.0);  // encontra quantos conjuntos de 4 existem no inteiro
    div_frac = ceil(k / 4.0); // encontra quantos conjuntos de 4 existem na fracao

    // separa o input recebido na parte inteira (n) e fracionaria (m)
    n = (int)num;
    m = num - n;

    // pega o valor inteiro de quatro em quatro e converte em hexadecimal
    int q = 0;
    while (n)
    {
        numHexaInt[q++] = (n & 0b1111); // salva a informação de 4 bits significativos do inteiro
        n >>= 4;                        // desloca a parte inteira em 4 posicoes
    }

    // imprime a parte inteira em ordem inversa
    printf("\nHexadecimal: ");
    if (isSigned)
        printf("-"); // imprime o sinal negativo se a variavel isSigned for true
    for (q = div_int - 1; q >= 0; q--)
        printf("%X", numHexaInt[q]); // imprime cada digito salvo no vetor

    q = 0; // armazena qtd de casas da parte fracionaria
    // inicia conversao da parte fracionaria se m nao for 0 e tiver ate 20 casas fracionarias
    while (m && q < 20)
    {
        m *= 16;                   // multiplica fracionario por 16 para transformar temporariamente em inteiro
        numHexaFrac[q++] = (int)m; // salva parte "inteira" da conversao
        m = m - (int)m;            // salva a parte fracionaria restante para conversao
    }

    // imprime a parte fracionaria em ordem direta
    printf(".");
    for (q = 0; q < div_frac; q++)
        printf("%X", numHexaFrac[q]); // imprime cada digito salvo no vetor
};                                    // Acabou a função: conversao

void trocas(double *a, double *b)
{
    /*
    Funcao para auxiliar nas trocas de valores em diferentes posicoes de um
    ponteiro do tipo double.
    */
    double aux;

    aux = *a;
    *a = *b;
    *b = aux;
}; // Acabou a função: trocas

int verificaDigitado(int n, int grauEquacao)
{
    /*
    Funcao criada para verificar se o número que foi digitado no coeficiente
    é 0 no caso de x[n] e x[0]
    */

    int digitado;
    printf("Valor invalido. Digite novamente\n");
    scanf("%d", &digitado);

    if ((digitado <= 0 && n != grauEquacao) ||
        (digitado == 0 && n == grauEquacao))
    {
        digitado = verificaDigitado(n, grauEquacao);
    }
    return digitado;
} // Acabou a função: verificaDigitado

void equacaoAlgebrica()
{
    /*
    Função vai ler o grau de uma equacao algebrica, ler o coeficientes de n até
    0 Vai dar erro caso x[n] <= 0 ou x[0]
    */

    int grauEquacao, i, contadorLimites = 0, novoValor;
    double *coeficientes, limites[4];

    printf("\nDigite o grau da equacao: ");
    scanf("%d%*c", &grauEquacao);

    coeficientes = malloc(sizeof(double) * grauEquacao + 1);

    // Caso coeficiente é nulo
    if (coeficientes == NULL)
    {
        printf("\n\nFaltou memoria.\n");
        return;
    }

    /*
    Vai receber os valores do coeficiente, verificando se o x[n] >= 0 e
    x[0] != 0 para funcionar
    */
    for (i = 0; i <= grauEquacao; i++)
    {
        printf("\nDigite x[%d]: ", grauEquacao - i);
        scanf("%lf%*c", &coeficientes[i]);
        if (((i == 0) && (coeficientes[i] <= 0)) ||
            ((i == (grauEquacao)) && (coeficientes[i] == 0)))
        {
            novoValor = verificaDigitado(i, grauEquacao);
            coeficientes[i] = novoValor;
        }
    }

    // Calcula L para limite superior das raizes positivas.
    teoremaLagrange(grauEquacao, coeficientes[0], coeficientes, limites, contadorLimites);
    contadorLimites++;

    for (i = 0; i < (grauEquacao + 1) / 2; i++)
    {
        // Invertemos a ordem dos coeficientes para obter X^n . p(1/x)
        trocas(&coeficientes[i], &coeficientes[grauEquacao - i]);
    }

    // Calcula L1 para o Limite inferior das raizes positivas.
    teoremaLagrange(grauEquacao, coeficientes[0], coeficientes, limites, contadorLimites);
    contadorLimites++;

    for (i = 0; i <= grauEquacao; i++)
    {
        //	Trocamos o sinal dos coeficientes de indice impar para obter X^n . p(-1/x)
        if ((grauEquacao - i) % 2)
            coeficientes[i] *= -1;
    }

    // Calcula L3 para o limite superior das raizes negativas
    teoremaLagrange(grauEquacao, coeficientes[0], coeficientes, limites, contadorLimites);
    contadorLimites++;

    for (i = 0; i < (grauEquacao + 1) / 2; i++)
    {
        //	Invertemos a ordem dos coeficientes para obter p(-x)
        trocas(&coeficientes[i], &coeficientes[grauEquacao - i]);
    }

    // Calcula L2 para o limite inferior das raizes negativas
    teoremaLagrange(grauEquacao, coeficientes[0], coeficientes, limites, contadorLimites);

    printf("\nLimites das raizes positivas: ");
    printf("\n%lf <= x+ <= %lf", 1 / limites[1], limites[0]);

    printf("\nLimites das raizes negativas: ");
    printf("\n%lf <= x- <= %lf", -limites[3], -1 / limites[2]);

    // Chamada do metodo de Newton
    metodoNewton(limites, grauEquacao, coeficientes);

    // Desalocar memória
    free(coeficientes);

} // Acabou a função: equacaoAlgebrica

void teoremaLagrange(double n, double an, double *coeficientes, double *limites, int contadorLimites)
{
    /*
    No Teorema de Lagrange vamos pegar um polinomio e encontrar seus limites

    n = grau do polinomio
    an = coeficiente de indice n.
    */

    double k = 0, b = 0;
    /*
    k = maior indice dos coeficientes negativos do polinomio
    b = modulo do menor coeficiente negativo
    */
    int i;

    if (an < 0)
    {
        // Quando temos um an negativo, teriamos uma raiz 0
        // Sendo assim vamos mutiplicar o f(x) por -1
        for (i = 0; i <= n; i++)
            coeficientes[i] *= -1;
        an *= -1;
    }

    for (i = 0; i <= n; i++)
    {
        if (coeficientes[i] < 0 && k == 0)
        {
            k = n - i;
            if (coeficientes[i] < 0 && coeficientes[i] < b)
            {
                b = coeficientes[i];
            }
        }
    }

    // guarda |b|
    b = fabs(b);
    limites[contadorLimites] = 1 + pow(b / an, 1.0 / (n - k));

} // Acabou a função: teoremaLagrange

void metodoNewton(double *limites, int grauEquacao, double *coeficientes)
{
    /*
    Função de metodoNewton começa recebendo o resultado do f(x) e f'(x).
    Zeramos as funções para o x[0]
    para x[0] usamos o limite superior do teorema de lagrande
    Depois imprimimos a quantidade de interação e a raiz aproximada
    */

    double aux, *dfx, x = limites[0], fx[2];
    // x: aproximacao resultante (limite superior)
    int contaIteracoes, i, z;
    // fx é o polinomio e a derivada

    dfx = malloc(sizeof(double) * grauEquacao);
    // Se a derivada for nula
    if (dfx == NULL)
    {
        printf("\n\nFaltou memoria.\n");
        return;
    }

    for (i = 0; i < grauEquacao; i++)
    {
        dfx[i] =
            coeficientes[i] *
            (grauEquacao - i); //	Encontramos os coeficientes da f'(x) de f(x)
    }

    for (contaIteracoes = 0; contaIteracoes < 1000; contaIteracoes++)
    {
        fx[0] = 0; //	Zerando o valor de f'(x)
        fx[1] = 0; //	Zerando o valor de f'(x)
        for (z = 0; z <= grauEquacao; z++)
        {
            // Vamos começar o metodo de Newton com a formula x[n+1] = x[n]-f(x)/f'(x)

            fx[0] += pow(x, grauEquacao - z) * coeficientes[z]; // Calcula f(x)
            if (z != grauEquacao)
                fx[1] += pow(x, grauEquacao - z - 1) * dfx[z]; // Calcula f'(x)
        }
        // metodo principal
        aux = x - fx[0] / fx[1];

        if (fabs(aux - x) < EPSILON)
        {
            printf("\n\nIteracoes: %d\n", contaIteracoes);
            printf("\nx = %lf", x);
            free(dfx);
            return;
        }
        x = aux;
    }

    printf("\n\nIteracoes: %d\n", contaIteracoes);
    printf("\nx = %lf\n", x);
    free(dfx);

} // Acabou a função: metodoNewton

double **alocacaoDeMatriz(int linha, int coluna)
{
    // Alocação dinâmica da matriz usando o "malloc()"
    int i, j;
    double **matrizCRIADA;
    matrizCRIADA = malloc(sizeof(double *) * linha);
    if (matrizCRIADA == NULL)
        return NULL;
    for (i = 0; i < linha; i++)
    {
        matrizCRIADA[i] = malloc(sizeof(double) * coluna);
        if (matrizCRIADA[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(matrizCRIADA[j]);
            free(matrizCRIADA);
            return NULL;
        }
    }
    return matrizCRIADA;
} // Acabou a função: alocacaoDeMatriz

MatrizGS *Leitura_Abertura_Arquivo()
{
    // FUNÇÃO QUE ABRE UM ARQUIVO SEGUNDO O DIRETÓRIO DADO PELO USUÁRIO E LER ESSE ARQUIVO, PASSANDO PARA UMA MATRIZ DE TAMANHO ESPECIFICADO NO ARQUIVO
    char nomeArquivo[20];
    int i, j, tam;
    double **maatriz;

    FILE *arquivo;

    printf("Digite o nome do arquivo: ");
    scanf(" %s", nomeArquivo);
    arquivo = fopen(nomeArquivo, "r"); // ABRINDO O ARQUIVO DADO COM O "fopen" E LENDO ELE COM O PARÂMETRO "r" de READ

    if (arquivo == NULL)
    { // FUNÇÃO PARA CASOS ONDE O ARQUIVO RETORNA NULO
        printf("O arquivo nao existe.\n");
        return NULL;
    }
    fscanf(arquivo, " %d", &tam); // "fscanf()" TRABALHA COM A LEITURA DE ENTRADA FORMATADA (SEMELHANTE AO "scanf()"). NESTE CASO ESTÁ RECEBENDO O NÚMERO DE LINHAS QUE O SISTEMA LINEAR POSSUI

    maatriz = alocacaoDeMatriz(tam, tam + 1); // CHAMA A FUNÇÃO PARA CRIAR UMA MATRIZ QUE TENHA N LINHAS E N+1 COLUNAS

    for (i = 0; i < tam; i++)
    { // GUARDA DENTRO DA MATRIZ CRIADA OS VALORES PASSADOS DENTRO DO ARQUIVO SEGUINDO A ORDEM DAS LINHAS E COLUNAS
        for (j = 0; j < tam + 1; j++)
        {
            fscanf(arquivo, " %lf", &maatriz[i][j]);
        }
    }
    fclose(arquivo); // FUNÇÃO QUE FECHA O ARQUIVO

    MatrizGS *Matriz_SL = (MatrizGS *)malloc(sizeof(MatrizGS)); //"malloc" É A FUNÇÃO CENTRAL DA ALOCAÇÃO DINAMICA DE MEMORIA, DEVEMOS CHAMAR O "sizeof" E RECUPERAR A QUANTIDADE DE MEMÓRIA UTILIZADA NO ARMAZENAMENTO.

    if (Matriz_SL == NULL)
        return NULL;
    Matriz_SL->matrizRecebida = maatriz;
    Matriz_SL->tamMatriz = tam;

    return Matriz_SL;
}; // Acabou a função: Leitura_Abertura_Arquivo

int VerificacaoDasLinhasEColunas(double **m)
{
    // FUNÇÃO QUE VERIFICA SE A MATRIZ DE COEFICIENTES SATISFAZ O CRITÉRIO DAS LINHAS OU O CRITÉRIO DAS COLUNAS.
    int var = 3, i, j;
    double pivo, Soma_da_linha, Soma_da_Coluna;

    for (i = 0; i < var; i++)
    {
        Soma_da_linha = 0.0;
        Soma_da_Coluna = 0.0;
        pivo = fabs(m[i][i]); // O pivo é localizado na linha i coluna i de uma determinada matriz, a função "fabs()" retorna o valor absoluto de x.

        for (j = 0; j < var; j++)
        {
            if (i != j)
            {

                Soma_da_linha = Soma_da_linha + fabs(m[i][j]);
                Soma_da_Coluna = Soma_da_Coluna + fabs(m[j][i]);
            }

            // O critério das linhas e das colunas é atendido quando o pivô é maior ou igual a soma dos elementos da sua linha e coluna
            if (Soma_da_linha > pivo || Soma_da_Coluna > pivo)
                return -1;
        } // DEVOLVE O VALOR 1 PARA BEM CONDICIONADA E -1 PARA MAL CONDICIONADA
    }
    return 1;
}; // Acabou a função: VerificacaoDasLinhasEColunas

void sistemaLinear()
{
    MatrizGS *Matriz_SL = Leitura_Abertura_Arquivo();
    // CHAMADA DA FUNÇÃO PARA ABRIR E LER O ARQUIVO
    if (Matriz_SL == NULL)
    {
        printf("Erro na leitura do arquivo.\n");
        return;
    }
    // SE O ARQUIVO FOR NULO A FUNÇÃO RETORNARÁ UMA MENSAGEM DE ERRO

    double **m = Matriz_SL->matrizRecebida;

    // SE A FUNÇÃO DE VERIFICAÇÃO DEVOLVER -1 ELA NÃO SATISFAZ O CRITÉRIO DAS LINHAS E DAS COLUNAS

    if (VerificacaoDasLinhasEColunas(m) == -1)
    {
        printf("\nO sistema linear não satisfaz o critério das linhas nem o critério das colunas.\n");
        return;
    }

    double pivo, Elemento_Linha;
    int i, j, interacoes = 0;
    int var = Matriz_SL->tamMatriz; // RECEBENDO O VALOR DA PRIMEIRA LINHA DO ARQUIVO, REFERENTE AO NUMERO DE VARIÁVEIS E LINHAS.

    double valores_linha_pivo[var], valoresAnteriores[var];

    for (i = 0; i < var; i++)
    {
        valores_linha_pivo[i] = 0.0;
        valoresAnteriores[i] = 0.0;
    }
    // EXECUTANDO 1000 iterações
    int Dif_Minima = 0;
    while (interacoes < 1000 && Dif_Minima == 0)
    {
        for (i = 0; i < var; i++)
        {
            Elemento_Linha = 0.0;
            pivo = m[i][i]; // PIVO
            for (j = 0; j < var; j++)
            {
                if (i != j)
                {
                    // CALCULANDO O NOVO VALOR DOS ELEMENTOS DA LINHA
                    Elemento_Linha = Elemento_Linha - (valores_linha_pivo[j] * m[i][j]);
                }
            }
            // CALCULANDO OS VALORES DOS MULTIPLICADORES
            valores_linha_pivo[i] = (Elemento_Linha + m[i][var]) / pivo;
        }

        Dif_Minima = 1;

        for (i = 0; i < var; i++)
        {
            Dif_Minima = (fabs(valoresAnteriores[i] - valores_linha_pivo[i]) < 0.00000001) && (Dif_Minima == 1) ? 1 : 0;
            valoresAnteriores[i] = valores_linha_pivo[i];
        }
        interacoes++;
    }

    printf("\n\n============RESOLUCAO DO SL METODO DE GAUSS-SEIDEL=============");
    printf("\n\n-- Numero de iteracoes realizadas: %d\n", interacoes);
    printf("\n-- Solucao encontrada:\n");
    for (i = 0; i < var; i++)
    {
        printf("x%d: %f; ", i + 1, valores_linha_pivo[i]);
    }
    printf("\n\n===============================================================\n\n");
}; // Acabou a função: sistemaLinear
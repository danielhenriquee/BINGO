// Daniel Henrique da Silva, Lucas dos Santos Luckow, Samuel Alfonso Werner Stuhlert, Victor Menezes Ferreira.

#include <iostream>
#include <locale.h>
#include <time.h>
#include <unistd.h>

using namespace std;

#define TAM 5

void delay(unsigned long t) {
  sleep(t);
} // Para controlar tempo de delay entre cada número sorteado, t em segundos

void voltarMenu(int &menu) {
  menu = 0;
  cout << "\nDigite qualquer tecla para voltar ao menu\n";
  system("read 0 -p");
  system("clear");
} // Para voltar ao menu

void imprimeMenu() {
  cout << endl;
  cout << "      :::::::::       :::::::::::       ::::    :::       ::::::::       :::::::: \n"
          "     :+:    :+:          :+:           :+:+:   :+:      :+:    :+:     :+:    :+: \n"
          "    +:+    +:+          +:+           :+:+:+  +:+      +:+            +:+    +:+  \n"
          "   +#++:++#+           +#+           +#+ +:+ +#+      :#:            +#+    +:+   \n"
          "  +#+    +#+          +#+           +#+  +#+#+#      +#+   +#+#     +#+    +#+    \n"
          " #+#    #+#          #+#           #+#   #+#+#      #+#    #+#     #+#    #+#     \n"
          "#########       ###########       ###    ####       ########       ########       \n\n\n";
  
  cout << "       1.┏┳┏┓┏┓┏┓┳┓\n"
          "          ┃┃┃┃┓┣┫┣┫\n"
          "         ┗┛┗┛┗┛┛┗┛┗\n\n\n";
    
  cout << "       2.┏┓┏┓┳┓┳┓┏┓\n"
          "         ┗┓┃┃┣┫┣┫┣ \n"
          "         ┗┛┗┛┻┛┛┗┗┛\n\n\n";
    
  cout << "       3.┏┓┏┓┳┳┓\n"
          "         ┗┓┣┫┃┣┫\n"
          "         ┗┛┛┗┻┛┗\n\n\n";
} // Imprime a tela do menu

void sobre() {
  cout << "\nDesenvolvedores:    Daniel Henrique da Silva\n"
          "                    Lucas dos Santos Luckow\n"
          "                    Samuel Alfonso Werner Stuhlert\n"
          "                    Victor Menezes Ferreira\n\n"
          "Professor:          Prof. Rafael Ballotin Martins\n"
          "Matéria:            Algoritmos e Programação II\n"
          "Agosto/2023\n\n";
} // Exibe o "sobre"

void imprimir(int cartela[TAM][TAM], string jogadores[TAM], int p, int numeros[75]) {
  cout << "0" << p << " - " << jogadores[p - 1] << endl; // Printa o número da cartela e seu dono
  cout << "╔═══════════════╗\n"; // Printa essa borda antes do loop que printa a cartela
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
      
      if (j == 0) { // Printa a borda antes da primeira coluna
        cout << "║";
      }
      
      if (cartela[i][j] < 10 and j != 8) { // Se o valor for de um dígito, printa 0 antes e ' '
        if (numeros[cartela[i][j] - 1] != 0) { // Verifica se o número já foi sorteado
          cout << "\033[32m0" << cartela[i][j] << " \033[0m"; // Muda a cor para verde e depois para a padrão de volta
        } else {
          cout << "0" << cartela[i][j] << " ";
        }
        
      } else if (cartela[i][j] > 0 and j == 8) { // Se o valor for de um dígito na última coluna, printa 0 sem ' '
        if (numeros[cartela[i][j] - 1] != 0) {
          cout << "\033[32m0" << cartela[i][j] << "\033[0m";
        } else {
          cout << "0" << cartela[i][j];
        }
        
      } else if (cartela[i][j] != 0 and j < 8) { // Se o valor for de dois dígitos, printa o valor com ' '
        if (numeros[cartela[i][j] - 1] != 0) {
          cout << "\033[32m" << cartela[i][j] << " \033[0m";
        } else {
          cout << cartela[i][j] << " ";
        }
        
      } else { // Printa o valor sem ' ' (última coluna)
          if (numeros[cartela[i][j] - 1] != 0) {
            cout << "\033[32m" << cartela[i][j] << "\033[0m";
        } else {
          cout << cartela[i][j];
        }
      }
    }
    cout << "║ " << endl; // Após cada fim da linha, printa ║ como borda e pula a linha
  }
  cout << "╚═══════════════╝\n\n"; // Após o loop que printa a cartela, printa  essa linha no final
} // Imprime as cartelas

void gerar(int cartela[TAM][TAM]) {
  int nmr = 0;
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
      cartela[i][j] = rand() % 15 + 1 + nmr; // 15+1 faz com que gere valores de 1 a 15, nmr começa em 0
    }
    nmr += 15; // Após o loop do 'j', antes de i++, soma 15 ao nmr, pois os valores min e max da prox linha são 15 a mais da anterior
  }
} // Gera cartela aleatória

void verificar(int cartela[TAM][TAM]) {
  int nmr = 0;
  for (int i = 0; i < TAM; i++) {
    for (int verifica = 0; verifica < 2; verifica++) { // Para reverificar depois de alterar o número, caso altere para outro número repetido
      for (int k = 0; k < TAM; k++) {
        for (int j = 0; j < TAM; j++) {
          if (k != j) {
            if (cartela[i][k] == cartela[i][j]) { // Passa por todas as colunas para ver se o valor se repete
              cartela[i][k] = rand() % 15 + 1 + nmr; // Caso haja um número repetido, substitui-o
            }
          }
        }
      }
    }
    nmr += 15;
  }
} // Verifica se há números repetidos na cartela

void bubblesort(int cartela[TAM][TAM]) {
  int i, j, cond, temp, linha;
  for (linha = 0; linha < TAM; linha++) { // Adicionado um 'for' para que passe por todas as linhas da matriz, ordenando-a por completo
    cond = 1;
    for (i = TAM - 1; (i >= 1) && (cond == 1); i--) {
      cond = 0;
      for (j = 0; j < i; j++) {
        if (cartela[linha][j + 1] < cartela[linha][j]) {
          temp = cartela[linha][j];
          cartela[linha][j] = cartela[linha][j + 1];
          cartela[linha][j + 1] = temp;
          cond = 1;
        }
      }
    }
  }
} // Bubblesort com ajuste para ordenar todas as linhas da matriz

void nomes(string jogadores[TAM]) {
  cin.ignore(); // limpa o buffer de entrada
  for (int i = 0; i < TAM; i++) {
    cout << endl << "Digite o nome do dono da cartela 0" << i + 1 << ": ";
    getline(cin, jogadores[i]);
  }
} // Recebe o nome dos jogadores

void sorteio(int numeros[75], int &nmr) {
  int i = 0; // Define i=0 para que possa inicar o loop
  while (i != 1) {
    nmr = rand() % 75 + 1;       // Sorteia um número de 1 a 75
    if (numeros[nmr - 1] == 0) { // Verifica se o número já foi sorteado antes
      numeros[nmr - 1] = nmr; // Se não foi sorteado antes, adiciona o número ao vetor
      i = 1;   // i=1 para que o loop não se repita
    } else {
      i = 0; // Se já foi sorteado, i=0 faz com que o loop continue
    }
  }
} // Sorteia um número

void sorteados(int numeros[75], int nmr) {
  system("clear");
  cout << endl << "Números sorteados: " << endl;
  for (int i = 0; i < 75; i++) {
    if (numeros[i] != 0) {
      cout << "\033[32m" << numeros[i] << "\033[0m" << "\t";
    }
  }
  cout << endl << "Último número sorteado: " << "\033[31m" << nmr << "\033[0m" << endl << endl;
} // Exibe os números sorteados

int ganhou(int cartela1[TAM][TAM], int cartela2[TAM][TAM], int cartela3[TAM][TAM], int cartela4[TAM][TAM], int cartela5[TAM][TAM], int numeros[75]) {
  int ganhador1 = 0, ganhador2 = 0, ganhador3 = 0, ganhador4 = 0, ganhador5 = 0; // zera os contadores
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
      if (cartela1[i][j] == numeros[cartela1[i][j] - 1]) { // verifica se o número da cartela já foi sorteado
        ganhador1++; // se sim, adiciona 1 ao contador
        if (ganhador1 == 25)
          return (ganhador1);
      }
      if (cartela2[i][j] == numeros[cartela2[i][j] - 1]) {
        ganhador2++;
        if (ganhador2 == 25)
          return (ganhador2);
      }
      if (cartela3[i][j] == numeros[cartela3[i][j] - 1]) {
        ganhador3++;
        if (ganhador3 == 25)
          return (ganhador3);
      }
      if (cartela4[i][j] == numeros[cartela4[i][j] - 1]) {
        ganhador4++;
        if (ganhador4 == 25)
          return (ganhador4);
      }
      if (cartela5[i][j] == numeros[cartela5[i][j] - 1]) {
        ganhador5++;
        if (ganhador5 == 25)
          return (ganhador5);
      }
    }
  }
  return 0;
} // Verifica se algum jogador ganhou

void telaGanhou(int cartela1[TAM][TAM], int cartela2[TAM][TAM], int cartela3[TAM][TAM], int cartela4[TAM][TAM], int cartela5[TAM][TAM], int numeros[75], string jogadores[TAM]) {
  cout<< "██████  ██ ███    ██  ██████   ██████  ██ \n"
         "██   ██ ██ ████   ██ ██       ██    ██ ██ \n"
         "██████  ██ ██ ██  ██ ██   ███ ██    ██ ██ \n"
         "██   ██ ██ ██  ██ ██ ██    ██ ██    ██    \n"
         "██████  ██ ██   ████  ██████   ██████  ██ \n\n\n";
                                                   
  int ganhador1 = 0, ganhador2 = 0, ganhador3 = 0, ganhador4 = 0, ganhador5 = 0;
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
      if (cartela1[i][j] == numeros[cartela1[i][j] - 1]) {
        ganhador1++;
        if (ganhador1 == 25)
          cout << "Parabéns " << jogadores[0] << " da cartela 01, você ganhou!\n";
      }
      if (cartela2[i][j] == numeros[cartela2[i][j] - 1]) {
        ganhador2++;
        if (ganhador2 == 25)
          cout << "Parabéns " << jogadores[1] << " da cartela 02, você ganhou!\n";
      }
      if (cartela3[i][j] == numeros[cartela3[i][j] - 1]) {
        ganhador3++;
        if (ganhador3 == 25)
          cout << "Parabéns " << jogadores[2] << " da cartela 03, você ganhou!\n";
      }
      if (cartela4[i][j] == numeros[cartela4[i][j] - 1]) {
        ganhador4++;
        if (ganhador4 == 25)
          cout << "Parabéns " << jogadores[3] << " da cartela 04, você ganhou!\n";
      }
      if (cartela5[i][j] == numeros[cartela5[i][j] - 1]) {
        ganhador5++;
        if (ganhador5 == 25)
          cout << "Parabéns " << jogadores[4] << " da cartela 05, você ganhou!\n";
      }
    }
  }
  cout << endl << endl;
} // Imprime na tela o(s) jogador(es) vencedor(es)

int main() {
  setlocale(LC_ALL, "Portuguese");
  srand(time(NULL));
  int menu;

  do {
    string(jogadores[TAM]);
    int numeros[75] = {0}, nmr;
    
    imprimeMenu();
    cin >> menu;

    switch (menu) {
    case 1: // Jogar

      system("clear");

      int cartela01[TAM][TAM];
      int cartela02[TAM][TAM];
      int cartela03[TAM][TAM];
      int cartela04[TAM][TAM];
      int cartela05[TAM][TAM];

      gerar(cartela01);
      verificar(cartela01);
      bubblesort(cartela01);

      gerar(cartela02);
      verificar(cartela02);
      bubblesort(cartela02);

      gerar(cartela03);
      verificar(cartela03);
      bubblesort(cartela03);

      gerar(cartela04);
      verificar(cartela04);
      bubblesort(cartela04);

      gerar(cartela05);
      verificar(cartela05);
      bubblesort(cartela05);

      nomes(jogadores);

      do {
        sorteio(numeros, nmr);
        sorteados(numeros, nmr);
        imprimir(cartela01, jogadores, 1, numeros);
        imprimir(cartela02, jogadores, 2, numeros);
        imprimir(cartela03, jogadores, 3, numeros);
        imprimir(cartela04, jogadores, 4, numeros);
        imprimir(cartela05, jogadores, 5, numeros);
        delay (1);
      } while (ganhou(cartela01, cartela02, cartela03, cartela04, cartela05, numeros) != 25);
      delay (3);
      telaGanhou(cartela01, cartela02, cartela03, cartela04, cartela05, numeros, jogadores);
      
      voltarMenu(menu);
      break;

    case 2: // Sobre
      system("clear");
      sobre();
      voltarMenu(menu);
      break;

    case 3: // Sair
      break;
    } // Fecha o switch

    system("clear");   // Limpa tudo antes de voltar ao menu
  } while (menu != 3); // Fecha o loop do jogo
  return 0;
}

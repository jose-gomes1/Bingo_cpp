#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

// Definição de cores ANSI
string BLUE = "\033[34m";
string RED = "\033[1;31m";
string GREEN = "\033[32m";
string RESET = "\033[0m";
string BOLD = "\u001b[1m";

// Função para gerar números únicos aleatórios
vector<int> generateUniqueNumbers(int min, int max, int count) {
    vector<int> numbers;
    for (int i = min; i <= max; ++i) {
        numbers.push_back(i);
    }
    random_shuffle(numbers.begin(), numbers.end());
    numbers.resize(count);
    sort(numbers.begin(), numbers.end());
    return numbers;
}

// Função para exibir o cartão de bingo
void displayBingoCard(const vector<int>& card) {
    for (int i = 0; i < 25; ++i) {
        if (i % 5 == 0 && i != 0) {
            cout << endl;
        }
        if (i == 12) {
            cout << " -   ";
        } else {
            cout << (card[i] == 0 ? BLUE + " 0   " + RESET : BLUE + to_string(card[i]) + "   " + RESET);
        }
    }
    cout << endl << endl;
}

// Função para gerar e salvar o arquivo do cartão de bingo
void generateBingoCardFile(const vector<int>& card, int cardNumber) {
    ofstream outFile("cartao" + to_string(cardNumber) + ".txt");
    if (outFile.is_open()) {
        for (int i = 0; i < 25; ++i) {
            if (i == 12) {
                outFile << "- ";
            } else {
                outFile << (card[i] == 0 ? "0" : to_string(card[i])) << " ";
            }
            if ((i + 1) % 5 == 0) {
                outFile << endl;
            }
        }
        outFile.close();
        cout << GREEN << "Cartão " << cardNumber << " salvo com sucesso." << RESET << endl;
    } else {
        cout << RED << "Erro ao abrir o arquivo para escrita." << RESET << endl;
    }
}

// Função para exibir a tabela com destaque em vermelho nos números sorteados
void displayNumberTable(const vector<int>& drawnNumbers, int numNumbers) {
    cout << BLUE << BOLD << "Tabela de Números Sorteados:" << RESET << endl;
    for (int i = 1; i <= numNumbers; ++i) {
        if (find(drawnNumbers.begin(), drawnNumbers.end(), i) != drawnNumbers.end()) {
            cout << RED << i << " " << RESET; // Destacar em vermelho
        } else {
            cout << GREEN << i << " " << RESET;
        }
        if (i % 10 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

// Função para exibir o número sorteado em ASCII
void displayAsciiNumber(int drawnNumber, int numRemaining) {
    cout << BLUE << BOLD << "Números Restantes: " << RESET << numRemaining << endl;
    cout << "_____________________" << endl;
    cout << "|                   |" << endl;
    cout << "|   " << setw(2) << drawnNumber << "   |" << endl;
    cout << "|___________________|" << RESET << endl;
}  
int main() {
    srand(time(0));

    int numNumbers, numCards;
    cout << BLUE << "Escolhe o número de sorteio (75, 90, ou 100): ";
    cin >> numNumbers;

    cout << BLUE << "Escolhe o número de cartões a serem gerados: ";
    cin >> numCards;

    // Geração de cartões de bingo
    vector<vector<int>> cards;
    for (int i = 1; i <= numCards; ++i) {
        vector<int> numbers = generateUniqueNumbers(1, numNumbers, 25);

        // Substitui o terceiro número da terceira coluna por "-"
        numbers[12] = 0;

        cards.push_back(numbers);
        generateBingoCardFile(numbers, i);
    }

    // Exibição dos cartões
    cout << BLUE << "Cartões de bingo gerados:" << RESET << endl;
    for (int i = 0; i < numCards; ++i) {
        cout << GREEN << "Cartão " << i + 1 << ":" << RESET << endl;
        displayBingoCard(cards[i]);
    }

    // Opção de sair
    char exitOption;
    cout << "Deseja sair? (s para sim, qualquer outra tecla para continuar): ";
    cin >> exitOption;
    if (exitOption == 's' || exitOption == 'S') {
        return 0;
    }

    // Sorteio
    vector<int> drawnNumbers;
    char drawType;
    cout << BLUE << "\nEscolhe o tipo de sorteio (a para automático, m para manual): ";
    cin >> drawType;

    if (drawType == 'a' || drawType == 'A') {
        cout << BLUE << BOLD << "\nSorteio Automático Iniciado..." << endl;

        for (int i = 1; i <= numNumbers; ++i) {
            int drawnNumber = rand() % numNumbers + 1;

            // Exibir números atual e anterior
            if (i > 1) {
                cout << "Número Anterior: " << drawnNumbers.back() << ", Número Atual: " << drawnNumber << endl;
            } else {
                cout << "Número Atual: " << drawnNumber << endl;
            }

            drawnNumbers.push_back(drawnNumber);

            // Aguarda por 1 segundo entre os sorteios
            this_thread::sleep_for(chrono::seconds(1));
            system("clear || cls");

            // Exibição da tabela com todos os números
            displayNumberTable(drawnNumbers, numNumbers);

            // Exibição do número sorteado em ASCII
            displayAsciiNumber(drawnNumber, numNumbers - i);
        }
    } else if (drawType == 'm' || drawType == 'M') {
        for (int i = 1; i <= numNumbers; ++i) {
            cout << "Pressiona qualquer tecla para sortear o próximo número...";
            cin.ignore();  // Ignora qualquer caractere pendente no buffer
            cin.get();     // Aguarda o usuário pressionar uma tecla
            int drawnNumber = rand() % numNumbers + 1;

            // Exibir números atual e anterior
            if (i > 1) {
                cout << "Número Anterior: " << drawnNumbers.back() << ", Número Atual: " << drawnNumber << endl;
            } else {
                cout << "Número Atual: " << drawnNumber << endl;
            }

            drawnNumbers.push_back(drawnNumber);
            system("clear || cls");

            // Exibição da tabela com todos os números
            displayNumberTable(drawnNumbers, numNumbers);

            // Exibição do número sorteado em ASCII
            displayAsciiNumber(drawnNumber, numNumbers - i);
        }
    } else {
        cout << RED << "Opção inválida. Escolhe 'a' para automático ou 'm' para manual." << RESET << endl;
        return 1;
    }

    return 0;
}

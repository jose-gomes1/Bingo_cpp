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
    cout << "|" << setw(10) << drawnNumber << setw(10) << " |" << endl;
    cout << "|___________________|" << RESET << endl;
}

// Função para gerar cartões de bingo
vector<vector<int>> generateBingoCards(int numCards, int numNumbers) {
    if (numNumbers != 75 && numNumbers != 90 && numNumbers != 100) {
        cout << RED << "Número de bingo inválido. Escolhe entre 75, 90 ou 100." << RESET << endl;
        return vector<vector<int>>();  // Retorna um vetor vazio se o número for inválido
    }

    vector<vector<int>> cards;
    for (int i = 1; i <= numCards; ++i) {
        vector<int> numbers = generateUniqueNumbers(1, numNumbers, 25);

        // Substitui o terceiro número da terceira coluna por "-"
        numbers[12] = 0;

        cards.push_back(numbers);
        generateBingoCardFile(numbers, i);
    }
    return cards;
}

int main() {
    srand(time(0));

    int numNumbers, numCards;
    char menuOption;

    do {
        cout << "\n===== Menu Inicial =====" << endl;
        cout << "1. Sorteio Automático" << endl;
        cout << "2. Sorteio Manual" << endl;
        cout << "3. Gerar Cartões" << endl;
        cout << "4. Sair" << endl;
        cout << "Escolhe a opção desejada (1/2/3/4): ";
        cin >> menuOption;

        switch (menuOption) {
            case '1': {
                cout << BLUE << "Escolhe o número de sorteio (75, 90, ou 100): ";
                cin >> numNumbers;

                // Sorteio Automático
                vector<int> drawnNumbers;
                cout << BLUE << BOLD << "\nSorteio Automático Iniciado..." << endl;

                for (int i = 1; i <= numNumbers; ++i) {
                    int drawnNumber = rand() % numNumbers + 1;

                    // Exibir números atual e anterior
                    if (i > 1) {
                        cout << "Número Atual: " << drawnNumbers.back() << endl;
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
                break;
            }
            case '2': {
                cout << BLUE << "Escolhe o número de sorteio (75, 90, ou 100): ";
                cin >> numNumbers;

                // Sorteio Manual
                vector<int> drawnNumbers;
                for (int i = 1; i <= numNumbers; ++i) {
                    cout << "Pressiona qualquer tecla para sortear o próximo número...";
                    cin.ignore();  // Ignora qualquer caractere pendente no buffer
                    cin.get();     // Aguarda o usuário pressionar uma tecla
                    int drawnNumber = rand() % numNumbers + 1;

                    // Exibir números atual e anterior
                    if (i > 1) {
                        cout << "Número Atual: " << drawnNumbers.back() << endl;
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
                break;
            }
            case '3': {
                int bingoSize;
                cout << BLUE << "Escolhe o tamanho do bingo (75, 90 ou 100): ";
                cin >> numNumbers;  // Atualizado para numNumbers
                cout << BLUE << "Escolhe o número de cartões a serem gerados: ";
                cin >> numCards;

                // Geração de cartões de bingo
                vector<vector<int>> cards = generateBingoCards(numCards, numNumbers);

                // Exibição dos cartões
                if (!cards.empty()) {
                    cout << BLUE << "Cartões de bingo gerados:" << RESET << endl;
                    for (int i = 0; i < numCards; ++i) {
                        cout << GREEN << "Cartão " << i + 1 << ":" << RESET << endl;
                        displayBingoCard(cards[i]);
                    }
                }
                break;
            }
            case '4':
                cout << "A sair do programa. Até logo!" << endl;
                break;
            default:
                cout << RED << "Opção inválida. Escolhe 1, 2, 3 ou 4." << RESET << endl;
        }
    } while (menuOption != '4');

    return 0;
}

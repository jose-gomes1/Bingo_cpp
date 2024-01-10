#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <thread>

using namespace std;

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
            cout << (card[i] == 0 ? " 0   " : to_string(card[i]) + "   ");
        }
    }
    cout << endl << endl;
}

// Função para gerar e salvar o arquivo do cartão de bingo
void generateBingoCardFile(const vector<int>& card, int cardNumber) {
    ofstream outFile("cartão" + to_string(cardNumber) + ".txt");
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
        cout << "Cartão " << cardNumber << " salvo com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo para escrita." << endl;
    }
}

int main() {
    srand(time(0));

    int numNumbers, numCards;
    cout << "Escolhe o número de sorteio (75, 90, ou 100): ";
    cin >> numNumbers;

    cout << "Escolhe o número de cartões a serem gerados: ";
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
    cout << "Cartões de bingo gerados: " << endl;
    for (int i = 0; i < numCards; ++i) {
        cout << "Cartão " << i + 1 << ":" << endl;
        displayBingoCard(cards[i]);
    }

    // Sorteio
    vector<int> drawnNumbers;
    char drawType;
    cout << "\nEscolhe o tipo de sorteio (a para automático, m para manual): ";
    cin >> drawType;

    if (drawType == 'a' || drawType == 'A') {
        cout << "\nSorteio Automático Iniciado..." << endl;

        for (int i = 1; i <= numNumbers; ++i) {
            int drawnNumber = rand() % numNumbers + 1;
            drawnNumbers.push_back(drawnNumber);
        }

        // Exibição do painel com todos os números sorteados
        cout << "Painel de Números Sorteados:" << endl;
        for (int i = 0; i < numNumbers; ++i) {
            cout << drawnNumbers[i] << " ";
        }
        cout << endl;
    } else if (drawType == 'm' || drawType == 'M') {
        for (int i = 1; i <= numNumbers; ++i) {
            cout << "Pressiona qualquer tecla para sortear o próximo número...";
            cin.get();
            int drawnNumber = rand() % numNumbers + 1;
            drawnNumbers.push_back(drawnNumber);
        }
    } else {
        cout << "Opção inválida. Escolhe 'a' para automático ou 'm' para manual." << endl;
        return 1;
    }

    return 0;
}

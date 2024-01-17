#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <iomanip>

using namespace std;

const int numLinhasCartao = 5;
const int numColunasCartao = 5;
const int numColunasPainel = 5;
const int intervaloEntreBolas = 500000;
const int msgPause = 2000000;

int sorteados = 0;
int numeroSorteado = 0;
int anterior = 0;

int numeroDeBolas, tipoSorteio, numeroDeCartoes;

string BLUE = "\033[34m";
string RED = "\033[1;31m";
string GREEN = "\033[32m";
string RESET = "\033[0m";
string BOLD = "\u001b[1m";

typedef struct {
    int numero;
    bool sorteado;
} bingoBall;

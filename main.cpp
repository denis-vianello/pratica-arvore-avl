#include <iostream>
using namespace std;

class No {
   public:
  int valor;
  No *esquerda;
  No *direita;
  int altura;
};

int max(int a, int b);

int altura(No *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}
 
No *novoNo(int valor) {
  No *no = new No();
  no->valor = valor;
  no->esquerda = NULL;
  no->direita = NULL;
  no->altura = 1;
  return (no);
}

// Rotaciona para esquerda
No *rotacionaEsquerda(No *x) {
  No *y = x->direita;
  No *T2 = y->esquerda;
  y->esquerda = x;
  x->direita = T2;
  x->altura = max(altura(x->esquerda),
          altura(x->direita)) +
        1;
  y->altura = max(altura(y->esquerda),
          altura(y->direita)) +
        1;
  return y;
}

// Rotaciona para direita
No *rotacionaDireita(No *y) {
  No *x = y->esquerda;
  No *T2 = x->direita;
  x->direita = y;
  y->esquerda = T2;
  y->altura = max(altura(y->esquerda),
          altura(y->direita)) +
        1;
  x->altura = max(altura(x->esquerda),
          altura(x->direita)) +
        1;
  return x;
}

// criterio de balanceamento de cada no
int criterioBalanceamento(No *N) {
  if (N == NULL)
    return 0;
  return altura(N->esquerda) -
       altura(N->direita);
}

No *insereNo(No *no, int valor) {
  // procura aonde inserir o no
  if (no == NULL)
    return (novoNo(valor));
  if (valor < no->valor)
    no->esquerda = insereNo(no->esquerda, valor);
  else if (valor > no->valor)
    no->direita = insereNo(no->direita, valor);
  else
    return no;

  // atualiza o criterio de balanceamento de cada no a balanceia a arvore
  no->altura = 1 + max(altura(no->esquerda),
               altura(no->direita));
  int criterio = criterioBalanceamento(no);
  if (criterio > 1) {
    if (valor < no->esquerda->valor) {
      return rotacionaDireita(no);
    } else if (valor > no->esquerda->valor) {
      no->esquerda = rotacionaEsquerda(no->esquerda);
      return rotacionaDireita(no);
    }
  }
  if (criterio < -1) {
    if (valor > no->direita->valor) {
      return rotacionaEsquerda(no);
    } else if (valor < no->direita->valor) {
      no->direita = rotacionaDireita(no->direita);
      return rotacionaEsquerda(no);
    }
  }
  return no;
}

No *menorValorNo(No *no) {
  No *current = no;
  while (current->esquerda != NULL)
    current = current->esquerda;
  return current;
}

No *deletarNo(No *raiz, int valor) {
  if (raiz == NULL)
    return raiz;
  if (valor < raiz->valor)
    raiz->esquerda = deletarNo(raiz->esquerda, valor);
  else if (valor > raiz->valor)
    raiz->direita = deletarNo(raiz->direita, valor);
  else {
    if ((raiz->esquerda == NULL) ||
      (raiz->direita == NULL)) {
      No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
      if (temp == NULL) {
        temp = raiz;
        raiz = NULL;
      } else
        *raiz = *temp;
      free(temp);
    } else {
      No *temp = menorValorNo(raiz->direita);
      raiz->valor = temp->valor;
      raiz->direita = deletarNo(raiz->direita,
                   temp->valor);
    }
  }

  if (raiz == NULL)
    return raiz;

  raiz->altura = 1 + max(altura(raiz->esquerda),
               altura(raiz->direita));
  int criterio = criterioBalanceamento(raiz);
  if (criterio > 1) {
    if (criterioBalanceamento(raiz->esquerda) >= 0) {
      return rotacionaDireita(raiz);
    } else {
      raiz->esquerda = rotacionaEsquerda(raiz->esquerda);
      return rotacionaDireita(raiz);
    }
  }
  if (criterio < -1) {
    if (criterioBalanceamento(raiz->direita) <= 0) {
      return rotacionaEsquerda(raiz);
    } else {
      raiz->direita = rotacionaDireita(raiz->direita);
      return rotacionaEsquerda(raiz);
    }
  }
  return raiz;
}

void imprimeArvore(No *raiz, string recuo, bool last) {
  if (raiz != nullptr) {
    cout << recuo;
    if (last) {
      cout << "R----";
      recuo += "   ";
    } else {
      cout << "L----";
      recuo += "|  ";
    }
    cout << raiz->valor << endl;
    imprimeArvore(raiz->esquerda, recuo, false);
    imprimeArvore(raiz->direita, recuo, true);
  }
}

int main() {
  No *raiz = NULL;
  raiz = insereNo(raiz, 70);
  raiz = insereNo(raiz, 45);
  raiz = insereNo(raiz, 13);
  raiz = insereNo(raiz, 22);
  raiz = insereNo(raiz, 7);
  raiz = insereNo(raiz, 6);
  raiz = insereNo(raiz, 15);
  raiz = insereNo(raiz, 33);
  raiz = insereNo(raiz, 66);
  raiz = insereNo(raiz, 27);
  imprimeArvore(raiz, "", true);
  raiz = deletarNo(raiz, 22);
  cout << "apos uma remoção " << endl;
  imprimeArvore(raiz, "", true);
  raiz = insereNo(raiz, 18);
  cout << "apos uma inserção " << endl;
  imprimeArvore(raiz, "", true);

}

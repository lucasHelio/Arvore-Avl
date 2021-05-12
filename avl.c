#include <stdio.h>
#include <stdlib.h>


typedef struct Avl {
    struct Avl *filhoEsq;
    struct Avl *filhoDir;
    int chave;
    int altura;
} Avl;

int altura(Avl *elem)   //retorna a altura do nó
{
    int altFEsq, altFDir;
    if(elem == NULL)
        return 0;
    
    altFEsq = altura(elem->filhoEsq);
    altFDir = altura(elem->filhoDir);


    //return (altFEsq > altFDir)? altFEsq++ : altFDir++;
    if(altFEsq > altFDir){
        altFEsq++;
        return altFEsq;
    }
    else{
        altFDir++;
        return altFDir;
    }
}


int vazia(Avl *elem) //checa se o no esta vazio
{
    return (elem == NULL);
}

void printlista(Avl *elem) //imprime a lista em pre-ordem
{
    if(!vazia(elem))
    {
        printf("%d\n", elem->chave);
        printlista(elem->filhoEsq);
        printlista(elem->filhoDir);
    }
}

Avl* novoNo() //cria um novo no com o valor de null
{
    Avl *no;
    no = (Avl*) malloc(sizeof(struct Avl));

    if(no == NULL)
    {
        printf("Erro de alocação de memória em nó\n");
        return NULL;
    }
    else 
        return no;
}

void checarAltura(Avl *elem)
{
    if(!vazia(elem))
    {
        elem->altura = altura(elem->filhoEsq) - altura(elem->filhoDir);
        checarAltura(elem->filhoEsq);
        checarAltura(elem->filhoDir);
        //return;
    }
}

int checarBalanco(Avl *elem)
{
    if(elem->altura == 2)
    {
        if(elem->filhoEsq->altura < 0) return 3; // rotaçao dupla a direita
        else return 1; //rotacao simples para direita    
    }
    
    else
    {
        if(elem->altura == -2) 
        {
            if(elem->filhoDir->altura >0)return 4 ; //rotaçao dupla para esquerda
            else return 2; //rotacao simples para esquerda
        }
        
    }
    return 0;
}

Avl* RotacaoEsquerda(Avl *pai)
{
    Avl *filho;

    filho = pai->filhoDir;
    pai->filhoDir = filho->filhoEsq;
    filho->filhoEsq = pai;
    filho->altura = altura(filho->filhoEsq) - altura(filho->filhoDir);
    pai->altura = altura(pai->filhoEsq) - altura(pai->filhoDir);
    return filho;
}

Avl* RotacaoDireita(Avl *pai)
{
    Avl *filho;

    filho = pai->filhoEsq;
    pai->filhoEsq = filho->filhoDir;
    filho->filhoDir = pai;
    filho->altura = altura(filho->filhoEsq) - altura(filho->filhoDir);
    pai->altura = altura(pai->filhoEsq) - altura(pai->filhoDir);
    return filho;
}

Avl* RotacaoDuplaEsquerda(Avl *pai)
{
    pai->filhoDir = RotacaoDireita(pai->filhoDir);
    pai = RotacaoEsquerda(pai);
    return(pai);
}

Avl* RotacaoDuplaDireita(Avl *pai)
{
    pai->filhoEsq = RotacaoEsquerda(pai->filhoEsq);
    pai = RotacaoDireita(pai);
    return(pai);
}


void inserir(Avl **elem, int valor) //insere na lista e rotaciona se necessario
{
    int resposta = 0;
    if(vazia(*elem))
    {
        *elem = novoNo();
        (*elem)->chave=valor;
        (*elem)->altura=0;
        (*elem)->filhoEsq = (*elem)->filhoDir = NULL;
    }

    else
    {
        if (valor < (*elem)->chave)
        {
            inserir(&(*elem)->filhoEsq, valor);
        }
        else 
        {
            if (valor > (*elem)->chave)
            {
                inserir(&(*elem)->filhoDir, valor);
            }
        }
    }
    checarAltura(*elem);
    resposta = checarBalanco(*elem);

    if(resposta == 1)
    {
        (*elem) = RotacaoDireita(*elem);
        return;
    }
    else if(resposta == 2)
    {
        (*elem) = RotacaoEsquerda(*elem);
        return;
    }
    else if(resposta == 3)
    {
        (*elem) = RotacaoDuplaDireita(*elem); 
        return;
    }

    else if(resposta == 4)
    {
        (*elem) = RotacaoDuplaEsquerda(*elem);
        return;
    }
    else return;
}



int main()
{
    Avl *raiz = NULL;
    int valor;

    //vamos ler as entradas e inserir na lista
    while(!feof(stdin)){
        if (scanf("%d", &valor) == 1) 
        inserir(&raiz, valor);
    }
    
    printlista(raiz);

    return 0;
}

#include <iostream>
#include <exception>
using namespace std;


/*ENUNCIADO:
Implemente uma arvore de busca binaria na qual cada elemento representa um produto que possui
 dois campos, um inteiro para o c�digo (chave) e um float para o pre�o. Para gerenciar a estrutura a 
  fun��o main apresentar� o seguinte menu: 0 para sair; 1 para inserir um produto; 2 para contar a quantidade de produtos;
   3 para fazer uma busca binaria pela chave prim�ria.  Se o usu�rio escolher inserir um produto o algoritmo deve solicitar 
   a chave e o pre�o e logo fazer a inser��o de forma ordenada pelo c�digo (chave).  C�digos repetidos n�o devem ser permitidos.
    O programa s� deve finalizar quando o usu�rio escolher a op��o 0, ou seja, o menu deve estar dentro de um ciclo de repeti��es.



como o enunciado s� pediu 3 escolhas, somente implementei as pedidas
Logo, n�o h� um algoritmo para remo��o de um elemento ou para imprimir todos os elementos
se poss�vel, usar a vers�o do c++11 pois estou usando o conceito de nullptr.
Se estiver usando o devc++, v� em ferramentas, op��es do compilador e compilador,
cole "-std=c++11" na janela branca e d� ok.

se estiver usando o navegador, preferencialmente no onlinegdb. apenas v� na op��o language e clique em c++11 ou c++14

ah, e eu n�o usei a biblioteca fstream para guardar os dados em algum arquivo bin�rio ou txt. os registros s� estar�o v�lidos
enquanto o programa estiver funcionando. Ap�s o encerramento do programa, todos os dados ser�o perdidos

at� mais!
*/
struct registro{
	int chave;
	float preco;
	registro* esq;
	registro* dir;
};


registro* inicializar(){ //inicializamos a raiz
	return NULL;
}

registro* criar_novo_registro(int ch,float preco){  //criamos um elemento v�lido para depois fazermos este elemento se anexar � raiz
	registro* novo=new registro;
	novo->esq=NULL;
	novo->dir=NULL;
	novo->chave=ch;
	novo->preco=preco;
	return novo;
}

registro* busca_recursiva(registro* raiz, int ch, bool* insert_func){ //utilizo este ponteiro pra uma variavel booleana pois precisaremos disso
if(raiz==NULL){                                                      //para checar se h� chaves duplicadas
	return NULL;
}
if(raiz->chave==ch){

 cout<<"\nelemento encontrado!\nchave: "<<raiz->chave<<"\npreco: "<<raiz->preco<<"\n\n";
 *insert_func=true;
 return raiz;
}
if(raiz->chave<ch)
	raiz->esq=busca_recursiva(raiz->dir,ch,insert_func);
	else
	raiz->dir=busca_recursiva(raiz->esq, ch,insert_func);
	
}

int tamanho_da_arvore(registro* r){   //este algoritmo � um algoritmo diferente mas utiliza a mesma ideia de funcao recursiva
    if (r==NULL)                    //por alguma raz�o em uma situa��o muito espec�fica, o tamanho n�o sai como o esperado. E eu n�o consegui resolver isto
        return 0;
   else{
       int rdir = tamanho_da_arvore(r->dir);
       int resq = tamanho_da_arvore(r->esq);
       if (resq > rdir)
           return(resq+1);
       else
        return(rdir+1);
       
   }
}

registro* adicionar_registro_na_arvore(registro* r, registro* reg){
if(r==NULL)
 return reg;
int x=reg->chave;
bool cond_busc=false;
busca_recursiva(r,x,&cond_busc);
if(cond_busc==true){
	cout<<"\n--CHAVE ENCONTRADA NA LISTA--\nfaca um novo request para inserir um produto com uma chave diferente.\n\n";
	return r;
}

if(reg->chave<r->chave)
 r->esq=adicionar_registro_na_arvore(r->esq, reg) ;
else
 r->dir=adicionar_registro_na_arvore(r->dir,reg);
return r;
}

main(){
	registro* raiz=inicializar();
	registro* elemento=nullptr; //colocamos este elemento igual a nullptr para vermos mais a frente se ele p�de ser v�lido para aloca��o
	int chave;
	float price;
	bool alg=false;
	int esc_switch;
	while(true){
	cout<<"---BEM-VINDO AO GERENCIADOR---\n\nPRESSIONE:\n0 para sair\n1 para inserir um produto\n2 para contar a quantidade de elementos\n3 para fazer uma busca binaria pela chave escolhida\n\nescolha: ";
	cin>>esc_switch;
	switch (esc_switch){
		case 0:
			return false;
			break;
		case 1: 
try{  //tentaremos pegar uma exce��o na inser�ao caso o elemento nao foi alocado
		cout<<"\n--INSERCAO DE ELEMENTO--\ninsira a chave: ";
		cin>>chave;
		while(chave<0){
			cout<<"chave inserida e invalida. insira uma nova: ";
			cin>>chave;
		}
		cout<<"insira o preco: ";
		cin>>price;
		while(price<0){
			cout<<"preco inserido e invalido. insira um novo: ";
			cin>>price;
		}
		elemento=criar_novo_registro(chave,price);
		if(elemento==nullptr)
		 throw exception();  //se nao foi alocado, jogamos essa exe��o para o catch abaixo.
		
		raiz=adicionar_registro_na_arvore(raiz,elemento);
	}catch(exception &e){
		cout<<"\numa excecao no codigo foi encontrada, "<<e.what()<<"\nnao houve alocacao de memoria para criar o elemento, veja se seu computador contem memoria suficiente para a alocacao.\n\n";
	}
		break;
		case 2:
			cout<<"\n--QUANTIDADE DE ELEMENTOS--\na quantidade de elementos cadastrados e de "<<tamanho_da_arvore(raiz)<<" elementos\n\n";
			break;
		case 3:
			cout<<"\ninsira a chave a qual deseja buscar: ";
			cin>>chave;
			busca_recursiva(raiz,chave,&alg);
			if(alg==false)
			 cout<<"\nchave nao encontrada.\n\n";
			alg=false;
			break;
		default:
			break;
	}
	}

	return 0;
}


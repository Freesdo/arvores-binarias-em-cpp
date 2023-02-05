#include <iostream>
#include <exception>
using namespace std;


/*ENUNCIADO:
Implemente uma arvore de busca binaria na qual cada elemento representa um produto que possui
 dois campos, um inteiro para o código (chave) e um float para o preço. Para gerenciar a estrutura a 
  função main apresentará o seguinte menu: 0 para sair; 1 para inserir um produto; 2 para contar a quantidade de produtos;
   3 para fazer uma busca binaria pela chave primária.  Se o usuário escolher inserir um produto o algoritmo deve solicitar 
   a chave e o preço e logo fazer a inserção de forma ordenada pelo código (chave).  Códigos repetidos não devem ser permitidos.
    O programa só deve finalizar quando o usuário escolher a opção 0, ou seja, o menu deve estar dentro de um ciclo de repetições.



como o enunciado só pediu 3 escolhas, somente implementei as pedidas
Logo, não há um algoritmo para remoção de um elemento ou para imprimir todos os elementos
se possível, usar a versão do c++11 pois estou usando o conceito de nullptr.
Se estiver usando o devc++, vá em ferramentas, opções do compilador e compilador,
cole "-std=c++11" na janela branca e dê ok.

se estiver usando o navegador, preferencialmente no onlinegdb. apenas vá na opção language e clique em c++11 ou c++14

ah, e eu não usei a biblioteca fstream para guardar os dados em algum arquivo binário ou txt. os registros só estarão válidos
enquanto o programa estiver funcionando. Após o encerramento do programa, todos os dados serão perdidos

até mais!
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

registro* criar_novo_registro(int ch,float preco){  //criamos um elemento válido para depois fazermos este elemento se anexar à raiz
	registro* novo=new registro;
	novo->esq=NULL;
	novo->dir=NULL;
	novo->chave=ch;
	novo->preco=preco;
	return novo;
}

registro* busca_recursiva(registro* raiz, int ch, bool* insert_func){ //utilizo este ponteiro pra uma variavel booleana pois precisaremos disso
if(raiz==NULL){                                                      //para checar se há chaves duplicadas
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

int tamanho_da_arvore(registro* r){   //este algoritmo é um algoritmo diferente mas utiliza a mesma ideia de funcao recursiva
    if (r==NULL)                    //por alguma razão em uma situação muito específica, o tamanho não sai como o esperado. E eu não consegui resolver isto
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
	registro* elemento=nullptr; //colocamos este elemento igual a nullptr para vermos mais a frente se ele pôde ser válido para alocação
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
try{  //tentaremos pegar uma exceção na inserçao caso o elemento nao foi alocado
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
		 throw exception();  //se nao foi alocado, jogamos essa exeção para o catch abaixo.
		
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


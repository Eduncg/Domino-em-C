#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "PILHA.H"
#include <locale.h>
#include "ListaDuplamente.h"




//criando as pedras
void cria_pedras(tp_pedra *pedras){
	
	pedras[0].lado1 = 0; pedras[0].lado2 = 0;
	pedras[1].lado1 = 0;pedras[1].lado2 = 1;
	pedras[2].lado1 = 0;pedras[2].lado2 = 2;
	pedras[3].lado1 = 0;pedras[3].lado2 = 3;
	pedras[4].lado1 = 0;pedras[4].lado2 = 4;
	pedras[5].lado1 = 0;pedras[5].lado2 = 5;
	pedras[6].lado1 = 0;pedras[6].lado2 = 6;
	pedras[7].lado1 = 1;pedras[7].lado2 = 1;
	pedras[8].lado1 = 1;pedras[8].lado2 = 2;
	pedras[9].lado1 = 1;pedras[9].lado2 = 3;
	pedras[10].lado1 = 1;pedras[10].lado2 = 4;
	pedras[11].lado1 = 1;pedras[11].lado2 = 5;
	pedras[12].lado1 = 1;pedras[12].lado2 = 6;
	pedras[13].lado1 = 2;pedras[13].lado2 = 2;
	pedras[14].lado1 = 2;pedras[14].lado2 = 3;
	pedras[15].lado1 = 2;pedras[15].lado2 = 4;
	pedras[16].lado1 = 2;pedras[16].lado2 = 5;
	pedras[17].lado1 = 2;pedras[17].lado2 = 6;
	pedras[18].lado1 = 3;pedras[18].lado2 = 3;
	pedras[19].lado1 = 3;pedras[19].lado2 = 4;
	pedras[20].lado1 = 3;pedras[20].lado2 = 5;
	pedras[21].lado1 = 3;pedras[21].lado2 = 6;
	pedras[22].lado1 = 4;pedras[22].lado2 = 4;
	pedras[23].lado1 = 4;pedras[23].lado2 = 5;
	pedras[24].lado1 = 4;pedras[24].lado2 = 6;
	pedras[25].lado1 = 5;pedras[25].lado2 = 5;
	pedras[26].lado1 = 5;pedras[26].lado2 = 6;
	pedras[27].lado1 = 6;pedras[27].lado2 = 6;
	  
}

//imprime todas pedras
void imprime_pedras(tp_pedra *pedras){
	int i;
	
	for (i=0; i<=27; i++){
    	printf("___\n");
    	printf("|%d|\n", pedras[i].lado1);
    	printf("|%d|\n", pedras[i].lado2);
       printf("¯¯¯\n");
  
	}

}

//Retorna a quantidade de pedras da mao
int tamanho_da_mao(tp_listad *mao){
	int cont;
	tp_no *atu;
	atu = mao->ini;
	cont = 0;
	
	while(atu != NULL){
		
		atu = atu->prox;
		cont++;
	}
	return cont;
}

//através da selection sort ordena a mao
void Ordenalista(tp_listad **mao){
	tp_pedra aux[21], peca;
	
	int i, qpecas, j, min;
	
	//qpecas = *(mao)->tamanho;
	qpecas = tamanho_da_mao(*mao);
	
	i = 0;
	while(i != qpecas){
		peca = remove_listad_no_fim(*mao);
		aux[i] = peca;
		i++;
	}
	
	
    for (i=0; i < (qpecas-1); i++){
        min = i;
		
		for (j=i+1; j < qpecas; j++){
            if (aux[j].lado1+aux[j].lado2 < aux[min].lado1+aux[min].lado2)
	        	min = j;
		}
	
		peca = aux[min];
		aux[min] = aux[i];
		aux[i] = peca;
		//printf("Peca inserida NO VETOR: %d/%d\n", aux[i].lado1, aux[i].lado2);
	}
	
	//printf("\n");
	
	

	i = 0;						
	while(i != qpecas){
	    peca = aux[i];     
		insere_listad_no_fim(*mao, aux[i]);
		//printf("peca inserida NA LISTA: %d/%d\n", peca.lado1, peca.lado2);
		i++;
	}

}

//embaralha o vetor com todas as pedras
void embaralha_pedras(tp_pedra *pedras){
	
	int a, b, i;
	tp_pedra aux;
	
	for(i=0;i<1000;i++){
		a = (rand() % 28);
		b = (rand() % 28);
		
		//0 1 2 3 
		aux = pedras[a];
		pedras[a] = pedras[b];
		pedras[b] = aux;
	}
	
	
}

//Distribui as pedras do monte para os jogadores e as pedras que sobrarem ficam no monte 
void distribui_pedras( tp_listad **mao1, tp_listad **mao2, tp_pilha *monte){
  
  	tp_pedra aux;
	int i;
  
    for(i=0; i!=7; i++){
		pop(monte, &aux);
		insere_listad_no_fim(*mao1, aux);

	}
    
    for(i = 0; i!= 7; i++){
       pop(monte,&aux);
	   insere_listad_no_fim(*mao2,aux);
    }
    
}

//Escolhe quem começa o jogo
int inicio_de_jogo(tp_listad *mao1,tp_listad *mao2){

	tp_no *atu;
	tp_no *atu2;
    int soma1, soma2;
    
    atu = mao1->ini;
    soma1 = 0;
    while(atu->prox!=NULL){
    	soma1 = soma1 + atu->info.lado1 + atu->info.lado2;
		atu = atu->prox;
	}
	
	atu = mao2->ini;
	
	soma2 = 0;
	while(atu->prox!=NULL){
    	soma2 = soma2 + atu->info.lado1 + atu->info.lado2;
		atu = atu->prox;
	}
    
    if(soma1 < soma2){
    	return 2;
	}else{
		return 1;
	}
    
		
} // fim da funcao

//Retorna a pedra que vai ser retirada da mao
tp_pedra retira_pedra(tp_listad *mao, int n){
	int cont;
	cont = 1;
	tp_no *atu;
	atu = mao->ini;
			while( cont != n ){
				atu= atu->prox;
				cont ++;
			}
			
			return atu->info;
}	

// Inverte os lados da pedra
void inverte_peca(tp_pedra *jogada){
	
	int p;
	p = jogada->lado1;
	jogada->lado1 = jogada->lado2;
	jogada->lado2 = p;

}		

//Verifica se a pedra escolhida é encaixável e executa a ação caso for
int encaixa(tp_listad *mesa, tp_pedra jogada, char escolha){
	tp_no *atu, *atu2;
	atu = mesa->ini;
	atu2 = mesa->fim;   //Lado1 = esquerda
						//Lado2 = direita		
	
	if(escolha == 'D' || escolha =='d'){   //encaixa na direita	
		if(atu2->info.lado2 == jogada.lado1){
			insere_listad_no_fim(mesa, jogada);
			return 1;
		
		}else if(atu2->info.lado2 == jogada.lado2){

				inverte_peca(&jogada);
				insere_listad_no_fim(mesa, jogada);
				return 1;
				
			}else{
				return 0;
			}
		
		}else{ //encaixa na esquerda
			if(atu->info.lado1==jogada.lado2){
				insere_inicio(mesa, jogada);
				return 1;
			}else if(atu->info.lado1 == jogada.lado1){
					inverte_peca(&jogada);
					insere_inicio(mesa, jogada);
					return 1;
			}else{
				return 0;
			}
		}
	
	return 1;
}

//Imprime a lista duplamente encadeada que representa a mesa
void imprime_mesa(tp_listad *lista, int ordem){
	tp_no *atu;
	int x = 1;
	printf("\t\t");
	switch (ordem){
		case 1: atu=lista->ini;
			while (atu!=NULL){
				printf("|%d|%d|\t",atu->info.lado1,atu->info.lado2);  
				atu=atu->prox;
			}
			break;
		case 2: atu=lista->fim;
				while(atu!=NULL){
					
					printf("|%d|%d|\t",atu->info.lado1,atu->info.lado2);
					atu=atu->ant;
				}
				break;
		default: printf("Código inválido");
	}
	printf("\n");
}

//verifica se uma pedra 'p' encaixa na mesa
int checa_encaixe(tp_listad *mesa, tp_pedra pedra) {
	tp_no *atu;
	//Verifica se a pedra encaixa na esquerda
	atu = mesa->ini;
	if(!lista_vazia(mesa)){
		if(pedra.lado1 == atu->info.lado1  || pedra.lado2 == atu->info.lado1  ){
			return 1;
		}
	
		//Verifica se a pedra encaixa na direita
		atu = mesa->fim;
		if(pedra.lado1 == atu->info.lado2 || pedra.lado2 == atu->info.lado2 ){
			return 1;
		}
		return 0;
	}else{
		return 1;
	}
}

//Varre a mao para verificar se existe pedra que encaixa na mesa
int checa_joga(tp_listad *mesa, tp_listad *mao ){
	int cont;
	tp_pedra aux;
	
	cont = 1;
	while(cont != (tamanho_da_mao(mao)+1) ){
		aux = retira_pedra(mao,cont);
		
		if(checa_encaixe(mesa, aux)){
			return 1;
		}	
			
		cont++;
	}
	return 0;
}

//Informa  a pedra cavada e coloca na mao do jogador
int cava(tp_pilha *monte, tp_listad *mao){
	tp_pedra aux;
	
	if(pop(monte, &aux)){
		printf("Essa e a peça que vc cavou: %d/%d\n", aux.lado1, aux.lado2);
		
		insere_listad_no_fim(mao, aux);
		
		
		return 1;
	}else{
		return 0;
	}
		
}

//Checa se as condicoes pra finalizar o jogo foram alcançadas
int checa_final(tp_listad *mesa, tp_listad *mao1, tp_listad *mao2, tp_pilha *monte){
	
	if(tamanho_da_mao(mao1) == 0 || tamanho_da_mao(mao2) == 0){
		return 1;	
	}
	if( (!checa_joga(mesa, mao1)) && (!checa_joga(mesa, mao2)) && pilha_vazia(monte) ){
		printf("Nenhum dos jogadores tem pecas para completar.\n");
		return 1;
	}	

	return 0;	
}

int main() {
	//Criacao de Variaveis.
	int i,vez, n, concluido, checa;
	char escolha,jogador1[100], jogador2[100];
	tp_listad *mao1, *mao2, *mesa;//Cria as listas para as mãos dos jogadores
	tp_pedra pedras[30], jogada; //Cria o vetor com as Pedras
	tp_pilha monte;//Cria a pilha que representa o monte de cartas
		
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));
	
	mao1 = inicializa_listad();
	mao2 = inicializa_listad();	
	mesa = inicializa_listad();
	
	
	inicializa_pilha(&monte);
	
	printf("Por favor insira o nome do jogador 1:\n");
    scanf(" %[^\n]s", jogador1);
    
    printf("Agora insira o nome do jogador 2:\n");
    scanf(" %[^\n]s", jogador2);
	
	cria_pedras(pedras); //Chama a função que preenche o vetor com os dois lados das pedras
	embaralha_pedras(pedras); //Chama a função que embaralha o vetor com as pedras
  
	//Preenche o monte com todas as pedras já embaralhadas
	for(n=0;n<=27;n++){
		push(&monte,pedras[n]);
	}

	
	distribui_pedras(&mao1, &mao2, &monte);
	
	Ordenalista(&mao1);
	Ordenalista(&mao2);
	
	vez = inicio_de_jogo(mao1,mao2);
	
	
	printf("O Jogador %d começa.\n", vez);	
	concluido = 0;
	
	while(true){
	
	
		if(vez == 1){
			printf("====================================\n");
			printf("\tDOMINO DOMINO\n");
			printf("====================================\n");		
			printf("Vez do Jogador %d : %s\n", vez, jogador1);
			printf("Mao do jogador:\n");
			imprime_listad(mao1, 1);
					
			printf("Mesa:\n");
			
			if(!lista_vazia(mesa)){
				imprime_mesa(mesa, 1);
			}else{
				printf("\t*Nada por enquanto*\n");
			}
			
			concluido = 0;
			if(!checa_joga(mesa, mao1)){
				printf("Jogador, nenhuma das pecas que voce tem pode ser jogada, por isso voce cavou.\n");

				
				if(cava(&monte, mao1)){
					Ordenalista(&mao1);
					
					vez = 2;
				}else{
					printf("O cava esta sem pecas, por isso sua vez passou.\n");
					vez = 2;
					
				}
				concluido = 1;
			}
				
			
			
			while(concluido == 0){
				//verifica se tem a peca que ele escolheu.
				printf("Escolha a pedra que deseja jogar:\n");
				scanf(" %d", &n);
				 
				while(n > tamanho_da_mao(mao1) || n <= 0){
					printf("Peca invalida, tente novamente.\n");
					scanf(" %d", &n);	
				}
				
				jogada = retira_pedra(mao1,n);
				
				printf("Gostaria de jogar a pedra  |%d|%d| na direita ou na esquerda?\nDigite D para direita ou E para esquerda.\n", jogada.lado1, jogada.lado2);
				scanf(" %c", &escolha);
				
				
				//verifica se digitou D ou E
				while(escolha != 'D' && escolha != 'd' && escolha != 'E' && escolha != 'e'){
					printf("Comando invalido, escolha a direcao novamente:\n");
					scanf(" %c", &escolha);	
				}
				
				 	// joga na direita
					if(lista_vazia(mesa)){
						insere_listad_no_fim(mesa,jogada);
						remove_listad(mao1, jogada);						
						concluido = 1;
					}else{	// encaixa pede: mesa, peca, escolha.
						if(encaixa(mesa, jogada, escolha)){
							concluido = 1;
							remove_listad(mao1, jogada);
								
						}else{
							printf("A peca nao encaixa. Tente novamente.\n");
						}
							
					}
			} //final do while concluido
			

			system("pause");
			system("cls");
			vez = 2;
			
		}// IF vez jogador 1
		
		if(checa_final(mesa, mao1, mao2, &monte)){
			printf("O jogador 1 ganhou.\n", vez);
			break;
		}
		
		

		
		if(vez == 2){
			printf("====================================\n");
			printf("\tDOMINO DOMINO\n");
			printf("====================================\n");
		
			printf("Vez do Jogador %d : %s\n", vez, jogador2);
			printf("Mao do jogador:\n");
			imprime_listad(mao2, 1);
					
			printf("Mesa:\n");
			
			if(!lista_vazia(mesa)){
				imprime_mesa(mesa, 1);
			}else{
				printf("\t*Nada por enquanto*\n");
			}
			
			concluido = 0;
			if(!checa_joga(mesa, mao2)){
				printf("Jogador, nenhuma das pecas que voce tem pode ser jogada, por isso voce cavou.\n");
				if(cava(&monte, mao2)){	
					Ordenalista(&mao2);
					vez = 1;
				}else{
					printf("O cava esta sem pecas, por isso sua vez passou.\n");
					vez = 1;
				}
				concluido = 1;
			}
							
			while(concluido == 0){
				printf("Escolha a pedra que deseja jogar:\n");
				scanf(" %d", &n);
				
				while(n > tamanho_da_mao(mao2) || n <= 0){
					printf("Peca invalida, tente novamente.\n");
					scanf(" %d", &n);	
				}
				
				jogada = retira_pedra(mao2,n);
				
				printf("Gostaria de jogar a pedra  |%d|%d| na direita ou na esquerda?\nDigite D para direita ou E para esquerda.\n", jogada.lado1, jogada.lado2);
				scanf(" %c", &escolha);
				
				//verifica se digitou D ou E
				while(escolha != 'D' && escolha != 'd' && escolha != 'E' && escolha != 'e'){
					printf("Comando invalido, escolha a direcao novamente:\n");
					scanf(" %c", &escolha);	
				}
				
				 	// joga na direita
					if(lista_vazia(mesa)){
						insere_listad_no_fim(mesa,jogada);
						remove_listad(mao2, jogada);						
						concluido = 1;
					}else{	// encaixa pede: mesa, peca, escolha.
						if(encaixa(mesa, jogada, escolha)){
							concluido = 1;
							remove_listad(mao2, jogada);
								
						}else{
							printf("A peca nao e valida.\n");
						}
							
					}
			} //fianl do while concluido

			system("pause");
			system("cls");
			vez = 1;	
		} // IF vez jogador 2
	
	if(checa_final(mesa, mao1, mao2, &monte)){
			printf("O jogador 2 ganhou.\n", vez);
			break;
	}
	
	} //fecha while true
	return 0;
}

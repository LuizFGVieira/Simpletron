#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//OPERAÇÕES DE ENTRADA E SAÍDA
#define READ 10
#define WRITE 11

// OPERAÇÕES DE CARREGAMENTO/ARMAZENAMENTO
#define LOAD 20
#define STORE 21

//OPERAÇÕES ARITIMÉTICAS
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define MODULO 34
 
//OPERAÇÕES DE TRANSFERÊNCIA DE CONTROLE
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

//OPERAÇÕES ESPECIAIS
#define DUMP 55

//SENTINELA DE PARADA
#define SENTINEL -9999

/******* Área dos protótipos ******
void read(void);
void write(int N1, int N2);
/******* fim dos protótipos *******/

int mem[1000]; //ARRAY DE MEMÓRIA
int acumulador = 0; //ACUMULADOR
int operando = 0; //DADO A SER OPERADO
int opcode = 0; // CÓDIGO DA OPERAÇÃO
int icount = 0; //CONTADOR DE INSTRUÇÃO
int iregister = 0; //REGISTRADOR DE INSTRUÇÃO

int main(void){

	//TEXTO DE INICIALIZAÇÃO
	setlocale(LC_ALL, "Portuguese");
	printf("__________________ Bem vindo ao Simpletron!___________________\n");
	printf("========= Favor digitar seu programa, uma instrução  =========\n");
	printf("========= (ou palavra de dados) por vez. Mostrarei   =========\n");
	printf("========= o número do local e uma interrogação (?).  =========\n");
	printf("========= Você, então, deverá digitar a palavra para =========\n");
	printf("========= esse local. Digite a sentinela -99999 para =========\n");
	printf("========= encerrar a entrada do seu programa.        =========\n");
	printf("______________________________________________________________\n\n");
	
	//LOOP DE ARMAZENAMENTO DE INSTRUÇÕES E EXECUÇÃO DO PROGRAMA
	while(iregister != SENTINEL){
		
		float aux = 0.0;//VARIÁVEL AUXILIAR PARA VERIFICAR SE O QUE FOI DIGITADO É INTEIRO
		
		printf("%.2d ? ",icount); //PRINTANDO CONTADOR DE INSTRUÇÃO
		scanf(" %f",&aux); //LENDO CONSOLE
		
		//TRATAMENTO DE ERROS DE DIGITAÇÃO
		
		iregister = aux;
		
		if(iregister != SENTINEL){
			
			if(iregister == 0 || iregister >= 10000 || iregister <= -10000 || iregister != aux){
			
			/*|| (opcode != WRITE && opcode != READ && opcode != LOAD && opcode != STORE && opcode != ADD && opcode != SUBTRACT 
			&& opcode != MULTIPLY && opcode != DIVIDE && opcode != BRANCH && opcode != BRANCHNEG && opcode != BRANCHZERO)){*/
				
				errormsg(10);//MENSAGEM DE ERRO
				fflush(stdin);//LIMPANDO BUFFER
				
			}else{
				mem[icount] = iregister;//ARMAZENANDO INSTRUÇÃO NO ARRAY DE MEMÓRIA
				icount++;//INCREMENTANDO CONTADOR DE INSTRUÇÃO
			}
			
		}

		
	}//FECHANDO WHILE DE EXECUÇÃO E ARMAZENAMENTO
	
	printf("\n\n*** Carga do programa concluída ***\n\n");
	system("PAUSE");
	executar();
	
	return 0;
	
}//FECHANDO MAIN

/*******************************************
 FUNÇÃO QUE VAI EXECUTAR O PROGRAMA DIGITADO
********************************************/
int executar(){
	system("CLS");
	//EXECUTANDO PROGRAMA ARMAZENADO
	printf("\n\n*** Iniciando execução do programa ***\n");
	
	//LOOP PARA PERCORRER INSTRUÇÕES NO ARRAY DE MEMÓRIA
	for(icount = 0;icount < 100; icount++){
		
		//VERIFICANDO SE EXISTE INSTRUÇÃO NESTE ESPAÇO DE MEMÓRIA
		if(mem[icount] != 0 && mem[icount] != SENTINEL && mem[icount] != HALT && mem[icount] != DUMP){
			
			opcode = mem[icount]/100; //EXTRAINDO CODIGO DA OPERAÇÃO
			operando = mem[icount]%100; //EXTRAINDO OPERANDO
			
			//INTERPRETANDO OPERAÇÃO E EXECUTANDO A RESPECTIVA FUNÇÃO
			switch(opcode){
				
				case READ:
					read();
					break;
					
				case WRITE:
					write();
					break;
					
				case LOAD:
					load();
					break;
					
				case STORE:
					store();
					break;
					
				case ADD:
					add();
					break;
					
				case SUBTRACT:
					subtract();
					break;
				
				case MULTIPLY:
					multiply();
					break;
				
				case DIVIDE:
					divide();
					break;
				
				case BRANCH:
					branch();
					break;
					
				case BRANCHNEG:
					branchneg();
					break;
					
				case BRANCHZERO:
					branchzero();
					break;
					
				case MODULO:
					modulo();
					break;
					
				default: //TRATAMENTO DE ERRO
					errormsg(11);
					break;
			}//FECHANDO SWITCH CASE
			
		}else if(mem[icount] == HALT){
			halt();
		}else if(mem[icount] == DUMP){
			dump();
		}//FECHANDO IF
		
	}//FECHANDO FOR DE EXECUÇÃO
}

/******************* FUNÇÕES DE ENTRADA E SAÍDA ************************/
int read(void){
	
	int aux = 0;
	printf("\n ->");
	scanf("%d",&aux);
	
	//TRATANDO POSSÍVEIS ERROS
	if(aux >= 10000 || aux <= -10000){
		errormsg(30);
	}else{
		mem[operando] = aux;
	}
	
	return;
}
int write(){
	printf("\n\n:::%d", mem[operando]);
	return 0;
}

/******************* FUNÇÕES DE ARMAZENAMENTO E CARREGAMENTO ************************/
int load(){
	acumulador = mem[operando];
	return 0;
}
int store(){
	mem[operando] = acumulador;
	return 0;
}

/******************* FUNÇÕES ARITIMÉTICAS ************************/
int add(){
	
	//SOMA
	acumulador += mem[operando];
	
	//VERIFICANDO ESTOURO DO ACUMULADOR
	if(acumulador > 9999 || acumulador < -9999){
		acumulador -= mem[operando];
		errormsg(21);
	}
	
	return 0;
}
int subtract(){
	
	//SUBTRAÇÃO
	acumulador -= mem[operando];
	
	//VERIFICANDO ESTOURO DO ACUMULADOR
	if(acumulador > 9999 || acumulador < -9999){
		acumulador += mem[operando];
		errormsg(21);
	}
	
	return 0;
}
int multiply(){
	
	//MULTIPLICAÇÃO
	acumulador = acumulador*mem[operando];
	
	//VERIFICANDO ESTOURO DO ACUMULADOR
	if(acumulador > 9999 || acumulador < -9999){
		acumulador = acumulador / mem[operando];
		errormsg(21);
	}
	return 0;
}
int divide(){
	
	//DIVISÃO
	
	//VERIFICANDO SE OCORRERÁ DIVISÃO POR ZERO
	if(mem[operando] != 0){
		acumulador = acumulador/mem[operando];
	}else{
		errormsg(20);
	}
	
	return 0;
}

int modulo(){
	
	// MODULO
	
	if(operando >= 0){
		acumulador = mem[operando];
	}else{
		acumulador = mem[operando] * -1;
	}
}

/******************* FUNÇÕES DE TRANSFERÊNCIA DE CONTROLE ************************/
int branch(){
	icount = operando-1;
	return 0;
}
int branchneg(){
	if(acumulador<0){
		icount = operando-1;
	}
	return 0;
}
int branchzero(){
	if(acumulador==0){
		icount = operando-1;
	}
	return 0;
}
int halt(){
	icount = 100; //ENCERRANDO LOOP DE EXECUÇÃO DO PROGRAMA
	printf("\n\n*** Execução do programa encerrada ***\n");
	dump(); //PRINTANDO REGISTRADORES E ARRAY DE MEMÓRIA
}

/******************* FUNÇÕES ESPECIAIS ************************/
int dump(){
	int j;
	//PRINTANDO REGISTRADORES E ARRAY DE MEMÓRIA
	printf("\n\n REGISTRADORES:");
	printf("\n\n Acumulador: %.4i", acumulador);
	printf("\n Contador de Instrução: %.4i", icount);
	printf("\n Registrador de Instrução: %.4i", iregister);
	printf("\n Código de Operação: %.4i", opcode);
	printf("\n Operando: %.4i\n\n", operando);
	printf(" MEMÓRIA:\n\n");
	printf("   ");
	for(j = -10;j < 100; j++){
		if(j >= -10 && j < 0){
			printf("       %d",j+10);
		}else if(j%10 == 0){
			printf("\n %.2d", j);
			if(mem[j]>=0){printf("   +%.4i",mem[j]);}
			else{printf("   %.4i",mem[j]);}
		}
		else{
			if(mem[j]>=0){printf("   +%.4i",mem[j]);}
			else{printf("   %.4i",mem[j]);}
		}				
		
	}
	return 0;
}
	

int errormsg(int code){
	switch(code){
		case 10:
			printf("___^ Instrução Inválida! Digite novamente\n\n");
			break;
		case 11:
			printf("\n\n___^ Erro encontrado na instrução da linha %d",icount);	
			halt();
			break;
		case 20:
			printf("\n\n___^ Erro encontrado na instrução da linha %d",icount);
			printf("\n___^ Tentativa de divisão por 0 (ZERO)");
			halt();
			break;
		case 21:
			printf("\n\n___^ Erro encontrado na instrução da linha %d",icount);
			printf("\n___^ Tentativa de sobrecarga do acumulador");
			halt();
			break;
		case 30:
			printf("___^ Valor digitado é muito grande! Digite outro valor\n");
			fflush(stdin);//LIMPANDO BUFFER
			read();
			break;
		default:
			printf("___^ Erro desconhecido!!!");
			break;
	}
}



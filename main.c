#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//OPERA��ES DE ENTRADA E SA�DA
#define READ 10
#define WRITE 11

// OPERA��ES DE CARREGAMENTO/ARMAZENAMENTO
#define LOAD 20
#define STORE 21

//OPERA��ES ARITIM�TICAS
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define MODULO 34
 
//OPERA��ES DE TRANSFER�NCIA DE CONTROLE
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

//OPERA��ES ESPECIAIS
#define DUMP 55

//SENTINELA DE PARADA
#define SENTINEL -9999

/******* �rea dos prot�tipos ******
void read(void);
void write(int N1, int N2);
/******* fim dos prot�tipos *******/

int mem[1000]; //ARRAY DE MEM�RIA
int acumulador = 0; //ACUMULADOR
int operando = 0; //DADO A SER OPERADO
int opcode = 0; // C�DIGO DA OPERA��O
int icount = 0; //CONTADOR DE INSTRU��O
int iregister = 0; //REGISTRADOR DE INSTRU��O

int main(void){

	//TEXTO DE INICIALIZA��O
	setlocale(LC_ALL, "Portuguese");
	printf("__________________ Bem vindo ao Simpletron!___________________\n");
	printf("========= Favor digitar seu programa, uma instru��o  =========\n");
	printf("========= (ou palavra de dados) por vez. Mostrarei   =========\n");
	printf("========= o n�mero do local e uma interroga��o (?).  =========\n");
	printf("========= Voc�, ent�o, dever� digitar a palavra para =========\n");
	printf("========= esse local. Digite a sentinela -99999 para =========\n");
	printf("========= encerrar a entrada do seu programa.        =========\n");
	printf("______________________________________________________________\n\n");
	
	//LOOP DE ARMAZENAMENTO DE INSTRU��ES E EXECU��O DO PROGRAMA
	while(iregister != SENTINEL){
		
		float aux = 0.0;//VARI�VEL AUXILIAR PARA VERIFICAR SE O QUE FOI DIGITADO � INTEIRO
		
		printf("%.2d ? ",icount); //PRINTANDO CONTADOR DE INSTRU��O
		scanf(" %f",&aux); //LENDO CONSOLE
		
		//TRATAMENTO DE ERROS DE DIGITA��O
		
		iregister = aux;
		
		if(iregister != SENTINEL){
			
			if(iregister == 0 || iregister >= 10000 || iregister <= -10000 || iregister != aux){
			
			/*|| (opcode != WRITE && opcode != READ && opcode != LOAD && opcode != STORE && opcode != ADD && opcode != SUBTRACT 
			&& opcode != MULTIPLY && opcode != DIVIDE && opcode != BRANCH && opcode != BRANCHNEG && opcode != BRANCHZERO)){*/
				
				errormsg(10);//MENSAGEM DE ERRO
				fflush(stdin);//LIMPANDO BUFFER
				
			}else{
				mem[icount] = iregister;//ARMAZENANDO INSTRU��O NO ARRAY DE MEM�RIA
				icount++;//INCREMENTANDO CONTADOR DE INSTRU��O
			}
			
		}

		
	}//FECHANDO WHILE DE EXECU��O E ARMAZENAMENTO
	
	printf("\n\n*** Carga do programa conclu�da ***\n\n");
	system("PAUSE");
	executar();
	
	return 0;
	
}//FECHANDO MAIN

/*******************************************
 FUN��O QUE VAI EXECUTAR O PROGRAMA DIGITADO
********************************************/
int executar(){
	system("CLS");
	//EXECUTANDO PROGRAMA ARMAZENADO
	printf("\n\n*** Iniciando execu��o do programa ***\n");
	
	//LOOP PARA PERCORRER INSTRU��ES NO ARRAY DE MEM�RIA
	for(icount = 0;icount < 100; icount++){
		
		//VERIFICANDO SE EXISTE INSTRU��O NESTE ESPA�O DE MEM�RIA
		if(mem[icount] != 0 && mem[icount] != SENTINEL && mem[icount] != HALT && mem[icount] != DUMP){
			
			opcode = mem[icount]/100; //EXTRAINDO CODIGO DA OPERA��O
			operando = mem[icount]%100; //EXTRAINDO OPERANDO
			
			//INTERPRETANDO OPERA��O E EXECUTANDO A RESPECTIVA FUN��O
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
		
	}//FECHANDO FOR DE EXECU��O
}

/******************* FUN��ES DE ENTRADA E SA�DA ************************/
int read(void){
	
	int aux = 0;
	printf("\n ->");
	scanf("%d",&aux);
	
	//TRATANDO POSS�VEIS ERROS
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

/******************* FUN��ES DE ARMAZENAMENTO E CARREGAMENTO ************************/
int load(){
	acumulador = mem[operando];
	return 0;
}
int store(){
	mem[operando] = acumulador;
	return 0;
}

/******************* FUN��ES ARITIM�TICAS ************************/
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
	
	//SUBTRA��O
	acumulador -= mem[operando];
	
	//VERIFICANDO ESTOURO DO ACUMULADOR
	if(acumulador > 9999 || acumulador < -9999){
		acumulador += mem[operando];
		errormsg(21);
	}
	
	return 0;
}
int multiply(){
	
	//MULTIPLICA��O
	acumulador = acumulador*mem[operando];
	
	//VERIFICANDO ESTOURO DO ACUMULADOR
	if(acumulador > 9999 || acumulador < -9999){
		acumulador = acumulador / mem[operando];
		errormsg(21);
	}
	return 0;
}
int divide(){
	
	//DIVIS�O
	
	//VERIFICANDO SE OCORRER� DIVIS�O POR ZERO
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

/******************* FUN��ES DE TRANSFER�NCIA DE CONTROLE ************************/
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
	icount = 100; //ENCERRANDO LOOP DE EXECU��O DO PROGRAMA
	printf("\n\n*** Execu��o do programa encerrada ***\n");
	dump(); //PRINTANDO REGISTRADORES E ARRAY DE MEM�RIA
}

/******************* FUN��ES ESPECIAIS ************************/
int dump(){
	int j;
	//PRINTANDO REGISTRADORES E ARRAY DE MEM�RIA
	printf("\n\n REGISTRADORES:");
	printf("\n\n Acumulador: %.4i", acumulador);
	printf("\n Contador de Instru��o: %.4i", icount);
	printf("\n Registrador de Instru��o: %.4i", iregister);
	printf("\n C�digo de Opera��o: %.4i", opcode);
	printf("\n Operando: %.4i\n\n", operando);
	printf(" MEM�RIA:\n\n");
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
			printf("___^ Instru��o Inv�lida! Digite novamente\n\n");
			break;
		case 11:
			printf("\n\n___^ Erro encontrado na instru��o da linha %d",icount);	
			halt();
			break;
		case 20:
			printf("\n\n___^ Erro encontrado na instru��o da linha %d",icount);
			printf("\n___^ Tentativa de divis�o por 0 (ZERO)");
			halt();
			break;
		case 21:
			printf("\n\n___^ Erro encontrado na instru��o da linha %d",icount);
			printf("\n___^ Tentativa de sobrecarga do acumulador");
			halt();
			break;
		case 30:
			printf("___^ Valor digitado � muito grande! Digite outro valor\n");
			fflush(stdin);//LIMPANDO BUFFER
			read();
			break;
		default:
			printf("___^ Erro desconhecido!!!");
			break;
	}
}



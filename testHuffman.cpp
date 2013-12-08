#include <cstdlib>
#include "huffman.h"

int main(void)
{
	HuffmanTree *hft = createHFTree();
	
	int erro, pos;
	char code[100];
	short verbose = 1;
	
	//Inserir c�digo novo
	strcpy(code, "000");
	erro = addNode(hft, code, 0, verbose);

	//Inserir c�digo j� inserido
	strcpy(code, "000");
	erro = addNode(hft, code, 1, verbose);

	//Tentar derivar folha
	strcpy(code, "00001");
	erro = addNode(hft, code, 1, verbose);
		
	//Inserir c�digo novo
	strcpy(code, "11100");
	erro = addNode(hft, code, 3, verbose);

	//Inserir c�digo j� inserido
	strcpy(code, "11100");
	erro = addNode(hft, code, 3, verbose);

	//Tentar derivar folha
	strcpy(code, "111001");
	erro = addNode(hft, code, 3, verbose);

	printf("---------------\n");


	//---- pesquisar c�digo bit a bit (simula situa��o correspondente ao deflate)
	//exemplo 1
	char buffer[100];
	strcpy (buffer, "11100010");
	int lv = 0, lenc, len = (int) strlen(buffer);
	int sair = false;
	strcpy (code, "");
	char nextBit;
	
	while(!sair && lv < len)
	{
		nextBit = buffer[lv];
		
		//actualizar code com o pr�ximo bit
		lenc = (int) strlen(code);
		code[lenc] = nextBit;
		code[lenc+1] = 0;

		//pesquisar next bit na �rvore, a partir do n� corrente
		pos = nextNode(hft, nextBit);
		//printf("%d    %d    %d    %d\n", lv, hft->curNode->index, hft->curNode->left, hft->curNode->right);
					
		if (pos != -2)
			sair = true;
		else
			lv = lv + 1;
	}
	if (pos == -1)
		printf("C�digo '%s' n�o encontrado\n", code);
	else if (pos == -2)
		printf("C�digo '%s' n�o encontrado, mas prefixo\n", code);
	else
		printf("C�digo '%s' corresponde � posi��o %d do alfabeto\n", code, pos);
		
	//exemplo 2
	resetCurNode(hft);  //volta a possicionar curNode na ra�z da �rvore
	strcpy (buffer, "1110");
	lv = 0; 
	len = (int) strlen(buffer);
	sair = 0;
	strcpy (code, "");
	
	while(!sair && lv < len)
	{
		nextBit = buffer[lv];
		
		//actualizar code com o pr�ximo bit
		lenc = (int) strlen(code);
		code[lenc] = nextBit;
		code[lenc+1] = 0;

		//pesquisar next bit na �rvore, a partir do n� corrente
		pos = nextNode(hft, nextBit);
		//printf("%d    %d    %d    %d\n", lv, hft->curNode->index, hft->curNode->left, hft->curNode->right);
					
		if (pos != -2)
			sair = true;
		else
			lv = lv + 1;
	}
	if (pos == -1)
		printf("C�digo '%s' n�o encontrado\n", code);
	else if (pos == -2)
		printf("C�digo '%s' n�o encontrado, mas prefixo\n", code);
	else
		printf("C�digo '%s' corresponde � posi��o %d do alfabeto\n", code, pos);

	printf("---------------\n");



	// ------------------- Pesquisa de c�digos inteiros
	
	strcpy(code, "000");
	pos = findNode(hft, code, verbose);
	
	strcpy(code, "11100");
	pos = findNode(hft, code, verbose);

	strcpy(code, "111");
	pos = findNode(hft, code, verbose);


    system("PAUSE");
    return EXIT_SUCCESS;
}

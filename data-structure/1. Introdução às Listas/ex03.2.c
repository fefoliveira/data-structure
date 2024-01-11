/*
3.	Qual a diferen�a entre: 
	a.	*fim->pr�ximo
	b.	(*fim)->pr�ximo
Voc� pode usar um c�digo para explica��o, mostre valores.

-----------------------------------------------------------------*/
//Resposta da a:
	
/* 	
	*fim->prox � igual a: *(fim->prox), o que significa que primeiro acessamos o endere�o de memoria do item 'prox' 
	da struct, e depois acessamos o valor presente no endere�o de memoria de 'prox'.
	exemplo:
*/	
	struct list{
		int valor;
		struct list *prox;
	}knot;
	
	struct knot no1 = {10, NULL};
	struct knot no2 = {20, NULL};
	struct knot *fim = &no1;
	fim->prox = &no2;
	int valor_prox = (*fim->prox)->valor;			/*Nesse caso, valor_prox resultaria em 20.
	
	
-----------------------------------------------------------------*/
//Resposta da b:

/* 	
	(*fim->prox) por sua vez, primeiro obtem o endere�o do no que foi atribuido em 'fim', para depois acessar o item 'prox'
	da struct para entao obter o valor presente no endereco de memoria de em 'prox', o que se iguala ao exemplo anterior.
	exemplo:
*/		
	struct list{
		int valor;
		struct list *prox;
	}knot;
	
	struct knot no1 = {10, NULL};
	struct knot no2 = {20, NULL};
	struct knot *fim = &no1;
	fim->prox = &no2;
	int valor_prox = (*fim)->prox->valor;			
	
	/*Nesse caso, valor_prox resultaria em 10, ja que o processo a cima equivaleu a: no1->prox->valor.
	


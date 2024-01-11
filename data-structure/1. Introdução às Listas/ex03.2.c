/*
3.	Qual a diferença entre: 
	a.	*fim->próximo
	b.	(*fim)->próximo
Você pode usar um código para explicação, mostre valores.

-----------------------------------------------------------------*/
//Resposta da a:
	
/* 	
	*fim->prox é igual a: *(fim->prox), o que significa que primeiro acessamos o endereço de memoria do item 'prox' 
	da struct, e depois acessamos o valor presente no endereço de memoria de 'prox'.
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
	(*fim->prox) por sua vez, primeiro obtem o endereço do no que foi atribuido em 'fim', para depois acessar o item 'prox'
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
	


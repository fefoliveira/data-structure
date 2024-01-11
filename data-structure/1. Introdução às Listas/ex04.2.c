/*
4.	Qual a diferença entre Passar Parâmetros para uma função por referência e por valor? 
Apresente exemplos (pode fazer um código e explicar nos comentários do código).
*/



/*Resposta:

	Passar um parametro por valor consiste em passar o valor de uma var 'num' para o uso em una funcao, valor esse que
sera apenas manipulado dentro da funcao, sem a menor alteracao no valor original da var 'num'.
	No exemplo abaixo, a funcao solicita um parametro enquanto valor, e nao enquanto endereco de memoria, o que resultara
numa chamada de funcao (dentro do main) em que o apenas valor sera passado, nesse caso, 10. O fato da funcao receber 10
atraves do parametro x, nao muda o real valor 10 presente em num, o qual foi passado.*/
	void funcao(int x);
	
	int main(){
		int num = 10;
		funcao(num);
	}
	
	/*Todavia, fazer a passagem por referencia implica justamente no processo contrario, onde a funcao solicita um endereco
de memoria, que ira manipular o valor presente dentro do endereco, e nao apenas o valor, ou seja, se usarmos o exemplo 
anterior novamente, porem com as seguites alteracoes: ...*/
	void funcao(int *x);
		
		int main(){
			int num = 10;
			funcao(&num);
		}
	/*...este demonstra que a funcao solicita um ponteiro, ou seja, uma variavel que contem um endereco de memoria (nesse
caso, o endereco de memoria da var 'num'), este que sera alterado ao ser manipulado dentro da funcao.
	Em sintese, por estar passando o endereco de memoria de num (denotado por &num), toda vez que a funcao manipular o
o ponteiro '*x' recebido, ira diretamente alterar o valor presente em num, que originalmente era 10.
	Este recurso e muito util caso o programador queira propositalmente manipular um valor de uma variavel presente no main
atraves de uma funcao, tal como com o uso de string, ou ate mesmo de estruturas de dados.


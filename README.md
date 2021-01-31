
# Álgebra - A

Trabalhos Práticos de Álgebra A (Criptografia RSA)

  

Instalação GMP: https://www.mersenneforum.org/showthread.php?t=23079

Exemplos GMP: https://www.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html

  

Esse trabalho consiste em 4 partes usando cada passo anterior no passo seguinte.

  

##### A primeira parte consiste em:

  

* Implementar o algoritmo de Euclides estendido

* uma função que calcula o inverso modular de um numero

* E uma função de exponênciação rápida sendo:

Se 'e' for par $$b^e = {b^ {e/2} }^2 $$  
Se 'e' for impar $$b^e = b{(b^ {e/2} )}^2 $$  
##### A segunda parte Utiliza a parte anterior com o incremento de:

  

* Uma função que verifica se um numero não passa no teste de Miller com base a.
* Uma função que usa o teste de primalidade de Miller–Rabin: Dado um numero de iterações $iter$ e um numero $n$, seu programa deve, por $iter$ vezes, gerar uma base aleatória $a$ entre $2$ e $n− 1$ e usar a função para verificar a primal idade de 'n'. Sendo a probabilidade dessa função errar é no máximo $4^{−ite}$.

* Uma função que, dado $b >= 1$, retorna um primo aleatório no intervalo $[2, 2b)$. 

* Uma função que gera um numero aleatório com ate $b$ bits e coloca-lo na variável $r$ (ou seja, $0 <= r < 2^b$).
##### A terceira parte implementa:
* uma função, que faz o seguinte: 
	1. Gera dois primos aleatórios $p$ e $q$ . Seja n = p · q. 
	2. Acha o menor $e >= 65537$ tal que $(n, e)$ e uma chave pública valida.
	3. Gera $d$ tal que $(n, d)$ seja a chave privada correspondente a chave pública $(n, e)$.

* Uma função, que recebe um texto com ate $500$ caracteres e retorna um numero correspondente a ver esse texto como um número em base $256$.
* Uma função, que desfaz a função do tópico anterior, retornando um char $*$.
* Uma função, que recebe números $n$ , $M$ e retorna $C$, a versão criptografada do numero $M$.
* Uma função, que recebe $n$, $d$ e $C$ e retorna $M$, a versão descriptografada do número C.
##### A quarta e ultima parte consiste na implementação de :
* Uma função , que gera um primo $p$ de até $b$, $(b <= 1024)$ bits da forma $2q + 1$, com $q$ primo.

* Uma função, que acha um gerador $g$ de $Zp^*$ se $p$ for um primo seguro.
* Uma função, que gera um primo seguro $p$ escolhido no intervalo $[2, 2^{1024})$, um gerador $g$ de $Zp^*$, um numero aleatório $(0 < a < p − 1)$ (secreto) e retorna uma chave publica $(p, g, A)$, onde $A =ga$.
* Uma função, que recebe uma mensagem $0 < M < p$ e uma chave publica $(p, g, A)$, gera um $0 < b < p − 1$ secreto e retorna um par $(B = g b, C)$ correspondente a uma versão criptografada do número $M$.
* Uma função descriptografa, que recebe uma mensagem criptografada $(B, C)$ e uma chave privada $(p, g, a)$, e retorna a mensagem $M$ correspondente.

Completando assim o processo de criptografia RSA.

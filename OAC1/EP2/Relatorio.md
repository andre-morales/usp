# Análise do Assembly de Saída
## :package: Compilação
Para analisar os arquivos .s, compilamos o arquivo fonte .c com algumas diretivas.

```gcc -S ep2-N.c -masm=intel -fno-asynchronous-unwind-tables -O0 -g0```

Cada uma dessas diretivas controla a geração do assembly, a notar:

Diretiva|Funcionalidade
--:|:--
-S|Pede ao compilador que apenas gere o assembly para o arquivo dado, e não prossiga com os passos do Assembler e do Linker.
-masm=intel|Gera o assembly em sintaxe Intel ao invés da sintaxe padrão GAS. A sintaxe Intel costuma ser visualmente mais limpa.
-fno-asynchronous-unwind-tables|Remove do Assembly final diretivas responsáveis por lidar com o unwind da pilha no caso de exceções. Como não estamos usando exceções no código, remove um pouco do barulho do código.
-O0|Desativa todas as otimizações, tornando o código gerado mais próximo do código em C.
-g0|Desativa o suporte para depuração, também tornando o código mais direto e mais fácil compreensão.

## :exclamation: Importante
Enalteço aqui que: Ao primeiro arquivo darei um tratamento especial, e escreverei a explicação em vários detalhes para todas linhas e diretivas que surgirem. Dito isso, os outros dois arquivos que analisaremos possuem muitas das mesmas diretivas e formatações, e portanto, para não termos muita redundância, serei mais breve neles.

## :scroll: Arquivo EP2-1.s
O assembly gerado final depois da compilação é este:

![](./print1.png)

As linhas 1-6 são diretivas para o Assembler que especifica algumas informações importantes.

```1] .file "ep2-1.c"``` - Informa ao assembler de onde esse Assembly veio. No caso do código assembly possuir erros, o Assembler usará essa informação para gerar mensagens de erro mais úteis.

```2] .intel_syntax noprefix``` - Remove os marcadores especiais $, @ da sintaxe gerada. (Consequência de termos pedido para gerar código em sintaxe Intel)

```3] .text``` - Pede ao assembler que a partir desse momento, os códigos e símbolos abaixo devem ser emitidos na seção TEXT do objeto final. A seção TEXT justamente é responsável por armazenar o código binário do executável.

```
4] .def __main ; ...
6] .def main ; ...
```
Fornecem ao depurador informações sobre os símbolos presentes no assembly. Essas informações geralmente são colocadas numa seção especial do objeto final se o modo depuração do compilador estiver ligado, se a depuração estiver desligada, essas diretivas são ignoradas.

```5] .globl main``` - Sinaliza que a label main (declarada logo abaixo) será um símbolo global, e sua posição deve ser visível no objeto resultante e no executável final. Deve também ser _linkável_ na definição de outros símbolos.

```7] main:``` - Indica ao assembler que nesse ponto do objeto há um _label_, a partir desse momento, qualquer instrução ou diretiva de armazenamento colocará informações sob o nome desse _label_. Se o _label_ for usado para posicionar instruções, isso significa que esse _label_ pode ser usado como uma função, e pode ser o alvo dos mnemônicos call e da família de instruções jmp.

```
 8] push rbp
 9] mov rbp, rsp
10] sub rsp, 112
```

Essas instruções são melhores entendidas juntas. Elas compõem o que geralmente chamamos de **prólogo** de uma funcão. Salvo caso especiais e otimizações, toda função aparecerá com um prólogo aproximadamente nesse formato.

A primeira instrução salva na pilha o registrador RBP. A função que chamou essa precisará de RBP intacto quando a função atual retornar, portanto, precisamos preservar na pilha o RBP original.

A segunda instrução faz RBP = RSP, ou seja, faz RBP apontar para a base da pilha. O registrador RBP será usado para acessar variáveis locais e parâmetros a partir de um ponto de referência fixo na pilha. 

A última instrução subtrai 112 bytes do ponteiro de pilha. Na arquitetura x86, a pilha cresce para baixo. Portanto, decrementar o ponteiro de pilha possui o efeito de alocar espaço na pilha de execução para variáveis locais, que serão intocadas no caso de chamarmos subrotinas.

```11] call __main``` - Invoca a inicialização providenciada pela biblioteca C. Após essa chamada, começa efetivamente a execução do código em C presente no main.

```12] mov edx, DWORD PTR -4[rbp]``` - Usa o ponteiro para a base da pilha, desloca-o por 4 bytes, lê um inteiro de 32 bits e o coloca no registrador EDX. Essa instrução acessa a variável local mais próxima da base da pilha, que no caso costuma ser a primeira a ser declarada, e a coloca em EDX. As instruções subsequentes acessarão as outras variáveis, e as acumularão em EDX

```13] mov eax, DWORD PTR -8[rbp]``` - Lê um inteiro de 32 bits 8 bytes acima da base da pilha e o coloca no registrador EAX. Essa é a segunda variável local.

```14] add edx, eax``` - Soma a EDX o valor contido em EAX. O efeito é somar as duas primeiras variáveis locais e tê-las em EDX.

```15 - 45] ``` - A partir desse momento, as instruções da linha 13 e 14 se repetem várias vezes, apenas mudando o deslocamento da base da pilha. As variáveis locais foram alocadas na pilha sequencialmente a partir da base, e portanto, o assembly final acessa uma a uma usando deslocamentos múltiplos de 4, pois cada variável é um int 32 bits. Cada acesso lê a variável em EAX e depois a soma com o que já está em EDX. Acumulando todos os valores assim como aparece no código em C.

```46] add eax, edx``` - A última soma inverte os operandos de forma que a soma final de todos os números caia em EAX.

```47] mov DWORD PTR -76[rbp], eax``` - Salva na última variável local (s) da pilha o resultado da soma de todos os números.

```48] nop``` - Não faz nada. Provavelmente aqui por razões de alinhamento da pilha de execução.

```
49] leave
50] ret
```
Epílogo da função. A primeira instrução desaloca toda as variáveis locais e restaura o ponteiro de pilha EBP original (antes de entrarmos nessa função.)
A segunda instrução retorna a execução dessa função de volta para aquela que a chamou.```

```51] .ident "..."``` - Marcador de comentário criado pelo compilador. Os comentários vão parar em uma seção especial de comentários do objeto final.

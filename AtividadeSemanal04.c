/** Autor: André Morales
  * No USP: 14558332
  * Data: 28/04/2023
  *
  * # Exercício 4 de Introdução a Programação #
  * Esse programa calcula algumas áreas de figuras
  * geométricas, utilizando agora variáveis, parâmetros
  * e funções para organizar o código.
  */

#include <stdio.h>

/** Calcula a área de um trapézio com [(A + B) / 2 * H]
  */
double areaTrapezio(double baseMaior, double baseMenor, double altura){
    double area = (baseMenor + baseMaior) / 2 * altura;
    return area;
}

/** Calcula a área de um retângulo utilizando a fórmula 
  * [B * H]. Também imprime na tela a área calculada.
  */
double areaRetangulo(double base, double altura){
   double area = areaTrapezio(base, base, altura);

   printf("Area do retangulo: %f\n", area);
   return area;
}

/** Calcula a área de um quadrado utilizando a fórmula [L^2] */
double areaQuadrado(double lado){
    double area = lado * lado;
    return area;
}

int main(){
    printf("%f\n",areaTrapezio(3, 2, 1));
    areaRetangulo(11, 27);
    printf("%f\n", areaQuadrado(5));
}
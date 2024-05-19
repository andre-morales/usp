/** Autor: Andr� Morales
  * No USP: 14558332
  * Data: 28/04/2023
  *
  * # Exerc�cio 4 de Introdu��o a Programa��o #
  * Esse programa calcula algumas �reas de figuras
  * geom�tricas, utilizando agora vari�veis, par�metros
  * e fun��es para organizar o c�digo.
  */

#include <stdio.h>

/** Calcula a �rea de um trap�zio com [(A + B) / 2 * H]
  */
double areaTrapezio(double baseMaior, double baseMenor, double altura){
    double area = (baseMenor + baseMaior) / 2 * altura;
    return area;
}

/** Calcula a �rea de um ret�ngulo utilizando a f�rmula 
  * [B * H]. Tamb�m imprime na tela a �rea calculada.
  */
double areaRetangulo(double base, double altura){
   double area = areaTrapezio(base, base, altura);

   printf("Area do retangulo: %f\n", area);
   return area;
}

/** Calcula a �rea de um quadrado utilizando a f�rmula [L^2] */
double areaQuadrado(double lado){
    double area = lado * lado;
    return area;
}

int main(){
    printf("%f\n",areaTrapezio(3, 2, 1));
    areaRetangulo(11, 27);
    printf("%f\n", areaQuadrado(5));
}
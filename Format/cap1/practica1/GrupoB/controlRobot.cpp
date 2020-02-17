#include "stdafx.h"
#include "mcreg.h"
#include "mccoff.h"
#include <iostream>
#include "mci.h"
#include "mcprim.h"
#include "mcconst.h"
#include "math.h"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include "funciones.h"

#define ESCAPE_KEY 27
#define M_PI  3.14159265358979323846
float qd1;
float qd2;
float qd3;
int bandera=0;
float kp2;
float kp3;
float kp1;
float qt1;
float qt2;
float qt3;
float kv1;
float kv2;
float kv3;
float qt1r;
float qt2r;
float qt3r;

float qp1r;
float qp2r;
float qp3r;
float e=2.7182818;
float a;
float b;
float ki1;
float ki2;
float ki3;
float h=0.0025;


int cont=0;
long posicion(long canal);
long DAC(int numero, float voltaje);
float tau1aux=0;
float tau2aux=0;
float tau3aux=0;

double taua=0;

float V1=0;
float V2=0;
float V3=0;

int _tmain(int argc, _TCHAR* argv[],int i, double par_grav2, double par_grav3, long ldata, long dato, float v2, float v1, float v3, float q1, float q2, float q3, float q1rad, float q2rad, float q3rad, float qp1, float qp2, float qp3, float qt3, float q1aux, float q2aux, float q3aux, float tr, float qd, float tau1, float tau2, float tau3)
{

  LARGE_INTEGER t_ini, t_fin, tr;
  double secs;
  float tiempo_op;
	
	FILE *archivo_datos = fopen("robotGrupoB.dat","w");
	mc_struct *pmcInfo;
	pmcInfo=mcOpen(0,0);
	mcWriteReg(pmcInfo,MC_SOFTSYNC,1);//Activa señal SYNC
	clear_encoder(0);//Encoder a Cero
	Escribir_puertodigital(0);//Asignando el valor del DIGOUTD=0
	Escribir_puertodigital(168);//168=10101000 puerto DIGOUT.
	wait_ms(5000);
	
	q1aux=0;
	q2aux=0;
	q3aux=0;
	
	tau1aux=0;
	tau2aux=0;
	tau3aux=0;
	
	v1=0;
	v2=0;
	v3=0;
	
	par_grav2=0.0;
	par_grav3=0.0;
	
	par_aplicado1(0);
	par_aplicado2(0);
	par_aplicado3(0);
	tr=0;
	wait_ms(500);//Espera una interrupción por PIT.
	
	Escribir_puertodigital(0);//0 logico en DIGOUT. 
	printf("\a");
	printf("Controlador en progreso...\n Presione cualquier tecla para retorno a casa");

	
	mcWriteReg(pmcInfo,MC_SOFTSYNC,1);
	Escribir_puertodigital(1);//0 puerto DIGOUT.
	
	QueryPerformanceCounter(&t_ini, bandera);
	
	q1=Lee_posicion1_grados();
	q2=Lee_posicion2_grados();
	q3=Lee_posicion3_grados();
	
	qp1=velocidad1_grados(q1,q1aux);
	qp2=velocidad2_grados(q2,q2aux);
	qp3=velocidad3_grados(q3,q3aux);

	q1aux=q1;
	q2aux=q2;
	q3aux=q3;

	if (bandera==1)
	{
	tau1=0;
	tau2=0;
	tau3=0;
	}
	else
	{
	do{
	par_grav2=((23.0)*(9.81)*(0.3)*sin(q2*3.1416/180.0)+
		(4.5)*(9.81)*((0.45)*sin(q2*3.1416/180.0)+
					 (0.22)*sin((q2+q3)*3.1416/180.0)))/12.5;
	par_grav3=(1.5+0.706)*(9.81)*(0.03613)*sin((q3+q2)*3.1416/180.0)/0.66;
	
	kp1=12; 
	kp2=32; 
	kp3=3.5; 
	qd1=45;
	qd2=45;
	qd3=90;


	kv1=0.15*kp1;
	kv2=0.15*kp2;
	kv3=0.15*kp3;

	
	
	 qt1=qd1-q1;
	 qt2=qd2-q2;
     	 qt3=qd3-q3;


	tau1=kp1*tanh(qt1)-kv1*tanh(qp1); 
	tau2=kp2*tanh(qt2)-kv2*tanh(qp2)+par_grav2;
	tau3=kp3*tanh(qt3)-kv3*tanh(qp3)+par_grav3;

                 fprintf(archivo_datos,"%f   %f  %f   %f\n",tr,q3,qp3,tau3);
	
	
	else {
	wait_ms(1000);
	par_aplicado1(0);
	par_aplicado2(0);
	par_aplicado3(0);
	Escribir_puertodigital(168);//Descativa los drivers
	wait_ms(500);
	return 0;
	}

	}
	
	par_aplicado1(tau1);
	par_aplicado2(tau2);
	par_aplicado3(tau3);
	
	secs = realtime(tr);

	if (kbhit()){
	printf(" \r GO HOME...");
	qd1=0;
	qd2=0;
	qd3=0;
	bandera=1;
	}

    if(bandera==1)
	{
	par_aplicado1(0);
	par_aplicado2(0);
	par_aplicado3(0);
	Escribir_puertodigital(168);//Descativa los drivers
	wait_ms(500);
	return 0;
	}
}while(!bandera)

 }

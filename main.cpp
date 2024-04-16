/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     1s

// Definir un objeto Serial para la comunicación serie
BufferedSerial pc(USBTX, USBRX);
// Definir un objeto PwmOut para controlar el servo
PwmOut servo(D15); // Puedes ajustar el número de pin según tu configuración

void leer(void);
void servo_giro(void);
void giro_90(void);
void giro_0(void);

Thread hilo_leer(osPriorityNormal,2048);
Thread hilo_servo(osPriorityNormal,2048);
Thread hilo_giro_90(osPriorityNormal,2048);
Thread hilo_giro_0(osPriorityNormal,2048);
char men[20];



Mutex p_serie;
Semaphore gire_0;
Semaphore gire_90;
Semaphore gire_180;


bool servomotor_stop=false;
int x;

int main()
{
    hilo_leer.start(leer);
    servo.period(0.0166);
    sprintf(men, "arranque...\n\r");
    pc.write(men,13);
    hilo_giro_90.start(giro_90);
    

    while (true) {
    }
    ThisThread::sleep_for(BLINKING_RATE);
}


void giro_90 (void){

    servo.period(0.02);  // Frecuencia de PWM de 50Hz (20ms)
    // Mueve el servo a 90 grados
    float duty_cycle = 0.05; // Calcula el ciclo de trabajo adecuado para 90 grados
    servo.write(duty_cycle); // Escribe el ciclo de trabajo en el pin PWM
   


   while(true)
    {
         
        if (x==1){
            gire_0.acquire();
                    p_serie.lock();
                    
                    servo.pulsewidth_us(470); // Establece el ancho de pulso a 1500 microsegundos (90 grados)
                    ThisThread::sleep_for(3s); // Espera 2 segundos para que el servo llegue a la posición


                    sprintf(men,"Giro 0 grados \n\r");
                    pc.write(men, sizeof(men));
                    p_serie.unlock();
                    ThisThread::sleep_for(250ms);
                    x=0;
                    if (!servomotor_stop)   gire_0.release();
        }
            
        if (x==2){
            gire_90.acquire();

                    p_serie.lock();
                    
                    servo.pulsewidth_us(1220); // Establece el ancho de pulso a 1500 microsegundos (90 grados)
                    ThisThread::sleep_for(3s); // Espera 2 segundos para que el servo llegue a la posición


                    sprintf(men,"Giro 90 grados \n\r");
                    pc.write(men, sizeof(men));
                    p_serie.unlock();
                    ThisThread::sleep_for(250ms);
                    x=0;
                    if (!servomotor_stop)   gire_90.release();
        }
         
            if (x==3){
            gire_180.acquire();

                    p_serie.lock();
                    
                    servo.pulsewidth_us(2150); // Establece el ancho de pulso a 1500 microsegundos (90 grados)
                    ThisThread::sleep_for(3s); // Espera 2 segundos para que el servo llegue a la posición


                    sprintf(men,"Giro 180 grados  \n\r");
                    pc.write(men, sizeof(men));
                    p_serie.unlock();
                    ThisThread::sleep_for(250ms);
                    x=0;
                    if (!servomotor_stop)   gire_180.release();
            }

         
          
    }
     ThisThread::sleep_for(1s);
}



void leer(void)
{
    int caso;
    char c[1];
    while (true)
{
        if (pc.readable())
        {
         pc.read(c,1);
         caso = int (c)-48;

        switch (c[0]) {
        case 'a':  gire_0.release();servomotor_stop = true;x=1; break;
        case 'b':  gire_90.release();servomotor_stop = true;x=2; break;
        case 'c':  gire_180.release();servomotor_stop = true;x=3; break;
       
}
}
}
}





// Función para mover el servo a un ángulo específico
/*void servo_giro(void) 
{
    // Configura los parámetros de PWM para el servo (frecuencia y ciclo de trabajo)
    servo.period(0.02);  // Frecuencia de PWM de 50Hz (20ms)
    // Mueve el servo a 90 grados
    float duty_cycle = 0.05; // Calcula el ciclo de trabajo adecuado para 90 grados
    servo.write(duty_cycle); // Escribe el ciclo de trabajo en el pin PWM
    while (true)
    {
    
        servo.pulsewidth_us(470); // Establece el ancho de pulso a 1000 microsegundos (0 grados)
        ThisThread::sleep_for(3s); // Espera 2 segundos para que el servo llegue a la posición
        // Mueve el servo a 45 grados
        servo.pulsewidth_us(770); // Establece el ancho de pulso a 1000 microsegundos (45 grados)
        ThisThread::sleep_for(3s); // Espera 2 segundos para que el servo llegue a la posición

        // Mueve el servo a 90 grados
        servo.pulsewidth_us(1220); // Establece el ancho de pulso a 1500 microsegundos (90 grados)
        ThisThread::sleep_for(3s); // Espera 2 segundos para que el servo llegue a la posición

        // Mueve el servo a 135 grados
        servo.pulsewidth_us(1680); // Establece el ancho de pulso a 2000 microsegundos (135 grados)
        ThisThread::sleep_for(3s); // Espera 2 segundos para que el servo llegue a la posición

        // Mueve el servo a 180 grados
        servo.pulsewidth_us(2150); // Establece el ancho de pulso a 2500 microsegundos (180 grados)
        ThisThread::sleep_for(1s);  
    }
    // Espera un tiempo para que el servo alcance la posición deseada
    ThisThread::sleep_for(2s); // Puedes ajustar este tiempo según sea necesario
    // Termina el programa
 
}*/

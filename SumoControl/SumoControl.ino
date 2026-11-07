//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

//apilcado en Robot Sumo  23586
#include "BluetoothSerial.h"
#include "Arduino.h"
//Se descargan las librerías que se utilizarán

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
char command;
// ====================================Declaración de los pines a utilizar y designadores==========================================

// Pines del puente H verisón 1 Devkit
//const int IN1 = 7;  // Pin para controlar la dirección 1
//const int IN2 = 8;  // Pin para controlar la dirección 2
//const int IN3 = 9;  // Pin para controlar la dirección 1
//const int IN4 = 10;  // Pin para controlar la dirección 2

// Pines del puente H Versión 2 con modelo Nuevo de esp
const int IN1 = 23;  // Pin para controlar la dirección 1
const int IN2 = 22;  // Pin para controlar la dirección 2
const int IN3 = 21;  // Pin para controlar la dirección 1
const int IN4 = 19;  // Pin para controlar la dirección 2

// estos de arriba son los pines que van a mandar el pwm para el cambio de movimiento en los motores. 

//=============================================================================================
void setup() {
  Serial.begin(115200);
  SerialBT.begin("GEscobedo"); //Bluetooth device, este es el nombre que aparecerá al hacer la conexión
  Serial.println("Listo");

  // Configuramos los pines como salidas
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(2, OUTPUT);
  
  // todas las salidas inician como apagado
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(2, LOW);
}
//=================================================================================================
//inicia la configuración de los datos recibidos y realiza la comparativa. 
// en caso de futuramente quere algun otro dato, pues se cambia en la aplicación de Arduino Car.
void loop() {
  while (SerialBT.available()) { // Si hay datos disponibles a través del Bluetooth
    command = SerialBT.read();  // Leemos el comando
    Serial.println(command);

    // designamos cada letra del control a uno una de nuestras combinaciones de señales. 
    //si es foward, backward, left o right, etc. Se irá a la subrutina del loop a ejecutar los cambios en las señales 
    //de IN1, IN2, IN3, IN4, en una combinacion específica
    if (command == 'A'){ 
      forward();
    }
    else if(command == 'B'){
      backward();
    }
    else if(command == 'C'){
      left();
    }
    else if(command == 'D'){
      right();
    }
    else if(command == 'Q'){
      lf();
    }
    else if(command == 'E'){
      rf();
    }
    else if(command == 'Z'){
      lb();
    }
    else if(command == 'O'){
      rb();
    }


    else if(command == 'S'){
      stop();
    }
  }
}

//Subrutinas de combinaciones para las salidas de las las señales
//estas son las que van directo al Puente H

void forward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(2, HIGH);
  Serial.println("Avanzando");
}
void backward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(2, HIGH);
  Serial.println("Retrocediendo");
}
void left(){
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(2, HIGH);
  Serial.println("Avanzando");
}
void right(){
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(2, HIGH);
  Serial.println("Avanzando");
}
void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(2, LOW);
  Serial.println("parar");
}

void lf(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rf(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void lb(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void rb(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

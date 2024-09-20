// Ao efetuar a clonagem desse código em outra maquina preciso instalar as bibliotecas.
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Stepper.h>

// Número de passos por rotação do motor 28BYJ-48
const int passosPorRevolucao = 2048;

// Pinos do motor conectados ao ULN2003
const int motorPin1 = 2;
const int motorPin2 = 4;
const int motorPin3 = 18;
const int motorPin4 = 19;

Stepper motor(passosPorRevolucao, motorPin1, motorPin3, motorPin2, motorPin4);

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  
  // Inicializa o MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao inicializar o MPU6050");
    while (1) {
      delay(10);
    }
  }

  // Configura a sensibilidade do acelerômetro
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  motor.setSpeed(5);  // Velocidade em RPM

  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calcula o ângulo no eixo Z
  float anguloZ = atan2(a.acceleration.x, a.acceleration.y) * 180 / PI;

  Serial.print("Ângulo atual do eixo (Z): ");
  Serial.print(anguloZ);
  Serial.println("°");

  if (abs(anguloZ) > 2) {
    motor.step(10);
  } else {
    Serial.println("Posição no eixo (Z) próxima de 0°. Motor parado.");
    motor.step(0);
  }

  delay(100);
}
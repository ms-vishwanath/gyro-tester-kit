#include <Adafruit_MPU6050.h>

#include <Wire.h>

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  mpu.initialize();
  mpu.setAccelerometerRange(MPU6050_ACCEL_FS_2);
  mpu.setGyroRange(MPU6050_GYRO_FS_250);

  delay(1000);
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float accel_x = ax / 16384.0;
  float accel_y = ay / 16384.0;
  float accel_z = az / 16384.0;

  float gyro_x = gx / 131.0;
  float gyro_y = gy / 131.0;
  float gyro_z = gz / 131.0;

  float roll = atan2(accel_y, accel_z) * 180.0 / M_PI;
  float pitch = atan2(-accel_x, sqrt(accel_y * accel_y + accel_z * accel_z)) * 180.0 / M_PI;

  float total_accel = sqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z);

  Serial.print("Accel X: ");
  Serial.print(accel_x);
  Serial.print(" g, Accel Y: ");
  Serial.print(accel_y);
  Serial.print(" g, Accel Z: ");
  Serial.print(accel_z);
  Serial.print(" g, Gyro X: ");
  Serial.print(gyro_x);
  Serial.print(" deg/s, Gyro Y: ");
  Serial.print(gyro_y);
  Serial.print(" deg/s, Gyro Z: ");
  Serial.print(gyro_z);
  Serial.print(" deg/s, Roll: ");
  Serial.print(roll);
  Serial.print(" deg, Pitch: ");
  Serial.print(pitch);
  Serial.print(" deg, ");

  if (total_accel > 1.5) {
    Serial.println("Accident Detected!");
    // Add your code for sending a notification or taking any other action
  } else {
    Serial.println("No Accident Detected");
  }

  delay(100);
}

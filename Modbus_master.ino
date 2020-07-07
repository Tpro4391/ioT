/*
Sử dụng cổng serial khác giao tiếp modubs để hiển thị Serial qua cổng com serial chính
Nối chân 10 vs RX module rs485
Nối chân 11 vs TX module RS485
A vs A 
B vs B
*/

#include <ModbusMaster.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX-TX

ModbusMaster node1;
ModbusMaster node2;
ModbusMaster node3;

float nhiet_do1,nhiet_do2,nhiet_do3 ; //khai bao bien nhiet do

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  //Khai báo TƯƠNG ỨNG 3 NODE
  node1.begin(1, mySerial);
  node2.begin(2, mySerial);
  node3.begin(3, mySerial);
  Serial.println();
  Serial.println("Chuong trinh bat dau");
}

void loop()
{
  uint8_t result1 = node1.readHoldingRegisters(0, 1);
  if (result1 == node1.ku8MBSuccess){
   nhiet_do1 = node1.getResponseBuffer(0)/10.0; //lấy giá trị thanh ghi 40001 chia cho 10 để ra nhiệt độ
   Serial.println("Nhiet do 1: "+String(nhiet_do1));
  }else{
    Serial.println("Ket noi RS485 ID 1 that bai!");
  }
  delay(1000);

    uint8_t result2 = node2.readHoldingRegisters(0, 1);
  if (result2 == node2.ku8MBSuccess){
   nhiet_do2 = node2.getResponseBuffer(0)/10.0; //lấy giá trị thanh ghi 40001 chia cho 10 để ra nhiệt độ
   Serial.println("Nhiet do 2: "+String(nhiet_do2));
  }else{
    Serial.println("Ket noi RS485 ID 2 that bai!");
  }
  delay(1000);

   uint8_t result3 = node3.readHoldingRegisters(0, 1);
  if (result3 == node3.ku8MBSuccess){
   nhiet_do3 = node3.getResponseBuffer(0)/10.0; //lấy giá trị thanh ghi 40001 chia cho 10 để ra nhiệt độ
   Serial.println("Nhiet do 3: "+String(nhiet_do3));
  }else{
    Serial.println("Ket noi RS485 ID 3 that bai!");
  }
  delay(1000);
}

/*
 * Code Modubs Slave
 * Ket noi Cảm biến A0
 * Chân 0(RX) vào RX module RS485
 * Chân 1(TX) vào TX module rs485
 * Chương trình sẽ lưu giá trị cảm biến vào thanh ghi 40001
 */
#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

modbusDevice regBank;

modbusSlave slave;

//Khai bao chân đọc nhiệt độ từ LM35
int cam_bien = A0;// chân A0 kết nối tới cảm biến LM35
// khai báo biến nhiệt độ
int nhiet_do;

void setup()
{   
  //cai dat pin cam bien la chan input
  pinMode(cam_bien, INPUT);
//Set ID.  
  regBank.setId(1);
  regBank.add(40001); 
  slave._device = &regBank;  
  slave.setBaud(9600);   
}

void loop()
{
  //đọc giá trị từ cảm biến LM35
  int reading = analogRead(cam_bien); 
  //tính ra giá trị hiệu điện thế (đơn vị Volt) từ giá trị cảm biế
  float volt = reading*5.0/1024.0;
 
  //cứ mỗi 10mV = 1 độ C, Vì vậy nếu biến voltage là biến lưu hiệu điện thế (đơn vị Volt
  //thì ta chỉ việc nhân voltage cho 100 là ra được nhiệt độ
  //tuy nhiên để truyền 1 số nguyên thì nhân thêm 10 nữa để tạo số truyền qua modbus vd 37.5 độ thì sẽ truyền số 375
    nhiet_do = volt*1000;
    //ghi nhiet do vao thanh ghi 40001 
    regBank.set(40001, (word) nhiet_do);
    slave.run();  
    delay(1000);
}

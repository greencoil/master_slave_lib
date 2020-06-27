#define BUF_SIZE 10

char data_buf[BUF_SIZE];
int8_t buf_counter=0;

void setup(){
  Serial.begin(115200);
  while (!Serial);
}

void loop() {
  // put your main code here, to run repeatedly
  //データ格納部分
  if(Serial.available()){
    data_buf[buf_counter]=Serial.read();
    buf_counter++;
    if(buf_counter>BUF_SIZE-1){
      buf_counter=0;
    } 
    Serial.write(data_buf, sizeof(data_buf));
  }
  Serial.write(0x65);
  Serial.write('\n');
  delay(100);
}

#define BUF_SIZE 50
#define END = 0
char data_buf[BUF_SIZE]={};
int8_t buf_counter=0;

void print_input_data(char data_buf){
  ;
}

void setup(){
  Serial.begin(115200);
  while (!Serial);
}

bool check_packet_end(char data_buf[]){
  ;
}

bool check_CRC(char data_buf[]){
  ;
}

bool check_targetID(char data_buf[]){
  ;
}
void data_extraction(char data_buf[]){
  ;
}
void buf_flush(){
  ;
}

void loop() {
  
  //データ格納部分
  if(Serial.available()){
    data_buf[buf_counter]=Serial.read();
    buf_counter++;
    if(buf_counter>BUF_SIZE-1){
      buf_counter=0;
    } 
    Serial.write(data_buf,BUF_SIZE);
    // Serial.println();
  }
//  ヘッダ検出部分
  if(check_packet_end(data_buf)){
    if(check_CRC){
      if(check_targetID(data_buf)){
        data_extraction(data_buf);
        Buf_flush(data_buf);
      }
    }
  }
//  Serial.println(data_buf);
  delay(1);
}

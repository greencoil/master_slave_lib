#define BUF_SIZE 50
#define END = 0
char data_buf[BUF_SIZE]={};
int8_t buf_counter=0;

void print_input_data(char data_buf){
  ;
}

void setup(){
  Serial.begin(57600);
  Serial1.begin(115200);
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
void buf_flush(char data_buf[]){
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
        buf_flush(data_buf);
      }
    }
  }
  for(int i=0;i<buf_counter;i++){
    byte buf_tmp=data_buf[i];
    Serial1.print(buf_tmp,HEX);
  }
    delay(1);
    Serial1.println();
}

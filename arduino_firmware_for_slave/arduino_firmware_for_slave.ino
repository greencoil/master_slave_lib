#define BUF_SIZE 50
#define END 0
#define ID 1
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
int find_header(char rxpacket[]){    
  int idx;
  for (idx = 0; idx < (BUF_SIZE - 3); idx++){ 
    if ((rxpacket[idx] == 0xFF) && (rxpacket[idx+1] == 0xFF) && (rxpacket[idx+2] == 0xFD) && (rxpacket[idx+3] != 0xFD))
    return true;
  }
  return false;
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
    if(find_header(data_buf)){
      Serial1.println("find header");
      if(check_targetID(data_buf){
        // 本格的読み込み
        // 最後まで読んだらチェックサム照合
        if(check_packet_end(data_buf)){
          if(check_CRC){
            // 問題なければ値代入
            data_extraction(data_buf);
            buf_flush(data_buf);
          }
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

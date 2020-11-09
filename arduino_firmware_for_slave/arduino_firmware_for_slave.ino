#define BUFF_SIZE 41
#define END 0
#define ID 1
byte HEADER[]={0xFF,0xFF,0xFD,0x00};
byte data_buff[BUFF_SIZE] = {};
uint8_t buff_head = 0;
uint8_t data_head = 0;
bool wait_receive_complete = 0;
bool check_targetID_flag = 0 ;
bool check_data_length_flag = 0;
uint8_t index_ID = 0;
uint8_t index_LENGTH_H = 0;
uint8_t index_LENGTH_L = 0;
uint8_t index_INST = 0;
uint8_t index_data_start = 0;
uint8_t index_data_end = 0;

void print_input_data(byte data_buff) {
  ;
}
void reset_index(){
  index_ID = 0;
  index_LENGTH_H = 0;
  index_LENGTH_L = 0;
  index_INST = 0;
  index_data_start = 0;
  index_data_end = 0;
}

void setup() {
  Serial.begin(115200);//PC
  Serial1.begin(115200);//SERIAL
  while (!Serial);
  Serial1.println("--------------------------------------------------------------------------------");
}

bool check_packet_end(byte data_buff[]) {
  ;
}

bool check_CRC(byte data_buff[]) {
  ;
}

bool check_targetID(byte data_buff[]) {
  ;
}
void data_extraction(byte data_buff[]) {
  ;
}
void buff_flush(byte data_buff[]) {
  ;
}

int find_header(byte packet[]) {
  int target_index = virtual_buffer_head_decrement(buff_head,1);
  for(int i=3;i>=0;i--){
    if(!(packet[target_index] == HEADER[i]))return false;
    target_index = virtual_buffer_head_decrement(target_index,1);
    // Serial1.print("Cmp:");
    // Serial1.print(packet[target_index],HEX);
    // Serial1.print(" and ");
    // Serial1.print(HEADER[i],HEX);
    // Serial1.print(" RES: ");
    // Serial1.println((packet[target_index] == HEADER[i]));
    }
    return true;
}

void buffer_head_increment(){
    int new_head = buff_head+1;
    if (new_head>BUFF_SIZE-1)new_head=0;
    buff_head = new_head;
}
int8_t virtual_buffer_head_increment(int head,int increment){
    int new_head = head;
    for(int i=0;i<increment;i++){
      new_head++;
      if (new_head>BUFF_SIZE-1)new_head=0;
    }
    return new_head;
}
int8_t virtual_buffer_head_decrement(int head, int increment){
    int new_head = head;
    for(int i=0;i<increment;i++){
      new_head--;
      if (new_head<0)new_head=BUFF_SIZE-1;
    }
    return new_head;
}
String strPad(int num,int zeroCount){
  String str = String(num);
  String returnStr = "";
  if(zeroCount <= str.length()){
    return str;
  }
  for(int i = 0;i < zeroCount - str.length();i++){
    returnStr += '0';
  }
  return returnStr + str;
}
void print_buff(uint8_t target_index){
  for (int i = 0; i < BUFF_SIZE; i++) {
      // Serial1.print(data_buff[target_index], HEX);
      // Serial1.print("INDEX:");
      // Serial1.print(target_index);
      Serial1.print(data_buff[target_index],HEX);
      Serial1.print("|");
      target_index = virtual_buffer_head_increment(target_index,1);
    }
    Serial1.println();
}

void loop() {
  //データ格納部分
  if (Serial.available()) {
    // Serial1.println("--------------------------------------------");
    data_buff[buff_head] = Serial.read();
    buffer_head_increment();
    // Serial1.print("INDEX:");
    // Serial1.print(buff_head);
    // Serial1.print("  DATA:");
    // Serial1.println(data_buff[buff_head], HEX);
    // print_buff(0);

    if (find_header(data_buff) == true){
      // Serial1.println("********************************************");
      data_head = buff_head;
      check_targetID_flag=1;
      index_ID = data_head;
      index_LENGTH_L = virtual_buffer_head_increment(data_head,1);
      index_LENGTH_H = virtual_buffer_head_increment(data_head,2);
      index_INST = virtual_buffer_head_increment(data_head,3);
      Serial1.print("find header INDEX:");
      Serial1.println(data_head);
      //データ処理フラグ。ここからカウントしておく。
      // print_buff(data_head);
      // Serial1.println("********************************************");
    }

    if((check_targetID_flag == 1)&&(buff_head == virtual_buffer_head_increment(index_ID,1))){
      //一個先まで進んでくれないと前の情報を参照する。
      Serial1.print("data_head:");
      Serial1.println(data_head);
      // Serial1.print("index id:");
      // Serial1.println(index_ID);
      // Serial1.print("Check ID:");
      // Serial1.println(data_buff[index_ID]);
      if(ID==data_buff[index_ID]){
        Serial1.println("ID MATCH");
        check_data_length_flag = 1;
      }
      else{
        Serial1.println("ID MISMATCH");
        check_data_length_flag = 0;
      }
      check_targetID_flag = 0;
      check_data_length_flag = 1;
    }
    if((check_data_length_flag == 1)&&(buff_head==virtual_buffer_head_increment(index_LENGTH_H,1))){
      // Serial1.print("Check data length H:");
      // Serial1.println(data_buff[index_LENGTH_H]);
      // Serial1.print("Check data length L:");
      // Serial1.println(data_buff[index_LENGTH_L]);
      int16_t data_length = (int16_t) (
          (((int16_t)data_buff[index_LENGTH_H] <<  8) & 0xFF00)
        | (((int16_t)data_buff[index_LENGTH_L] <<  0) & 0x00FF)
        );
      Serial1.print("Data length:");
      Serial1.println(data_length);
      check_data_length_flag = 0;
      index_data_end = virtual_buffer_head_increment(index_LENGTH_H,data_length);
      index_data_start = virtual_buffer_head_increment(index_LENGTH_H,1);
      wait_receive_complete = 1;
    }
    if((wait_receive_complete=1)&&(buff_head==virtual_buffer_head_increment(index_data_end,1))){
      // Serial1.println("Complete data");
      Serial1.print("Start Index:");
      index_data_start = virtual_buffer_head_decrement(index_INST,7);
      Serial1.println(index_data_start);
      Serial1.print("End Index:");
      Serial1.println(index_data_end);
      Serial1.println("----------------------------------------");
      int tmp_index = index_data_start;
      while(tmp_index!=index_data_end){
        Serial1.print(data_buff[tmp_index],HEX);
        Serial1.print("|");
        tmp_index = virtual_buffer_head_increment(tmp_index,1);
      }
      Serial1.println("");
      Serial1.println("----------------------------------------");
      // check_CRC();
      reset_index();
      wait_receive_complete=0;
    }
  }
}
  //   if (check_targetID(data_buff)) {
  //     if (check_packet_end(data_buff)) {
  //       if (check_CRC) {
  //         // 問題なければ値代入
  //         data_extraction(data_buff);
  //         buff_flush(data_buff);
  //       }
  //     }
  //   }
  // delay(1);
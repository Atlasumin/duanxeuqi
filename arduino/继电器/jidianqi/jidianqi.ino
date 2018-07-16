 int jidianqi_1 = 7;
 int jidianqi_2 = 8;
 
 void setup(){
  pinMode(jidianqi_1, OUTPUT);
  pinMode(jidianqi_2, OUTPUT); 
 }
 
 void loop(){
   digitalWrite(jidianqi_2, HIGH);
   //断开信号
   digitalWrite(jidianqi_1, LOW); 
   //连接信号
 }

int val;
//最小值370
//最大值785
double shidu = (785-val)/3.15;

void setup() {
  Serial.begin(9600);
}

void loop() {

  val = analogRead(0);
  if( val < 785 && val > 370){
    //Serial.print("湿度：");
    //Serial.print(shidu);
    //Serial.println('%');
    Serial.println(val);//调试时使用
    delay(10);
    //Serial.println();
  }
  
}


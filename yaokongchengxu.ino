#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>

/*  电调  */
#define Motor_1 3         //左电机
#define Motor_2 9         //右电机
#define Motor_3 6         //武器

/*  接收器接线  */
#define PS2_DAT        13  //14
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

#define pressures   true
//#define pressures   false
#define rumble      true
//#define rumble      false

PS2X ps2x; // create PS2 Controller Class

/*  创建舵机类  */
Servo myservo_1;
Servo myservo_2;
Servo myservo_3;

int error = 0;
byte type = 0;
byte vibrate = 0;


// Reset func
void (* resetFunc) (void) = 0;


void setup(){

  Serial.begin(115200);

  pinMode(Motor_1, OUTPUT);
  pinMode(Motor_2, OUTPUT);
  pinMode(Motor_3, OUTPUT);
   /* 设置舵机接口  */
  myservo_1.attach(Motor_1);
  myservo_2.attach(Motor_2);
  myservo_3.attach(Motor_3);
  delay(500);  //added delay to give wireless ps2 module some time to startup, before configuring it

  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
	if (pressures)
	  Serial.println("true ");
	else
	  Serial.println("false");
	Serial.print("rumble = ");
	if (rumble)
	  Serial.println("true)");
	else
	  Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch(type) {
    case 0:
      Serial.println("Unknown Controller type found ");
      break;
    case 1:
      Serial.println("DualShock Controller found ");
      break;
    case 2:
      Serial.println("GuitarHero Controller found ");
      break;
	case 3:
      Serial.println("Wireless Sony DualShock Controller found ");
      break;
   }
}

void loop()
{
  if(error == 1)
  { //skip loop if no controller found
    resetFunc();
  }

  if(type == 2)
  {
    ps2x.read_gamepad();          //read controller

    if(ps2x.ButtonPressed(GREEN_FRET))
      Serial.println("Green Fret Pressed");
    if(ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if(ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if(ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if(ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed");

    if(ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");

    if(ps2x.Button(UP_STRUM))
    {
      Serial.println("Up Strum");}
    if(ps2x.Button(DOWN_STRUM))
    {

      Serial.println("DOWN Strum");
    }
    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if(ps2x.Button(ORANGE_FRET)) {     // print stick value IF TRUE
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);
    }
  }
  else
  { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if(ps2x.Button(PSB_PAD_UP))
    {
      myservo_1.write(66);
      myservo_2.write(65);
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
   else if(ps2x.Button(PSB_PAD_RIGHT))
   {
       myservo_1.write(65);
       myservo_2.write(90);
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
   else if(ps2x.Button(PSB_PAD_LEFT))
   {
     myservo_1.write(90);
     myservo_2.write(64);
     Serial.print("Left held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }

  else  if(ps2x.Button(PSB_PAD_DOWN))
    {
      myservo_1.write(115);
      myservo_2.write(116);
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }
  else
  {
       myservo_1.write(90);
       myservo_2.write(90);
       myservo_3.write(90);
  }
    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState())
    {        //will be TRUE if any button changes state (on to off, or off to on)

    }
       if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
        /*武器系统*/
    /*if(ps2x.Button(PSB_TRIANGLE))
    {

    }       */
    if(ps2x./*New*/Button/*State*/(PSB_CROSS))
    {                                                         //will be TRUE if button was JUST pressed OR released
       myservo_3.write(45);
      Serial.println("X just changed");
    }
    if(ps2x.Button(PSB_CIRCLE))
    {
       myservo_3.write(135);
      Serial.println("Circle just pressed");
    }
    /*else
    {
      myservo_3.write(90);
    }*/

    /*if(ps2x.ButtonReleased(PSB_SQUARE))
    {//will be TRUE if button was JUST released
      digitalWrite(IN3,LOW);
      Serial.println("Square just released");
    } */
    //运动操作
 int RY=ps2x.Analog(PSS_RY),LY=ps2x.Analog(PSS_LY),RX=ps2x.Analog(PSS_RX),LX=ps2x.Analog(PSS_LX)/*,pwm_lq,pwm_lh,pwm_rq,pwm_rh*/;
    if(ps2x.Button(PSB_L1) && !(ps2x.Button(PSB_R1)))
    {
        if(LY==127)   //左电机情况
        {
        myservo_1.write(90);
        }
        if(ps2x.Analog(PSS_LY)>=0&&ps2x.Analog(PSS_LY)<127) //如果左遥杆向正前方摇动
        {//前进
          myservo_1.write(map(ps2x.Analog(PSS_LY),127,0,85,65));
        }
        if(ps2x.Analog(PSS_LY)>127&&ps2x.Analog(PSS_LY)<=255) //如果左遥杆向正后方摇动
        {//后退
          myservo_1.write(map(ps2x.Analog(PSS_LY),127,255,100,125 ));
        }

        if(RY==127)   //右电机情况
        {
        myservo_2.write(90);
        }
        if(ps2x.Analog(PSS_RY)>=0&&ps2x.Analog(PSS_RY)<127) //如果右遥杆向正前方摇动
        {//前进
          myservo_2.write(map(ps2x.Analog(PSS_RY),127,0,85,65));
        }
        if(ps2x.Analog(PSS_RY)>127&&ps2x.Analog(PSS_RY)<=255) //如果右遥杆向正后方摇动
        {//后退
          myservo_2.write(map(ps2x.Analog(PSS_RY),127,255,100,121));
        }

      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC);
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
    }
    if(ps2x.Button(PSB_L1) && ps2x.Button(PSB_R1))
    {
      if(RY==127)   //右电机情况
      {
      myservo_3.write(90);
      }
      if(ps2x.Analog(PSS_RY)>=0&&ps2x.Analog(PSS_RY)<127) //如果右遥杆向正前方摇动
      {//前进
        myservo_3.write(map(ps2x.Analog(PSS_RY),127,0,90,45));
      }
      if(ps2x.Analog(PSS_RY)>127&&ps2x.Analog(PSS_RY)<=255) //如果右遥杆向正后方摇动
      {//后退
        myservo_3.write(map(ps2x.Analog(PSS_RY),127,255,90,135));
      }
        Serial.println(ps2x.Analog(PSS_RY), DEC);
    }
   }

     delay(50);
  }

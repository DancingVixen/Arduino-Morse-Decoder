/*
  Program to decode morse code inputted trough a push button or key. The schematic attached has an Status LED
  and a buzzer. Both of these are optional. Code written by RF-Fox[KG3FOX]

 Pinout:
 *  
 *  Digital pin 2: lead 1 of button
 *  Digital pin 4: LED positive
 *  GND: Button lead 2
 *  GND: LED Negative
 */

unsigned long signal_len,t1,t2;   //Button press time
int inputPin = 2;                 //Push button input pin
int ledPin = 4;                   //LED feedback pin
String code = "";                 //Alphabet storage string

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP); //Internal resistor used to keep circuit simple
  pinMode(ledPin,OUTPUT);
}

void loop()
{
NextDotDash:
  while (digitalRead(inputPin) == HIGH) {}
  t1 = millis();                            //Time button pressed
  digitalWrite(ledPin, HIGH);               //Turns the LED on when the button is pressed
  while (digitalRead(inputPin) == LOW) {}
  t2 = millis();                            //Time button released
  digitalWrite(ledPin, LOW);                //Turnd LED off when the button is released
  signal_len = t2 - t1;                     //Time button is pressed
  if (signal_len > 50)                      //Subtracts slight offset of button debouncing
  {
    code += readio();                       //Detects dot or dash
  }
  while ((millis() - t2) < 500)           //If button press greater than 0.5s go to the next alphabet
  {     
    if (digitalRead(inputPin) == LOW)
    {
      goto NextDotDash;
    }
  }
  convertor();                          //Deciphers dots and dashes to plaintext
}

char readio()
{
  if (signal_len < 250 && signal_len > 50)
  {
    return '.';                        //If the button is pressed for less than 0.250seconds, it is a dot
  }
  else if (signal_len > 250)           //0.250 second change is about 8 word per minute, calculate and change this to your desired speed
  {
    return '-';                        //If the button is pressed for more than 0.250seconds, it is a dash
  }
}

void convertor()
{
  static String letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
                            };
  
  static String numbers[] = {".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", "E"
                            };
        
  int i = 0;
  if (code == ".-.-.-")
  {
    Serial.print(".");        //Period
  }

   if (code == "--..--")
  {
    Serial.print(",");        //comma
  }

 if (code == "..--..")
  {
    Serial.print("?");        //Question mark
  }
  
    if (code == ".----")
  {
    Serial.print("1");        //Number 1
  }

   if (code == "..---")
  {
    Serial.print("2");        //Number 2
  }

   if (code == "...--")
  {
    Serial.print("3");        //Number 3
  }
   
   if (code == "....-")
  {
    Serial.print("4");        //Number 4
  }

   if (code == ".....")
  {
    Serial.print("5");        //Number 5
  }

   if (code == "-....")
  {
    Serial.print("6");        //Number 6
  }

   if (code == "--...")
  {
    Serial.print("7");        //Number 7
  }

   if (code == "---..")
  {
    Serial.print("8");        //Number 8
  }

   if (code == "----.")
  {
    Serial.print("9");        //Number 9
  }

   if (code == "-----")
  {
    Serial.print("0");        //Number 0
  }
  
  else
  {
    while (letters[i] != "E")  //Compares input code with alphabet array
    {
      if (letters[i] == code)
      {
        Serial.print(char('A' + i));
        break;
      }
      i++;
    }
   // if (letters[i] == "E")
   // {
    //  Serial.println();  //Future error when no letters/numbers are detected
   // }
  }
  code = "";                            //reset code to blank string
}
//Code written by RF-Fox[KG3FOX]

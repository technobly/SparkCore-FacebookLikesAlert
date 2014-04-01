/*
 * SPARK MAKER KIT - FACEBOOK LIKES ALERT
 * =========================================================
 * Copy this into a new application at:
 * https://www.spark.io/build and go nuts!
 * !! WIRING info on line 15 below !!
 * ---------------------------------------------------------
 *  Author: BDub
 * Website: http://technobly.com
 *    Date: Mar 31st 2014
 * =========================================================
 * https://github.com/technobly/SparkCore-FacebookLikesAlert
 * 
 *
 * WIRING is so simple
 * -----------------------------
 * SERVO             SPARK CORE
 * Brown or Black  - GND
 * Red             - VIN (5V)
 * Orange or White - A7
 * -----------------------------
 */

/* ============================= INCLUDES ================================== */
#include "application.h"

/* ======== STUFF YOU CAN CHANGE AFTER YOU UNDERSTAND WHAT IT DOES ========= */
#define DEBUG_SERIAL false
#define SKIP_CHARS 512 // the number of characters to skip buffering
#define HOST "graph.facebook.com" // all Facebook pages start with this domain
#define PATH "/sparkdevices" // change this to whatever page you want
#define SERVO_DEG_0 39 // servo degree value to point to digit 0
#define SERVO_DEG_9 79 // servo degree value to point to digit 9
#define BUFFER_SIZE_MAX 1024 // size of our save buffer (keep it small)

/* ============================= PROTOTYPES ================================ */
char * http_get(char const * hostname, String path);

/* ============================= HTTP ====================================== */
TCPClient client;
char buffer[BUFFER_SIZE_MAX];

char * http_get(char const * hostname, String path) {

  int i = 0;
  int j = 0;
  int k = 0;
  bool printOnce = false;

  if (client.connect(hostname, 80)) {
    client.print("GET ");
    client.print(path);
    client.println(" HTTP/1.1");
    client.print("HOST: ");
    client.println(hostname);
    client.println("Connection: close");
    client.println();
    client.flush();
  } else {
    if(DEBUG_SERIAL) Serial.println("\r\n\r\nConnection Failed!");
    client.flush();
    client.stop();
    return NULL;
  }

  // wait 5 seconds or less for the host to respond
  uint32_t startTime = millis();
  while(!client.available() && (millis() - startTime) < 5000);

  if(DEBUG_SERIAL) Serial.println("\r\n\r\nREADING HOST DATA......");
  uint32_t lastRead = millis();
  // If the host doesn't close it's connection, we'll timeout in 10 seconds.
  while (client.connected() && (millis() - lastRead) < 10000) {
    while (client.available()) {
      char c = client.read();
      /*
      if(DEBUG_SERIAL) {
        Serial.print(c);
        if(i++ > 100) {
          delay(5);
          i = 0;
        }
      }
      */
      if(c == -1) {
        Serial.print("\r\n\r\nERROR......\r\n\r\n");
        client.flush();
        client.stop();
      }
      if(j++ >= SKIP_CHARS) { // don't buffer the first X bytes to save memory
        if(DEBUG_SERIAL && !printOnce) {
          Serial.print("\r\n\r\nSAVING......\r\n\r\n");
          printOnce = true;
        }
        buffer[k++] = c; // save character to buffer
        Serial.print(c);
        delayMicroseconds(100);
      	if(k >= BUFFER_SIZE_MAX) { // if we reach the end of our buffer, just bail.
          Serial.print("\r\n\r\nOUT OF BUFFER SPACE......\r\n\r\n");
          client.flush();
      	  client.stop();
      	}
      }
      // as long as we're reading data, reset the lastRead time.
      lastRead = millis();
    } // END while(client.available())
  } // END while(client.connected())
  
  client.flush();
  client.stop();
  
  if(DEBUG_SERIAL) {
    Serial.print("\r\nCHARACTERS RECEIVED: ");
    Serial.println(SKIP_CHARS + k);
  }

  return buffer;
}

/* ============================= APPLICATION.cpp =========================== */
char *ptrStr;
char *ptrEnd;
char result[21];
uint32_t new_likes_val = 0;
uint32_t old_likes_val = 0;
uint32_t lastTime;
int blinkCount;
bool ledState = true;
Servo likeservo;
uint8_t servoPos = 0;
bool achievementUnlocked = false; // global flag for triggering an action

void setup() {
  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH);
  likeservo.attach(A7);  // attaches the servo on the A7 pin to the servo object
  likeservo.write(0); // start with servo fully clockwise (down pushup)
  if(DEBUG_SERIAL) { 
    Serial.begin(115200);
    while (!Serial.available()) { // After Core D7 LED turns on, open serial monitor and press enter!
      SPARK_WLAN_Loop();
    }
  }

  // Force FB to be polled immediately on start
  lastTime = millis() + 500UL;
  blinkCount = 19;
}

void loop() {
  if(millis() - lastTime > 500UL) {
    lastTime = millis();
    blinkCount++; // time waits for no one!
    if(blinkCount >= 20 && !achievementUnlocked) { // don't poll FB during push ups
      blinkCount = 0;
      uint32_t start = millis();
      char * response = http_get(HOST, PATH);
      if(DEBUG_SERIAL) {
        Serial.print("Time: ");
        Serial.print(millis()-start);
        Serial.println(" ms\r\n");
      }
      ptrStr = strstr(response, "\"likes\":");  // search for string ["likes": ] in response
      if(ptrStr != NULL) // if successful then ptrStr now points at ["likes": ]
      {
        ptrStr += 8; //advance pointer to likes number.
        int x = 0;
        while(x<20 && *ptrStr != ',') {
          result[x++] = *ptrStr++;
        }
        result[x] = '\0';
        new_likes_val = strtol(result,&ptrEnd,10); // convert string to long int if you need a working number
        if(DEBUG_SERIAL) {
          Serial.print("Found likes: ");
          Serial.println(new_likes_val);
        }

        // every time is goes up from the last known highest point,
        // an achievement is unlocked!  This also prevents griefing
        // since it would be very easy to unlike and like over and over.
        if(new_likes_val > old_likes_val) {
          if(DEBUG_SERIAL) Serial.println("Achievement Unlocked!");
          old_likes_val = new_likes_val;
          achievementUnlocked = true;
        }
      }
      else
      {
        if(DEBUG_SERIAL) Serial.println("Likes not found!\n");  // `strstr` returns NULL if search string not found
      }
      // END if(ptrStr != NULL)
    } 
    else { // toggle the led while we wait for 10 second mark
      ledState = !ledState;
      digitalWrite(D7, ledState);
    } // END if(blinkCount >= 20 && !achievementUnlocked)
  } // END if(millis() - lastTime > 500UL)

  // If our 'likes' token was matched...
  if(achievementUnlocked) {
    achievementUnlocked = false;

    // Do something special with our servo and the result ;-)
    // This will make our one finger pushup guy point to 
    // each digit in the 'likes' value every 700ms, delay for 
    // 2 seconds, and then repeat that 3 more times just to 
    // make sure you see it.  Then he'll return to a down position.
    uint8_t x;
    uint8_t y = 0;
    while( y++ < 4 ) {
      x = 0; // reset result[] index to point to the first digit
      while( x<20 && result[x] != '\0' ) {
        // scale the current 'likes' digit (0-9) to servoPos's range
        servoPos = map(result[x]-'0',0,9,SERVO_DEG_0,SERVO_DEG_9);
        // tell servo to go to position in variable 'servoPos'
        if(x!=0 && result[x] == result[x-1]) {
          // if this digit is the same as the last one, 
          // quickly move the pointer down and back up
          // to help indicate a new digit in the 'likes' number.
          likeservo.write(map(result[x]-'2',0,9,SERVO_DEG_0,SERVO_DEG_9));
          delay(200);
          likeservo.write(servoPos);
          delay(500);
        }
        else {
          // else just go to the next 'likes' number in the sequence.
          likeservo.write(servoPos);
          delay(700);
        }
        /*
        if(DEBUG_SERIAL) {
          Serial.print(result[x]-'0');
          Serial.print(" ");
          Serial.println(servoPos);
        }
        */
        x++; // increment result[] index to point to the next digit
      }
      delay(2000);
    }
    likeservo.write(0); // Return to down position

  } // END if(achievementUnlocked)
}
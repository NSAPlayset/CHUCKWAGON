#include <Wire.h>

#define MAX_MSG_SIZE 32

char msg[MAX_MSG_SIZE];
int done_copy_pin = 2;
int msg_ready_pin = 3;

volatile bool done_copy = true;

void setup()
{
  Wire.begin(0x42);
  Wire.onReceive(receive_i2c);
  Wire.onRequest(request_i2c);

  Serial.begin(9600);

  /* Setup the GPIO to the BBB to indicate when a msg is ready */
  pinMode (msg_ready_pin, OUTPUT);
  clear_bbb_signal ();
}

void loop()
{
  delay(100);
}

void signal_bbb ()
{
  digitalWrite (msg_ready_pin, HIGH);
}

void clear_bbb_signal ()
{
  digitalWrite (msg_ready_pin, LOW);
}

void receive_i2c(int num_bytes)
{


  memset (msg, sizeof(msg), 0);

  Serial.println("Num bytes");
  Serial.print(num_bytes);
  Serial.println("");

  Serial.println("Receiving msg:");
  for (int x = 0; x < MAX_MSG_SIZE && x < num_bytes; x++)
    {
      msg[x] = (char) Wire.read();
      Serial.print(msg[x]);
    }

  done_copy = false;

  Serial.print("\n");

  signal_bbb ();


}

void request_i2c ()
{
  Serial.print ("Received request");
  Wire.write (msg);
  done_copy = true;
  clear_bbb_signal ();
}

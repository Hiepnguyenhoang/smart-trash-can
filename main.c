#include <Servo.h>

#define close_angle 0
#define open_angle 110

int trig_pin = 13;
int echo_pin = 12;
int servo_pin = 11;
long _time, dist;
Servo myservo;

unsigned long previous_Millis = 0;
unsigned char auto_Trigger = 0;
unsigned long auto_Millis = 0;

void setup()
{
    Serial.begin(9600);
    myservo.attach(servo_pin);
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
    myservo.write(0);
}

int calculate_distance()
{
    long sum = 0;
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(trig_pin, LOW);
        delayMicroseconds(2);
        digitalWrite(trig_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig_pin, LOW);
        _time = pulseIn(echo_pin, HIGH, 17400);
        sum += _time;
    }
    return (int((sum / 3)/58));
}

void loop()
{
    if(millis() - previous_Millis >= 100) // ms
    {
        previous_Millis = millis();
        dist = calculate_distance();
        Serial.print(dist);
        if(dist < 25) 
        {
            auto_Trigger = 1;
            auto_Millis = millis();
            myservo.write(open_angle);
        }
    }
    if(millis() - auto_Millis >= 3000 && auto_Trigger == 1) //ms
    {
        auto_Trigger = 0;
        myservo.write(close_angle);
    }
}

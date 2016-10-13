#include "mbed.h"
#include "rtos.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>
#include "BufferedSerial.h"
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
 
ros::NodeHandle nh;
/*
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

std_msgs::String banana_msg;
ros::Publisher banana("banana", &banana_msg);

std_msgs::String wulala_msg;
ros::Publisher wulala("wulala", &wulala_msg);
*/
geometry_msgs::Vector3 feedback_wheel_angularVel_msg;
geometry_msgs::Vector3 cmd_wheel_angularVel_msg;
geometry_msgs::Vector3 cmd_wheel_PWM_msg;
geometry_msgs::Twist feedback_vel_msg;
ros::Publisher cmd_wheel_angularVel_pub("/andbot/cmd_wheel_angularVel", &cmd_wheel_angularVel_msg);
ros::Publisher cmd_wheel_PWM_pub("/andbot/cmd_wheel_PWM", &cmd_wheel_PWM_msg);
ros::Publisher feedback_wheel_angularVel_pub("/andbot/feedback_wheel_angularVel", &feedback_wheel_angularVel_msg);
ros::Publisher feedback_vel_pub("/andbot/feedback_vel", &feedback_vel_msg);

DigitalOut myled(LED1);
Serial Serial1(PA_9, PA_10);
Serial Serial3(PC_10, PC_11);
Serial Serial4(PA_0, PA_1);
Ticker toggle_led_ticker;

int kerker = 0XAABB;
int wahaha = 0XCCDD;
int lalala = 0XEEFF;

char hello[13] = "hello world!";
char bababanana[11] = "bababanana";
char wow[11] = "wawawanana";

uint8_t high_byte (int in)
{
    uint8_t out = in >> 8;
    return out;
    }

uint8_t low_byte (int in)
{
    uint8_t out = in & 0X00FF;
    return out;
    }
 

void messageCb(const std_msgs::Empty& toggle_msg)
{
    myled = !myled;   // blink the led
    Serial1.putc('C');
}
 
ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb);

uint8_t haha = high_byte(kerker);
uint8_t baba = low_byte(kerker);
uint8_t lala = high_byte(wahaha);
uint8_t kaka = low_byte(wahaha);
uint8_t coca = high_byte(lalala);
uint8_t cola = low_byte(lalala);
 
void toggle_led() 
{
/*    Serial1.putc(haha);
    Serial1.putc(baba);
    Serial1.putc(lala);
    Serial1.putc(kaka);
    Serial1.putc(coca);
    Serial1.putc(cola);
    */
}


void blink(void const *n) 
{
	cmd_wheel_angularVel_pub.publish( &cmd_wheel_angularVel_msg ); 
} 

void blink1(void const *n)
{
	cmd_wheel_PWM_pub.publish( &cmd_wheel_PWM_msg );
}

void blink2(void const *n)
{
	feedback_wheel_angularVel_pub.publish( &feedback_wheel_angularVel_msg ); 
}

void blink3(void const *n)
{
	feedback_vel_pub.publish( &feedback_vel_msg ); 
}


void serial_read()
{
      char buffer[5];
      if(Serial1.readable() && (Serial1.getc() == '{' )){
	    Serial1.gets(buffer,5);
	    Serial3.putc(buffer[0]);
            Serial3.putc(buffer[1]);
            Serial3.putc(buffer[2]);
            Serial3.putc(buffer[3]);
      }	
}

int main() {
    nh.getHardware()->setBaud(1000000);
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(feedback_wheel_angularVel_pub);
    nh.advertise(cmd_wheel_angularVel_pub);    
    nh.advertise(cmd_wheel_PWM_pub);
    nh.advertise(feedback_vel_pub);
    //toggle_led_ticker.attach(&toggle_led, 0.02);
    Serial1.baud(1000000);
    Serial3.baud(1000000);
    Serial4.baud(1000000);
    RtosTimer led_1_timer(blink, osTimerPeriodic, (void *)0);
    RtosTimer led_2_timer(blink1, osTimerPeriodic, (void *)0);
    RtosTimer led_3_timer(blink2, osTimerPeriodic, (void *)0);
    RtosTimer led_4_timer(blink3, osTimerPeriodic, (void *)0);
    led_1_timer.start(20);
    led_2_timer.start(50);
    led_3_timer.start(50);
    led_4_timer.start(50);
    while (1) {
	serial_read();
        nh.spinOnce();
    }
}

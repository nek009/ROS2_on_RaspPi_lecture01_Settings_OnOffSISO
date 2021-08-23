#include <pigpiod_if2.h>
#include <iostream>
#include <unistd.h>

void callback_push_switch(int pi, unsigned user_gpio, unsigned level, uint32_t tick);

int main(int argc, char* argv[]){
  // Initialize
  int pi = pigpio_start(NULL,NULL);
  if(pi < 0){
    std::cerr << "Error:pigpio_start" << std::endl;
    return -1;
  }

  // Set GPIO21 OUTPUT
  set_mode(pi, 21, PI_OUTPUT);
  // Set GPIO26 INPUT
  set_mode(pi, 26, PI_INPUT);
  // Set callback function for GPIO26
  callback(pi, 26, EITHER_EDGE, callback_push_switch);

  // Process callback function during wait 10 sec.
  sleep(10);

  pigpio_stop(pi);
  return 0;
}

void callback_push_switch(int pi, unsigned user_gpio, unsigned level, uint32_t tick){
  std::cout << "gpio:" << user_gpio << ":level:" << level << ":tick:" << tick << std::endl;
  gpio_write(pi,21,level);
}

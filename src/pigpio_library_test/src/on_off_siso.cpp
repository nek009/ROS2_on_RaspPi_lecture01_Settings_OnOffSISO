#include <pigpiod_if2.h>
#include <iostream>
#include <unistd.h>

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

  for(int i=0 ; i<10 ; i++){
    int input = gpio_read(pi,26);
    gpio_write(pi,21,input);
    sleep(1);
  }

  pigpio_stop(pi);
  return 0;
}

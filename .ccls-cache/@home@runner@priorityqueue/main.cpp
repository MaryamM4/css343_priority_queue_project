#include "CovidPriorityQueue.h"

#include <iostream>

int main() {
  COVIDPriorityQueue cpQueue;

  cpQueue.initFromFile("input.txt");
  cpQueue.setAvailableVaccines(4);
  cpQueue.displayAvailable();

  std::cout << "\nEND.\n" << std::endl;
  return 0;
}
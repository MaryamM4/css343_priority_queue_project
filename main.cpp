#include "CovidPriorityQueue.h"

#include <iostream>

int main() {
  COVIDPriorityQueue cpQueue = COVIDPriorityQueue();

  cpQueue.initFromFile("input.txt");
  cpQueue.setAvailableVaccines(4);
  cpQueue.displayAvailable();

  std::cout << "\nEND.\n" << std::endl;
  return 0;
}
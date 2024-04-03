/**
 * COVIDPriorityQueue (Source file)
 * CSS 343 HW 1: Priority Queue
 * ==============================
 * Maintain a priority queue for covid vaccination that
 * is determined based on the following:
 *
 * - Age of the patient (Older patients get higher priority)-
 *   patients under 5 are not enlisted into the queue.
 *
 * - Existing illnesses (you can assume this is a binary field
 *   that has the highest priority)
 * ==============================
 * Implemented by Maryam M, 2024
 */

#include "CovidPriorityQueue.h"

#include <algorithm> // For remove_if function (to remove whitespace)
#include <iostream>
#include <sstream>
#include <stack>

COVIDPriorityQueue::COVIDPriorityQueue() {}

COVIDPriorityQueue::~COVIDPriorityQueue() {
  while (!vaccineQueue.empty()) {
    vaccineQueue.pop();
  }
}

/**
 * Displays patients by priority,
 * but only up to the number of avaiable vaccines.
 */
void COVIDPriorityQueue::displayAvailable() {
  std::stack<CovidPatient *> patientStack;

  int i = 0;
  while (i < availableVaccines && !vaccineQueue.empty()) {
    i++;
    patientStack.push(vaccineQueue.top());
    std::cout << i << ": " << *(vaccineQueue.top()) << std::endl;

    vaccineQueue.pop();
  }

  // Return stack contents to queue
  while (!patientStack.empty()) {
    vaccineQueue.push(patientStack.top());
    patientStack.pop();
  }
}

/**
 * Initilizes queue based on file input.
 * Only adds patients that are eligible for the vaccine.
 *
 * File line format should be the following:
 * name (string), age (string), has precondition (string, yes/no)
 *
 * @param  string representing filename.
 * @return false if file could not be opened, or failed to read.
 *         Also return false if no patients were added to the queue.
 *         Otherwise return true.
 */
bool COVIDPriorityQueue::initFromFile(std::string filename) {
  std::fstream file;
  file.open(filename);

  if (file.is_open()) {
    return initFromFile(file);

  } else {
    return false;
  }
}

/**
 * Initilizes queue based on file input.
 * Only adds patients that are eligible for the vaccine.
 *
 * File line format should be the following:
 * name (string), age (string), has precondition (string, yes/no)
 *
 * @param  Input file fstream.
 * @return false if file could not be opened, or failed to read.
 *         Also return false if no patients were added to the queue.
 *         Otherwise return true.
 */
bool COVIDPriorityQueue::initFromFile(std::fstream &infile) {
  std::string currLine;
  while (std::getline(infile, currLine)) {

    CovidPatient *patient = strToPatient(currLine);

    if (patient != nullptr && isEligibleForVaccine(patient)) {
      vaccineQueue.push(patient);
    }
  }

  return (vaccineQueue.size() > 0);
}

/**
 * @param   String in the following format:
 *          Name (string), Age (int), Precondition Illnesses (string: Yes/No)
 * @returns Pointer to patient with the given data.
 *          On invalid input, returns nullptr.
 */
CovidPatient *COVIDPriorityQueue::strToPatient(std::string patientInfo) {
  std::string name;
  std::string ageStr;
  std::string hasPreconditionIllness;

  std::istringstream iss(patientInfo);

  if (std::getline(iss, name, ',') && std::getline(iss, ageStr, ',') &&
      std::getline(iss, hasPreconditionIllness)) {

    int age = std::stoi(ageStr);
    bool hasPrecondition = false;

    // Remove whitespaces and convert to lowercase
    normalizeStr(hasPreconditionIllness);

    if (hasPreconditionIllness == "yes") {
      hasPrecondition = true;

    } else if (hasPreconditionIllness != "no") {
      // If the condition field is neither "yes" or "no", the input is invalid.
      std::cout << "Invalid condition: " << hasPreconditionIllness << std::endl;
      return nullptr;
    }

    CovidPatient *patient = new CovidPatient(name, age, hasPrecondition);
    return patient;
  }
  return nullptr;
}

/**
 * Determines patient is eligible for the covid vaccine
 * by the following:
 * - [Age]: Must be >= 5 years old.
 *
 * @return true if the patient is eligible, false otherwise.
 */
bool COVIDPriorityQueue::isEligibleForVaccine(CovidPatient *patient) {
  return (patient->age >= 5);
}

/**
 * Removes the surrounding whitespaces in a string,
 * and converts it to lowercase.
 *
 * References:
 * - https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
 * - https://www.geeksforgeeks.org/conversion-
 *   whole-string-uppercase-lowercase-using-stl-c/
 */
void COVIDPriorityQueue::normalizeStr(std::string &str) {
  auto newEnd = remove_if(str.begin(), str.end(), isspace);
  str.erase(newEnd, str.end());

  transform(str.begin(), str.end(), str.begin(), ::tolower);
}

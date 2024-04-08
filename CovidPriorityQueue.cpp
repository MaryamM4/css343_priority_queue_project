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

COVIDPriorityQueue::~COVIDPriorityQueue() {
  while (!vaccineQueue.empty()) {
    CovidPatient *Patient = vaccineQueue.top();
    // std::cout << "Delete CovidPriorityQ patient: " << *Patient << std::endl;
    
    delete(Patient);
    Patient = nullptr;
    
    vaccineQueue.pop();
  }

  //std::cout << "Delete CovidPriorityQ" << std::endl;
}

/**
 * Displays patients by priority,
 * but only up to the number of avaiable vaccines.
 */
void COVIDPriorityQueue::displayAvailable() {
  std::stack<CovidPatient *> PatientStack;

  int PatientNum = 0;
  while (PatientNum < availableVaccines && !vaccineQueue.empty()) {
    PatientNum++;
    PatientStack.push(vaccineQueue.top());
    std::cout << PatientNum << ": " << *(vaccineQueue.top()) << std::endl;

    vaccineQueue.pop();
  }

  // Return stack contents to queue
  while (!PatientStack.empty()) {
    vaccineQueue.push(PatientStack.top());
    PatientStack.pop();
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
bool COVIDPriorityQueue::initFromFile(const std::string &filename) {
  std::fstream File(filename);

  if (File.is_open()) {
    return initFromFile(File);
  } 

  // Failed to open file. 
  return false;
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
  std::string CurrLine;

  while (std::getline(infile, CurrLine)) {
    CovidPatient *Patient = strToPatient(CurrLine);
    
    if (Patient != nullptr && isEligibleForVaccine(Patient)) {
      vaccineQueue.push(Patient);
    }
  }

  return (!vaccineQueue.empty());
}

/**
 * @param   String in the following format:
 *          Name (string), Age (int), Precondition Illnesses (string: Yes/No)
 * @returns Pointer to patient with the given data.
 *          On invalid input, returns nullptr.
 */
CovidPatient *COVIDPriorityQueue::strToPatient(const std::string &patientInfo) {
  std::string Name;
  std::string AgeStr;
  std::string HasPreconditionIllness;

  std::istringstream Iss(patientInfo);

  if (std::getline(Iss, Name, ',') && std::getline(Iss, AgeStr, ',') &&
      std::getline(Iss, HasPreconditionIllness)) {

    const int Age = std::stoi(AgeStr);
    int HasPrecondition = 0;

    // Remove whitespaces and convert to lowercase
    normalizeStr(HasPreconditionIllness);

    if (HasPreconditionIllness == "yes") {
      HasPrecondition = 1;

    } else if (HasPreconditionIllness != "no") {
      // If the condition field is neither "yes" or "no", the input is invalid.
      std::cout << "Invalid condition: " << HasPreconditionIllness << std::endl;
      return nullptr;
    }

    CovidPatient *Patient = new CovidPatient(Name, Age, HasPrecondition);
    return Patient;
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
bool COVIDPriorityQueue::isEligibleForVaccine(const CovidPatient *patient) const {
  return (patient->getAge() >= MinEligibleAge);
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
  auto NewEnd = remove_if(str.begin(), str.end(), isspace);
  str.erase(NewEnd, str.end());

  transform(str.begin(), str.end(), str.begin(), ::tolower);
}

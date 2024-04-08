/**
 * COVIDPriorityQueue (Header file)
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


#ifndef COVID_PRIORITY_QUEUE_H
#define COVID_PRIORITY_QUEUE_H

#include "CovidPatient.h"
#include <fstream> // For reading files
#include <functional> // for std::greater
#include <memory> // For unique_ptr & make_unique
#include <queue>

class COVIDPriorityQueue {
public:
  COVIDPriorityQueue() : availableVaccines(0) {}
  explicit COVIDPriorityQueue(int numVaccines) : availableVaccines(numVaccines) {}
  ~COVIDPriorityQueue();

  bool empty() const;
  template <typename ItemType> void push(const ItemType &newEntry);
  void pop();
  template <typename ItemType> ItemType &top();

  bool initFromFile(const std::string &filename);
  bool initFromFile(std::fstream &infile);

  // Returns False if under 5.
  bool isEligibleForVaccine(const CovidPatient *patient) const;

  void displayAvailable(); // RENAME

  bool setAvailableVaccines(int num) {
    if (num > 0) {
      availableVaccines = num;
      return true;
    }
    return false;
  }

  int getAvailableVaccines() const { return availableVaccines; }

private:
  const int MinEligibleAge = 5;

std::priority_queue<CovidPatient *, std::vector<CovidPatient *>,
                ComparePatient>
vaccineQueue;

  int availableVaccines; // Number of available vaccines.

  // ==[HELPER METHODS]==
  // Returns patient based on single string. String format should be:
  // Name (string), Age (int), Precondition Illnesses (string: Yes/No)
  static CovidPatient *strToPatient(const std::string &patientInfo);

  // Helper function: Removes whitespaces and converts string to lowercase
  static void normalizeStr(std::string &str);
};

#endif // COVID_PRIORITY_QUEUE_H
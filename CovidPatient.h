/**
 * Patient (Header file)
 * =====================
 * Stores patient name, age, and existence of conditions.
 *
 * Compares patients by the following:
 * - Existing illnesses
 *   (Assume this is a binary field that has the highest priority)
 * - Age: Older patients have greater priority.
 * -
 */

#pragma once

#include <string>

class CovidPatient {

public:
  CovidPatient(std::string name, int age, int hadCondition)
      : name(name), age(age), precondition_illnesses(hadCondition) {}

  const std::string name;
  const int age;
  const int precondition_illnesses; // 0 for none, 1 for yes.
  // Int (instead of bool) for comparison reasons.

  // Overloaded operators
  friend std::ostream &operator<<(std::ostream &os,
                                  const CovidPatient &patient); // Name only
};

/**
 * Compares the lhs and rhs patient.
 *
 * Prioritizes the following:
 * - [Existing illnesses]
 *    (Assume this is a binary field that has the highest priority)
 * - [Age]: Older patients have greater priority.
 *
 * @return true if rhs patient has greater priority,
 *         otherwise return false.
 */
struct ComparePatient {
  bool operator()(const CovidPatient *lhs, const CovidPatient *rhs) const {
    if (rhs->precondition_illnesses > lhs->precondition_illnesses) {
      return true;

    } else if (rhs->precondition_illnesses < lhs->precondition_illnesses) {
      return false;
    }

    return (rhs->age > lhs->age);
  }
};
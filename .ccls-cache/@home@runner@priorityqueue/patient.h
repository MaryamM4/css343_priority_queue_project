/**
 * Patient (Header file)
 * =====================
 * Stores patient name, age, and conditions.
 *
 * Determines eleigibility for a vaccince by the following:
 * - Age: Must be over 5.
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
  CovidPatient(std::string name, int age, std::string conditions)
      : name(name), age(age), conditions(conditions) {}

  const std::string name;
  const int age;
  const std::string conditions; // Existing conditions

  // Returns False if under 5.
  bool isEligible();

  // Overloaded operators
  bool operator<(const CovidPatient &rhs) const;
  bool operator>(const CovidPatient &rhs) const;
  bool operator==(const CovidPatient &rhs) const;
  bool operator<=(const CovidPatient &rhs) const;
  bool operator>=(const CovidPatient &rhs) const;
};
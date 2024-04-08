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


#ifndef COVID_PATIENT_H
#define COVID_PATIENT_H

#include <string>

class CovidPatient {

public:
  CovidPatient(std::string name, int age, int hadCondition)
      : name(std::move(name)), age(age), precondition_illnesses(hadCondition) {}

  // Accessor methods
  std::string getName() const { return name; }
  int getAge() const { return age; }
  int getPreconditionStatus() const { return precondition_illnesses; }

  // Overloaded operator
  friend std::ostream &operator<<(std::ostream &outStream,
                                  const CovidPatient &patient); 

private:
  const std::string name;
  const int age;

  // Int (instead of bool) for comparison reasons.
  const int precondition_illnesses; // 0 for none, 1 for yes.
  
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
    if (lhs == nullptr || rhs == nullptr) {
      return false; 
    }

    const int LCondition = lhs->getPreconditionStatus();
    const int RCondition = rhs->getPreconditionStatus();

    // Prioritize is patient with a condition.
    if (RCondition > LCondition) {
      return true;
    } 
    
    if (RCondition < LCondition) {
      return false;
    }

    // If both have the same precondition status, compare by age. 
    return (rhs->getAge() > lhs->getAge());
  }
};

#endif // COVID_PATIENT_H
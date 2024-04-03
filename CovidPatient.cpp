#include "CovidPatient.h"

/**
 * Overloaded << operator only returns patient name.
 */
std::ostream &operator<<(std::ostream &os, const CovidPatient &patient) {
  os << patient.name;
  return os;
}
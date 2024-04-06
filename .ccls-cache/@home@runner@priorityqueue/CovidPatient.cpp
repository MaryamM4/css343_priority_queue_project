#include "CovidPatient.h"

/**
 * Overloaded << operator only returns patient name.
 */
std::ostream &operator<<(std::ostream &outStream, const CovidPatient &patient) {
    outStream << patient.name;
  return outStream;
}
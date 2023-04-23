#ifndef IDTYPE_HPP_
#define IDTYPE_HPP_

#include <string>

using std::string;

class IDType {
   public:
    /**
     * @brief Obtain the corresponding type of vehicle identification code or employee identification code
     *
     */
    virtual string getIdentifier() = 0;
};

#endif  // IDTYPE_HPP_
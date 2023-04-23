#ifndef IDREADER_HPP_
#define IDREADER_HPP_

#include "../Config.hpp"
#include "../IDType/IDType.hpp"

class IDReader {
   public:
    IDReader() {}

    /**
     * @brief Read the content and judge whether the read is successful
     *
     * @return true
     * @return false
     */
    virtual bool Read() = 0;

    /**
     * @brief Update what is currently stored
     *
     */
    virtual string update(uint16_t opt = 0) = 0;

    /**
     * @brief Get employee/vehicle information that has recently entered the parking lot
     *
     * @return void*, which can be converted to any desired pointer type
     */
    virtual void* getLeast() = 0;

    /**
     * @brief List all elements, can be IDCard, Barcode and Number Plate
     *
     */
    virtual void showAllElement() = 0;

    virtual ~IDReader() = default;
};

#endif  // IDREADER_HPP_
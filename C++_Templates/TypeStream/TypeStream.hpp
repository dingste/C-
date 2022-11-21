#include <iostream>


#define SERIALIZE_START '{'
#define SERIALIZE_DELIMITER '_'
#define SERIALIZE_END '}'

 std::ostream& operator<<(std::ostream& out, const T_NAME& transmit) {
    out << transmit.signature << SERIALIZE_START
        << transmit.foo << SERIALIZE_DELIMITER
        << transmit.foo  << SERIALIZE_END;
    return out;
    }
    
    std::istream& operator>>(std::istream& in, T_NAME& transmit) {
    char singlechar;

    in >> singlechar;
    transmit.signature = (char) singlechar;
    in >> singlechar;
    if (singlechar == SERIALIZE_START) {
        in >> transmit.foo;
        in >> singlechar;
        if (singlechar == SERIALIZE_DELIMITER) {
            in >> transmit.foo;
            in >> singlechar;
            if (singlechar != SERIALIZE_END) {
                //deserializationAssert();
                //in.clear();
            }
        }
    }
    return in;
    } 

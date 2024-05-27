#include <iostream>
#include <string>

#include <climits> // for the UINT_MAX

int binaryString(const std::string& binary) {
    int result = 0;
    for (size_t i = 0; i < binary.size(); ++i) {
        result *= 2;
        if (binary[i] == '1') {
            result += 1;
        }
    }
    return result;
}

int hexChar(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

unsigned int hexString(const std::string& hex) {
    unsigned int result = 0;
    for (char c : hex) {
        int value = hexChar(c);
        if (value == -1) {
            std::cerr << "Error: Invalid hexadecimal character '" << c << "'" << std::endl;
            return UINT_MAX; 
        }
        if (result > (UINT_MAX / 16)) {
            std::cerr << "Error: Hexadecimal value is too large to convert" << std::endl;
            return UINT_MAX;
        }
        result = result * 16 + value;
    }
    return result;
}

int main() 
{  
    std::string smallBinary = "1";                    
    std::string middleBinary = "101010";              
    std::string fullBinary = "1111111111111111"; 

    std::string smallHex = "A";                      
    std::string middleHex = "1A2B";                  
    std::string fullHex = "FFFFFFFF";                

    std::cout << "Small binary (" << smallBinary << ") to int: " << binaryString(smallBinary) << std::endl;
    std::cout << "Middle binary (" << middleBinary << ") to int: " << binaryString(middleBinary) << std::endl;
    std::cout << "Full binary (" << fullBinary << ") to int: " << binaryString(fullBinary) << std::endl;

    std::cout << "Small hex (" << smallHex << ") to int: " << hexString(smallHex) << std::endl;
    std::cout << "Middle hex (" << middleHex << ") to int: " << hexString(middleHex) << std::endl;
    std::cout << "Full hex (" << fullHex << ") to int: " << hexString(fullHex) << std::endl;

    return 0;
}

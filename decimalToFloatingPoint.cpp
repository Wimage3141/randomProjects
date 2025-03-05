#include <iostream>
#include <string>
#include <cmath>
#include <bitset>
#include <algorithm>

using namespace std;

// Convert integer part to binary
string decimalToBinary(int d) {
    if (d == 0) return "0";
    string binary;
    while (d) {
        binary.push_back((d % 2) + '0');
        d /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

// Convert fractional part to binary
string fractionToBinary(string fraction) {
    fraction = "0." + fraction;
    double df = std::stod(fraction);
    string binaryFraction;
    int n = 64;  // 64-bit precision to avoid extra padding late

    while (n--) {
        df *= 2;
        if (df >= 1) {
            binaryFraction.push_back('1');
            df -= 1;
        } else {
            binaryFraction.push_back('0');
        }
    }
    return binaryFraction;
}

// Convert decimal to IEEE 754 32-bit floating-point representation
string convertToFP(double decimal) {
    if (decimal == 0.0) return "0" + string(8, '0') + string(23, '0'); // Special case for zero

    string signBit = (decimal < 0) ? "1" : "0";
    decimal = abs(decimal);

    int integerPart = static_cast<int>(decimal);
    double fractionalPart = decimal - integerPart;

    string intBinary = decimalToBinary(integerPart);
    string fracBinary = fractionToBinary(to_string(fractionalPart).substr(2)); // Remove "0."

    // Normalize the binary representation
    string normalized;
    int exponent;
    
    if (integerPart != 0) {
        exponent = intBinary.size() - 1;
        normalized = intBinary + fracBinary;
        normalized.erase(0, 1); // Remove leading 1 (implicit in IEEE 754)
    } else {
        // If no integer part, shift until first 1 appears in fraction part
        size_t firstOne = fracBinary.find('1');
        exponent = -static_cast<int>(firstOne) - 1;
        normalized = fracBinary.substr(firstOne + 1);
    }

    // stored exponent = actual exponent + bias (127)
    int biasedExponent = exponent + 127;
    string exponentBits = bitset<8>(biasedExponent).to_string();

    // Mantissa should be exactly 23 bits (truncate excess from 64-bit fraction)
    string mantissa = normalized.substr(0, 23);
    while (mantissa.size() < 23) mantissa.push_back('0');

    // final IEEE 754 32-bit binary string!
    return signBit + exponentBits + mantissa;
}

int main() {
    double num = -0.175571;
    cout << "IEEE 754 Representation: " << convertToFP(num) << endl;
    return 0;
}

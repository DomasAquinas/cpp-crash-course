// Exercise 7-1 from C++ Crash Course

#include <cstddef>
#include <cstdint>
#include <stdexcept>

// Construct a class UnsignedBigInteger that holds values bigger than a long
// and implement +, - (bonus: *, /, %)
class UnsignedBigInteger {

    UnsignedBigInteger() = default;
    UnsignedBigInteger(int initial_value) {
        for (size_t byte_i; byte_i < sizeof(int); byte_i++) {
           value[byte_i] = (initial_value >> (8 * byte_i)) & 128; 
        }
    }
    UnsignedBigInteger(UnsignedBigInteger&) = default;
    UnsignedBigInteger& operator= (UnsignedBigInteger&) = default;
    UnsignedBigInteger(UnsignedBigInteger&&) = default;
    UnsignedBigInteger& operator= (UnsignedBigInteger&&) = default;

    void operator= (const UnsignedBigInteger& assigned_value) {
        for (size_t byte_i; byte_i < size; byte_i++) {
            value[byte_i] = assigned_value.value[byte_i];
        }
    }

    bool operator== (UnsignedBigInteger operand) {
        bool result {true};
        for (size_t byte_i; byte_i < size; byte_i++) {
            if (this->value[byte_i] != operand.value[byte_i]) {
                result = false;
                break;
            }
        }
        return result;
    }

    bool operator> (UnsignedBigInteger operand) {
        bool result {false};
        for (size_t byte_i {size-1}; byte_i >= 0; byte_i--) {
            if (this->value[byte_i] != operand.value[byte_i]) {
                result = (this->value[byte_i] > operand.value[byte_i]);
                break;
            }
        }
        return result;
    }

    bool operator>= (UnsignedBigInteger operand) {
        return *this > operand || *this == operand;
    }

    bool operator< (UnsignedBigInteger operand) {
        bool result {false};
        for (size_t byte_i {size-1}; byte_i >= 0; byte_i--) {
            if (this->value[byte_i] != operand.value[byte_i]) {
                result = (this->value[byte_i] < operand.value[byte_i]);
                break;
            }
        }
        return result;
    }

    bool operator<= (UnsignedBigInteger operand) {
        return *this < operand || *this == operand;
    }

    UnsignedBigInteger operator+ (UnsignedBigInteger addend) {
        uint16_t tmp_sum { };
        uint8_t carry { 0 };
        for (size_t byte_i; byte_i < size; byte_i++) {
            tmp_sum = this->value[byte_i] + addend.value[byte_i] + carry;
            this->value[byte_i] = get_lower_byte(tmp_sum);
            carry = get_upper_byte(tmp_sum);
        }
        if (carry > 0) {
            throw(std::runtime_error("Result too large for UnsignedBigInteger"));
        }
        return *this;
    }

    UnsignedBigInteger operator+ (int addend) {
        return *this + UnsignedBigInteger(addend);
    }

    UnsignedBigInteger operator- (UnsignedBigInteger subtrahend) {
        uint16_t tmp_minuend { 0 };
        for(size_t byte_i; byte_i < size; byte_i++) {
            tmp_minuend = this->value[byte_i];
            if (tmp_minuend < subtrahend.value[byte_i]) {
                size_t carry_i { byte_i + 1 };
                while (carry_i <= size) {
                    if (carry_i == size) {
                        this->set_to_zero();
                        return *this;
                    }
                    if (this->value[carry_i] > 0) {
                        this->value[carry_i]--;
                        break;
                    }
                }
                while (carry_i > byte_i) {
                    this->value[carry_i] = UINT8_MAX;
                }
                tmp_minuend += UINT8_MAX;
            }
            this->value[byte_i] = tmp_minuend - subtrahend.value[byte_i];
        }
        return *this;
    }

    UnsignedBigInteger operator- (int subtrahend) {
        return *this - UnsignedBigInteger(subtrahend);
    }

    UnsignedBigInteger operator* (UnsignedBigInteger factor) {
        uint16_t tmp_product { 0 };
        uint8_t carry { 0 };
        for (size_t byte_i; byte_i < size; byte_i++) {
            tmp_product = this->value[byte_i] * factor.value[byte_i] + carry;
            carry = get_upper_byte(tmp_product);
            this->value[byte_i] = get_lower_byte(tmp_product);
        }
        if (carry > 0) {
            throw(std::runtime_error("Result too large for UnsignedBigInteger"));
        }
        return *this;
    }

    UnsignedBigInteger operator* (int factor) {
        return *this * UnsignedBigInteger(factor);
    }

    UnsignedBigInteger operator/ (UnsignedBigInteger divisor) {
        while (divisor.value[0] & 1 == 0 && this->value[0] &1 == 0) {
            divisor.divide_by_two();
            this->divide_by_two();
        }
        UnsignedBigInteger quotient;
        while (*this >= divisor) {
            *this = *this - divisor;
            quotient = quotient + 1;
        }
        return quotient;
    }

    UnsignedBigInteger operator/ (int divisor) {
        return *this / UnsignedBigInteger(divisor);
    }

    UnsignedBigInteger operator% (UnsignedBigInteger modulus) {
        while (modulus.value[0] & 1 == 0 && this->value[0] &1 == 0) {
            modulus.divide_by_two();
            this->divide_by_two();
        }
        UnsignedBigInteger quotient;
        while (*this >= modulus) {
            *this = *this - modulus;
        }
        return *this;
    }

    UnsignedBigInteger operator% (int modulus) {
        return *this % UnsignedBigInteger(modulus);
    }

    operator int () const {
        int result {0};
        for (size_t byte_i {size-1}; byte_i >= 0; byte_i--) {
            result << 8;
            result += this->value[byte_i];
        }
        return result;
    }

    uint8_t value[8] { };  // 64-bit unsigned value
    const static size_t size { sizeof(value)/sizeof(char) };

private:

    // Get the lower byte from a 16-bit value
    uint8_t get_lower_byte(uint16_t val) {
        return val & 255;
    }
    
    // Get the upper byte from a 16-bit value
    uint8_t get_upper_byte(uint16_t val) {
        return val >> 8;
    }

    // Set UnsignedBigInteger to zero
    void set_to_zero() {
        for (uint8_t& byte : this->value) {
            byte = 0;
        };
    }

    // Divide an UnsignedBigInteger by two
    void divide_by_two() {
        bool carry_down { false };
        bool tmp_carry { false };
        for (size_t byte_i {size-1}; byte_i >= 0; byte_i--) {
            tmp_carry = this->value[byte_i] & 1;
            this->value[byte_i] >> 1;
            if (carry_down) {
                this->value[byte_i] += 128;
            }
            carry_down = tmp_carry;
        }
    }

    // Check equality to 1
    bool is_equal_to_1() {
        bool result { false };
        for (size_t byte_i {size-1}; byte_i > 0; byte_i--) {
            result = !this->value[byte_i];
            if (!result) {
                break;
            }
        }
        return result & (this->value[0] == 1);
    }
};

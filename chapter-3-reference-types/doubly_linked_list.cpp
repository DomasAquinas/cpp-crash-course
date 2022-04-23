// Exercise 3-3

#include <cstdio>

struct Element {
    Element* next{};
    Element* previous{};  // Ex

    void insert_after(Element* new_element) {
        if (this->next != nullptr) {
            this->next->previous = new_element;
        }
        new_element->next = this->next;
        new_element->previous = this;  // Ex
        this->next = new_element;
    }

    void insert_before(Element* new_element) {  // Ex
        if (this->previous != nullptr) {
            this->previous->next = new_element;
        }
        new_element->next = this;
        new_element->previous = this->previous;
        this->previous = new_element;
    }

    char prefix[2];
    short operating_number;
};

int main() {
    Element trooper1, trooper2, trooper3;
    trooper1.prefix[0] = 'T';
    trooper1.prefix[1] = 'K';
    trooper1.operating_number = 421;
    trooper1.insert_after(&trooper3);
    trooper3.prefix[0] = 'L';
    trooper3.prefix[1] = 'S';
    trooper3.operating_number = 005;  // oops - this is octal...
    trooper3.insert_before(&trooper2);
    trooper2.prefix[0] = 'F';
    trooper2.prefix[1] = 'N';
    trooper2.operating_number = 2187;

    for (Element *cursor = &trooper1; cursor; cursor = cursor->next) {
        printf("stormtrooper %c%c-%d\n",
               cursor->prefix[0],
               cursor->prefix[1],
               cursor->operating_number);
    }

    for (Element *cursor = &trooper3; cursor; cursor = cursor->previous) {
        printf("stormtrooper %c%c-%d\n",
               cursor->prefix[0],
               cursor->prefix[1],
               cursor->operating_number);
    }
}
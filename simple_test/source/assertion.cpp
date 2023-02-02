//
// Created by toby on 2/2/23.
//

#include "../include/assertion.h"

const char *AssertException::what() const noexcept {
    return message.c_str();
}

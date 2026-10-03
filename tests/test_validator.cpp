#include "sensorbridgex/validator.hpp"
#include <cassert>
#include <iostream>
int main(){sbx::Config c;assert(sbx::validate({1,"now",20,50},c).accepted);assert(!sbx::validate({0,"now",20,50},c).accepted);assert(!sbx::validate({1,"",20,50},c).accepted);assert(!sbx::validate({1,"now",100,50},c).accepted);assert(!sbx::validate({1,"now",20,101},c).accepted);std::cout<<"Validator unit tests passed.\n";}

// test_repetitive_sequence.cpp
/* Copyright 2024 Roman Tsykaliak
     This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.
     This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
     You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <https://www.gnu.org/licenses/>. 
*/
#include <iostream>
#include <stdexcept>
#include <source_location>
#include <string_view>
#include <cassert>
#include "repetitive_sequence.hpp"
void test() {
  RepetitiveSequence<int,std::string_view> rs{"one"};
  rs.update(1,3,"one");
  std::cout << "1, 3, 'one'\n" << rs << '\n';
  assert(check(rs, "{}"));
  rs.update(1,3,"two");
  std::cout << "1, 3, 'two'\n" << rs << '\n';
  assert(check(rs, "{(1,two),(3,one),}"));
  rs.update(1,3,"one");
  std::cout << "1, 3, 'one'\n" << rs << '\n';
  assert(check(rs, "{}"));
  rs.update(1,3,"two");
  rs.update(5,7,"three");
  std::cout << "1, 3, 'two'; 5, 7, 'three'\n" << rs << '\n';
  assert(check(rs, "{(1,two),(3,one),(5,three),(7,one),}"));
  rs.update(1,7,"one");
  std::cout << "1, 7, 'one'\n" << rs << '\n';
  assert(check(rs, "{}"));
  rs.update(1,3,"two");
  rs.update(5,7,"three");
  rs.update(1,7,"four");
  std::cout << "1, 3, 'two'; 5, 7, 'three'; 1, 7, 'four'\n" << rs << '\n';
  assert(check(rs, "{(1,four),(7,one),}"));
  rs.update(-7,1,"five");
  std::cout << "-7, 1, 'five'\n" << rs << '\n';
  assert(check(rs, "{(-7,five),(1,four),(7,one),}"));
  rs.update(7,11,"six");
  std::cout << "7, 11, 'six'\n" << rs << '\n';
  assert(check(rs, "{(-7,five),(1,four),(7,six),(11,one),}"));
  rs.update(-7,11,"seven");
  std::cout << "-7, 11, 'seven'\n" << rs << '\n';
  assert(check(rs, "{(-7,seven),(11,one),}"));
  rs.update(1,1,"eight"); // noop
  std::cout << "1, 1, 'eight'\n" << rs << '\n';
  assert(check(rs, "{(-7,seven),(11,one),}"));
  rs.update(-1,1,"nine");
  std::cout << "-1, 1, 'nine'\n" << rs << '\n';
  assert(check(rs, "{(-7,seven),(-1,nine),(1,seven),(11,one),}"));
  rs.update(-8,12,"one");
  std::cout << "-8, 12, 'one'\n" << rs << '\n';
  assert(check(rs, "{}"));
  rs.update(-8,-5,"ten");
  rs.update(4,8,"eleven");
  rs.update(-6,5,"twelve");
  std::cout << "-8, -5, 'ten'; 4, 8, 'eleven'; -6, 5, 'twelve'\n" << rs << '\n';
  assert(check(rs, "{(-8,ten),(-6,twelve),(5,eleven),(8,one),}"));
}
void testWithoutOutput() {
  RepetitiveSequence<int,std::string_view> rs{"one"};
  rs.update(1,3,"one");
  assert(check(rs, "{}"));
  rs.update(1,3,"two");
  assert(check(rs, "{(1,two),(3,one),}"));
  rs.update(1,3,"one");
  assert(check(rs, "{}"));
  rs.update(1,3,"two");
  rs.update(5,7,"three");
  assert(check(rs, "{(1,two),(3,one),(5,three),(7,one),}"));
  rs.update(1,7,"one");
  assert(check(rs, "{}"));
  rs.update(1,3,"two");
  rs.update(5,7,"three");
  rs.update(1,7,"four");
  assert(check(rs, "{(1,four),(7,one),}"));
  rs.update(-7,1,"five");
  assert(check(rs, "{(-7,five),(1,four),(7,one),}"));
  rs.update(7,11,"six");
  assert(check(rs, "{(-7,five),(1,four),(7,six),(11,one),}"));
  rs.update(-7,11,"seven");
  assert(check(rs, "{(-7,seven),(11,one),}"));
  rs.update(1,1,"eight"); // noop
  assert(check(rs, "{(-7,seven),(11,one),}"));
  rs.update(-1,1,"nine");
  assert(check(rs, "{(-7,seven),(-1,nine),(1,seven),(11,one),}"));
  rs.update(-8,12,"one");
  assert(check(rs, "{}"));
  rs.update(-8,-5,"ten");
  rs.update(4,8,"eleven");
  rs.update(-6,5,"twelve");
  assert(check(rs, "{(-8,ten),(-6,twelve),(5,eleven),(8,one),}"));
}
void testWithCharKeys() {
  //   a   b  c  d  e  f  g  h  i  j  k l m n o p q r s t u  v  w  x  y  z
  // -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
  RepetitiveSequence<char,std::string_view> rs{"one"};
  rs.update('m','o',"one");
  std::cout << "'m', 'o', 'one'\n" << rs << '\n';
  assert(check(rs, "{}"));
  rs.update('m','o',"two");
  std::cout << "'m', 'o', 'two'\n" << rs << '\n';
  assert(check(rs, "{(m,two),(o,one),}"));
  rs.update('m','o',"one");
  std::cout << "'m', 'o', 'one'\n" << rs << '\n';
  assert(check(rs, "{}"));
  rs.update('m','o',"two");
  rs.update('q','s',"three");
  std::cout << "'m', 'o', 'two'; 'q', 's', 'three'\n" << rs << '\n';
  assert(check(rs, "{(m,two),(o,one),(q,three),(s,one),}"));
  rs.update('m','s',"one");
  std::cout << "'m', 's', 'one'\n" << rs << '\n';
  assert(check(rs, "{}"));
  rs.update('m','o',"two");
  rs.update('q','s',"three");
  rs.update('m','s',"four");
  std::cout << "'m', 'o', 'two'; 'q', 's', 'three'; 'm', 's', 'four'\n" << rs << '\n';
  assert(check(rs, "{(m,four),(s,one),}"));
  rs.update('e','m',"five");
  std::cout << "'e', 'm', 'five'\n" << rs << '\n';
  assert(check(rs, "{(e,five),(m,four),(s,one),}"));
  rs.update('s','w',"six");
  std::cout << "'s', 'w', 'six'\n" << rs << '\n';
  assert(check(rs, "{(e,five),(m,four),(s,six),(w,one),}"));
  rs.update('e','w',"seven");
  std::cout << "'e', 'w', 'seven'\n" << rs << '\n';
  assert(check(rs, "{(e,seven),(w,one),}"));
  rs.update('m','m',"eight"); // noop
  std::cout << "'m', 'm', 'eight'\n" << rs << '\n';
  assert(check(rs, "{(e,seven),(w,one),}"));
  rs.update('k','m',"nine");
  std::cout << "'k', 'm', 'nine'\n" << rs << '\n';
  assert(check(rs, "{(e,seven),(k,nine),(m,seven),(w,one),}"));
  rs.update('d','x',"one");
  std::cout << "'d', 'x', 'one'\n" << rs << '\n';
  assert(check(rs, "{}"));
  rs.update('d','g',"ten");
  rs.update('p','t',"eleven");
  rs.update('f','q',"twelve");
  std::cout << "'d', 'g', 'ten'; 'p', 't', 'eleven'; 'f', 'q', 'twelve'\n" << rs << '\n';
  assert(check(rs, "{(d,ten),(f,twelve),(q,eleven),(t,one),}"));
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
try {
  test();
  testWithoutOutput();
  testWithCharKeys();
  return EXIT_SUCCESS;
} catch (std::exception& e) {
  std::cerr << std::source_location::current().function_name() <<"  "<< e.what() <<'\n';
  return EXIT_FAILURE;
} catch (...) {
  std::cerr << std::source_location::current().function_name() <<"   unknown exception\n";
  return EXIT_FAILURE;
}

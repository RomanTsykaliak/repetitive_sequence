// repetitive_sequence.hpp
/*
Copyright 2024 Roman Tsykaliak
  This program is free software: you can
redistribute it and/or modify it under the terms
of the GNU General Public License as published
by the Free Software Foundation, either version
3 of the License, or (at your option) any later
version.
  This program is distributed in the hope that
it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU General Public License for
more details.
  You should have received a copy of the GNU
General Public License along with this program.
If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#include <map>
#include <iostream>
#include <ranges>
#include <string_view>
#include <sstream>
template<std::copyable Key, std::copyable Value>
requires
requires(std::remove_reference_t<Key>& key,
         std::remove_reference_t<Value>& value){
  {key < key} -> std::convertible_to<bool>;
  {value == value} -> std::convertible_to<bool>;
}
class RepetitiveSequence {
  std::map<Key,Value> intervals;
  Value every;
 public:
  RepetitiveSequence(const Value& v) :every{v}{}
  void update(const Key& begin, const Key& end,
              const Value& value) {
    if(begin < end) {
      auto pairEnd{every == value
        ? intervals.insert_or_assign(end, every)
        : intervals.try_emplace(end, every)};
      // propagete previous value for insertion
      // in the middle
      if(pairEnd.first != intervals.begin() &&
         std::next(pairEnd.first)
                           != intervals.end()) {
        pairEnd.first->second=
               std::prev(pairEnd.first)->second;
      }
      auto pairBegin{intervals.insert_or_assign
                                (begin, value)};
      // erase consecutive keys between
      // `begin` and `end`
      for(auto i{std::next(pairBegin.first)};
          i != pairEnd.first; ) {
        i= intervals.erase(i);
      }
      // if the first values are `every`, then
      // erase all keys with `every`
      for(auto i{intervals.begin()},
               e{intervals.end()};
          i != e && i->second == every; ) {
        i= intervals.erase(i);
  } } }
  const Value& operator[] (const Key& key)const{
    if(auto i{intervals.upper_bound(key)};
       i != intervals.begin()) {
      return std::prev(i)->second;
    }
    return every;
  }
  friend std::ostream& operator<<
                (std::ostream& strm,
                 const RepetitiveSequence& sq) {
    strm << "..." "\n"
         << sq.every << "\n"
         << sq.every << "\n";
    if(!sq.intervals.empty()) {
      for(auto i: std::ranges::iota_view
        {sq.intervals.begin()->first,
         std::prev(sq.intervals.end())->first}){
        strm << sq[i] << '\n';
    } }
    strm << sq.every << "\n"
         << sq.every << "\n"
                        "...";
    return strm;
  }
 private:
  friend bool check(const RepetitiveSequence&sq,
                    std::string_view sv) {
    std::ostringstream os;
    os << "{";
    for(const auto& [key, value]: sq.intervals){
      os <<'('<< key <<','<< value <<"),";
    }
    os << "}";
    return os.str() == sv;
} };

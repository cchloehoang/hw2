#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(std::string name, double price, int qty, std::string genre, std::string rating)
    :Product("movie", name, price, qty) {
      genre_ = genre;
      rating_ = rating;
    }

std::set<std::string> Movie::keywords() const {
  set<string> result = parseStringToWords(name_);
  result.insert(convToLower(genre_));
  return result;
}

std::string Movie::displayString() const {
  stringstream ss;
  ss << name_ << "\n";
  ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Movie::dump(std::ostream& os) const {
  os << "movie" << "\n";
  os << name_ << "\n";
  os << fixed << setprecision(2) << price_ << "\n";
  os << qty_ << "\n";
  os << genre_ << "\n";
  os << rating_ << "\n";
}
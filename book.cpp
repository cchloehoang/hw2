#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(std::string name, double price, int qty, std::string isbn, std::string author)
    :Product("book", name, price, qty) {
      isbn_ = isbn;
      author_ = author;
    }

std::set<std::string> Book::keywords() const {
  set<string> nameToWords = parseStringToWords(name_);
  set<string> authorToWords = parseStringToWords(author_);
  set<string> result = setUnion(nameToWords, authorToWords); //combining
  result.insert(isbn_);
  return result;
}

std::string Book::displayString() const {
  stringstream ss;
  ss << name_ << "\n";
  ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Book::dump(std::ostream& os) const {
  os << "book" << "\n";
  os << name_ << "\n";
  os << fixed << setprecision(2) << price_ << "\n";
  os << qty_ << "\n";
  os << isbn_ << "\n";
  os << author_ << "\n";
}
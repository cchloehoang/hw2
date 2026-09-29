#include <iostream>
#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore() {
  for (size_t i = 0; i < products_.size(); i++) {
    delete products_[i];
  }
  for (size_t i = 0; i < users_.size(); i++) {
    delete users_[i];
  }
}

void MyDataStore::addUser(User* u) {
  users_.push_back(u);
}

User* MyDataStore::findUser(string username) {
  for (size_t i = 0; i < users_.size(); i++) {
    if (convToLower(users_[i]->getName()) == convToLower(username)) {
      return users_[i];
    }
  }
  return NULL;
}

void MyDataStore::addProduct(Product* p) {
  products_.push_back(p);
  set<string> words = p->keywords();
  for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
    string word = *it;
    keywordMap_[word].insert(p);
  }
}

vector<Product*>MyDataStore::search(vector<string>& terms, int type) {
  set<Product*> result; //found
  //make stuff owercase
  for (size_t i = 0; i < terms.size(); i++) {
    string term = convToLower(terms[i]);
    //get
    //start with products
    //for and keep only products
    //or combine
    set<Product*> matches;
    if (keywordMap_.count(term) > 0) {
      matches = keywordMap_[term];
    }

    if (i == 0) {
      result = matches;
    }
    else if (type == 0) {
      result = setIntersection(result, matches);
    }
    else {
      result = setUnion(result, matches);
    }
  }

  vector<Product*> hits;
  for (set<Product*>::iterator it = result.begin(); it != result.end(); it++) {
    hits.push_back(*it);
  }
  return hits;
}

void MyDataStore::dump(ostream& ofile) {
  ofile << "<products>" << endl;
  for (size_t i = 0; i <products_.size(); i++) {
    //write in
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for (size_t i = 0; i <users_.size(); i++) {
    //write in
    users_[i]->dump(ofile);
  }
  ofile << "</users>" << endl;
}

bool MyDataStore::addToCart(string username, Product* p) {
  if (findUser(username) == NULL) {
    return false;
  }
  carts_[convToLower(username)].push_back(p);
  return true;
}

bool MyDataStore::viewCart(string username) {
  if (findUser(username) == NULL) {
    return false;
  }
  vector<Product*> cart = carts_[convToLower(username)];
  for (size_t i = 0; i < cart.size(); i++) {
    cout << "Item " << i + 1 << endl;
    cout <<cart[i]->displayString() << endl;
    cout << endl;
  }
  return true;
}

bool MyDataStore::buyCart(string username) {
  User* user = findUser(username);
  if (user == NULL) {
    return false;
  }

  string name = convToLower(username);
  vector<Product*> leftover;

  for(size_t i = 0; i < carts_[name].size(); i++) {
    Product* p = carts_[name][i];
    if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
      p->subtractQty(1);
      user->deductAmount(p->getPrice());
    }
    else {
      leftover.push_back(p);
    }
  }
  carts_[name] = leftover;
  return true;
}
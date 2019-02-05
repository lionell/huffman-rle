#include <bits/stdc++.h>

using namespace std;

struct Node {
  Node *zero;
  Node *one;
  char val;
  int freq;
};

struct Cmp {
  bool operator()(const Node *a, const Node *b) {
    return a->freq < b->freq;
  }
};

string read() {
  string l, res = "";
  while (getline(cin, l)) {
    res += l + '\n';
  }
  return res;
}

map<char, int> count(const string &s) {
  map<char, int> fs;
  for (char c : s) fs[c]++;
  return fs;
}

Node *build(const map<char, int> &fs) {
  set<Node*, Cmp> s;
  for (auto const& p : fs) {
    s.insert(new Node{nullptr, nullptr, p.first, p.second});
  }
  while (s.size() > 1) {
    Node *left = *s.begin();
    s.erase(s.begin());
    Node *right = *s.begin();
    s.erase(s.begin());
    s.insert(new Node{left, right, 0, left->freq + right->freq});
  }
  return *s.begin();
}

void optimize(Node *root, bool zero = true) {
  if (root->val) return;
  if (zero && root->zero->freq < root->one->freq) swap(root->zero, root->one);
  if (!zero && root->zero->freq > root->one->freq) swap(root->zero, root->one);
  optimize(root->zero, true);
  optimize(root->one, false);
}

map<char, string> convolute(const Node *root) {
  map<char, string> res;
  if (root->val != 0) {
    res[root->val] = "";
    return res;
  }
  map<char, string> zero = convolute(root->zero);
  for (auto const& p : zero) {
    res[p.first] = "0" + p.second;
  }
  map<char, string> one = convolute(root->one);
  for (auto const& p : one) {
    res[p.first] = "1" + p.second;
  }
  return res;
}

string huffman(const string &text, map<char, string> &mapping) {
  string res = "";
  for (char c : text) {
    res += mapping[c];
  }
  return res;
}

void flush(stringstream &out, char c, int cnt) {
  if (cnt > 3) {
    out << cnt << "@" << c;
  } else {
    for (int j = 0; j < cnt; j++) out << c;
  }
}

string rle(const string &s) {
  stringstream out;
  char c = s[0];
  int cnt = 1;
  for (int i = 1; i < s.length(); i++) {
    if (s[i] != c) {
      flush(out, c, cnt);
      c = s[i];
      cnt = 1;
    } else cnt++;
  }
  flush(out, c, cnt);
  return out.str();
}

void dispose(Node *root) {
  if (!root->val) {
    dispose(root->zero);
    dispose(root->one);
  }
  delete root;
}

string run(const string &text, bool opt) {
  Node *root = build(count(text));
  if (opt) optimize(root);
  map<char, string> mapping = convolute(root);
  dispose(root);
  return rle(huffman(text, mapping));
}

void write(const string &s, string filename) {
  ofstream out(filename);
  out << s;
}

int main() {
  string text = read();

  string without = run(text, false);
  write(without, "out.txt");
  string with = run(text, true);
  write(with, "opt.txt");

  cout << without.length() << " chars w/o optimization" << endl;
  cout << with.length() << " chars with optimization" << endl;
  cout << setprecision(3) << 100. - (100. * with.length() / without.length()) << "% benefit";
  return 0;
}

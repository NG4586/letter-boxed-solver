// Nathaniel Graves
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
using std::ifstream;
using std::getline;
using std::string;
using std::vector;
using std::queue;
using std::map;
using std::set;
using std::cin;
using std::cout;
using std::endl;

void connect(map<char, int> sides)
{
  cout << "calculating, this may take some time." << endl;
  ifstream words("dictionary.txt");
  map<string, vector<string> > wordMap;
  map<char, vector<string> > linkWords;
  vector<string> newEntry;
  string word;
  int n;
  while (getline(words, word))
    {
      for (n = 0; n < word.size(); n ++)
        {
          word[n] = tolower(word[n]);
          if (!sides.count(word[n]) || (n > 0 && sides[word[n]] == sides[word[n - 1]]))
            {
              break;
            }
        }
      if (n == word.size())
        {
          wordMap[word] = newEntry;
          if (!linkWords.count(word[0]))
            {
              linkWords[word[0]] = newEntry;
            }
          linkWords[word[0]].push_back(word);
        }
    }
  words.close();
  map<string, set<char> > paths;
  queue<string> nextPath;
  set<char> unvisited;
  map<string, vector<string> >::iterator i;
  map<char, int>::iterator h;
  for (i = wordMap.begin(); i != wordMap.end(); i ++)
    {
      (i -> second) = linkWords[(i -> first)[(i -> first).size() - 1]];
      for (h = sides.begin(); h != sides.end(); h ++)
        {
          if ((i -> first).find(h -> first) == string::npos)
            {
              unvisited.insert(h -> first);
            }
        }
      paths[i -> first] = unvisited;
      nextPath.push(i -> first);
      unvisited.clear();
    }
  string nextWord;
  int m;
  while (!paths[nextPath.front()].empty())
    {
      for (n = 0; n < wordMap[nextPath.front()].size(); n ++)
        {
          nextWord = wordMap[nextPath.front()][n];
          wordMap[nextPath.front() + "-" + nextWord] = wordMap[nextWord];
          nextWord = nextPath.front() + "-" + nextWord;
          paths[nextWord] = paths[nextPath.front()];
          for (m = nextPath.front().size(); m < nextWord.size(); m ++)
            {
              if (paths[nextWord].count(nextWord[m]))
                {
                  paths[nextWord].erase(nextWord[m]);
                }
            }
          nextPath.push(nextWord);
        }
      wordMap.erase(nextPath.front());
      nextPath.pop();
    }
  cout << nextPath.front() << endl;
}

int main()
{
  string letters;
  map<char, int> letterBox;
  for (int n = 0; n < 4; n ++)
    {
      cout << "Side " << n << ":" << endl;
      cin >> letters;
      for (int m = 0; m < letters.size(); m ++)
        {
          letterBox[letters[m]] = n;
        }
    }
  connect(letterBox);
  return 0;
}

#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
// ok we'll do a prototype to create
// need a string for the partially built word, a string for the fixed letters and -, the floats that have to be used, and the current index, and the result
void create(std::string partialWord, const std::string& in, std::string floating, int position, const std::set<std::string>&dict, std::set<std::string>&final);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> final;
    create("", in, floating, 0, dict, final);
    return final;

}

// Define any helper functions here
void create(std::string partialWord, const std::string& in, std::string floating, int position, const std::set<std::string>&dict, std::set<std::string>&final)
{
  // ok this is gonna be recursive
  // so base case first!! 
  // base case will be if the word is fully correct
  if(position == in.size())
  {
    if(floating.empty() && dict.find(partialWord) != dict.end()) // only adds the word when all the floating letters have been used and it exists in the dictionary
    {
      final.insert(partialWord);
    }
    return;
  }
  // second case is when we need to fill in a - 
  if(in[position] != '-')
  {
    // recursively call the function to use the floating letter and go forward
    create(partialWord + in[position], in, floating, position+1, dict, final);
  }
  else // this will cqtch when its bnlank and we have got to fill it
  {
    // ok this is taking too long im circling through all the letters when i shouldnt be 
    std::set<char>openLetters;
    int blanks = 0;
    for(size_t i = position; i < in.size(); ++i)
    {
      if(in[i] == '-')
      {
        blanks++;
      }
    }
    if((int)floating.size() == blanks)
    {
      for(char c : floating)
      {
        openLetters.insert(c);
      }
    }
    else
    {
      for(char a = 'a'; a<='z'; ++a)
      {
        openLetters.insert(a);
      }
    }
    
    //if(floating.size() > 0) // we have to start with these letters first
    //{
   // for(char c : floating)
    //{
     // openLetters.insert(c);
   // }
    // then try all the other letters
    //if((int)(in.size()- position) > (int)floating.size())
    //if((in.size() - position) > floating.size())
    //{
     //for(char a = 'a'; a <= 'z'; ++a)
     // {
     //   openLetters.insert(a);
      //}
    //}
    //if(floating.empty())
    //{
      //for(char c = 'a'; c <= 'z'; ++c)
      //{
       // openLetters.insert(c);
     // }
    //}
   // else
   //{
    //  for(char a = 'a'; a<= 'z'; ++a)
     // {
      //  openLetters.insert(a);
     // }
   // }
    for(char b : openLetters)
    {
      std::string newFloat = floating;
       // size_t position = newFloat.find(b);
      size_t floatPosition = newFloat.find(b);
        //if(position != std::string::npos)
      if(floatPosition != std::string::npos)
      {
          //newFloat.erase(position, 1);
        newFloat.erase(floatPosition, 1);
      }
      create(partialWord+b, in, newFloat, position+1, dict, final);
    }
    //}
  }
}



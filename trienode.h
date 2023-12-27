/* trienode.h contains structure and function declarations for 
   a trie implementation 
   CSE374 HW5 
   Copyright 2023 Paul Lam
*/

#ifndef TRIENODE_H_
#define TRIENODE_H_

#include <stdbool.h>

// Define the structure for a trie node
typedef struct trieNode {
  char *word;
  struct trieNode *branch[10];
} Node;

// Function declarations

// Create and initialize a new trie node
Node *CreateTrieNode();

// Build a trie by inserting a word into it
void BuildTrie(Node *root, char *word);

// Find a node in the trie based on a key sequence
Node *FindNode(Node *root, char *keySeq);

// Free the memory allocated for the trie
void FreeTrie(Node *root);

#endif  // TRIENODE_H_

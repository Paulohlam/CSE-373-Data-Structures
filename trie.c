/* trie.c
   Author: Paul Lam
   Purpose: Implementation of a trie data structure for building, searching, and deleting a trie.
   CSE374, HW5
   Copyright 2023 Paul Lam
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trienode.h"

/* Creates a new trie node
* Returns: Pointer to the newly created node
*/
Node *CreateTrieNode() {
  Node *node = (Node *)malloc(sizeof(Node));
  node->word = NULL;
  for (int i = 0; i < 10; i++) {
    node->branch[i] = NULL;
  }
  return node;
}

/* Returns the digit corresponding to the given letter
* Parameters: letter is the letter for which to determine the digit
* Returns: The digit corresponding to the letter and returns -1 if the letter is not found
*/
int getDigit(char letter) {
  const char *letters[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs",
                         "tuv", "wxyz"};
  for (int i = 0; i < 8; i++) {
    if (strchr(letters[i], letter) != NULL) {
      return i + 2;
    }
  }
  return -1;
}

/* Inserts a word into the trie
* Parameter: root is a pointer to the root node of the trie
* Parameter: word is the word to be inserted
*/
void BuildTrie(Node *root, char *word) {
  Node *current = root;
  int length = strlen(word);
  for (int i = 0; i < length; i++) {
    char letter = tolower(word[i]);
    int digit = getDigit(letter);
    if (digit == -1) {
      continue;
    }
    if (current->branch[digit] == NULL) {
      current->branch[digit] = CreateTrieNode();
    }
    current = current->branch[digit];
  }
  if (current->word == NULL) {
    current->word = strdup(word);
  } else {
    Node *temp = current;
    while (temp->branch[0] != NULL) {
      temp = temp->branch[0];
    }
    temp->branch[0] = CreateTrieNode();
    temp->branch[0]->word = strdup(word);
  }
}

/* Finds the node in the trie corresponding to the given key sequence
* Parameter root is the pointer to the root node of the trie
* Parameter keySeq is the key sequence that is being searched
* Returns the pointer to the found node and returns NULL if not found
*/
Node *FindNode(Node *root, char *keySeq) {
  Node *current = root;
  int length = strlen(keySeq);
  for (int i = 0; i < length; i++) {
    if (keySeq[i] != '#') {
      int digit = keySeq[i] - '0';
      if (current->branch[digit] == NULL) {
        return NULL;
      }
      current = current->branch[digit];
    } else {
      if (current->branch[0] == NULL) {
        return NULL;
      }
      current = current->branch[0];
    }
  }
  return current;
}

/* FreeTrie: Frees the memory allocated for the trie.
* Parameter root is the pointer to the root node of the trie
*/
void FreeTrie(Node *root) {
  if (root == NULL) {
    return;
  }
  for (int i = 0; i < 10; i++) {
    FreeTrie(root->branch[i]);
  }
  free(root->word);
  free(root);
}

/* tnine.c
   Author: Paul Lam
   Purpose: Drives a trie/t9 program. Builds a trie according to trienode and runs an interactive session for retrieving words using t9 sequences.
   CSE374, HW5
   Copyright 2023 Paul Lam
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trienode.h"

#define MAX_INPUT_LENGTH 100

// Main function which reads from given file and outputs results
// based on given sequence
int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <dictionary_file>\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Could not open the file.\n");
    return 1;
  }

  Node *root = CreateTrieNode();

  char word[MAX_INPUT_LENGTH];
  while (fgets(word, sizeof(word), fp) != NULL) {
    size_t len = strlen(word);
    if (word[len - 1] == '\n') {
      word[len - 1] = '\0';
    }

    // Allocate memory for the word
    char *newWord = (char *)malloc((len + 1) * sizeof(char));
    if (newWord == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      return 1;
    }

    // Copy the word to the allocated memory
    strncpy(newWord, word, len + 1);

    // Build the trie with the word
    BuildTrie(root, newWord);
  }
  fclose(fp);

  printf("Enter \"exit\" to quit.\n");
  char input[MAX_INPUT_LENGTH];
  Node *current = root;
  bool shouldExit = false;

  while (!shouldExit) {
    printf("Enter Key Sequence (or \"#\" for next word):\n");
    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
      input[len - 1] = '\0';
    }

    if (strcmp(input, "exit") == 0) {
      shouldExit = true;
      continue;
    }

    if (input[0] == '#') {
      current = FindNode(current, input);
    } else {
      current = FindNode(root, input);
    }

    if (current != NULL) {
      if (current->word != NULL) {
        printf("'%s'\n", current->word);
      } else {
        printf("Not found in current dictionary.\n");
      }
    } else {
      if (input[strlen(input) - 1] == '#') {
        printf("There are no more T9onyms\n");
      } else {
        printf("Not found in current dictionary.\n");
      }
    }
  }

  // Free the trie and allocated memory
  FreeTrie(root);

  return 0;
}

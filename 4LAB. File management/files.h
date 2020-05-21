#pragma once

#include "define.h"
#include "struct.h"

int numOnFile(char fileName[]);
int readingOne(int fileDiscriptor, void* databuf, int length);
int WritingOne(int fileDiscriptor, struct Zoo data);
int addElement(int argc, char* argv[], char fileName[]);
int delElement(char* argv[], int count, char secondFileName[], char fileName[]);
int modifyElement(int argc, char*argv[], int count, char filename[]);
struct Zoo readingToRec(int argc, char* argv[]);
struct Node* createListOfFile(int argc, char* argv[],char filename[], int num);
struct Node* sort(struct Node* p_root);
void printOneStr(struct Node* p_tmp);
void printAll(struct Node* p_head);
void printOneStrSecondReq(struct Node* p_tmp);
void printForSecondReq(struct Node* p_head);
struct Node* sortForSecond(struct Node* p_root);
void deleteList(struct Node* pHead);
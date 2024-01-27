#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct TreeNode {
  char data;
  struct TreeNode *left;
  struct TreeNode *right;
};

struct TreeNode *createNode(char val) {
  struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
  if (newNode != NULL) {
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
  }
  return newNode;
}

int isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '$');
}

struct TreeNode *ExpressionTree(char postfix[]) {
  struct TreeNode *stack[100];
  int top = -1, i;
  for (i = 0; postfix[i] != '\0'; i++) {
    struct TreeNode *newNode = createNode(postfix[i]);
    if (isdigit(postfix[i])) {
      stack[++top] = newNode;
    } else if (isOperator(postfix[i])) {
      newNode->right = stack[top--];
      newNode->left = stack[top--];
      stack[++top] = newNode;
    }
  }
  return stack[top];
}

void inorder(struct TreeNode *root) {
  if (root != NULL) {
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
  }
}

int evaluateTree(struct TreeNode *root) {
  if (root->data == '+')
    return evaluateTree(root->left) + evaluateTree(root->right);
  else if (root->data == '-')
    return evaluateTree(root->left) - evaluateTree(root->right);
  else if (root->data == '*')
    return evaluateTree(root->left) * evaluateTree(root->right);
  else if (root->data == '/')     
    return evaluateTree(root->left) / evaluateTree(root->right);
  else if (root->data == '$')     
    return pow(evaluateTree(root->left), evaluateTree(root->right));
  else     
    return root->data - '0';
  }

void freeExpressionTree(struct TreeNode *root) {
  if (root != NULL) {
    freeExpressionTree(root->left);
    freeExpressionTree(root->right);
    free(root);
  }
}

int main() {
  char postfixExpression[100];
  printf("Enter a postfix expression: ");
  scanf("%s", postfixExpression);
  struct TreeNode *root = ExpressionTree(postfixExpression);
  printf("In order Traversal of the expression tree: ");
  inorder(root);
  printf("\n");
  int result = evaluateTree(root);
  printf("Result: %d\n", result);
  freeExpressionTree(root);
  return 0;
}

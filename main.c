/* main.c
 *
 * Justin Greever
 * CS201 - A4
 * 5/22/2021
 *
 * The goal behind this program is to bring together all the things we have learned so far.
 * This program will be a menu-based program that will perform the following operations:
 *      Exit
 *      Addition
 *      Subtraction
 *      Multiplication
 *      Division
 *      Modulo
 *      Reverse Input
 *
 * The program will accept 32-bit integers (positive or negative) as the argument, and UP TO 15 arguments in either
 * hexadecimal or decimal. If using hexadecimal we must also accept the start of the value may have 0x or 0X,
 * they must be accepted.
 *
 * The rules are as follows for the menu choice functions:
 *      Addition: calculate from L -> R
 *      Subtraction: calculate from L -> R
 *      Multiplication: calculate from L -> R
 *      Division: calculate the first number divided by the second number from L -> R, discard the rest of the values
 *      Modulo: calculate the first number modulo the second number from L -> R, discard the rest of the values
 *      Reverse Input: print the input values in reverse from L -> R: ./a4 one two three -> eerht owt eno
 *
 *      Your program must have a function for printing the menu. The function is required to accept a structure
 *      containing the number of items in the menu and the menu text.
 *
 *      Your program will not store the item number with the menu item text. This must be computed when the menu is
 *      displayed. e.g.:
 *          char *choices[] = {"Exit", "Addition", "Subtraction", "Multiplication", "Division", "Modulo", "Reverse Input"};
 *
 *     Your program must have a function that implements each menu item. The individual functions are allowed to call
 *     other functions. The exception is menu item 0 (exit) which can be handled however you wish.
 *
 *     Your program must contain a function dispatch table as described in class. The entries must be ordered such that
 *     when the menu item is selected by number that the function dispatch table entry for that number selects the
 *     corresponding function to perform the action named in the menu.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

#define MAXINPUT 15 /* set the max number of arguments we will use */




/* Structs */
typedef struct {
    int totalArguments; /* the total arguments the user passed in */
    long *usersInputValues[MAXINPUT]; /* used to store *argv[] arguments as decimal */
    char *usersInputStrings[MAXINPUT]; /* used to store *argv[] arguments as strings */
} userArguments;

/* Typedefs for fdt */
typedef void fdtMenu(userArguments *toRun);

typedef struct {
    int numberOfMenuItems;
    char *textOfMenuItems[MAXINPUT];
} menuOptions;

typedef struct {
    fdtMenu *runMenuItem;
} fdtOptions;




/* functions or function declarations */
void exitProgram(userArguments toExit);
void addition(userArguments toAdd);
void subtraction(userArguments toSubtract);
void multiplication(userArguments toMultiply);
void division(userArguments toDivide);
void modulo(userArguments toModulo);
void reverseInput(userArguments toReverse);




/* let's us exit the program from the menu */
void
exitProgram(userArguments toExit) {
    printf("Normally, the program would exit here. This is for testing.\n");
    //exit(EXIT_SUCCESS);
}




/* Add arguments and print result */
void
addition(userArguments toAdd) {
    int totalArgs = toAdd.totalArguments;
    long additionResults = 0;
    for (int i = 0; i < totalArgs; i++) {
        additionResults += (long)toAdd.usersInputValues[i];
        printf("%ld", (long)toAdd.usersInputValues[i]);
        if (i != totalArgs - 1)
            printf(" + ");
        else
            printf(" = %ld\n", additionResults);
    }
}




/* Subtract arguments and print result */
void
subtraction(userArguments toSubtract) {
    int totalArgs = toSubtract.totalArguments;
    long additionResults = 0;
    for (int i = 0; i < totalArgs; i++) {
        additionResults -= (long)toSubtract.usersInputValues[i];
        printf("%ld", (long)toSubtract.usersInputValues[i]);
        if (i != totalArgs - 1)
            printf(" - ");
        else
            printf(" = %ld\n", additionResults);
    }
}




/* Multiply arguments and print result */
void
multiplication(userArguments toMultiply) {
    int totalArgs = toMultiply.totalArguments;
    long additionResults = 1;
    for (int i = 0; i < totalArgs; i++) {
        additionResults *= (long)toMultiply.usersInputValues[i];
        printf("%ld", (long)toMultiply.usersInputValues[i]);
        if (i != totalArgs - 1)
            printf(" * ");
        else
            printf(" = %ld\n", additionResults);
    }
}




/* Divide first two arguments, ignore the rest, and print result */
void
division(userArguments toDivide) {
    long argOne = (long) toDivide.usersInputValues[0];
    long argTwo = (long) toDivide.usersInputValues[1];
    float divideTotal = (float)argOne / (float)argTwo;
    printf("%ld / %ld = %lf\n", (long)toDivide.usersInputValues[0], (long)toDivide.usersInputValues[1], divideTotal);
}




/* Modulo first two arguments, ignore the rest, and print result */
void
modulo(userArguments toModulo) {
    /* check if the divisor is 0, if so, print the answer as undefined, otherwise continue with mod */
    if (toModulo.usersInputValues[1] == 0) {
        printf("%ld %% %ld = undefined\n", (long) toModulo.usersInputValues[0], (long) toModulo.usersInputValues[1]);
    } else {
        long moduloTotal = (long) toModulo.usersInputValues[0] % (long) toModulo.usersInputValues[1];
        printf("%ld mod %ld = %ld\n", (long) toModulo.usersInputValues[0], (long) toModulo.usersInputValues[1],
               moduloTotal);
    }
}




/* take the users input and print out in reverse */
void
reverseInput(userArguments toReverse) {
    printf("Reverse: "); /* TODO: Finish reverse function */
}




/* prints our menu */
void
printMenu(menuOptions menu) {
    printf("\n");
    for (int i = 0; i < menu.numberOfMenuItems; i++) {
        printf("%d)\t%s\n", i, menu.textOfMenuItems[i]);
    }
    printf("\n");
    printf("Enter choice: ");
}




/* Function Dispatch Table */
fdtOptions fdt[] = {
        (void (*)(userArguments *)) exitProgram,
        (void (*)(userArguments *)) addition,
        (void (*)(userArguments *)) subtraction,
        (void (*)(userArguments *)) multiplication,
        (void (*)(userArguments *)) division,
        (void (*)(userArguments *)) modulo,
        (void (*)(userArguments *)) reverseInput
};





/* our main function */
int
main(int argc, char *argv[]) {
    /* Variables */
    char *menuChoices[] = {
            "Exit",
            "Addition",
            "Subtraction",
            "Multiplication",
            "Division",
            "Modulo",
            "Reverse Input"
    };
    int menuCount = sizeof(menuChoices) / sizeof(menuChoices[0]);
    menuOptions menu;
    userArguments ua;
    ua.totalArguments = (argc - 1);
    int idx = 0;
    int choice = 0;

    /* If there are more than 15 arguments, set args equal to 15 so we can ignore any more arguments past that */
    /* If there are less than 3 arguments (program name included), then fail */
    if (argc > MAXINPUT)
        ua.totalArguments = MAXINPUT;
    else if (argc < 3) {
        printf("Error: Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }

    /* let's get the arguments passed in and store them for use later */
    for (int i = 0; i < ua.totalArguments; i++) {
        ua.usersInputValues[i] = (long *) strtol(argv[i + 1], NULL, 0);
    }

    while (idx < argc) {
        ua.usersInputStrings[idx] = argv[idx];
        idx++;
    }

    menu.numberOfMenuItems = menuCount;
    for (int i = 0; i < menu.numberOfMenuItems; i++) {
        menu.textOfMenuItems[i] = menuChoices[i];
    }

    printMenu(menu);
    choice = getchar();

    (*fdt[choice].runMenuItem)((userArguments *) menuChoices[choice]);

    exit(EXIT_SUCCESS);
}

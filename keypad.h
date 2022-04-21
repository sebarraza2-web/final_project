#ifndef KEYPAD_H_
#define KEYPAD_H_

/* define pin values corresponding to keypad */
#define ROWS P2
#define COLS P6

#define R1 BIT4
#define R2 BIT5
#define R3 BIT6
#define R4 BIT7

#define C1 BIT4
#define C2 BIT5
#define C3 BIT6
#define C4 BIT0

/* function prototypes */
void keypad_init();
char keypad_get_key();

#endif /* KEYPAD_H_ */

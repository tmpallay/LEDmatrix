#define ROW1 8
#define ROW2 9
#define ROW3 10
#define ROW4 11
#define ROW5 12
#define ROW6 13

#define COL1 2
#define COL2 3
#define COL3 4
#define COL4 5
#define COL5 6
#define COL6 7

int ROW[] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6 };
int COL[] = { COL1, COL2, COL3, COL4, COL5, COL6 };

void setup() {

  for( int i = 0; i < 6; i++ ) {
    digitalWrite( ROW[i], LOW );
    pinMode( ROW[i], OUTPUT );
  }

  for( int i = 0; i < 6; i++ ) {
    digitalWrite( COL[i], HIGH );
    pinMode( COL[i], OUTPUT );
  }

  randomSeed(analogRead(0));

}

/*
 * Function: led_pulse
 * --------------------
 * Illuminates a chosen LED for a specified amount of time
 * 
 * row: row that the LED occupies
 * col: column that the LED occupies
 * t : length of time that the LED will be illuminated in MICROSECONDS
 */
void led_pulse( int row, int col, unsigned long t ) {

  int multiple = t / 16383;
  int r = t % 16383;
  if( t > 16383 ) t = 16383;

  digitalWrite( ROW[row - 1], HIGH );
  digitalWrite( COL[col - 1], LOW );

  while( multiple ) {
    delayMicroseconds( t );
    multiple--;
  }
  delayMicroseconds( r );
  
  digitalWrite( ROW[row - 1], LOW );
  digitalWrite( COL[col - 1], HIGH );
  
}

/*
 * Function: row_pulse
 * --------------------
 * Illuminates a chosen row of LEDs for a specified amount of time
 * 
 * row: row to be illuminated
 * row_t: length of time that the row will be illuminated in MILLISECONDS
 */
void row_pulse( int row, unsigned long row_t ) {

  unsigned long start = millis();
  while( millis() - start < row_t ) {
    
    for( int col = 1; col < 7; col++) led_pulse( row, col, 10 );
      
  }
  
}

/*
 * Function: col_pulse
 * --------------------
 * Illuminates a chosen column of LEDs for a specified amount of time
 * 
 * col: column to be illuminated
 * col_t: length of time that the column will be illuminated in MILLISECONDS
 */
void col_pulse( int col, unsigned long col_t ) {

  unsigned long start = millis();
  while( millis() - start < col_t ) {
    
    for( int row = 1; row < 7; row++) led_pulse( row, col, 10 );
      
  }
  
}

/*
 * Function: all_on
 * --------------------
 * Illuminates all LEDs in the matrix for a specified amount of time
 * 
 * all_t: length of time that all LEDs will be illuminated in MILLISECONDS
 */
void all_on( unsigned long all_t ) {
  
  unsigned long start = millis();
  while( millis() - start < all_t ) {
    
    for( int row = 1; row < 7; row++) {
      for( int col = 1; col < 7; col++) {
        led_pulse( row, col, 20 );
      }
    }
    
  }

}

/*
 * Function: zig_rows
 * --------------------
 * Illuminates rows one by one, in a back and forth pattern.
 *    This starts with row 1, progreses to row 6, then ends back at row 2
 * 
 * repeat: number of times that the pattern will be repeated
 * row_t: length of time that each individual row will be illuminated in MILLISECONDS
 */
void zig_rows( int repeat, unsigned long row_t ) {

  while( repeat ) {
  
    for( unsigned long i = 2345654321; i > 0; i = i / 10 )
      row_pulse( i % 10, row_t );
      
    repeat--;
  }
  
}

/*
 * Function: zig_cols
 * --------------------
 * Illuminates columns one by one, in a back and forth pattern.
 *    This starts with column 1, progreses to column 6, then ends back at column 2
 * 
 * repeat: number of times that the pattern will be repeated
 * col_t: length of time that each individual column will be illuminated in MILLISECONDS
 */
void zig_cols( int repeat, unsigned long col_t ) {
 
  while( repeat ) {
  
    for( unsigned long i = 2345654321; i > 0; i = i / 10 )
      col_pulse( i % 10, col_t );

    repeat--;
  }
  
}

/*
 * Function: led_rand
 * --------------------
 * Illuminates a specified number of random LEDs in the matrix, each for a specified amount of time
 * 
 * repeat: number of LEDs to be illuminated, one after another
 * t: length of time that the random LED will be illuminated in MILLISECONDS
 */
void led_rand( int repeat, unsigned long t ) {

  while( repeat ) {
    led_pulse( random( 1, 7 ), random( 1, 7 ), t * 1000 );
    repeat--;
  }
  
}

void loop() {

  zig_rows( 2, 200 );
  all_on( 500 );

  led_rand( 20, 200 );
  all_on( 500 );

  zig_cols( 2, 200 );
  all_on( 500 );

  led_rand( 20, 200 );
  all_on( 500 );
  
}

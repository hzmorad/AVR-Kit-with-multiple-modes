# AVR-Kit-with-multiple-modes
•	Mode 1: An Alarm system for an oven.
•	Mode 2: LDR is used and LED with a different power supply is connected to a relay.
•	Mode 3: Calculator
          1.	Multi-operation with priority ((*, /), (+,-)).
          2.	Can take operands up to 5 digits.
          3.	Operate up to 10 digits.
          4.	Capable of dealing with negative numbers
          5.	Capable of dealing with decimal numbers with an accuracy of 2 digits after the decimal point.
          6.	Accept (+,-) as a sign for first number (ex: -234+13=).
          7.	Accept multiple signs for one number (ex: 5---2=3).
          8.	There is no limit for display per operation.
          9.	After each operation there are 2 options to clear display by pressing the clear button or continue by pressing any operator button.
          10.	The result has special cases: 
              - "Out of Range" when result >= 2147483648 or result <=-2147483648 and you can clear display by pressing the clear button or continue by pressing any operator button. In case you continued, if the new result is within the range it will be printed else it will print "Out of Range" again and so on.
              -	"Math Error" will be printed wherever you operate division by zero and the code gets stuck until clear button is pressed.

# Note: Updating the mode via UART.

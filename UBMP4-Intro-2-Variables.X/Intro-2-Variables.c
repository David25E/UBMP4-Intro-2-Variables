/*==============================================================================
 Project: Intro-2-Variables
 Date:    May 16, 2021
 
 This example program demonstrates the use of byte (char) constants and
 variables to count button presses and trigger actions when a limit is reached.
  
 Additional program analysis and programming activities demonstrate using bit
 (Boolean, or bool) variables to store state for operations such as preventing 
 multiple counting of a singe button press during successive program loops.
 Additional activities include the creation of a two-player rapid-clicker game,
 simulating a real-world toggle button, and counting switch contact bounce.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program constant definitions
const unsigned char maxCount = 100;
 #define pressed 0
 #define notPressed 1

// Program variable definitions
unsigned char SW2Count = 0;
bool SW2Pressed = false;

unsigned char SW5Count = 0;
bool SW5Pressed = false;

bool SW4Pressed = false;
unsigned char SW3Count = 0;


int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    // Code in this while loop runs repeatedly.
    while(1)
	{
     
for(int i = 0; i < pressed; i ++){      
        if(SW4 == pressed)
        {
            LED5 = 1;
            }
            return 0;
}



        // Add a short delay to the main while loop.
        __delay_ms(10);
        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }

}
}
    
/* Program Analysis
 * 
 * 1. The 'SW2Count' variable is created within RAM as an 8-bit memory location
 *    by the declaration: 'unsigned char SW2Count = 0;'
 *    What is the the maximum value an 8-bit variable can store?
 *    What are some benefits and drawbacks of using 8-bit variables in an 8-bit
 *    microcontroller?

 The maximum value an 8-bit variable can store is 255, which is eight 1's in binary code. Or 2^8 = 256, so integers 0 through 255.
 Benefits of this is that the 8-bit microcontroller is working within its native boundaries of values between 0 and 255. It will process the variable the fastest, compared to using larger variables. 
 However, this can be an issuse if you wish to work with larger variables because the MCU will require more steps and a longer amount of time to process the information.

 * 
 * 2. The constant 'maxCount' is defined using a declaration similar to that
 *    used for the SW2Count variable, but with the 'const' prefix added in the
 *    declaration. Can you think of some advantages of declaring a constant like
 *    this, using a separate statement above the main code, rather than just
 *    embedding the value of the constant where it is needed in the code?

 Advantages like this is that you are able to use the variable for any other potential blockes of code below or between it. Plus, it will set it to a global variable.
 If you decide to declare it inside the block of code as well, the variable will always stay constant to the set global value.
 * 
 * 3. This program should light LED D3 every time SW2 is pressed, and light
 *    LED D4 once the count reaches 50. Try it, and count how many times you
 *    have to press the button until LED D4 turns on. SW3 resets the count so
 *    you can perform repeated attempts.
 * 
 *    Did your count reach 50? Can you describe what the program is doing?
 *    (Hint: try pressing and releasing the button at different rates of speed.)

 My count did not reach 50, because the program is counting the total time of how long I am pressing down the buttons. 
 For example, I can hold it once and it will flash up around half a second to a second after, or press it several times rapdily until it lights up, which can be like 8 times.
 The counting depends on the length of how long I am holding down the button.
 * 
 * 4. Modify the second 'if' structure to add the else block, as shown below:

        if(SW2Count >= maxCount)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Now, press and hold pushbutton SW2 for at least 10 seconds while watching
 *    LED D4. LED D4 should stay on continuously while the value of SW2Count is
 *    higher than maxCount. If LED D4 turns off, what can you infer about the
 *    value of the SW2Count variable? Can you explain what happens to the
 *    SW2Count variable as the SW2 button is held?

 If LED D4 turns on, I can infer that the code is being reset because the SW2 button is going beyond its variable limit. As the SW2 button is held,
 the SW2Count variable is being overwritten and restarting.
 * 
 * 5. We can set a limit on the SW2Count variable by encapsulating its increment
 *    statement inside a conditional statement. In your program, replace the
 *    line 'SW2Count = SW2Count + 1;' with the code, below:
 
            if(SW2Count < 255)
            {
                SW2Count += 1;
            }

 *    This code demonstrates the use of the assignment operator '+=' to shorten
 *    the statement 'SW2Count = SW2Count + 1;' The same operation is performed,
 *    but in a more compact form. After adding this code, what is the maximum
 *    value that the SW2Count variable will reach? How does this affect the
 *    operation of LED D4 when SW2 is held?

 After adding this code, the maximum value the SW2Count variable will reach 254 because the "if statement" will only work if SW2Count is less than 255.
 It affects the operation of LED D4 when SW2 is held by making it continuously flash after SW2Count reaches 50 and will not stop and flash again like in question 4.
 *
 * 6. The fundamental problem with this program is that pushbutton SW2 is sensed
 *    in each cycle of the loop and if its state is read as pressed, another
 *    count is added to the SW2Count variable. Rather than responding to state,
 *    the program needs to be made to respond only to each new press -- in other
 *    words, a *change* of SW2 state, from not-pressed to pressed. Doing this
 *    requires the use of another variable to store the prior state of SW2, so
 *    that its current state can be evaluated as being the same, or different
 *    from its state in the previous loop. Replace the initial if-else condition 
 *    with the following two if conditions:

        // Count new SW2 button presses
        if(SW2 == 0 && SW2Pressed == false)
        {
            LED3 = 1;
            SW2Pressed = true;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
        }

        // Clear pressed state if released
        if(SW2 == 1)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
 *    These two if conditions make use of the Boolean SW2Pressed variable to
 *    store the current state of SW2 for the next cycle of the main while loop.
 *    Boolean variables can store 0/false or 1/true, interchangeably. The first
 *    if condition, above, compares the current SW2 state with the previously
 *    stored SW2Pressed variable so that a new count is only added when the SW2
 *    button is pressed and SW2Pressed is false. In the if structure, SW2Pressed
 *    is set to true before a count is added. The following if structure resets
 *    SW2Pressed to false when the button is released. Try the code to verify
 *    that it works.
 * 
 *    The conditional statement in the first if condition can also be written:

        if(SW2 == 0 && !SW2Pressed)

 *    The '!SW2Pressed' expression is read as 'not SW2Pressed' and is equivalent
 *    to SW2Pressed being false. Similarly, using the variable name by itself
 *    (eg. SW2Pressed) in a condition is equivalent to SW2Pressed being true.
 * 
 * 7. A pushbutton's logic state can also be defined as a word in a similar way
 *    to a variable (eg. the way SW2Pressed represents 1 or 0, or true or false)
 *    which can help to make the code more readable. Add the following lines to
 *    the 'Program constant definitions' section at the top of the code:
 
 #define pressed 0
 #define notPressed 1

 *    Now, instead of comparing the state of the button to 0 or 1, the button
 *    input can be compared with the named definition for 0 or 1, making the
 *    program more readable at the expense of hiding the actual switch value in
 *    the definition statement instead of making it obvious in the if structure.
 *    Try it in your code, and modify the SW3 reset button to work with the same
 *    pressed adn notPressed definitions.
 
        // Count new SW2 button presses
        if(SW2 == pressed && SW2Pressed == false)
        {
            LED3 = 1;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
            SW2Pressed = true;
        }

        // Clear pressed state if released
        if(SW2 == notPressed)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
 * 
// Count new SW2 button presses
        if(SW2 == pressed && SW2Pressed == false)
        {
            LED3 = 1;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
            SW2Pressed = true;
        }

        // Clear pressed state if released
        if(SW2 == notPressed)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
        if(SW2Count >= maxCount)
        {
            LED4 = 1;
        }
         else
        {
            LED4 = 0;
        }
        
        // Reset count and turn off LED D4
        if(SW3 == pressed)
        {
            LED4 = 0;
            SW2Count = 0;
        }

 * Programming Activities
 * 
 * 1. Can you make a two-player rapid-clicker style game using this program as 
 *    a starting point? Let's use SW5 for the second player's pushbutton so that
 *    the two players can face each other from across the UBMP4 circuit board.
 *    Duplicate SW2Count and SW2Pressed to create SW5Count and SW5Pressed
 *    variables. Then, duplicate the required if condition structures and modify
 *    the variable names to represent the second player. LED D4 can still light
 *    if player 1 is the first to reach maxCount. Use LED D5 to show if the
 *    second palyer wins. Use a logical condition statement to reset the game
 *    by clearing the count and turning off the LEDs if either SW3 or SW4 is
 *    pressed.

 
// Count new SW2 button presses
        if(SW2 == pressed && SW2Pressed == false)
        {
            LED3 = 1;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
            SW2Pressed = true;
        }

        // Clear pressed state if released
        if(SW2 == notPressed)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
        if(SW2Count >= maxCount)
        {
            LED4 = 1;
        }
         else
        {
            LED4 = 0;
        }
        

//Second Player
// Count new SW5 button presses
        if(SW5 == pressed && SW5Pressed == false)
        {
            LED6 = 1;
            if(SW5Count < 255)
            {
                SW5Count = SW5Count + 1;
            }
            SW5Pressed = true;
        }

        // Clear pressed state if released
        if(SW5 == notPressed)
        {
            LED6 = 0;
            SW5Pressed = false;
        }
        
        if(SW5Count >= maxCount)
        {
            LED5 = 1;
        }
         else
        {
            LED5 = 0;
        }
        
        // Reset count and turn off either LED4 or LED5
        if(SW3 == pressed && SW4 == pressed)
        {
            LED4 = 0;
            SW2Count = 0;
            LED5 = 0;
            SW5Count = 0;
        }
 * 
 * 2. Use your knowledge of Boolean variables and logical conditions to simulate
 *    a toggle button. Each new press of the toggle button will 'toggle' an LED
 *    to its opposite state. (Toggle buttons are commonly used as push-on, 
 *    push-off power buttons in digital devices.)

   //toggle button
  
 * 
 * 3. A multi-function button can be used to enable one action when pressed, and
 *    a second or alternate action when held. A variable that counts loop cycles
 *    can be used to determine how long a button is held (just as the first
 *    program unitentionally did, because of the loop structure). Make a
 *    multifunction button that lights one LED when a button is pressed, and
 *    lights a second LED after the button is held for more that one second.

     if(SW3 == pressed)
       {
           LED4 = 1;
           SW3Count = SW3Count + 1;
       }
      
       if(SW3Count >= maxCount)
       {
           LED5 = 1;
       }
       if(SW4 == pressed)
        {
            LED4 = 0;
            LED5 = 0;
            SW3Count = 0;
        }
 
 * 
 * 4. Do your pushbuttons bounce? Switch bounce is the term that describes
 *    switch contacts repeatedly closing and opening before settling in their
 *    final (usually closed) state. Switch bounce in a room's light switch is
 *    not a big concern, but switch bounce can be an issue in a toggle button
 *    because the speed of a microcontroller lets it see each bounce as a new,
 *    separate event. Use a variable to count the number of times a pushbutton
 *    is pressed and display the count on the LEDs. Use a separate pushbutton
 *    to reset the count and turn off the LEDs so that the test can be repeated.
 *    To determine if your switches bounce, try pressing them at various speeds
 *    and using different amounts of force.

unsigned char SW4Count = 0;
//toggle button
for(int i = 0; i < pressed; i ++){      
        if(SW4 == pressed)
        {
            LED5 = 1;
            }
}
if(SW5 == pressed){
    LED 5 = 0;
    SW4Count = 0;
}
 * 
 * 5. Did your pushbuttons bounce? Can you think of a technique similar to the
 *    multi-function button that could be implemented to make your program
 *    ignore switch bounces. Multiple switch activations within a 50ms time span
 *    might indicate switch bounce and can be safely ignored.

 A technique similar to a multi-function button is having a fair time span between each press. 
 */
 
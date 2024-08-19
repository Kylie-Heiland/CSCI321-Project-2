//  This program is extended from the previous project, Project #1. Using input from the user, this program can convert signed binary to decimal or signed decimal to binary
//  using two's complement. This program is also able to add two binary numbers, first by converting to two's complement if one or both of the binary numbers are negative. 
//  Finally, this program can provide sign extension so that there are 16 bit strings, as well as use two's complement of binary numbers in order to make adding binary numbers and
//  converting between binary and decimal a bit easier. 
//  Kylie Heiland
//  9/5/2022

#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>

using namespace std;

int binary_to_decimal_signed(string s);
// precondition: s is a string that consists of only 0s and 1s
// postcondition: the decimal integer that is represented by s in two's complement

string signed_extension(string s);
// precondition: s is a string that consists of only 0s and 1s that is at most 16 bits
// postcondition: a 16 bit string has been returned as signed extension of s. For instance, if s = "0101" then
//                return value will be "00000000000000000101" total 12 0s are added in front of s

string decimal_to_binary_signed(int n);
// precondition: n is an integer
// postcondition: nâ€™s two's complement binary representation is returned as a string of 0s and 1s

string add_binaries_signed(string b1, string b2);
// precondition: b1 and b2 are strings that consists of 0s and 1s at most 32 bits, i.e.
//               b1 and b2 are two's complement binary representations of two integers. "0" is 0, "1" is -1
//               However, "10" will be consider as "1111111111111110" as -2
// postcondition: the sum of b1 and b2 is returned as (up to) 32 bits two's complement representation.
// For instance, if b1 = â€œ1101â€ (-3), b2 = â€œ01â€ (+1), then the return value is â€œ1111111111111110â€ (-2)

string twos_complement(string s);
// precondition: s is a string that consists of only 0s and 1s
// postcondition: two's complement of s is returned as an 16 bits binary integer. For instance, if s = "1101", then
//                return value will be "1111111111111101"

int binary_to_decimal(string s);
// precondition: s is a string that consists of only 0s and 1s
// postcondition: the positive decimal integer that is represented by s

string decimal_to_binary(int n);
// precondition: n is a positive integer
// postcondition: nâ€™s binary representation is returned as a string of 0s and 1s

string add_binaries(string b1, string b2);
// precondition: b1 and b2 are strings that consists of 0s and 1s, i.e.
//               b1 and b2 are binary representations of two positive integers
// postcondition: the sum of b1 and b2 is returned. For instance,
//  if b1 = â€œ11â€, b2 = â€œ01â€, then the return value is â€œ100â€

void menu();
// display the menu. Student shall not modify this function

int grade();
// returns an integer that represents the studentâ€™s grade of this projects.
// Student shall NOT modify

bool is_binary(string b);
// returns true if the given string s consists of only 0s and 1s; false otherwise

bool test_binary_to_decimal_signed();
// returns true if the studentâ€™s implementation of binary_to_decimal function
// is correct; false otherwise. Student shall not modify this function

bool test_decimal_to_binary_signed();
//  returns true if the studentâ€™s implementation of decimal_to_binary function is correct; false otherwise. Student shall not modify this function

bool test_add_binaries_signed();
// which returns true if the studentâ€™s implementation of add_binaries function
// is correct; false otherwise. Student shall not modify this function

bool test_signed_extension();
// return true if the student's implementation of sign_extension function
// is correct; false otherwise. Student shall not modify this function

bool test_twos_complement();
// return true if the student's implementation of twos_complement function
// is correct; false otherwise. Student shall not modify this function


int main()
{
    int choice;
    string b1, b2;
    int x, score;
    do{
        // display menu
        menu();
        cout << "Enter your choice: ";
        cin >> choice;
        // based on choice to perform tasks
        switch(choice){
            case 1:
                cout << "Enter a binary string: ";
                cin >> b1;
                if(!is_binary(b1))
                    cout << "It is not a binary number\n";
                else
                    cout << "Its decimal value is: " << binary_to_decimal_signed(b1) << endl;
                break;
                
            case 2:
                cout << "Enter an integer: ";
                cin >> x;
                
                cout << "Its binary representation is: " <<decimal_to_binary_signed(x) << endl;
                break;
                
            case 3:
                cout << "Enter two binary numbers, separated by white space: ";
                cin >> b1 >> b2;
                if(!is_binary(b1) || !is_binary(b2))
                    cout << "At least one number is not a binary" << endl;
                else
                    cout << "The sum is: " << add_binaries_signed(b1, b2) << endl;
                break;
                
            case 4:
                cout << "Enter a binary number: ";
                cin >> b1;
                cout << "Its signed extension to 16 bits is: " << signed_extension(b1) << endl;;
                break;
                
            case 5:
                cout << "Enter a binary number: ";
                cin >> b1;
                cout << "Its two's complement is: " << twos_complement(b1) << endl;
                break;
                
            case 6:
                score = grade();
                cout << "If you turn in your project on blackboard now, you will get " << score << " out of 10" << endl;
                cout << "Your instructor will decide if one-two more points will be added or not based on your program style, such as good commnets (1 points) and good efficiency (1 point)" << endl;
                break;
                
            case 7:
                cout << "Thanks for using binary calculator program. Good-bye" << endl;
                break;
            default:
                cout << "Wrong choice. Please choose 1-5 from menu" << endl;
                break;
        }
        
    }while(choice != 7);
    return 0;
}

string signed_extension(string s){
    bool firstLoop = true;
    
    string temporary; 

    int size = s.length();
    
    if(size == 16){ //If there are already 16 bits, then no 0s are added and s is returned.
        return s;
    }

    for(int i = 1; i <= 16 - size; i++){ 
        if(firstLoop){
            if(s.at(0) == '0'){ //If the first character of the string is 0, then the characters added will all be 0.
                temporary = "0";
            }
            else{ //If the first character of the string is 1, then the characters added will all be 1.
                temporary = "1";
            }
                firstLoop = false;
            }
        else{
            if(s.at(0) == '0'){ //If the first character of the string is 0, then the characters added will all be 0.
                temporary = temporary + '0';
            }
            else{ //If the first character of the string is 1, then the characters added will all be 1.
                temporary = temporary + '1';
            }
        }
    }

    temporary = temporary + s; //Concatenates the original string to the temporary string.

    int length = s.length();
    if(length > 16){ //If there are over 16 bits, any digits past the 2^15 are ignored.
            int a = length - 16;
            temporary = "";
            for(; a < length; a++){
                temporary = temporary + s.at(a);
            }
        }

    return temporary;
}

int binary_to_decimal_signed(string s){
    int decimal;
    if(s.at(0) == '1'){ //If the highest bit is 1, the number is stored in two's complement notation.
        s = twos_complement(s);
        decimal = -binary_to_decimal(s);
    }
    else{
        decimal = binary_to_decimal(s);
    }
    return decimal;
}

string decimal_to_binary_signed(int n){
    if(n < 0){ //If the decimal number is negative.
        n = abs(n); //Convert the negative decimal number to absolute value.
        string binary = decimal_to_binary(n);
        return(twos_complement("0" + binary));
    }

    string binary = decimal_to_binary(n);

    if(binary.at(0) == '1'){ //Adds a 0 at the beginning of the string if the first character of the original string was 1.
        return signed_extension("0" + binary);
    }
    else{ //Since the highest bit is already 0, no "0" will need to be added at the beginning.
        return (signed_extension(decimal_to_binary(n))); 
    }
}

string add_binaries_signed(string b1, string b2){
    //Converts both binary numbers into decimal numbers for easier addition.
    int decimal1 = binary_to_decimal_signed(b1);
    int decimal2 = binary_to_decimal_signed(b2);

    int sum = decimal1 + decimal2; //Adds the two decimal numbers together.

    return(decimal_to_binary_signed(sum));
}

string twos_complement(string s){
    string temporary; 

    bool firstLoop = true;
    
    s = signed_extension(s); //Makes the s string be 16 bits (if it is not already).
    int size = s.length();

    for(int i = 0; i < size; i++){ //Loops through each character in the string, reversing the bit value.
        if(firstLoop){ 
            if(s.at(0) == '1') //If the string starts with 1, then it is reversed to 0.
                temporary = "0";
            else //If the string starts with 0, then it is reversed to 1.
                temporary = "1";
            firstLoop = false; //The first loop is now over.
        }
        else{
            if(s.at(i) == '0'){ //If the specific string character is 0, then it is reversed to 1.
                temporary = temporary + '1';
            }
            else{ //If the specific string character is 1, then it is reversed to 0.
                temporary = temporary + '0';
            }
        }
    }
    
    //The string of bits (binary) is now reversed.

    int decimal = binary_to_decimal(temporary) + 1; //Add 1 to the reversed binary value, which has been converted to decimal for simplicity sake.

    temporary = decimal_to_binary(decimal); //Reverses the decimal number to binary.

    if(s.at(0) == '1'){ //Adds a 0 at the beginning of the string if the first character of the original string was 1.
        temporary = signed_extension("0" + temporary); 
    }        
    else{ //If the string starts with 0.
        temporary = signed_extension(temporary); 

        s = temporary;

        int length = s.length();
        if(length > 16){ //If there are over 16 bits, any digits past the 2^15 are ignored.
            int a = length - 16;
            temporary = "";
            for(; a < length; a++){
                temporary = temporary + s.at(a);
            }
        }
    }
    return temporary; //Returns a string of binary numbers which have been reversed, converted into decimal, added by 1, and then converted back into binary (while also remaining to be 16 digits long).
}

int binary_to_decimal(string s){
    assert(is_binary(s));
    int result = 0;
    for(int i = 0; i < s.length(); i++)
        result = result * 2 + (s[i] - 48);
    return result;
}

string decimal_to_binary(int n){
    if(n == 0) return string("0"); // special case 0
    
    string result = "";
    while(n > 0){
        result = string(1, (char) (n%2 + 48)) + result; // add last digit of n in front of the result
        n = n/2;
    }
    return result;
}

string add_binaries(string b1, string b2){
    // you implement this
    assert(is_binary(b1) && is_binary(b2));
    string result = "";
    int carry = 0;
    int i1 = (int) b1.length()-1;
    int i2 = (int) b2.length()-1;
    while(i1 >= 0 || i2 >= 0)
    {
        int d1 = 0, d2 = 0;
        if(i1 >= 0) d1 = b1[i1] - 48;
        if(i2 >= 0) d2 = b2[i2] - 48;
        int sum = carry + d1 + d2; // single digit sum
        carry = sum / 2; // carry is 1 if sum is 2 or 3; 0 otherwise
        result = string(1, (char) (48+sum%2)) + result;
        i1--;
        i2--;
    }
    if(carry != 0)
        result = "1" + result;
    return result;
}
void menu()
{
    cout << "\n******************************\n";
    cout << "*          Menu              *\n";
    cout << "* 1. Binary to Decimal       *\n";
    cout << "* 2. Decimal to Binary       *\n";
    cout << "* 3. Add two Binaries        *\n";
    cout << "* 4. Signed extension        *\n";
    cout << "* 5. Two's complement        *\n";
    cout << "* 6. Grade                   *\n";
    cout << "* 7. Quit                    *\n";
    cout << "******************************\n\n";
}

int grade(){
    int result = 0;
    // binary_to_decimal function worth 2 points
    if(test_binary_to_decimal_signed()){
        cout << "binary_to_decimal_signed function pass the test" << endl;
        result += 2;
    }
    else
        cout << "binary_to_decimal_signed function failed" << endl;
    
    // decinal_to_binary_signed function worth 1 points
    if(test_decimal_to_binary_signed()){
        cout << "decimal_to_binary_signed function passed the test" << endl;
        result += 1;
    }
    else
        cout << "decimal_to_binary_signed function failed" << endl;
    
    // add_binaries function worth 2 points
    if(test_add_binaries_signed()){
        cout << "add_binaries_signed function passed the test" << endl;
        result += 2;
    }
    else
        cout << "add_binaries_signed function failed" << endl;
    
    // signed_extension function worth 1 point
    if(test_signed_extension()){
        cout << "sign_extension function passed the test" << endl;
        result += 1;
    }
    else
        cout << "sign_extension function failed" << endl;
    
    // twos_complement function worth 2 point
    if(test_twos_complement()){
        cout << "twos_complement function passed the test" << endl;
        result += 2;
    }
    else
        cout << "twos_complement function failed" << endl;
    return result;
}

bool is_binary(string s){
    for(int i = 0; i < s.length(); i++)
        if(s[i] != '0' && s[i] != '1') // one element in s is not '0' or '1'
            return false;  // then it is not a binary number representation
    return true;
}

bool test_binary_to_decimal_signed(){
    if(binary_to_decimal_signed("0") != 0 || binary_to_decimal_signed("1") != -1 || binary_to_decimal_signed("01") != 1)
        return false;
    if(binary_to_decimal_signed("010") != 2 || binary_to_decimal_signed("10") != -2)
        return false;
    if(binary_to_decimal_signed("01101") != 13 || binary_to_decimal_signed("1101") != -3)
        return false;
    return true;
}

bool test_decimal_to_binary_signed(){
    if(decimal_to_binary_signed(0) != "0000000000000000" || decimal_to_binary_signed(1) != "0000000000000001")
        return false;
    if(decimal_to_binary_signed(-1) != "1111111111111111")
        return false;
    if(decimal_to_binary_signed(-2) != "1111111111111110" || decimal_to_binary_signed(-13) != "1111111111110011")
        return false;
    return true;
}

bool test_add_binaries_signed(){
    if(add_binaries_signed("0", "0") != "0000000000000000") return false;
    if(add_binaries_signed("0", "110101") != "1111111111110101") return false;
    if(add_binaries_signed("1", "110101") != "1111111111110100") return false;
    if(add_binaries_signed("101", "111011") != "1111111111111000") return false;
    return true;
}

bool test_signed_extension(){
    if(signed_extension("1") != "1111111111111111" || signed_extension("0") != "0000000000000000") return false;
    if(signed_extension("10101") != "1111111111110101" || signed_extension("0101") != "0000000000000101") return false;
    return true;
}

bool test_twos_complement(){
    if(twos_complement("1") != "0000000000000001" || twos_complement("0") != "0000000000000000") return false;
    if(twos_complement("01") != "1111111111111111" || twos_complement("10") != "0000000000000010") return false;
    if(twos_complement("10101") != "0000000000001011") return false;
    return true;
    
}

/*
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 1
Enter a binary string: 01001011
Its decimal value is: 75

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 1
Enter a binary string: 1010001
Its decimal value is: -47

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 1
Enter a binary string: 100110000
Its decimal value is: -208

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 2
Enter an integer: -17
Its binary representation is: 1111111111101111

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 2
Enter an integer: -29
Its binary representation is: 1111111111100011

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 2
Enter an integer: 82
Its binary representation is: 0000000001010010

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 3
Enter two binary numbers, separated by white space: 0100 1101
The sum is: 0000000000000001

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 3
Enter two binary numbers, separated by white space: 0011 11101
The sum is: 0000000000000000

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 3
Enter two binary numbers, separated by white space: 001110 111111110
The sum is: 0000000000001100

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 4
Enter a binary number: 1100110
Its signed extension to 16 bits is: 1111111111100110

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 4
Enter a binary number: 0100101
Its signed extension to 16 bits is: 0000000000100101

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 4
Enter a binary number: 1010101010101011101
Its signed extension to 16 bits is: 0101010101011101

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 5
Enter a binary number: 10101001110
Its two's complement is: 0000001010110010

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 5
Enter a binary number: 01101010
Its two's complement is: 1111111110010110

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 5
Enter a binary number: 10100101101110
Its two's complement is: 0001011010010010

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 6
binary_to_decimal_signed function pass the test
decimal_to_binary_signed function passed the test
add_binaries_signed function passed the test
sign_extension function passed the test
twos_complement function passed the test
If you turn in your project on blackboard now, you will get 8 out of 10
Your instructor will decide if one-two more points will be added or not based on your program style, such as good commnets (1 points) and good efficiency (1 point)

******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decimal to Binary       *
* 3. Add two Binaries        *
* 4. Signed extension        *
* 5. Two's complement        *
* 6. Grade                   *
* 7. Quit                    *
******************************

Enter your choice: 7
Thanks for using binary calculator program. Good-bye */
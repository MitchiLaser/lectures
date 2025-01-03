# TCL Cheat Sheet

## Print to console
```tcl
puts "Hello, World!" ;# prints text in double quotes
puts {Hello, World!} ;# prints text in curly braces

puts -nonewline Hello
puts World! ;# prints text without quotes or braces
```
## Comments

Comments in TCL are either at the beginning of a line and starting with a `#` or in between a line and starting with `;#`. The semicolon is important to separate TCL commands from the comment.
```tcl
# This is a comment
puts "Hello, World!" ;# This is also a comment
```
## Variables

Variables in TCL are defined using the `set` command. The content of the variable can be accessed using the `$` sign.
```tcl
set name "John Doe"
puts $name
```
The value of a variable can also be accessed within a string:
```tcl
set name "John Doe"
puts "Hello, $name" ;# prints "Hello, John Doe"
```
To forget the content of a variable, the `unset` command can be used.
```tcl
set name "John Doe"
puts $name ;# prints "John Doe"
unset name
puts $name ;# Error: can't read "name": no such variable
```
## Escaped Sequences

Using the `$` sign, the value of a variable can be substituted in a string. What do we do when we want to print the raw text instead of performing a substitution? For this special case, the `$` sign can be escaped using the backslash `\`.
```tcl
set name "John Doe"
puts "Hello, $name" ;# prints "Hello, John Doe"
puts "Hello, \$name" ;# prints "Hello, $name"
```
There are also other special characters that can be escaped using the backslash `\`:
- `\n` - newline
- `\t` - tab
- `\"` - double quote
- `\\` - backslash
```tcl
puts "This string is two li\nes long."
puts "This string has a \tab in the middle."
puts "This string has a \"quote\" in it."
```
The backslash can be used to escape the last character of a line to continue the command on the next line.
```tcl
puts "This is a very long string \
that spans multiple lines."
```
It is highly recommended to use the backslash to escape a dollar sign when it is not used for variable substitution, even though most of the times it also seems to work without escaping it.
```tcl
set a anything
puts "$$a is good but \$$a is better."
```

## Curly Brackets

Curly brackets `{}` can be used in a similar way as double quotes `""` to define a string. The big difference between the two is that the curly brackets do not perform variable substitution. Even the backslash does not escape the special characters in curly braces as it does in double quotes.
```tcl
set phrase "The lemon is sour"
puts "$phrase" ;# prints "The lemon is sour"
puts {$phrase} ;# prints "$phrase"
# further examples
puts "{$phrase}" ;# prints the phrase with curly braces
puts {I don't think, "the lemon tastes sour."} ;# prints the phrase, including the double quotes
```
The only thing that is substituted in curly braces is the backslash `\` to continue the command on the next line.
```tcl
puts {This is a very long string\
that spans multiple lines.}
# prints "This is a very long string that spans multiple lines."
```
In this example the backslash in combination with the line break is replaced with a space.

## Square Brackets: Interpolation

Commands within square brackets are evaluated before the surrounding command is executed. The result of the command within the square brackets is substituted in the surrounding command which is executed afterwards. This process is called interpolation. At first a simple example shows hot two variables can be initialised with the same value, using the `set` command which returns the value of the variable it sets.
```tcl
set a [set b 42]
puts $a ;# prints 42
puts $b ;# prints 42
```
In this example the `set` command within the square brackets is executed first and returns the value `42`. This value is then substituted in the surrounding `set` command which sets the variable `a` to `42`. This substitution only works when it is not being used in curly braces.
```tcl
set z {[set x "string 1"]}
puts $z ;# prints [set x "string 1"]
puts $x ;# Error: can't read "x": no such variable
```
Double quotes allow for a substitution of the command within a string.
```tcl
set z "[set x "string 1"]"
puts $z ;# prints string 1
puts $x ;# prints the same thing
```
Within double quotes the square brackets can be escaped using the backslash.
```tcl
set z "\[set x "string 1"\]"
puts $z ;# prints [set x {string 1}]
puts $x ;# Error: can't read "x": no such variable
```

## Arithmetic Operators

The `expr` command is used to evaluate arithmetic expressions and return the result as a string. The result can be stored in a variable using interpolation:
```tcl
set a 5
set b 3
puts [expr $a + $b] ;# prints 8
puts [expr {$a + $b}] ;# prints 8
```
**Performance Tipp**: Using curly braces `{}` around the expression (`{$a + $b}`) is faster than using no braces (`$a + $b`) because then the result is just the string which can be evaluated later. This might come at the cost of some side effects.

The `expr` command supports a variety of arithmetic operators as well as mathematical functions (`sin()`, `cos()`, `log()` which is the natural logarithm to the base e, `sqrt()` and many others) and the evaluation of boolean expressions. Within the expression brackets are used the same way as in regular mathematical expressions. Many commands use `expr` behind the scene, such as `if`, `while` and `for` which are discussed later.

If there are two operators applied to the same operand, the operators are applied along a pre defined preference order. The following example demonstrates this behavior with the addition and the multiplication operator. It also shows that brackets change the order of the evaluation.
```tcl
puts [expr {2 + 2 * 4}] ;# prints 10
puts [expr {(2 + 2) * 4}] ;# prints 16
```
### Operands

Where possible, operands are interpreted as integer values. They might be specified in decimal, in binary with the first two characters being `0b`, in octal with the first character being `0o` or in hexadecimal with the first two characters being `0x`. For compatibility reasons with older TCL versions an octal value is also detected when only the first character is `0`. The following example demonstrates this behavior where each statements prints the number `10`.
```tcl
puts [expr 10]
puts [expr 0b1010]
puts [expr 0o12]
puts [expr 0xA]
```
If no integer representation of the operand is possible, the operand is interpreted as a floating point number. There are many ways to specify a floating point number, as shown in the following example:
```tcl
puts [expr 3.14]
puts [expr 3.] ;# the decimal part is 0
puts [expr .14] ;# the integer part is 0
puts [expr 3.5e-1] ;# scientific notation
```
If none of these representations is possible, the operand is interpreted as a string.
```tcl
set number 3,14 ;# the comma is not the decimal separator!
expr {$number > 3} ;# True, because the string "3,14" alphabetically comes after "3"
expr {$number > 3.0} ;# False, because the string "3,14" alphabetically comes before "3.0"
```

### Operators for integers

The following table lists all the operators that work on numbers (integers and floats). This table is sorted by the hierarchy of the operators: Operators listed first in this list are the preferred ones.

| Operator   | Description                        | Explaination                                   |
| :--------: | :--------------------------------: | :-----------------------------------:          |
| - +        | unary minus, unary plus            | multiplication with (-1) / with (+1)           |
| **         | exponent                           |                                                |
| * / %      | multiplication, division, modulo   | modulo is the remainder of a division          |
| + -        | addition, subtraction              |                                                |
| << >>      | shift left / shift right           | perform a bitwise shift                        |
| < <= > >=  | comparison                         | less, less or equal, greater, greater or equal |
| == !=      | equality, inequality               |                                                |
| ~ !        | bitwise NOT, logical NOT           |                                                |
| &          | bitwise AND                        |                                                |
| ^          | bitwise XOR                        |                                                |
| \|         | bitwise OR                         |                                                |
| &&         | logical AND                        |                                                |
| \|\|       | logical OR                         |                                                |
| ? :        | conditional (ternary operator)     | later explained in detail                      |

### Operators for strings

There are only two groups of operators available to compare strings with each other:

| Operator          | Description                        | Explaination                                   |
| :--------:        | :--------------------------------: | :-----------------------------------:          |
| == != < > <= >=   | comparison                         | less, less or equal, greater, greater or equal |
| eq ne lt gt le ge | comparison                         | less, less or equal, greater, greater or equal |

### Ternary operator

The ternary operator `? :` is a conditional operator that is used to evaluate a boolean expression. It can be described as a short form of an `if` - `else` statement: `condition ? return-if-true : return-if-false`. The following example demonstrates the usage of the ternary operator.
```tcl
set x 1
expr{ $x % 2 ? "Odd" : "Even" } ;# prints "Odd"
```
In this example the condition `1 % 2` is evaluated to `1` which is interpreted as `True` (everything which is not equal to zero is treated as `True`). The string `"Odd"` is returned if the condition is `True` and the string `"Even"` is returned if the condition is `False`.

### Mathematical functions

By default there is a set of mathematical functions available in TCL. These functions can be used in the `expr` command. The following example demonstrates the usage of the `sqrt()` function.
```tcl
puts [expr {sqrt(9)}] ;# prints 3.0
```
The following table lists all the mathematical functions that are available in TCL:

|       |        |        |       |
|:-----:|:------:|:------:|:-----:|
| abs   | acos   | asin   | atan  |
| atan2 | bool   | ceil   | cos   |
| cosh  | double | entier | exp   |
| floor | fmod   | hypot  | int   |
| isqrt | log    | log10  | max   |
| min   | pow    | rand   | round |
| sin   | sinh   | sqrt   | srand |
| tan   | tanh   | wide   |       |

### Data types

TCL does not know many data types beside strings. There are four different representations of number: `double`, `int` (integer), `wide` (large integer) and `entire` (integer or wide, depending on the context). These are also the names of the functions to convert between the data types.

- `double` contains a (double precision) floating point number
- `int` contains an integer value. The conversion from a double to an integer truncates the decimal part.
- `wide` contains a large integer value. It behaves the same as `int` but can store larger numbers.
- `entire` contains an integer of appropriate size. Depending on the number itself the data type is either `int` or `wide` or an integer of arbitrary size.

These representations are important because computers internally have different methods to store numbers. There are some rules for the data type of the result of an operation: If both operands are integers, the result is an integer. If at least one of the operands is a double, the result is a double. This can lead to some unexpected results:
```tcl
puts [expr 1/2] ;# prints 0 because the decimal part is truncated
puts [expr -1/2] ;# prints -1
puts [expr 1.0/2] ;# prints 0.5
puts [expr 1/2.0] ;# prints 0.5
puts [expr double(1)/2] ;# prints 0.5
```
The representation for floating point values is not always exact because there are some numerical abbreviations. These are regularly really small but can ad up and lead to some unexpected results.
```tcl
set pi1 [expr {4*atan(1)}]
set pi2 [expr {6*asin(0.5)}]
puts [expr {$pi1-$pi2}] ;# -4.440892098500626e-16
```
### Examples

**Square root**
```tcl
set x 100
set y 256
puts "The square root of [expr $x + $y] is [expr {sqrt($x + $y)}]"
```
**Hypotenuse of a triangle**
```tcl
set A 3
set B 4
puts "The hypotenuse of a triangle: [expr {hypot($A, $B)}]"
```
**Attention: Numbers with leading zero**

Every number that starts with a `0` is interpreted as an octal number. Therefore the number `0700` is interpreted as `7*8*8 = 448`. This produces errors, when the number contains an `8` or a `9`.
```tcl
expr {0900+1} ;# should be "$0900" or "{0900}" or "0900(...)" or ... (invalid octal number?)
```
## Control Structures: If

The syntax for the `if` statement is as follows, where the `else` and `elseif` parts are optional (indicated with question marks):
```tcl
if {expr1} ?then? {
    body1
} elseif {expr2} ?then? {
    body2
} elseif {
    ...
} else {
    bodyN
}
```
There are different ways how a condition can be evaluated:

|                     | False |            True |
|:--------------------|:-----:|----------------:|
| numeric value       |   0   | everything else |
| string "Yes" / "No" |  "No" |           "Yes" |
| True / False        | False |            True |

Strings which are identical to "Yes", "No", "True" or "False" are interpreted as boolean values. There is no case sensitivity, meaning that "YeS" and "nO" are also valid boolean values.

If the condition is true then the body of the `if` statement is executed. Otherwise the next condition is checked and if the last condition is false the `else` part is executed.
```tcl
set x 1

if {$x == 2} {puts "$x is 2"} else {puts "$x is not 2"}

if {$x != 1} {
    puts "$x is != 1"
} else {
    puts "$x is 1"
}
```
In these examples it is important that an opening curly brace `{` is on the same line as the previous closing curly brace `}` and the condition is in the same line as the `if` statement. Otherwise the `if` statement is not recognized as a single command.

## Control Structures: Switch

Instead of a long chain of `if` - `elseif` - `else` statements, the `switch` statement can be used. The syntax is as follows:
```tcl
switch ?options? string {
   pattern1 {
       body1
   }
   ?pattern2 {
       body2
   }?
   ...
   ?patternN {
       bodyN
   }?
}
```
The `switch` statement compares the string with the patterns. If the first pattern matches the string, the body of the first pattern is executed. If the first pattern does not match the string, the next pattern is checked. This process is repeated until a pattern matches the string or the end of the `switch` statement is reached.

If none of the patterns match the string and a `default` pattern is provided, the body of the `default` pattern is executed. This pattern is optional and needs to be placed as the last pattern in the `switch` statement. This guarantees that some set of code will be executed no matter what the content of the string is. If there is no `default` pattern and none of the patterns match the string, the `switch` command returns an empty string.

By default the `pattern` uses the *glob-style matching* where the asterisk `*` matches any sequence of characters, e.g, the pattern `chocolate*` matches the strings `chocolate`, `chocolates` or `chocolate-cake` but not `choco-late`. This can be disabled by using `-exact` for the options, causing the patterns to be treated as strings which have to be matched exactly. Another alternative is to use `-regexp` for the options, which allows for regular expressions to be used as patterns, which are described later in detail.

Here are some examples for the use of the `switch` statement:
```tcl
set x 1
switch $x {
    1 {puts "One"}
    2 {puts "Two"}
    3 {puts "Three"}
    default {puts "Something else"}
}
```
When there are two patterns which want to use the same body, the `-` sign tells to use the body of the next pattern. The following example demonstrates this behavior:
```tcl
set str "a"
switch -exact $str {
    "a" -
    "b" {
        puts "Using the body of pattern 'b' for both a and b"
    }
}
```
The `switch` statement becomes more useful than nested `if` - `elseif` - `else` statements when there are many conditions to check:
```tcl
set edges 3

switch $edges {
    0 -
    1 -
    2 {puts "Not a polygon"}
    3 {puts "Triangle"}
    4 {puts "Quadrilateral"}
    5 {puts "Pentagon"}
    6 {puts "Hexagon"}
    # further patterns ...
    default {puts "Unknown polygon"}
}
```
The last example shows that variable substitution is not available for the patterns because the whole `switch` statement is surrounded by curly braces:
```tcl
set x [set y 1] ;# set both variables to 1

switch $x {
   $y {puts "The value of x is the same as the value of y"}
   1 {puts "The value of x is 1"}
   default {puts "No match for x"}
}
```
This example prints the text *The value of x is 1*. When the variable x is set the following way: `set x {$y}` the text *The value of x is the same as the value of y* is printed.

### Alternative Syntax

Regularly the patterns do not allow for a variable substitution because the whole `switch` statement is surrounded by curly braces. To bypass this limitation the `switch` statement supports an alternative syntax in which the curly braces are omitted and all the patterns are passed to the switch statement as arguments:
```tcl
switch ?options? string\
   pattern1 {
       body1
   }\
   ?pattern2 {
       body2
   }?\
   ...\
   ?patternN {
       bodyN
   }?
```
In this case the backslashes are necessary to continue the switch command on the next line. The following example demonstrates the usage of the alternative syntax for the previous example:
```tcl
set x [set y 1]

switch $x\
    $y {
        puts "The value of x is the same as the value of y"
    }\
    1 {
        puts "The value of x is 1"
    }\
    default {
        puts "No match for x"
    }
# prints "The value of x is the same as the value of y"
```
## Control Structures: While loop

The `while` loop is used to execute a block of code as long as a condition is true. The syntax is as follows:
```tcl
while condition {
    body
}
```
The condition is evaluated every time before the body of the loop is executed. When the condition evaluates to `true` the body of the loop is executed and the whole process repeat's itself. Otherwise when the condition evaluates to `false` the body is skipped and the program continues after the loop.

The condition goes through the same substitution and evaluation process as every command. It can be placed within curly braces `{}` or a string with double quotes `""`. When the condition is a constant string, the `while` loop is executed infinitely (as long as the string is not empty or `"false"`).
```tcl
set x 1
while {$x < 10} {
    puts $x
    set x [expr $x + 1]
}
```
This example will print the numbers from 1 to 9. The condition is evaluated before the body of the loop is executed. The variable `x` is incremented by one in every iteration of the loop.

### Continue and Break

Within the body of the `while` loop the `continue` command can be used to skip the rest of the body and start the next iteration of the loop. The `break` command can be used to exit the loop immediately and continue the program with the code after the loop.
```tcl
set x 1
while {$x < 10} {
    set x [expr $x + 1]
    if {$x > 7} break
    if {$x < 2} continue
    puts $x
}
# prints numbers 3 to 7
```
The loop starts with its initial value of `x` being set to `1`. At the beginning of the body the value of `x` is incremented by one. If `x` is greater than `7` the loop is exited immediately. As long as `x` is less than `2` the execution of the body is skipped and the next iteration of the loop is started where the condition is evaluated again and the body gets executed. Therefore the values `1` and `2` are not printed and the loop stops at values higher than `7`.

## Control Structures: For loop

Another loop constructor is the for loop which is used to execute a block of code based on a count-oriented condition. There are many cases where a loop is used to count a variable from a start value to an end value. With a `while` loop it might be done the following way:
```tcl
set x 1
while {$x <= 10} {
    # The body
    # This is where the code for the loop goes
    # ...
    set x [expr $x + 1] ;# increment the loop variable
}
```
Even though this works perfectly fine is introduces some boilerplate code: The initialisation of the loop variable before entering the loop and the incrementation of the loop variable at the end of the loop. The `for` loop is a more concise way to write this kind of loop by combining the initialisation, the condition and the incrementation of the loop variable in one line. The syntax is as follows:
```tcl
for {start} {condition} {next} {
    body
}
```
The `start` part is executed once before the loop starts to perform an initialisation of the loop variable. On each iteration of the loop the `condition` is evaluated and the body is executed if the condition is true (like in the `while` loop). After every execution of the body the `next` part is executed before re-evaluating the condition. This is typically used to increment or decrement the loop variable.

It is important to have the opening curly brace `{` on the same line as the `for` statement. Otherwise it is not recognized as a single command and the TCL interpreter will throw an error. Within the body the loop can be exited using the `break` command and the next iteration can be started using the `continue` command, where the evaluation of the body is aborted but the incrementation is still executed.

Because incrementing the loop variable is a common task, TCL has a special command to replace `set x [expr {$x + 1}]` with `incr x`. By default an incrementation increases the value by one but it can be changed by providing a second argument to the `incr` command. When setting this value to `-1` the loop variable is decremented instead.
```tcl
for {set i 0} {$i < 10} {incr i} {
    puts $i ;# prints the numbers 1 to 10
}

for {set i 10} {$i > 0} {incr i -1} {
    puts $i ;# prints the numbers 10 to 1
    if {$i == 5} break ;# abort the execution of the loop when i is 5
}
```
## Procedures

Procedures are used to group a set of commands together. Instead of copying and pasting the same code multiple times, the code can be placed in a procedure and called whenever it is needed. Let's assume that your code needs to print the same text multiple times. Instead of writing the same code multiple times, a procedure can be defined which prints the text. Here is the code for this example:
```tcl
proc printText {} {
    puts "Hello, World!"
}

printText ;# call the procedure the first time
printText ;# call the procedure the second time
```
When the procedure is called, the execution jumps to the lines of the procedure and executes the code defined there. After the execution of the procedure the execution jumps back to the line where the procedure was called and continues with the code there. In the example above the procedure is defined using the `proc` command, followed by the name of the procedure. We will shortly take a closer look on the empty curly braces `{}`. The body of the procedure is placed within curly braces like the body of a loop or a conditional statement. The procedure is called by using the name of the procedure.

**Arguments**

Procedures can take arguments which are used within the body of the procedure. Take a look on the following example: You have multiple situations where you need to calculate the mean value of three numbers. Since you have to perform this operation multiple times it is useful to define a procedure for this task. Your procedure should take three arguments and perform the calculation based on this input.
```tcl
proc mean {a b c} {
    expr {($a + $b + $c) / 3.0} ;# the calculated value is returned.
}

puts [mean 1 2 3] ;# prints 2.0
puts [mean 4 5 6] ;# prints 5.0
```
The curly braces after the name are used to define the arguments of the procedure. These are variables that can be accessed within the body. The initialisation of these variables is done when the procedure is called. All arguments are separated by spaces, there is no limit for the number of arguments.

With this completed picture of procedures in TCL the syntax of the `proc` command can finally be summarized:
```tcl
proc name {arguments} {
    body
}
```
When `proc` is evaluated it creates a new command. This can also be used to overwrite existing procedures as well as builtin commands, like the `for` or the `while` loop.

### Return Value

In the previous example a value was calculated based on the input arguments. This value can either be printed on the command line within the procedure or it can be returned to the calling code. Imagine you want to use the `mean` procedure in the following way:
```tcl
set x [mean 1 2 3]
puts "The mean value is $x"
```
In this case the evaluation of the `mean` procedure call needs to be replaced by the calculated value which then can be stored in the variable `x`. When a procedure ends with a line of code producing a value, this value is returned to the calling code. Alternatively the `return` command takes a value and returns it to the calling code. It also exits the procedure immediately. The following example demonstrates this behavior:
```tcl
proc mean {a b c} {
    return [expr {($a + $b + $c) / 3.0}] ;# use of return is optional but not wrong
}
```
The following example uses the `return` command to abort the execution of a procedure when a condition is met. The return value is based on the condition:
```tcl
proc abs {a} {
    if {$a < 0} {
        return [expr {-1 * $a}] ;# abort execution and return negative value
    }
    return $a
}

puts [abs -5] ;# prints 5
puts [abs 5] ;# prints 5
```
Even though a procedure can have a large amount of arguments it can only return one single value. In case the execution of the procedure needs to be aborted but there is no value to return, the `return` command can be used without an argument, which is equivalent to returning an empty string.

### Variation in Arguments

By now all out examples have taken a fixed number of arguments, defined with the procedure. But what if the number of arguments is not fixed? TCL offers the possibility of default values for these arguments, in case they are not provided. In the following example the default values for the arguments `b` and `c` are provided by grouping them with the argument name in curly braces `{}`. This allows to call the procedure with only a single argument, two arguments or up to three arguments. Note that the arguments with default values have to be defined after the arguments without default values.
```tcl
proc callme {a {b 2} {c 3}} {
    puts "a: $a, b: $b, c: $c"
}

callme 1 ;# prints "a: 1, b: 2, c: 3"
callme 1 4 ;# prints "a: 1, b: 4, c: 3"
callme 1 4 5 ;# prints "a: 1, b: 4, c: 5"
```
When the last declared arguments is the word `args`, the procedure can take an arbitrary number of arguments. These arguments are stored in a list which can be accessed within the body of the procedure. The details of this are going to be explained later in detail.

## Variabel Scope

There are different locations where variables can be defined: As an argument or within the body of a procedure, or somewhere else in the TCL script. Based on the location where a variable is defined, the variable has a different region where it is available, called the *scope*. It can be bound to the body of a procedure / conditional statement / ... or it can be available within the whole script. These two fields of availability are called the local and the global scope.

The topmost level is the **global** scope where variables are available within the whole script. Otherwise variables are bound to a **local** scope when they are defined within a procedure or a namespace (more on that later).

The scope in which a variable is accessible can be changed using the `global` and the `upvar` command. The `global` command will make a variable from the global scope available within a local scope. This can be used to transfer data from a procedure:
```tcl
global log ;# declare global variable
# it is not necessary to declare this variable before its usage

proc logMessage {message} {
    global log ;# make variable available in the local scope
    set log "$message"
}

logMessage "Something is gonna happen"
puts $log
```
The `upvar` command works in a similar way: It makes a variable from a higher scope available within the current scope. The syntax of the `upvar` command is as follows:
```tcl
upvar ?level? otherVar myVar
```
This makes the variable `otherVar` from another scope available in the current scope unter the name `myVar`. To describe from which scope the variable `otherVar` should be taken, the `level` argument needs to provide this information: It contains the number of levels to go up in the scope hierarchy (the number of nested function calls). The default value for `level` is `1` which means that the variable is taken from the next higher scope. The number can also be defined with a preceded `#` symbol to reference levels down from the global scope, where `#0` is the global scope itself. Because this can lead to a lot of trouble, it is highly recommended to use `upvar` only with the default value for `level`. The following example demonstrates the usage:
```tcl
proc setPositive {variable value} {
    upvar 1 $variable myvar
    if {$value < 0} {
        set myvar [expr {-$value}]
    } else {
        set myvar $value
    }
}

setPositive x -5
setPositive y 5
puts "X :$x    Y: $y" ;# prints "X: 5 Y: 5"
```
## Lists
TODO! Continue at: https://wiki.tcl-lang.org/page/Tcl+Tutorial+Lesson+14

Lists are a fundamental data type in TCL. They are used to store multiple values in a single variable. The values are separated by spaces and can be of any data type. The following example demonstrates the creation of a list:
```tcl
# set a variable to a list of values
set lst {1 2 3 4 5}

# use the split command
set lst [split "1.2.3.4.5" "."] ;# split at the dots

# use the list command
set lst [list 1 2 3 4 5]
```
The `split` command is used to split a string into a list of values. The first argument is the string to split and the second argument is the character which is used to split the string. The `list` command is used to create a list of values. The values are separated by spaces and can be of any data type.

Each element in the list can be accessed using its corresponding index. The index starts at `0` and goes up to the number of elements in the list minus one. The following example demonstrates the access with the `lindex` command. It also demonstrates the usage of the `llength` command which returns the number of elements in a list (the largest index plus one):
```tcl
set lst {1 2 3 4 5}
for {set i 0} {$i < [llength $lst]} {incr i} {
    puts [lindex $lst $i]
}
```
The first argument of the `lindex` command is the list and the second argument is the index of the element. In general a string which contains spaces is treated as a list of strings, separated by spaces. When accessing an index which is out of bounds, the `lindex` command returns an empty string.

## List Operations

Two lists can be joined together using the `concat` command. It takes an arbitrary number of lists as arguments and returns a new list which contains all the elements of the input lists.
```tcl
set lst1 {1 2 3}
set lst2 {4 5 6}
puts [concat $lst1 $lst2 "7"] ;# prints "1 2 3 4 5 6 7"]
```
The `concat` command can take an arbitrary number of lists or strings as arguments but the order of the return value stays preserved as the order of the input lists.

To insert an element at a specific index in a list the `linsert` command can be used. The first argument is the list, the second argument is the index and the third argument is the value to insert. In the following example the value `7` is inserted before the 3rd position (index 2) to be available at the index 2 in the resulting list:
```tcl
set lst {1 2 3 4 5}
set lst [linsert $lst 2 7]
puts $lst ;# prints "1 2 7 3 4 5"
```
To add new values at the end of a list the `lappend` command can be used. The first argument is the list and the remaining arguments are the values to append.
```tcl
set bakery "bread cheesecake croissant"
lappend bakery "Donut" "eclair"
puts $bakery ;# prints "bread cheesecake croissant Donut eclair"
```
The `lreplace` command is used to replace a range of elements in a list with a new list of elements. The first argument is the list, the second argument is the first index to be replaced, the third argument is the last index to be replaced and the remaining arguments are the new elements. In the following example the elements at the 2nd and 3rd position are replaced with the elements `7` and `8`:
```tcl
set lst {1 2 3 4 5}
set lst [lreplace $lst 1 2 7 8]
puts $lst ;# prints "1 7 8 4 5"
```
In these cases using a string with spaces treats the argument as a separate list instead of single list entries:
```tcl
lreplace "Hello World" 1 1 "Chocolate" "Cake"
# prints "Hello Chocolate Cake"

lreplace "Hello World" 1 1 "Chocolate Cake"
# prints "Hello {Chocolate Cake}"
```
To extract a sub-list from a list the `lrange` command can be used. The first argument is the list, the second argument is the first index to extract and the third argument is the last index to extract.
```tcl
set lst {1 2 3 4 5}
puts [lrange $lst 1 3] ;# prints "2 3 4"
```
Sorting a list is done using the `lsort` command. It performs a lexicographical sort on the elements of the list. The sorting algorithm in use is Merge Sort with a runtime complexity of O(n log n).
```tcl
set numbers {5 3 1 4 2}
puts [lsort $numbers] ;# prints "1 2 3 4 5"
puts [lsort -decreasing $numbers] ;# prints "5 4 3 2 1"
```
The sorting might be done in decreasing order by providing the `-decreasing` option. The `-integer` option can be used to sort the list as integers instead of strings. The `-real` option can be used to sort the list as floating point numbers.
```tcl
set numbers {5.7 3.2 1.1 4.9 2.3}
puts [lsort -real -decreasing $numbers] ;# prints "5.7 4.9 3.2 2.3 1.1"
```

//TODO

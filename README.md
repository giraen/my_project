# **Sample testing with Ceedling framework**

## Pre-requisites
The current machine must have the following installed:
1. [Ruby](https://rubyinstaller.org/) to install the framework
2. Your preferred code editor. In this case, I used [VSCode](https://code.visualstudio.com/download)
3. [Git](https://git-scm.com/downloads) for version control
4. [MinGW](https://sourceforge.net/projects/mingw/) to download the compiler for C/C++
5. [Python](https://www.python.org/downloads/) if we want to use gcovr

## Steps
1. Install the pre-requisites. For the setup of ruby, it comes with the installation of mingw. Since we have mingw installed separately, we can opt to not include that anymore.
2. To use and compile C/C++ in VSCode, we have to the recommended extensions.
3. After setting everything up, use a terminal and type the following and hit enter.
```ruby
gem install ceedling
```
4. In the terminal again, type and enter the following to scaffold a C project.
```ruby
ceedling new <name of the project>
```
For example, we can call it my_project
```ruby
ceedling new my_project
```
5. Take note that everything we put in src/ are codes we want to test. Under test/ are the codes that will test everything found in the src/

## Writing the test codes
### Example 1
Let's assume we are testing basic_ops.c
Then, the file under test/ should be named test_basic_ops.c
It should always follow the naming format of test_*.c
Inside the test file, header file of the actual code that we want to test and unity header must always be added. Then, we can use test functions such as ```TEST_ASSERT_EQUAL()``` that compares the output of the code to the expected value.

### Example 2
For another test, we will test led_drive.c
Since there are two functions inside it, one helps in setting up the global variable, another outputs it. For that, we will use the set function and use the assertion of equal to the function that will output the value of the variable. As observed, there is another function called setup and teardown which will be used later on.

### Example 3
For this example, the global variables must be declared with extern as well as the data type. Then initialize the variables inside setUp. setUp will reset these variables for every test done. Without it, the value of the variables will be retained for the next test.
Meanwhile, tearDown are used for freeing memory, and resetting mocks.  

Example 3 Test case 2 shows how we can test the function's behavior or operation when it comes to changing the global variables. The variable result will just store the success of executing the function. Thus, it can be removed so that the function will appear to have parameters with no return values. In this case, we are checking if 5 (in bit) is same with Jill after telling the do_bit_man that will manipulate Jill (see code of bit_manipulation.c)

Example 3 also demonstrates mocking of functions. By adding this code below
```C
#include "mock_adc.h"
```
It already assumes a mock of the adc.c
This allows us to input arguments to the functions found inside the file. In this case, we used adc_read_ExpectAndReturn with the argument of 35. This means that we expect a function adc_read and it should return 35. Thus, when we executed line 51, aside from manipulating the bits, it also executed the if-else block. For mocking, we should follow the format of
```
<name of the original function>_<something you want to do>
```
So it could be any of the following
```
<name of the original function>_ExpectAndReturn
<name of the original function>_ExpectAndThrow
<name of the original function>_StubWtihCallback
<name of the original function>_IgnoreAndReturn
<name of the original function>_ExpectWithArray
<name of the original function>_Ignore
<name of the original function>_Ignore_<name of parameter to ignore>
<name of the original function>_ReturnThruPtr_ParameterName
```
Some can be found through the summary included in this repository. Additionally, some needed some plugin or modification in the project.yml such as the ExpectWithArray. It can be added under :cmock: then :plugins:

So for array, we can just add it as '- :array'
For ReturnThruPtr, it is '- :return_thru_ptr'

## Usage with Github actions
Github actions configurations especially under steps are just the commands or calls to packages from github executed in order.
Checkout is always used, then next is the ruby and the dependencies. Then, similar on how we test it in our local machine, we also use the command ceedling test:all which will run all the tests that we have. Take note that this may vary depending on the runner (runs-on) that we have as we add more packages that will test our code remotely. This could be a linter, gcovr, and more.
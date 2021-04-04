# CPPND: Capstone AdminChatBot!
This readme file is best read on github while in the root directory of the project. https://github.com/astroess/CppND-Capstone-AdminChatbot .  Capstone Option 1 - Chatbot was chosen to fulfill the requirement. <br><br>
The AdminChatBot is made up of 2 applications.  When the project is built using the "Basic Build Instructions" below, 2 executables are generated (adminuser and adminchatbot).  adminuser is a command line program that will allow the admin user to add new Admin users for use within the adminchatbot application.  The adminchatbot executable is the actual chatbot gui application.  Both programs should be run from the build directory.  

<h2>Dependencies for Running Locally</h2>
* cmake >= 5.5 <br>
* All OSes: [click here for installation instructions](https://cmake.org/install/) <br>
* make >= 4.1 (Linux, Mac), 3.81 (Windows) <br>
  <blockquote>* Linux: make is installed by default on most Linux distros<br>
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/) - not tested. <br>
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm) - not tested.</blockquote>
* gcc/g++ >= 5.5 <br>
  <blockquote>* Linux: gcc / g++ is installed by default on most Linux distros<br>
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)<br>
  * Windows: recommend using [MinGW](http://www.mingw.org/) </blockquote>
* wxWidgets >= 3.0.  This was already installed in Udacity's workspace. <br>
* RapidJson >= 1.1.  This is included with the project code.  No extra install is needed.

<h2>Class Files Tree</h2>
<img src="images/ClassStructure.jpg" title="admin chatbot"/>
<ul>
  <li>The "data" directory contains 2 files for both programs.  The "adminusers.txt" file contains user names and passwords for both programs.  The "answers.json" file contains the keywords and answers for adminchatbot in JSON format.</li>
  <li>The "images" directory contains the images for the AdminChatBot.</li>
  <li>The "include" directory contains the header files and rapidjson parser header files.</li>
  <li>The "src" directory contains the implementation code.</li>
  <li>The "utils" directory contains the adminusers.cpp file that contains the procedural code for adminusers.</li>
  <li>adminutility.h, adminutility.cpp -  These are the header and implementation files for the AdminUtility class. This is a standard utility class with miscellaneous functions used by both prorams.</li>
  <li>answernode.h, answernode.cpp - These are the header and implementation files for the AnswerNode class.  This class is delcared and initialized as a unique smart pointer and hold the current state of the keywords/answers' data file in memory.</li>
  <li>answers.h, answers.cpp - These are the header and implementation files for the Answers class.  This class holds the wxWidgets definitions for the Answers Dialog window that contains the JSON data current held in the AnswerNode class.</li>
  <li>chatbot.h, chatbot.cpp - These are the header and implementation files for the ChatBot class.  This class is repsonsible for handling messages between the user and AdminChatbot application.  It also holds the Levenshtein string distance calculation function.</li>
  <li>chatgui.h, chatgui.cpp - These are the header and implementation files for variable wxWidget Frame and Dialog classes for the application.</li>
  <li>chatlogic.h, chatlogic.cpp - These are the header and implementation files for the ChatLogic class.  The ChatLog class controls the flow of data within the AdminChatBot application.</li>
</ul>

<h2>Basic Build Instructions</h2>

1. Clone this repo, https://github.com/astroess/CppND-Capstone-AdminChatbot.git
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./adminuser or ./adminchatbot`.

<b>Suggested Run Path</b>
1. Run adminuser first and add a user/password for yourself.
2. Then run adminchatbot and use the created credentials in the previous step to log in as an admin.  User/passwords are case sensitive.
3. Experiment with adding new answers and keywords.  It is assumed that the person running adminchatbot understands the structure of Json data.
4. It is assumed that both executables will be run from the ./build directory.  Future enhancements could include a properties file that would define data file locations.

<h2>Admin User (adminuser) Details</h2>
<img src="images/AdminUser.jpg" title="admin user"/>
Running the "adminusers" program brings the above command line menu up. This is fairly straight forward procedural program.  It writes/reads credential records to the adminusers.txt file in the data/ directory. There is one user (GuestAdmin) currently in the file.  A new record can be added by entering "1" at the command line.  Follow the instructions.  Hitting 2 will bring up the delete sub-menu.  An admin user record list can be viewed by entering "3" at the command line.
<br><br>
To exit the program, enter "Q" at the command line of the main menu, otherwise follow the general instructions to back out to the main menu.
<br><br>
<b>Admin User Program Features and Rubric Points</b>
<ul>
  <li>Passwords are encrypted once a new admin user record is created.</li>
  <li>The same adminuser.txt file is used within the adminchatbot application to authenticate an Admin user.</li>
  <li>Can't Ctrl-C out of the program.  Must quit the from the main menu. </li> 
  <li>There's a lock file mechanism in place so that only one adminusers instance at a time can modify the adminusers.txt file.</li>
</ul>
<h2>AdminChatBot (adminchatbot) Details</h2>
<img src="images/AdminChatBot.jpg" title="admin chatbot"/>
The main chatbot application uses wxWidgets as it's GUI framework.  The main entry point of the application is ChatBotApp::OnInit() in chatgui.cpp.  While at first glance this chatbot might look similar to CppND-Memory-Management-Chatbot, it is however very different.  The intent of this chatbot is for Admin users who desire to make changes to the keywords/answers can do so easily using the application.  Changes can also be made to the answers.json using another editor.
<br><br>
The general user part of the Admin Chatbot application works like any other chatbot.  The user types in a question or keyword, and an automated question is returned.  To exit the application, click on the red X on the top bar of the window frame.
<br><br>
<b>AdminChatBot Features and Rubric Points</b>
<ul>
  <li>Admin authentication that includes decryption of the admin password.</li>
  <li>Memory management throughout including the use of smart unique pointers (AnswerNode).</li>
  <li>Multi-Threaded functionality (ChatLogic::RunDataSynchronization).  In a nutshell, when AdminChatBot starts, another thread is spun to synchronize any file changes with the primary AnswerNode</li> 
  <li>When the application is exiting, the ChatLogic Destructor will make sure that the second thread is stopped.</li>
  <li>Object Oriented Design Classes are used throughout AdminChatBot.</li>
</ul>
<br>



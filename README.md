# seabattle
console game sea battle . 

This is a demo version of the game "sea battle". To start the game you need:  
1. Build program.
2. Open 3 terminals . 
3. In one run the server **./mainserv {port}** . 
4. In the other two, start the client **./client {port}**
5. Input IP address of the server in terminals where client are running **127.0.0.1**
6. Follow the instructions in client terminals.

To build and run program:

# Build
**In folder 'client':**

cmake .

make

./client {OPTIONS}

**In folder 'server'**

cmake .

make

./mainserv {OPTIONS}

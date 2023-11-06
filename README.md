# Web Server

## :loudspeaker:	Introduction

This is a simple C++ web server that serves static files over HTTP. It can handle GET requests for HTML and CSS files and responds with the appropriate content type. The server is designed for educational purposes and can be used as a starting point to understand basic web server concepts.

## :mechanical_arm:	 Usage

To use this web server, follow these steps:

1. Clone the repository:
   
2. Compile the code:
g++ server.cpp -o server

3. Run the server:
./server

4. The server will start listening on port 8081 by default. You can access it in a web browser by opening `http://localhost:8081` or by making HTTP GET requests to the server.

###  :anger:	 To close the server:
Click Ctrl+C to close.

### :calling:	 To access the website:
Open a web browser or use a tool like curl to access files:

To request the default index.html file:
http://localhost:8081/

To request other HTML or CSS files:
http://localhost:8081/yourfile.html or 
http://localhost:8081/yourstyle.css

## :rotating_light:	 Safety Concernes
Security: This code lacks security measures and is not suitable for a production environment. 

Performance: This is a basic server and may not perform well under heavy traffic. Consider advanced web server technologies for scalability.

File Access: Ensure proper file access controls to prevent unauthorized access to sensitive files.





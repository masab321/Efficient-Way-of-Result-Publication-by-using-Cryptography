Efficient Way of Exam Result Publications System.

At the present time, almost every exam results are published through the internet. Students can collect their results by providing registration numbers and other credentials. One of the main problems of this kind of result publication system is, students have to wait for a long time to get their results during the peak hours of publication day. The reason behind this problem is huge traffic on the publication server for a period of time. As a result, students need to wait in suspense for a long period of time. It is almost impossible for someone with a slow internet connection to get their result quickly. 
In this project my idea is to encrypt the result and send it to the students throug their email. Because results are officially prepared few days before the publication date. On the publication date all I need to do is publish the decryption password. I believe the process is enough secure for password whith length >= 14.

There are two parts of my project. Server side and client side.
Server Side: In server side I collect the result in csv format. This csv dataset is encrypted by using a symmetric key algorithm. Encrypted data is sent to the students using Gmail.
Client Side: I have made a very simple android application which can decrypt the data and show detail result.
                                                 
DESIGN SPECIFICATION:
 
Introduction: 
Technology has made human life easier. There is always a way to improve current technologies for better service. In this project I have tried to improve online academic result publication systems. The design of this project is described below:

Cryptography: 
This project is mainly based on cryptography. So I had to find a suitable cryptographic algorithm. In this project I have needed a library that has a framework for both C++ and Java. C++ is a very fast language. As the performance is the main thing I was trying to achieve in this project. So, I have used C++. But it is also possible to use other programming languages on the server side. In this project I was using the same key to encrypt and decrypt. Therefore I need a symmetric key Cryptographic algorithm. Therefore I have chosen an AES algorithm to encrypt and the key used to encrypt and decrypt should be small and easy to publish. So, I have chosen ‘Themis’ cryptographic library. 

Themis: 
Themis is a cross-platform high-level cryptographic library for mobile, web, and server platforms. Themis provides 4 important cryptographic services. Among them I have used the ‘Secure Cell’ container for this project. Secure Cell is built around AES-256-GCM,  AES-256-CTR cryptographic algorithms.   

Secure Cell:        
Secure Cell is a high-level cryptographic container which provides a simple way of securing data. Secure Cell also has different modes. Here I have used the Secure cell in seal mode. 
Secure Cell in seal mode uses AES-256-GCM cryptographic algorithm. It’s a very easy to use 
framework. User only needs to provide a Password and Data to encrypt. Seal mode automatically uses a strong Key Derivation Function (KDF) to generate the required 256 bit key. Secure Cell in Seal mode will encrypt the data and append an “authentication tag” to it with auxiliary security information

Key Derivation Function:   
A key required to encrypt should be random, unpredictable and fairly long. But these kinds of keys are not very easy to remember for human beings. But humans can remember passphrases or passwords. Passwords can not be used in encryption in algorithms. Because they may be shorter than required and passwords are also created for limited characters. A key derivation function (KDF) is used to mitigate for deficiencies of passphrases when they are used as keys. KDF augments the input with additional randomness and multiplies the computation complexity by repeated application of hash functions. Cracking a passphrase without KDF requires much less resources than cracking a key. KDF increases resource usage significantly so that cracking a passphrase is not practical. Secure Cell uses a strong password-based KDF (PBKDF2) to convert passphrases into intermediate keys, which are then passed to NIST SP 800-108-based KDF to convert them into the format required by AES.
Finally I had to encode the data to send through email servers. Encrypted data is encoded using base 64 encoding algorithms.

Mail Server:    
A mail server is a server that handles and delivers e-mail over a network, usually over the Internet. A mail server can receive emails from client computers and deliver them to other mail servers. A mail server can also deliver emails to client computers. An advanced mobile phone or Smartphone, with email capabilities, can be regarded as a client computer in these circumstances. A mail server is needed which can send encrypted results to the students through their university email. I have used gmail mailing service. I also have used the POCO C++ library to develop mail program.
Here, I need an email lookup table. In the cryptographic part of the project all data are saved with email as primary key. So, I can easily create an email lookup table from that dataset.

Android Client Application:   
In this project I needed a very simple android application. I believe it is better to make simple and easy to use android applications. There are only two activities in my application. One takes the encrypted data and password from the user. And another one is to display detailed results.


Conclusion:  

By using this system universities and other institutions can publish student results within a few minutes. Every student will receive their result as quickly as possible. Another advantage of this system is it will not cost any extra money to set up. It is even possible to set up in existing systems.  

Future work and Further Development:

In every system, it is always possible to improve. So, it is also possible to improve this project. First of all, check this system to process heavy databases and improve the lackings. It is also possible to set up this system to publish board exam results. Though I have tried to keep the client side as simple as possible, the client side of my project can be improved. I have only developed an android application. But client applications for all major platforms e.g. iOS, Windows, Linux etc. are necessary. The server application can also be developed for other operating systems. Finally with some more optimized cryptographic algorithms it is also possible to reduce the encryption time.  











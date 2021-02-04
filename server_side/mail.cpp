// g++  -o prog mail.cpp -lPocoFoundation -lPocoNet  -lPocoNetSSL -lPocoUtil  && ./prog

#include <iostream>
#include <string>

#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/SSLManager.h>
using namespace std;

class mail{
private:
    Poco::Net::MailMessage mailMessage;
    Poco::Net::SecureSMTPClientSession session = Poco::Net::SecureSMTPClientSession("smtp.gmail.com", 587);
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> ptrHandler = new Poco::Net::AcceptCertificateHandler(false);
    Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    vector<Poco::Net::MailRecipient> rcv;

    string email, pass, rcv_email;

public:
    mail(){

    }
    void set_recipient(string s){
        rcv_email = s;
        rcv.clear();
        rcv.push_back(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, s, "user1"));
        mailMessage.setRecipients(rcv);
    }
    void set_content(string s){ mailMessage.setContent(s); }
    void set_subject(string s){ mailMessage.setSubject(s); }
    void set_sender_email(string s){ email = s; }
    void set_sender_password(string s){ pass = s; }

    void start_session()
    {
        session.open();
        Poco::Net::initializeSSL();
        try
        {
            session.login();
            if (session.startTLS(ptrContext))
            {
                session.login(Poco::Net::SecureSMTPClientSession::AUTH_LOGIN, email, pass);
            }
            cout << "Session created and logged in successfully!" << endl;
        }
        catch (Poco::Net::SMTPException &e)
        {
            std::cout << e.message() << std::endl;
            session.close();
            Poco::Net::uninitializeSSL();
        }
    }
    void stop_session(){
        session.close();
        Poco::Net::uninitializeSSL();
    }
    void send(){
        session.sendMessage(mailMessage);
        cout << "Message sent from " << email << " from " << rcv_email << endl;
    }
};


// int main(){
//     mail m;
//     string email = "masab15-9811@diu.edu.bd", pass = "semiheaven321", rcv_email = "masabhasnain1@gmail.com";
//     m.set_subject("result");
//     m.set_sender_email(email);
//     m.set_recipient(rcv_email);
//     m.set_content("AAEBQQwAAAAQAAAAEQAAABYAAADZjFbOopW8TwBCTMpEhvoNcoZGv+TJUI3F37ygQA0DABAAfCIp3xc23EJhrljC8flGJmdGk0/XC/0gODuh8GQ0MplB");
//     m.set_sender_password(pass);

//     m.start_session();
//     m.send();
//     m.stop_session();

// }
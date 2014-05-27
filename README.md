ATM
===

ATM server-client application.

### Server

Server includes SQLite database management, handles requests and responses to clients.

### Client

Client simulates Automated teller machine with GUI implemented using Qt.

Using card number and PIN authentication client performs the following actions:

  - Balance Enquiry
  - Withdrawal
  - Transfer between accounts
  - Periodic transfer between accounts


### Client-server connection

It's a RESTful API via HTTPS. Every client is required to have a key / certificate signed with Bank CA certificate.
There are sample SSL certificates for testing purposes in ssl directory.

[More](https://github.com/bogdan-kulynych/bank/blob/master/README.md)

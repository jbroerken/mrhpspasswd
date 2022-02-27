*************
Password File
*************
mrhpspasswd uses a password file to store the current password hash. This file 
is on every password check or set event. The password hash is stored as given 
by the password hash function.

File Structure
--------------
The password hash is stored as given by the password hash function. The file 
identifies itself as a text file, but the content contains binary data.

There are no comments or formats used in the file. The hash is simply written 
from the beginning of the file.
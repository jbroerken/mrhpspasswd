CBSet
=====
The CBSet callback is used to set a new password for password 
verification.

Action
------
The callback will create a hash from the given password string which 
is then stored as the currently used password hash. A result event is 
then created and sent to the user package, with the result of the event 
depending on a successfull password hash update.

The password access is also checked when running this callback. The 
password update will always fail without even trying to update the 
password hash if password access is currently locked.

Recieved Events
---------------
* MRH_EVENT_PASSWORD_SET_U

Returned Events
---------------
* MRH_EVENT_PASSWORD_SET_S

Files
-----
The callback is implemented in the following files:

.. code-block:: c

    Callback/Password/CBSet.cpp
    Callback/Password/CBSet.h
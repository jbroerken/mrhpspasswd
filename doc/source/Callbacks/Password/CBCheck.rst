CBCheck
=======
The CBCheck callback is used to compare a given password with 
the password stored by the service.

Action
------
The callback will create a hash from the given password string which 
is then checked with the currently stored password hash. A result 
event is then created and sent to the user package, with the result 
of the event depending on a successfull comparison between hashes.

The password access is also checked when running this callback. A failed 
password check will be remembered by the service. The password check will 
always fail without even trying to compare the password hashes if password 
access is currently locked.

.. note::

    The returned event will be seen by mrhcore, which only sets password 
    authentication if the event is sent as a service event from 
    the service side.

Recieved Events
---------------
* MRH_EVENT_PASSWORD_CHECK_U

Returned Events
---------------
* MRH_EVENT_PASSWORD_CHECK_S

Files
-----
The callback is implemented in the following files:

.. code-block:: c

    Callback/Password/CBCheck.cpp
    Callback/Password/CBCheck.h
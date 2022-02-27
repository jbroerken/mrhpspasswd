************
Service Info
************
mrhpspasswd is the default password service used by the MRH platform. 
This service only implements default password events.

Service Identifiers
-------------------
The service uses the following identifiers:

.. list-table::
    :header-rows: 1

    * - Identifier
      - Value
    * - Supplier ID
      - MRH (0x4d524800)
    * - Binary ID
      - PASS (0x50415353)
    * - Version
      - 1


Features
--------
The following features are provided by the service:
  
.. list-table::
    :header-rows: 1

    * - Feature
      - Description
    * - Check password
      - The service can check if a password is valid.
    * - Update password
      - The service can set a new password.

  
Events
------
The following events are handled by the service:

* MRH_EVENT_PS_RESET_REQUEST_U
* MRH_EVENT_PASSWORD_AVAIL_U
* MRH_EVENT_PASSWORD_CUSTOM_COMMAND_U
* MRH_EVENT_PASSWORD_CHECK_U
* MRH_EVENT_PASSWORD_SET_U

.. note::
    
    Custom command events will return the event MRH_EVENT_NOT_IMPLEMENTED_S!
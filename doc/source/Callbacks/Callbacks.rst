*********
Callbacks
*********
The service uses callbacks to react to recieved events. All callbacks are 
given to libmrhpsb and executed on a callback thread. Each callback handles 
one specific event. 

Service Callbacks
-----------------
.. toctree::
  :maxdepth: 1

  Service Availability <Service/CBAvail>
  Custom Command <Service/CBCustomCommand>
  
  
Password Callbacks
------------------
.. toctree::
  :maxdepth: 1

  Check Password <Password/CBCheck>
  Set Password <Password/CBSet>
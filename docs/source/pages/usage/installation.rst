Installation
============

Prerequisites for Running
-------------------------

**Required:**

- libstdc++6:i386

**Optional:**

- libcurl
- libssl
- libsqlite3

**Installation on Debian/Ubuntu**

.. code-block:: bash

    sudo dpkg --add-architecture i386
    sudo apt update
    sudo apt install libstdc++6:i386 libcurl4t64:i386 libssl3t64:i386 libsqlite3-0:i386



Installing
------------

- Download ``iw1x.so`` from the `releases page <https://gitlab.com/kazam0180/iw1x-server/releases>`_
- Place ``iw1x.so`` in the CoD root directory.
- Inject ``iw1x.so`` into ``cod_lnxded`` when starting the server. Like:

.. code-block:: bash

    LD_PRELOAD="./iw1x.so" cod_lnxded +exec myserver.cfg

Refer to step 5 of the `cod.pm <https://cod.pm>`_ server setup `guide <https://cod.pm/guide/a7a40b/call-of-duty-1-server-on-linux-installing-and-configuring>`_ for details.

Build From Source
-----------------

See :doc:`../development/building`

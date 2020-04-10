# MySkyHDWifiRemote
ESP8266 Web Server to control MySkyHD Box via IR emulation.

You need to hard code your SSID and Wifi password first.

Once started, connecting to the IP of the ESP8266 a web page shows the remote control keys. It has been set up for a mobile phone in portrait mode.

If you add the page to the home screen (android) the page works as portrait only (no rotation) and full screen.
I suggest to add a IP reservation in your DHCP to let it keep the same address forever.

I resulted in this project after having put together various examples found on github (such as https://github.com/abhrodeep/Arduino_projs/blob/master/IRremoteESP.ino).

For the hardware I referred to this page:
https://www.instructables.com/id/Universal-Remote-Using-ESP8266Wifi-Controlled/

This code is experimental and you may use as it is and change it to suit your needs as I did.
Hope it can be helpful to someone.

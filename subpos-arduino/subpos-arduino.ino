extern "C" {
  #include "user_interface.h"
};
uint32_t beacon_rate = 100; //Default 100TU

#define packetSize    82

// Beacon Packet buffer
//http://mrncciew.com/2014/10/08/802-11-mgmt-beacon-frame/
                                      /* Beacon Frame Type */
uint8_t packet_buffer[packetSize] = { 0x80, 0x00, 0x00, 0x00, 
                /* DST MAC (Broadcast)*/
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                /* SRC MAC */
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,  
                /* BSSID */
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,  
                /* Counter */
                /*22*/  0xc0, 0x6c,
                /* Timestamp */
                /*24*/  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                /* Beacon Interval */
                /*32*/  0x64, 0x00, 
                /* Capability Info; set WEP so open networks don't accidentally get 
                stored in client Wi-Fi list when clicked (open networks allow one 
                click adding, WEP asks for password first). */ 
                /*34*/  0x11, 0x04, 
                /* SSID Element ID and Length of SSID */
                /*36*/  0x00, 0x1f, 
                /* SSID Octets */
                /*38*/  0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                /*44*/  0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                /*50*/  0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                /*56*/  0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                /*62*/  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                /*68*/  0x01,
                /* Config */
                /*69*/  0x01, 0x08, 0x82, 0x84,
                /*73*/  0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                /* Channel Num */
                /*81*/  0x01};     

/* Sends beacon packets. */
void beacon() {
    int i = wifi_send_pkt_freedom(packet_buffer, packetSize, 0);
    uint32_t timestamp = (uint32_t)packet_buffer[27] << 24 | (uint32_t)packet_buffer[26] << 16 |(uint32_t)packet_buffer[25] << 8 | packet_buffer[24];
    timestamp = timestamp + (beacon_rate * 1000);
    packet_buffer[24] = (unsigned char)(timestamp & 0xff);
    packet_buffer[25] = (unsigned char)(timestamp >> 8 & 0xff);
    packet_buffer[26] = (unsigned char)(timestamp >> 16 & 0xff);
    packet_buffer[27] = (unsigned char)(timestamp >> 24 & 0xff);
    /*if (i < 0)
    {
        at_port_print("\r\nError sending beacon frame.\r\n");
        at_response_error();
        
    } else {
        at_port_print(".");

    }*/
}

void setup() {
}

void loop() {
  beacon();
  delay(1000);
}

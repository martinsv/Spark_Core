int counter = 0;

void setup() {
    Spark.variable("counter", &counter, INT);
    
    unsigned char wver[2];
    unsigned char wmac[6];

    pinMode(D7, OUTPUT); // set D7 to output so we can flash it as a sign we are still running
    digitalWrite(D7, LOW); // make sure its off

    Serial.begin(9600); // init com port to 9600 baud

    // This section is here so you have time to setup your com port communications
    // take control of the rgb led    
    RGB.control(true);
    // flashy loop till you hit return in putty
    // I seem to have trouble flashing while in this loop.  hit enter then flash if it doesn't work
    while (!Serial.available()) {
        RGB.color(0, 255, 0);
        delay(500);
        RGB.color(0, 0, 255);
        delay(500);
        Serial.println("Press Enter to continue");
    };
    
    RGB.color(0, 0, 0); //Turn it off
    RGB.control(false); //restore control to spark core of the rgb status led
    
    Serial.println("\n");
    
    Serial.print("    Device Id: ");
    Serial.println(Spark.deviceID());

    Serial.print("    CC3000 FW: ");
    nvmem_read_sp_version(wver); 
    Serial.print(wver[0]); Serial.print("."); Serial.println(wver[1]);
    
    Serial.print("         SSID: ");
    Serial.println(Network.SSID());
    
    Serial.print("         RSSI: ");
    Serial.println(Network.RSSI());
    
    Serial.print("  MAC Address: ");
    Network.macAddress(wmac);  // makes me sad no leading 0
    Serial.print(wmac[5], HEX); Serial.print(":");
    Serial.print(wmac[4], HEX); Serial.print(":");
    Serial.print(wmac[3], HEX); Serial.print(":");
    Serial.print(wmac[2], HEX); Serial.print(":");
    Serial.print(wmac[1], HEX); Serial.print(":");
    Serial.println(wmac[0], HEX);

    Serial.print("     Local IP: ");
    Serial.println(Network.localIP());

    Serial.print("  Subnet Mask: ");
    Serial.println(Network.subnetMask());

    Serial.print("   Gateway IP: ");
    Serial.println(Network.gatewayIP());
 
    Serial.print(" Gateway Ping: ");
    Serial.println((Network.ping(Network.gatewayIP()) > 0 ? "Good" : "Bad"));
 
    Serial.print("  Google Ping: ");
    Serial.println((Network.ping(IPAddress(74,125,228,8)) > 0 ? "Good" : "Bad"));

    Serial.println("\nUser loop starting.\n");
    
}


void loop() {
    static unsigned long lastMillis = millis();
    
    
    if (millisElapsed(lastMillis) >= 1000) {
        lastMillis = millis();
        
        Serial.print("\r");
        Serial.print((++counter), DEC);
    }
}


unsigned long millisElapsed(unsigned long startMillis) {
    unsigned long curMillis = millis();
    
    return curMillis >= startMillis ? curMillis - startMillis : (4294967295ul - startMillis) + curMillis;
}

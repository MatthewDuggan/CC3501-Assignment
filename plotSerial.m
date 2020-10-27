close all;
clear all;
clc;
% close open serial ports 
delete(instrfindall);

% create serial object
s = serial("COM3", "BaudRate", 115200);

% open serial port
fopen(s);

i = 1;

figure
ylim([-100 100]);
while(1)
   line = fscanf(s);
   data = strsplit(strip(line),"/");
   pitch(i) = str2double(data(1));
   roll(i) = str2double(data(2));
   %disp(data);
   %disp("Pitch: " + pitch(i) + "; Roll: " + roll(i));
   %accX(i) = str2double(data(2));
   %plot(pitch);
 
   
   plot(pitch);
   hold on
   plot(roll)
   hold off
   ylim([-100 100]);
   % adding a legend makes it lag badly
   
   
   i = i + 1;
   
   pause(0.03)
    
 end
